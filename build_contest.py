# !/usr/bin/python3
import argparse,os
from shutil import copyfile

parser = argparse.ArgumentParser()
parser.add_argument('contest_name',type=str)
parser.add_argument('problem_count',type=int)
args = parser.parse_args()

dir_name = '0contest/'+args.contest_name + '/'

try:
    # Create target Directory
    os.mkdir(dir_name)
    print("Directory " , dir_name ,  " created ") 
except FileExistsError:
    print("Directory " , dir_name ,  " already exists")



for char_val in range(0,args.problem_count):
  file_name = 'p' + chr(char_val + 65) + '.cpp'

  try:
    copyfile('template.cpp', dir_name + file_name)
    print('File ' + file_name + ' created')
  except:
    print("Failed while copying file " + file_name)