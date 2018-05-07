#!/usr/bin/python3

outdata = []
with open('./Red_Car.obj', 'r') as file:
    for line in file:
        verts = [ str.split('/')[0] for str in line.split(' ') ]
        for i in range(len(verts)):
            outdata.append(verts[i] + ' ' + verts[-1 + i])

with open('./redcar.lines', 'w') as outfile:
    outfile.write('\n'.join(outdata))
        
