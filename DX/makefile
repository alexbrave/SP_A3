#
#   FILE      	  : makefile
#   PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
#   PROGRAMMER    : Alex Braverman
#   FIRST VERSION : March 25, 2020 
#   DESCRIPTION   : 
# 		This make file will create all the relevant objects that encodeInput
#		is dependent on.
#


# FINAL BINARY Target
# Instead of writing out all these object names when linking them in encodeInput
# we use a convenient variable instead!
TARGET_DEPENDENCIES := ./obj/DX.o ./obj/checkQueExists.o
TARGET_DEPENDENCIES += ../Common/obj/genRandSleep.o ./obj/executeWODAct.o
TARGET_DEPENDENCIES += ./obj/logMessage.o 

# Link everything, optionally including the math library (add -lm after -o ./bin/DC)
./bin/DX : $(TARGET_DEPENDENCIES)
	cc $(TARGET_DEPENDENCIES) -o ./bin/DX 
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DX.o : ./src/DX.c ./inc/DX.h
	cc -c -g ./src/DX.c -o ./obj/DX.o

../Common/obj/genRandSleep.o : ../Common/src/genRandSleep.c ../Common/inc/genRandSleep.h
	cc -c -g ../Common/src/genRandSleep.c -o ../Common/obj/genRandSleep.o

./obj/checkQueExists.o : ./src/checkQueExists.c ./inc/DX.h
	cc -c -g ./src/checkQueExists.c -o ./obj/checkQueExists.o 

./obj/executeWODAct.o : ./src/executeWODAct.c ./inc/DX.h
	cc -c -g ./src/executeWODAct.c -o ./obj/executeWODAct.o

./obj/logMessage.o : ./src/logMessage.c ./inc/DX.h
	cc -c -g ./src/logMessage.c -o ./obj/logMessage.o


#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DX

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


