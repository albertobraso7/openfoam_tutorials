#!/bin/bash

for folder in */ ; do
    if [ -d "${folder}system" ]; then
      echo "Cleaning $folder"
      ~/Desktop/cleanseq.py $folder
    fi
done
