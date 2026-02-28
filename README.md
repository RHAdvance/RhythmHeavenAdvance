
# Rhythm Heaven Advance

![Rhythm Heaven Advance](media/rha.png?raw=true "Rhythm Heaven Advance")

An unofficial English localization patch for *Rhythm Tengoku (ÉäÉYÉÄìVçë)* on the Game Boy Advance.

## About

**Rhythm Heaven Advance** is a fan-made localization project for *Rhythm Tengoku*. This project provides a complete English translation patch for the game.

Feel free to join our [Discord server](https://discord.gg/8PET8w8PU8) if you have any questions or suggestions, or if you would like to follow the project and participate!

## Installation

### Requirements

- A legally obtained ROM of *Rhythm Tengoku* **(Rev 0)** with CRC32 checksum: `349D7025`
- An IPS patcher tool (recommended: [ROM Patcher JS](https://www.marcrobledo.com/RomPatcher.js/))

### Steps

1. Download the latest `.ips` patch file from the [Releases](https://github.com/RHAdvance/RhythmHeavenAdvance/releases) page or download the latest nightly page at [our website](https://rhadvance.github.io/)
2. Open your IPS patcher tool
3. Select your *Rhythm Tengoku* ROM
4. Apply the downloaded patch
5. Load the patched ROM in your emulator or flashcard

## Building from Source

### Prerequisites

All platforms require:
- A legally obtained ROM of *Rhythm Tengoku* **(Rev 0)** (CRC32: `349D7025`)
- Git

### Windows

Use the [Linux instructions](#linux) via Windows Subsystem for Linux (WSL). Debian or Ubuntu distributions are recommended.

To set up WSL:
```bash
wsl --install
```

Then follow the Linux build instructions below.

### Linux

#### Dependencies

Install the required packages (Ubuntu/Debian):
```bash
sudo apt update
sudo apt install build-essential binutils-arm-none-eabi git libpng-dev ffmpeg
```

#### Install devkitPro

```bash
# Download and install devkitPro pacman (using my mirror for now)
wget https://www.shaffy.fr/install-devkitpro-pacman
chmod +x ./install-devkitpro-pacman
sudo ./install-devkitpro-pacman

# Set environment variables
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM
export DEVKITPPC=/opt/devkitpro/devkitPPC

# Install GBA development tools
sudo dkp-pacman -Sy
sudo dkp-pacman -S gba-dev
```

#### Clone and Build

1. **Clone this repository:**
   ```bash
   git clone https://github.com/RHAdvance/RhythmHeavenAdvance.git
   ```

2. **Set up agbcc:**
   ```bash
   git clone https://github.com/pret/agbcc.git
   cd agbcc
   ./build.sh
   ./install.sh ../RhythmHeavenAdvance
   cd ../RhythmHeavenAdvance
   ```

3. **Place your ROM:**
   - Copy your *Rhythm Tengoku* ROM into the project root directory
   - Rename it to `baserom.gba` (or as specified in the Makefile)

4. **Build the project:**
   ```bash
   make -j$(nproc)
   ```

The patched ROM will be generated in the `build/` directory.

### macOS

macOS build instructions are coming soon! (Pull request appreciated...)

## Credits
Check out the full credits [here](CREDITS.md)!

## Contact

- **Discord:** https://discord.gg/8PET8w8PU8
- **GitHub Issues:** [Report bugs](https://github.com/RHAdvance/RhythmHeavenAdvance/issues)

## Disclaimer

This is an unofficial fan project and is not affiliated with, endorsed by, or associated with Nintendo. All trademarks and copyrights belong to their respective owners. This patch is intended for personal use only with legally obtained copies of the game.

You are NOT permitted to use the patch for commercial purposes.

All rights concerning the assets or source code are reserved by the original authors and Nintendo for Rhythm Tengoku.