#!/bin/bash

# ---------------------------LICENSE NOTICE-------------------------------- 
# MIT License
#
# Copyright (c) 2018 David Asta
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#


# YOU MUST GET THIS INFORMATION 
# from obj/binaryAddresses.log in
# your game's project 
RUNADDR=1F77
LOADADDR=0040

#Compile the project with CPCtelera
make

# Copy necessary files to a temporary folder
rm -rf mydisk
mkdir mydisk
cp assets/loader.bas mydisk/
cp obj/cduels.bin mydisk/game.bin
cp assets/screen.scr mydisk/

# Create blank disk file
cd mydisk
${CPCT_PATH}/tools/iDSK-0.13/bin/iDSK cduels.dsk -n > /dev/null

# Add BASIC file to tape file
${CPCT_PATH}/tools/iDSK-0.13/bin/iDSK cduels.dsk -i loader.bas > /dev/null

# Add .SCR file with load address
${CPCT_PATH}/tools/iDSK-0.13/bin/iDSK cduels.dsk -i screen.scr -c C000 -t 1 > /dev/null

# Add .BIN file with load and execution addresses
${CPCT_PATH}/tools/iDSK-0.13/bin/iDSK cduels.dsk -i game.bin -e $RUNADDR -c $LOADADDR -t 1 > /dev/null

# Print DSK contents
${CPCT_PATH}/tools/iDSK-0.13/bin/iDSK cduels.dsk -l

# Remove unneccesary files
cd ..
rm -f mydisk/loader.bas
rm -f mydisk/game.bin
rm -f mydisk/screen.scr

echo Disk DSK file created!
