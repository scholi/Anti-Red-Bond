#!/usr/bin/python

# Author: Olivier Scholder
# License: GPL (http://gnu.org/licenses/gpl.html)
# File Version: 1.1
# Date: 06. 06. 08

from visual import *
import re, sys

f=open("output.dat","r")
lat=f.readlines()
f.close()
size=len(lat)
top_max=2
sx=int(lat[0])
sy=int(lat[1])
sz=int(lat[2])
lat=lat[3:]
print "Size: %ix%ix%i" % (sx,sy,sz)
f.close()
f=open("pointer.dat","r")
pointer=map(int,f.readlines())
f.close()

def follow(i):
	p=pointer[i]
	if p==0:
		return i
	else:
		return p


def bound(x,y,z,col,arb=false):
	if y>0:	
		a=follow(int(lat[z].split()[(y-1)*sx+x]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x,y-0.9,z), axis=(0,0.8,0), color=col, radius=0.1)
	if y<sy-1:
		a=follow(int(lat[z].split()[(y+1)*sx+x]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x,y+0.1,z), axis=(0,0.8,0), color=col, radius=0.1)

	if x>0:
		a=follow(int(lat[z].split()[y*sx+x-1]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x-0.9,y,z), axis=(0.8,0,0), color=col, radius=0.1)
	if x<sx-1:
		a=follow(int(lat[z].split()[y*sx+x+1]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x+0.1,y,z), axis=(0.8,0,0), color=col, radius=0.1)
	if z>0:
		a=follow(int(lat[z-1].split()[y*sx+x]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x,y,z-0.9), axis=(0,0,0.8), color=col, radius=0.1)
	if z<sz-1:
		a=follow(int(lat[z+1].split()[y*sx+x]))
		if a>0 and (a<=top_max or not arb): 
			cylinder(pos=(x,y,z+0.1), axis=(0,0,0.8), color=col, radius=0.1)

# Draw arrow
arrow(pos=(-1,-1,-1), axis=(0,0,size), shaftwidth=0.3)

# Draw cells
for z in range(sz):
	for y in range(sy):
		for x in range(sx):
			v=int(lat[z].split()[y*sx+x])
			if v==0:
				sphere(pos=(x,y,z), radius=0.1)
			else:
				if v<len(pointer):
					if follow(v)>1 and follow(v)<=top_max:
						sphere(pos=(x,y,z), radius=0.1, color=(1,1,0))
						bound(x,y,z,(1,1,0))
					elif follow(v)==1:
						sphere(pos=(x,y,z), radius=0.1, color=(0,1,1))
						bound(x,y,z,(0,1,1))
						
					else:
						sphere(pos=(x,y,z), radius=0.1, color=(0,1,0))
						bound(x,y,z,(0,1,0))
				else:
					sphere(pos=(x,y,z), radius=0.1, color=(0,1,0))
					bound(x,y,z,(0,1,0))
				

# Draw bridges

f=open("bridges.dat","r")
ff=f.readlines()
f.close()

for x in ff:
	r=map(int,re.findall("\((\d+),(\d+),(\d+)\)",x.split()[0])[0])
	if int(lat[r[2]].split()[r[1]*sx+r[0]])==0:
		sphere(pos=tuple(r), radius=0.1, color=(0,0,1))
	else:
		print x.split()[0]
		sphere(pos=tuple(r), radius=0.1, color=(1,0,1))

# Draw ARB
f=open("arb.dat","r")
ff=f.readlines()
f.close()

for x in ff:
	z=map(int, x.split())
	sphere(pos=tuple(z), radius=0.1, color=(1,0,0))
	bound(z[0],z[1],z[2],(1,0,0),true)
