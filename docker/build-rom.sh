#!/bin/bash

docker rm -f rhac

set -e
docker build -t rhai .
docker run -u "$(id -u):$(id -g)" -v "$(realpath baserom.gba):/home/rha/rt/baserom.gba:ro,Z" --name rhac rhai make -j
docker cp rhac:/home/rha/rt/build/rhythmheavenadvance.gba .
docker rm rhac
