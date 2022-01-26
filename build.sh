#!/bin/bash

echo "Building  \"lmc.c\""
tcc lmc.c	-o bin/lmc		#-m32

echo "Building  \"lma.c\""
tcc lma.c	-o bin/lma		#-m32


echo "Creating  \"lmc.tar.gz\""
tar -cf lmc.tar examples
mv lmc.tar bin/lmc.tar
cd bin
tar -rf lmc.tar lma lmc setup.sh
gzip -f lmc.tar
cd ..
