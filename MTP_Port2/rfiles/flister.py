from os import listdir
from os.path import isfile, join, isdir
rootfolder = "D:/ProjectData/caltech101/101_ObjectCategories/"
onlyfolders= [f for f in listdir(rootfolder) if isdir(join(rootfolder, f))]

with open('pointerList.list1', 'w') as plist:
	for ifolder in onlyfolders:
		subfolder = rootfolder + ifolder + "/"
		#folder = "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/cup"
		onlyfiles= [join(subfolder, f) for f in listdir(subfolder) if isfile(join(subfolder, f))]
		plist.write(ifolder+ "\n")
		plist.write(str(len(onlyfiles)) + "\n")
		with open(ifolder + ".list2", "w") as wfile:
			for iname in onlyfiles:
				wfile.write(iname + "\n")