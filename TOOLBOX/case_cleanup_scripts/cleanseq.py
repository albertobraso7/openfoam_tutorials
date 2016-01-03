#!/usr/bin/python

import os
import sys

my_cwd = os.getcwd()

os.chdir(sys.argv[1])

msh_files = [x for x in os.listdir("./") if ".msh" in x ]
print "Deleting .msh files"
os.system("rm "+' '.join(msh_files))

os.system("rm log.log log")

# Take care of case where there are reconstructed times.
num_files = [ \
  float(x) for x in os.listdir("./") \
  if (os.path.isdir(x)) and ('.' in x or x.isdigit()) and (x!="0") ]
num_files = [ int(x) if x.is_integer() else x for x in num_files ] 
max_seqtime = 0
if len(num_files) >= 1:
  max_seqtime = num_files[-1]
if len(num_files) > 1:
  num_files.pop()
  num_file_names = ' '.join(str(x) for x in num_files)
  os.system("rm -r "+num_file_names)

os.chdir(my_cwd)