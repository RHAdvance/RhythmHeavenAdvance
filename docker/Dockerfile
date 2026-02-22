FROM devkitpro/devkitarm:latest

RUN apt update -y
RUN apt install -y build-essential binutils-arm-none-eabi git libpng-dev ffmpeg

RUN useradd -ms /bin/bash rha
USER rha

RUN git clone https://github.com/RHAdvance/RhythmHeavenAdvance.git /home/rha/rt
RUN git clone https://github.com/pret/agbcc /home/rha/agbcc

WORKDIR /home/rha/agbcc
RUN ./build.sh
RUN ./install.sh /home/rha/rt

WORKDIR /home/rha/rt
