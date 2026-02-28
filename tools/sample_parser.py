#!/usr/bin/env python3
import sys, json, os, wave

pitches = ("C","C#","D","D#","E","F","F#","G","G#","A","A#","B")

def get_json_data(inputFile):
    with open(inputFile, 'r') as f:
        return json.load(f)


def write_sample(outputFile, sampleEntry):
    sampleName = sampleEntry["sample"].split(".")[0]

    outputFile.write("%s_pcm:\n" % sampleName)
    outputFile.write(".incbin \"build/audio/samples/%s.pcm\"\n" % sampleName)
    outputFile.write(".balign 4, 0\n")


def write_sample_data_struct(outputFile, sampleEntry, jsonDir):
    wavPath = os.path.join(os.path.join(jsonDir,"samples"),sampleEntry["sample"])
    wavFile = wave.open(wavPath)
    sampleName = sampleEntry["sample"].split(".")[0]
    
    pitch = sampleEntry["pitch"]
    
    length = (2 if "#" in pitch else 1)
    pitchOctave = int(pitch[length:])
    pitchNum = pitches.index(pitch[:length]) + pitchOctave*12
    
    if "loop" in sampleEntry.keys():
        loopStart = sampleEntry["loop"][0]
        loopEnd = sampleEntry["loop"][1]
    else:
        loopStart = 0
        loopEnd = 0

    outputFile.write(".section .data\n")
    outputFile.write(".global %s_data\n" % sampleName)
    outputFile.write("%s_data:\n" % sampleName)
    outputFile.write(".word %d\n" % (wavFile.getnframes()-1))
    outputFile.write(".word %d\n" % (wavFile.getframerate()))
    outputFile.write(".word %d\n" % pitchNum)
    outputFile.write(".word %d\n" % loopStart)
    outputFile.write(".word %d\n" % loopEnd)
    outputFile.write(".word %s_pcm\n\n" % sampleName)
    
def write_sample_file(sampleList, jsonData, input, output):
    jsonDir = os.path.dirname(input)
    outputFile = open(output, 'w')
    outputFile.write(".section .rodata\n\n")
    for sampleEntry in sampleList:
        write_sample(outputFile, sampleEntry)
    
    outputFile.write("\n")
    for sampleEntry in sampleList:
        write_sample_data_struct(outputFile, sampleEntry, jsonDir)

    outputFile.close()


if __name__ == "__main__":
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
    jsonData = get_json_data(inputFile)
    sampleList = jsonData["samples"]
    write_sample_file(sampleList, jsonData, inputFile, outputFile),
