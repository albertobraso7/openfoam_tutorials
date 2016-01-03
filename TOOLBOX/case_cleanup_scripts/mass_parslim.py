#!/usr/bin/python

import os
import sys
import subprocess
import time

folders = [x for x in os.listdir("./") if os.path.isdir(x) \
  and os.path.isdir(x+"/case")]

print folders

for x in [folders[0]]:
  print x
  # subprocess.call(['/bin/bash', '-i', '-c', "parslim "+x])
  os.system("/bin/bash -i -c parslim "+x)

# for x in folders[0]:
#   call(['/bin/bash', '-i', '-c', "meshclean "+x])
