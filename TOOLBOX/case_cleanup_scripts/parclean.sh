#!/bin/bash

echo "Cleaning: "
echo $1

reconstructPar -case $1 -latestTime

rm -r $1/processor*

rm $1/*.msh

# reconstructPar -case $1/case -latestTime

# rm -r $1/case/processor*

# rm $1/meshes/*/*.msh

echo "Current size: "
du -sh $1