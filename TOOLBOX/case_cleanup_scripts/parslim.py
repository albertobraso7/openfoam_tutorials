#!/usr/bin/python

import os
import sys

def leave_last(proc_folder):
  os.chdir(proc_folder)
  
  files = os.listdir("./")

  # print files

  num_files = [ \
    float(x) for x in files if ('.' in x or x.isdigit()) and (x!="0") ]
  num_files = [ int(x) if x.is_integer() else x for x in num_files ]

  # print num_files

  num_files.sort()

  max_partime = 0
  if len(num_files) >= 1:
    max_partime = num_files[-1]
  if len(num_files) > 1:
    num_files.pop()
    # num_files.pop()

    # print num_files

    num_file_names = ' '.join(str(x) for x in num_files)

    # print num_file_names

    os.system("rm -r "+num_file_names)

  os.chdir("../")
  return max_partime

my_cwd = os.getcwd()

# print sys.argv[1]
os.chdir(sys.argv[1])
os.chdir("case")

cd_files = [x for x in os.listdir("./") if "processor" in x ]

max_partime = 0
for x in cd_files:
  print "Slimming "+x
  max_partime = leave_last(x)

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

if max_seqtime >= max_partime:
  os.system("rm -r processor*")
elif max_seqtime != 0:
  os.system("rm -r "+str(max_seqtime))

os.chdir(my_cwd)