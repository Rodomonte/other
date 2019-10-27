from glob import glob
from os import listdir, mkdir, remove, rename
from subprocess import call
from shutil import rmtree

for folder in listdir('data'):
  if len(listdir('data/'+folder)) == 0:
    rmtree('data/'+folder)
