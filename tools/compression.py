#!/usr/bin/env python3
import sys, json, os, array

def read_from_rom(start, size):
    baserom.seek(start)
    data = baserom.read(size)
    return data


def pad4(addr):
    return (addr + 3) & ~3


def output_array(f, array, prefix, linelength):
    length = len(array)
    for i in range(length):
        if (i % linelength == 0):
            f.write(prefix + " ")
        f.write("0x%x" % array[i])
        if (i % linelength == linelength-1 or i == length - 1):
            f.write("\n")
        else:
            f.write(", ")


def append_unique_nibbles(array, unique_nibbles):
    for hword in array:
        for i in range(0, 16, 4):
            byte = (hword >> i) & 0xF
            if byte not in unique_nibbles:
                unique_nibbles.append(byte)

def get_unique_nibbles(array):
    unique_nibbles = []
    append_unique_nibbles(array, unique_nibbles)
    return unique_nibbles

# Compression Mode 1: 1:2 ratio
# Takes a nibble dictionary of length 4 and a halfword
# Returns one byte, with every two bits indexing one nibble
def mode_1_encode(dictionary, hword):
    result = 0
    for i in range(0, 16, 4):
        result = result | dictionary.index((hword >> i) & 0xF) << (i >> 1)
    return result

# Compression Mode 2: 1:4 ratio
# Takes a nibble dictionary of length 2 and a halfword array of length 4
# Returns a halfword, with every bit indexing one nibble
def mode_2_encode(dictionary, hwords):
    result = 0
    for i in range(16):
        result |= dictionary.index((hwords[i >> 2] >> ((i&3) << 2)) & 0xF) << i
    return result

# Check if the 1:4 compression mode is possible for the upcoming data
def mode_2_available(hwords):
    if (len(hwords) < 4):
        return False

    for i in range(0, len(hwords) - 3):
        if (len(get_unique_nibbles(hwords[i:i+4])) <= 2):
            return True
    return False


# An array of bits that are used to determine the encoding mode
class SlidingWindow:
    index: int = 0

    def __init__(self):
        self.data = []

    def append_bit(self, bit):
        if len(self.data) == 0:
            self.data.append(0)
        if self.index >= 32:
            self.index = 0
            self.data.append(0)
        self.data[-1] = self.data[-1] | (bit << self.index)
        self.index += 1
    
    def fill_rest(self, address):
        if len(self.data) == 0:
            return
        # Fill in all unused bits with the data from the ROM
        bytes = read_from_rom(address + (len(self.data)-1)*4, 4)
        # Unpack 4 bytes into one number
        word = 0
        for i in range(4):
            word |= bytes[i] << (i*8)
        bitmask = 0xFFFFFFFF >> (32 - self.index)
        bitmask = ~bitmask & 0xFFFFFFFF
        self.data[-1] = self.data[-1] | (word & bitmask)

class CompressedData:
    segmentCount: int = 0
    window1: SlidingWindow = SlidingWindow()
    window2: SlidingWindow = SlidingWindow()

    def __init__(self, data, address):
        self.compressed = []
        self.address = address
        self.compress(data)
    
    def get_nibble_from_rom(self, index, nibble):
        if self.address is None:
            return 0xF
        byte = read_from_rom(self.address + index, 1)[0]
        if nibble == 0:
            return byte & 0xF
        else:
            return byte >> 4

    def compress(self, data):
        i = 0
        self.decompressedSize = len(data)
        while True:
            # The compression algorithm will very often scan 8 bytes ahead,
            # looking to be able to use the highest ratio compression whereever
            # possible.

            mode2NibbleList = get_unique_nibbles(data[i:i+4])
            if len(mode2NibbleList) <= 2 and i+4 <= len(data):
                # 1:4 ratio encoding
                newEncodedData = []
                count = 0

                while len(mode2NibbleList) <= 2:
                    hword = mode_2_encode(mode2NibbleList, data[i:i+4])
                    newEncodedData.append(hword)
                    count += 1
                    i += 4
                    if i+4 > len(data) or count >= 256:
                        break
                    append_unique_nibbles(data[i:i+4], mode2NibbleList)

                self.compressed.append((count - 1) << 8 | mode2NibbleList[1] << 4 | mode2NibbleList[0])
                self.compressed.extend(newEncodedData)
                self.window1.append_bit(1)
                self.window2.append_bit(0)
                self.segmentCount += 1
                continue

            # Even if the immediate next 6 bytes can be done with 1:2 compression,
            # the algorithm will copy up to 4 bytes uncompressed if 1:4 compression
            # is possible after.
            if (i+5 > len(data) or not mode_2_available(data[i+1:i+6])):
                # Scan 6 bytes ahead
                mode1NibbleList = get_unique_nibbles(data[i:i+3])
                if len(mode1NibbleList) <= 4 and i+3 <= len(data):
                    # 1:2 ratio encoding
                    newEncodedData = []
                    count = 0
                    startingByte = mode_1_encode(mode1NibbleList, data[i])
                    i += 1

                    while len(mode1NibbleList) <= 4:
                        byte1 = mode_1_encode(mode1NibbleList, data[i])
                        byte2 = mode_1_encode(mode1NibbleList, data[i+1])
                        newEncodedData.append(byte1 | byte2 << 8)
                        count += 1
                        i += 2
                        if i+2 > len(data) or count >= 256:
                            break
                        # Check if we can end 1:2 compression here and start 1:4 compression
                        if mode_2_available(data[i:i+5]):
                            break
                        append_unique_nibbles(data[i:i+2], mode1NibbleList)

                    while len(mode1NibbleList) < 4:
                        mode1NibbleList.append(self.get_nibble_from_rom(len(self.compressed)*2+(len(mode1NibbleList) >> 1), len(mode1NibbleList) & 1))
                        

                    self.compressed.append(mode1NibbleList[3] << 12 | mode1NibbleList[2] << 8 | mode1NibbleList[1] << 4 | mode1NibbleList[0])
                    self.compressed.append((count - 1) | startingByte << 8)
                    self.compressed.extend(newEncodedData)
                    self.window1.append_bit(1)
                    self.window2.append_bit(1)
                    self.segmentCount += 1
                    continue

            if i >= len(data):
                break

            # Copy mode (no compression)
            self.compressed.append(data[i])
            self.window1.append_bit(0)
            i += 1
            self.segmentCount += 1

        if self.address is not None:
            self.window1.fill_rest(pad4(self.address + len(self.compressed)*2))
            self.window2.fill_rest(pad4(self.address + len(self.compressed)*2) + len(self.window1.data)*4)

    def output_to_file(self, f, symbol):
        # f is a currently open file object
        f.write("\n.balign 2, 0\n")
        f.write("%s_data:\n" % symbol)
        output_array(f, self.compressed, ".hword", 16)

        f.write("\n.balign 4, 0\n")
        f.write("%s_window1:\n" % symbol)
        output_array(f, self.window1.data, ".word", 8)

        f.write("\n.balign 4, 0\n")
        f.write("%s_window2:\n" % symbol)
        output_array(f, self.window2.data, ".word", 8)

        f.write("\n.balign 4, 0\n")
        f.write("%s_compressed:\n" % symbol)
        f.write(".word %s_data\n" % symbol)
        f.write(".hword %d\n" % self.decompressedSize)
        f.write(".hword %d\n" % self.segmentCount)
        f.write(".word %s_window1\n" % symbol)
        f.write(".word %s_window2\n\n" % symbol)
        
        if self.address is not None:
            self.dataSize = pad4(self.address + len(self.compressed)*2) + len(self.window1.data)*4 + len(self.window2.data)*4 + 16 - self.address


