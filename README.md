
<img width="1535" height="1370" alt="image" src="https://github.com/user-attachments/assets/ffbfed42-a33c-4206-babf-9cfb250e39e8" />

# Rhythm Paradise Advance (French) :
Un patch de localisation française pour le jeu Rhythm Tengoku sorti sur Game Boy Advance. « Rhythm Paradise Advance (French) » cherche à adapter aussi fidèlement que possible les textes, les illustrations et les voix, tout en gardant une cohérence avec la traduction française des autres jeux de la série Rhythm Paradise.
Ce projet est basé sur le travail de l'équipe derrière le patch anglais « Rhythm Heaven Advance ».

## Installation

To install the project, you need access to a Linux terminal. If you are on Windows 10 or 11, you can access a Linux terminal easily by installing **WSL (Windows Subsystem for Linux)**. If you are already on Linux, you can skip to the **Installing Dependencies** section. Otherwise, follow this guide to install WSL:

#### Installing WSL

To install WSL, first open up either a Command Prompt or Windows PowerShell window as an administrator. Run the command `wsl --install` to automatically install WSL defaulting to the Ubuntu distribution. Once the process finishes, restart your computer to finish the installation.

*Note: you will need to have virtualization enabled in your BIOS settings to use WSL, so if you encounter issues, check how to boot into BIOS and enable virtualization for your computer. For any other issues with installation, you can refer to the [official installation guide](https://docs.microsoft.com/en-us/windows/wsl/install).*
<br>
Once WSL is installed, upon opening it you will be prompted for a username and password. Note that when typing in the password, the characters will not show up, not even as asterisks, so type carefully as you will need to remember your password.

Once you've created a user, you should run two more commands to finish setting up your terminal. First, run `sudo apt update`, and then after this command has finished, run `sudo apt upgrade`. These commands will require you to enter your password. When prompted with `Do you want to continue? [Y/n]`, simply enter `y`. After doing this, WSL should be fully set up and ready to use.
<br>
It is also recommended to mount WSL to a drive letter to access your WSL filesystem from Windows more easily. To do this, follow [this guide](https://github.com/HackerN64/HackerSM64/wiki/Mounting-WSL-to-Drive).

If you are not familiar with the Linux terminal, a helpful command to know is `cd` which will change the current working directory. `cd ~/` will take you to your home directory, where it is recommended to store the repository. Additionally, copy and pasting in the WSL terminal is done through right-clicking instead of Ctrl+C / Ctrl+V, so to paste commands from this guide into your terminal, simply copy them with Ctrl+C, and then right click in your terminal to paste.


#### Installing Dependencies

To install the required dependencies for the project, first run this command:

`sudo apt install build-essential binutils-arm-none-eabi git libpng-dev ffmpeg`

After this, you should also run this command:

`sudo ln -s /proc/self/mounts /etc/mtab`

This command can help with issues with WSL when installing devkitPro. It is not always necessary to run, and may throw an error. If it does error, don't worry and just move on to the next step.

After this, you will need to install devkitPro. This process is very involved, so just run all these listed commands in this order, entering your password when prompted:

`wget https://apt.devkitpro.org/install-devkitpro-pacman`
`chmod +x ./install-devkitpro-pacman`
`sudo ./install-devkitpro-pacman`
`export DEVKITPRO=/opt/devkitpro`
`export DEVKITARM=/opt/devkitpro/devkitARM`
`export DEVKITPPC=/opt/devkitpro/devkitPPC`
`sudo dkp-pacman -Sy`
`sudo dkp-pacman -S gba-dev`

After running the final command, press enter and then type `y` to finish installing.


#### Cloning the Repository

Now you are ready to clone the repository. First, navigate to your home directory with `cd ~/` and then run this command:

`git clone https://github.com/RHAdvance/RhythmHeavenAdvance.git rt`

This will clone the repository into a folder named `rt` in your home directory. You can change `rt` to some other name if you wish to name the repository folder something else.

Before building the ROM, you will also need to install agbcc, the compiler used for Rhythm Tengoku. Make sure you are still in your home directory, and run

`git clone https://github.com/pret/agbcc`

After this, navigate to the agbcc directory with `cd ~/agbcc` and build the compiler by running `./build.sh`. Finally, install the compiler into the Rhythm Heaven Advance repository by running `./install.sh ~/rt`.

Lastly, you will need to acquire an unmodified rev0 Rhythm Tengoku ROM in order to build the project. This ROM is not provided, and you must source it yourself. Once you obtain this ROM, rename it to `baserom.gba` and place it in the `rt` directory.


#### Building the ROM

You are finally ready to build the repository! Navigate to the repository folder with `cd ~/rt`, and build the ROM by running `make -j`. (The `-j` parameter makes the build process able to run on multiple cores of your CPU, heavily speeding up the process.) Once the ROM has finished building, it will output a file at `build/rhythmheavenadvance.gba`! This is your compiled ROM.

If you have any other questions or concerns, join the [RHModding discord server](https://discord.com/invite/ps4rq53)!

## Credits (To Be Added)

#### this project wouldn't be possible without all the incredible people that came together to help out!

Asset Assembly:
+ SkyeStage
+ Cash Banooka
+ geometricentric
+ somethingAccurate
+ TinyCastleGuy
+ The Eggo55
+ Vincells
+ WindowsTiger
+ Kievit
+ NotWario
+ amdree
+ patataofcourse
+ Nate Candles
+ Itaific

Graphic Design:
+ Tailx
+ Vincells
+ Borists

Main Programming:
+ Itaific
+ ShaffySwitcher

Coding Contributions:
+ Deni_iguess
+ patataofcourse
+ Arthurtilly
+ Estexnt
+ Nibblez
+ Conhlee
+ MissKnowledge

Translation and Localization:
+ Mizuka Lover
+ somethingAccurate
+ ShaffySwitcher
+ castIe
+ patataofcourse

Localization Support:
+ Cash Banooka
+ SkyStage
+ RedRobocon
+ ThisIsMyUsername

SFX:
+ Rhythm Heaven Megamix
+ Cherryberryfaygo
+ Nabix and all of his family
+ Itaific
+ Sesu

Audio Engineering:
+ FireChat
+ castIe
+ Kievit

Bug Testing:
Everyone on the Rhythm Heaven Advance discord!
with special mention to nwqol 

Thank you all for your support!

Want to be here? Join our [Server!](https://discord.gg/8PET8w8PU8)
