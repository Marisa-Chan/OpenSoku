#!/usr/bin/python

import sys

def readl32(fl):
	return int.from_bytes(fl.read(4), byteorder="little")
	
def readsl32(fl):
	return int.from_bytes(fl.read(4), byteorder="little", signed=True)
	
def readl8(fl):
	return int.from_bytes(fl.read(1), byteorder="little")




fl = open(sys.argv[1], "rb")
fl.seek(4)

texNum = readl32(fl)

texNames = []

for i in range(0, texNum):
	nameLn = readl32(fl)
	texNames.append( fl.read(nameLn).decode("shift-jis") )
	fl.seek(4 * 4, 1)
	
guiNum = readl32(fl)

for i in range(0, guiNum):
	guide = readl32(fl)
	tpe = readl8(fl)
	
	print("GUID : ",guide)
	
	if (tpe in (0,2,3,4,5)):
		if (tpe == 0):
			print("\tCDesignSprite")
		else:
			print("\tCDesignGage {}".format(tpe - 2))
			
		tid = readl32(fl)
		x = readsl32(fl)
		y = readsl32(fl)
		invert = readl32(fl)
		print("\t\t{}\n\t\tx {}  y {}  invert {}".format(texNames[tid], x, y, invert))
	elif (tpe == 1):
		print("\tCDesignObjectBase")
		x = readsl32(fl)
		y = readsl32(fl)
		print("\t\tx {}  y {}".format(x, y))
	elif (tpe == 6):
		print("\tCDesignNumber")
		tid = readl32(fl)
		x = readsl32(fl)
		y = readsl32(fl)
		w = readl32(fl)
		h = readl32(fl)
		frames = readl32(fl)
		dw = readsl32(fl)
		intg = readl32(fl)
		flt = readl32(fl)
		print ("\t\t{}\n\t\tx {}  y {}  w {}  h {}  frames {}  spacing {}  int {}  float {}".format(texNames[tid], x, y, w, h, frames, dw, intg, flt))

fl.close()
