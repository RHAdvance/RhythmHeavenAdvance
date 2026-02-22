# Build with docker

## Installing dependencies
You only need to isntall docker. It is available in most major distros. You can also follow [the official docker install guide](https://docs.docker.com/engine/install).
On windows / macos you can use docker desktop.

Make sure you are in the docker group to be able to build the patched game without root:
```bash
sudo usermod -aG docker youruser 
newgrp docker # optional, you could also log out and log in again
```

## Building
Make sure you are in this file's folder.  
Add your legally obtained rhythm heaven copy in this folder and rename it to `baserom.gba`  
Run `build.sh`. It might take a bit. The patched rom will be put in the current folder
