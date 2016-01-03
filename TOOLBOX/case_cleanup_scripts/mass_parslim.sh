#!/bin/bash

for folder in */ ; do
    if [ -d "${folder}case" ]; then
      echo "Slimming $folder"
      ~/Desktop/parslim.py $folder
    fi
    if [ -d "${folder}mesh" ]; then
      ~/Desktop/meshclean.sh $folder
    fi
    if [ -d "${folder}meshes" ]; then
      ~/Desktop/meshesclean.sh $folder
    fi
    if [ -d "${folder}md" ]; then
      ~/Desktop/casemeshclean.sh $folder
    fi
done
