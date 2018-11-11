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
RUNADDR=0x1F77
LOADADDR=0x0040

#Compile the project with CPCtelera
make

# Copy necessary files to a temporary folder
rm -rf mytape
mkdir mytape
cp assets/loader.bas mytape/
cp obj/cduels.bin mytape/game.bin
cp assets/screen.scr mytape/

# Create blank tape file
cd mytape
${CPCT_PATH}/tools/2cdt/bin/2cdt -n . game.cdt > /dev/null

# Add BASIC file to tape file
${CPCT_PATH}/tools/2cdt/bin/2cdt -r "Cannon Duels" -F 0 loader.bas game.cdt > /dev/null

# Add .SCR file with load address
${CPCT_PATH}/tools/2cdt/bin/2cdt -r screen.scr -L 0xC000 screen.scr game.cdt > /dev/null

# Add .BIN file with load and execution addresses
${CPCT_PATH}/tools/2cdt/bin/2cdt -r game.bin -L $LOADADDR -X $RUNADDR game.bin game.cdt > /dev/null

# Remove unneccesary files
cd ..
rm -f mytape/loader.bas
rm -f mytape/game.bin
rm -f mytape/screen.scr

echo Tape CDT file created!
