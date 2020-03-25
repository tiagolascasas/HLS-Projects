#
#	Copyright (c) 1994 - Corinna G. Lee, University of Toronto
#
.SILENT:
.IGNORE:
CC = /gnu/bin/gcc
MAKE = /bin/make
TAG = "-----"
DataFile = abc.gif
#
# Set up symbolic links in sub-directories for input files (based on
# script in modemsim file).
#
setup:
	ln -s $(DataFile)			input
	ln -s ../$(DataFile)			Achop/input.dsp
	ln -s ../Achop/ptrs/output.sun		Bencode/input.dsp
	ln -s ../Bencode/ptrs/output.sun	Cnoise/input.dsp
	ln -s ../Cnoise/ptrs/output.sun		Ddecode/input.dsp
	ln -s ../Ddecode/ptrs/output.sun	Eglue/input.dsp
	ln -s Eglue/ptrs/output.sun		output

#
# Internal checks to ensure that encoder/decoder pairs generate output that
# is same as the input into the pair.  Note: names of input and output files
# for bcmp are hard-coded as "input" and "output", respectively.
#
validate:
	echo " "
	echo "$(TAG) VALIDATing `pwd`"
	$(MAKE) bcmp
	bcmp
	echo "$(TAG) DONE"

bcmp:	bcmp.o	; $(CC) -o $@ $?
