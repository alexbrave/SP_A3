#!/bin/bash


if [ "$#" -eq 0 ]
    then
        echo "No arguments supplied"
elif [ "$#" -eq 1 ]
    then
    if [ $1 -eq "make" ]
    cd DC
    make
    cd ../DR
    make
    cd ../DX
    make
    cd ..
    mv ./DX/bin/DX ./DR/bin/
    exit 1 
    
    fi
fi


# if [ expression1 ]
# then
#    statement1
#    statement2
#    .
# else
#    if [ expression2 ]
#    then
#       statement3
#       .
#    fi
# fi









# Script for compiling 

# Navigate to DC directory
cd ~/Desktop/SP_A3/SP_A3/DC
make clean
make


# Debug program with gdb
cd ~/Desktop/SP_A3/SP_A3/DC/bin
gdb DC
start

# break getOrCreateLogSem.c:30
c


# Start program and continue
start
c



# Debugging DC from DR directory
# cd ~/Desktop/SP_A3/SP_A3/DC
# make clean
# make


# Debug program with gdb
# cd ~/Desktop/SP_A3/SP_A3/DR/bin
# gdb DC
# start



# Linux see all semaphores
ipcs -s

#Linux remove semaphore with key
ipcsrm -S *key*


# Delete message queue
ipcrm -q *message queue ID*



# Compilation stuff for DX
# Navigate to DX directory
cd ~/Desktop/SP_A3/SP_A3/DX
make clean
make


# Debug program with gdb
cd ~/Desktop/SP_A3/SP_A3/DR/bin
mv ~/Desktop/SP_A3/SP_A3/DX/bin/DX ~/Desktop/SP_A3/SP_A3/DR/bin/
gdb DX
start
# break executeWODAct.c:43
c


# Compilation stuff for DR
# Navigate to DX directory
cd ~/Desktop/SP_A3/SP_A3/DR
make clean
make


# Debug program with gdb
cd ~/Desktop/SP_A3/SP_A3/DR/bin
gdb DR
start
c





