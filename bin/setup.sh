#!/bin/bash

read -p "Do you want to install  lmc (Interpreter)? [Y/n] " pn
if [ "${pn^^}" == "Y" ]; then
	echo -e "> cp lmc /usr/bin/lmc\n"
	cp lmc /usr/bin/lmc
fi

read -p "Do you want to install  lma (Assembler)? [Y/n] " pn
if [ "${pn^^}" == "Y" ]; then
	echo -e "> cp lma /usr/bin/lma\n"
	cp lma /usr/bin/lma
fi
