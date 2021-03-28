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
TARGET_DEPENDENCIES := ./obj/DC.o ../Common/obj/genRandSleep.o
TARGET_DEPENDENCIES += ./obj/genRandStatus.o ./obj/getOrCreateLogSem.o
TARGET_DEPENDENCIES += ./obj/logMessage.o ./obj/sendMessage.o 
TARGET_DEPENDENCIES += ./obj/releaseLogSem.o

# Link everything, optionally including the math library (add -lm after -o ./bin/DC)
./bin/DC : $(TARGET_DEPENDENCIES)
	cc $(TARGET_DEPENDENCIES) -o ./bin/DC 
#
# =======================================================
#                     Dependencies
# =======================================================   
# There are no debugging symbols being compiled, to add them add "-g" after "cc -c" for 
# each of the following object file directives                  
./obj/DC.o : ./src/DC.c ./inc/DC.h
	cc -c ./src/DC.c -o ./obj/DC.o

../Common/obj/genRandSleep.o : ../Common/src/genRandSleep.c ../Common/inc/genRandSleep.h
	cc -c ../Common/src/genRandSleep.c -o ../Common/obj/genRandSleep.o

./obj/genRandStatus.o : ./src/genRandStatus.c ./inc/DC.h
	cc -c ./src/genRandStatus.c -o ./obj/genRandStatus.o 

./obj/getOrCreateLogSem.o : ./src/getOrCreateLogSem.c ./inc/DC.h
	cc -c ./src/getOrCreateLogSem.c -o ./obj/getOrCreateLogSem.o

./obj/logMessage.o : ./src/logMessage.c ./inc/DC.h
	cc -c ./src/logMessage.c -o ./obj/logMessage.o

./obj/sendMessage.o : ./src/sendMessage.c ./inc/DC.h
	cc -c ./src/sendMessage.c -o ./obj/sendMessage.o

./obj/releaseLogSem.o : ./src/releaseLogSem.c ./inc/DC.h
	cc -c ./src/releaseLogSem.c -o ./obj/releaseLogSem.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DC

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


