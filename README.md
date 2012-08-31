# liblogc - C Library for file and video logging
###Copyright (C) 2012  Orazio Briante orazio.briante@hotmail.it

## Prerequisites:

* gcc, g++, or cc
* pkg-config
* autotools

## How to Generate Makefile:

	$ ./autogen.sh
  or

	$ sh autogen.sh


## Compile - Makefile:
    
	$ ./configure
	$ make

and if necessary:

	$ su
	# make install

 
## To enable Debug option on Compiling process:
 	
	$ ./configure --enable-debug
 	
    
## Unistalling - Makefile (if necessary)

	$ su
	# make uninstall

## To clean directory
 
 run "make clean" from the test source tree.
