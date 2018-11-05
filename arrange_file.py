# !/usr/bin/python3

import subprocess
from subprocess import Popen, PIPE
import os
import filecmp

def is_exec(path):
  session = subprocess.Popen(['file',path], stdout=PIPE, stderr=PIPE)
  stdout, stderr = session.communicate()
  if stderr:
    raise Exception("Error "+str(stderr))

  return str(stdout).find("ELF") != -1

def del_file(path):
  subprocess.call(['rm',path])
  print('remove file {}'.format(path))

for root, dirs, files in os.walk(".", topdown=False):
   for name in files:
      path = os.path.join(root, name)
      if is_exec(path):
        del_file(path)
      else:
        for template in ['template.cpp','templatenbits.cpp','templateold.cpp']:
          if filecmp.cmp(template,path) and root != '.':
            del_file(path)
          
      
