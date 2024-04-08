import os

def mkdir(name):
    os.system("mkdir " + name)

def move_file(file, directory):
        os.system("mv " + file + " " + directory)