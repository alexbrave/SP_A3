#
#   FILE      	  : makefile
#   PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
#   PROGRAMMER    : Andrey Takhtamirov
#   FIRST VERSION : March 25, 2020 
#   DESCRIPTION   : 
# 		This is the make file for the DR (Data Reader) application.
#


# FINAL BINARY Target
TARGET_DEPENDENCIES := ./obj/DR.o ./obj/DR_Logger.o

# Link everything, optionally including the math library (add -lm after -o ./bin/DR)
./bin/DR : $(TARGET_DEPENDENCIES)
	cc $(TARGET_DEPENDENCIES) -o ./bin/DR
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DR.o : ./src/DR.c ./inc/DR.h
	cc -c -g ./src/DR.c -o ./obj/DR.o

./obj/DR_Logger.o : ./src/DR_Logger.c ./inc/DR.h
	cc -c -g ./src/DR_Logger.c -o ./obj/DR_Logger.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DR

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	