class RleCompressedData:
    size: int = 0
    offset: int = 0

    def __init__(self, data):
        self.compressed = []
        self.counts = []
        self.compress(data)

    def add_count(self, count):
        while (count > 255):
            self.counts.append(0)
            count -= 255
        self.counts.append(count)

    def compress(self, data):
        i = 0
        self.offset = len(data)
        while True:
            count = 1
            self.size += 1
            curValue = data[i]
            self.compressed.append(curValue)
            if (i+1 >= self.offset):
                self.add_count(count)
                break
            while (data[i+1] != curValue or i+3 >= self.offset or  data[i+2] != curValue or data[i+3] != curValue):
                i += 1
                count += 1
                curValue = data[i]
                self.compressed.append(curValue)
                if (i+1 >= self.offset):
                    break
            self.add_count(count)
            i += 1
            if (i+1 >= self.offset):
                break

            count = 1
            self.size += 1
            while (data[i+1] == curValue):
                i += 1
                count += 1
                if (i+1 >= self.offset):
                    break
            self.add_count(count)
            i += 1
            if (i >= self.offset):
                break
            

    def output_to_file(self, f, symbol, double):
        if not double:
            f.write(".balign 2, 0\n")
            f.write("%s_data:\n" % symbol)
            output_array(f, self.compressed, ".hword", 16)
            f.write("\n")

        f.write("%s_rle_segments:\n" % symbol)
        output_array(f, self.counts, ".byte", 16)

        f.write("\n.balign 4, 0\n")
        f.write(".global %s\n" % symbol)
        f.write("%s:\n" % symbol)
        if (double):
            f.write(".word %s_compressed\n" % symbol)
        else:
            f.write(".word %s_data\n" % symbol)
        f.write(".word %s_rle_segments\n" % symbol)
        f.write(".hword %d\n" % self.size)
        f.write(".hword %d\n" % self.offset)
        f.write(".word %s\n" % ("1" if double else "0"))


def compress_file(input, output, double, revision):
    symbol = os.path.basename(input).split(".")[0]
    with open(input, 'rb') as f:
        data = array.array("H", f.read())
    
    address = None
    unusedDataLength = None
    with open("tools/compression_offsets.json", "r") as f:
        offsets = json.load(f)
        if symbol in offsets:
            address = offsets[symbol][revision]
            if len(offsets[symbol]) > 2:
                unusedDataLength = offsets[symbol][2]

    outputFile = open(output, 'w')
    outputFile.write('.section .data\n\n')

    rleData = RleCompressedData(data)
    if double:
        compressedData = CompressedData(rleData.compressed, address)
        compressedData.output_to_file(outputFile, symbol)
    rleData.output_to_file(outputFile, symbol, double)

    if unusedDataLength is not None:
        if double:
            startAddress = address + compressedData.dataSize
        else:
            startAddress = address + len(rleData.compressed)*2
        startAddress = pad4(startAddress + len(rleData.counts)) + 16
        unusedData = read_from_rom(startAddress, offsets[symbol][2])
        outputFile.write("%s_unused:\n" % symbol)
        output_array(outputFile, unusedData, ".byte", 16)
    
    outputFile.close()


if __name__ == "__main__":
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
    revision = int(sys.argv[3])
    double = not (inputFile.endswith(".tilemap") or inputFile.endswith(".rle.4bpp"))

    if (revision < 1):
        baserom = open("baserom.gba", "rb")
    else:
        baserom = open("baserom_rev1.gba", "rb")
    compress_file(inputFile, outputFile, double, revision)
