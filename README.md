# LittleManComputer
Assembler and Interpreter for the LittleManComputer Code written in C

# Installation
- *Windows:*
	- Download [lmc.zip](bin/lmc.zip)
	- Extract it anywhere
	- Add the folder to the PATH ([howto](https://windowsloop.com/how-to-add-to-windows-path/))
	- Open CMD and type `lmc` to verify installation
- *Linux:*
	- Download [lmc.tar.gz](bin/lmc.tar.gz)
	- Extract it anywhere:
	```
	$ mkdir tarlmc
	$ tar xf lmc.tar.gz -C tarlmc
	$ cd tarlmc
	```
	
	- Run `./setup.sh`
	```
	$ ./setup.sh
	Do you want to install  lmc (Interpreter)? [Y/n] y
	> cp lmc /usr/bin/lmc

	Do you want to install  lma (Assembler)? [Y/n] y
	> cp lma /usr/bin/lma
	
	```
	
	- Type `lmc` to verify installation
	```
	$ lmc
	No file specified.

	Usage:
	        From File:   lmc file.txt
	  Debug From File:   lmc +file.txt
	        Immediate:   lmc :901308901309508209902000 
	  Debug Immediate:   lmc +:901308901309508209902000

	```

# Build
- *Windows:*
	- Run `build.bat`
	- Output: `bin\lma.exe`, `bin\lmc.exe`
	- Requirements: [tcc for windows](http://download.savannah.gnu.org/releases/tinycc/)
- *Linux:*
	- Run `./build.sh`
	- Output: `bin/lma`, `bin/lmc`
	- Requirements: `apt install tcc`

# Assembler
- Comments
	- `;` Line comment
	- `/` Line comment
- Instructions
	- ADD
	- SUB
	- STA
	- LDA
	- BRA
	- BRZ
	- BRP
	- INP
	- OUT
	- HLT | COB
	- DAT

# Using
![example1](wiki/output1.png)
![example2](wiki/output2.png)
![example3](wiki/output3.png)
![example4](wiki/output4.png)
![example5](wiki/output5.png)

# Wiki
![wiki1](wiki/LittleManComputer.png)
![wiki2](wiki/ExecutionCycle.png)
![wiki3](wiki/Instructions.png)
![wiki4](wiki/Example.png)

# Arrays? Where is opcode 4xx?
![wiki4](wiki/opcode4.png)
![wiki5](wiki/array.png)

References:
- https://en.wikipedia.org/wiki/Little_man_computer
- https://stackoverflow.com/questions/42579740/what-happens-to-instructions-given-to-the-little-man-in-the-lmc-that-begin-with
