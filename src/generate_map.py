import random
import commands
import string
import os

tiles = {'f':3, 'g':1, 'G':2, 'h':4, 'm':7, 'r':5}
options = 'fgGhmr'

for i in 10, 20: #, 50, 100, 200, 500, 1000:
    cmd = str(str(len(tiles)) + '\n')
    for x in tiles:
        cmd += str( str(x) + ' ' + str(tiles[x]) + '\n')
    cmd += str(str(i) + ' ' + str(i) + '\n')
    for j in range(0,i):
        for k in range(0,i):
            cmd += str(str(random.choice(options))+ ' ')
        cmd+= '\n'
    cmd += str(str(random.randrange(i))+ ' ' + str(random.randrange(i)) +'\n')
    cmd += str(str(random.randrange(i)) +' ' + str(random.randrange(i)) + '\n')
    test = open('src/temp.txt','w')
    test.write(cmd)
    os.system("./src/dijkstras <src/temp.txt")
    test.close()
#os.remove('src/temp.txt')
