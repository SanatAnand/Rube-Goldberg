#!/bin/bash
# My first script

alias shiftto = "~/Desktop/cs251_base_code/bin/cs251_base"
echo "script running.... making and executing"
#########
cd ~/Desktop/cs251_base_code
make
cd ~
#########
echo "make done"
######
~/Desktop/cs251_base_code/bin/cs251_base
