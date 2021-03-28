#!/bin/bash

if [ "$#" -eq 0 ]
  then
    echo "No arguments supplied"
fi
if [ "$#" -eq 1 ]
  then
  if [ $1 == "make" ]
    then
    cd DC
    make
    cd ../DR
    make
    cd ../DX
    make
    cd ..
    mv ./DX/bin/DX ./DR/bin/
  fi
fi
if [ "$#" -eq 2 ]
  then
  if [ "$1" == "make" ]
    then
    if [ "$2" == "clean" ]
      then
      cd DC
      make clean
      cd ../DR
      make clean
      cd ../DX
      make clean
      cd ..
    fi
  fi
fi

