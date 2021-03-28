#
#   FILE      	  : makefile
#   PROJECT       : SENG2030-21W-Sec1-System Programming - Assignment #3
#   PROGRAMMER    : Andrey Takhtamirov
#   FIRST VERSION : March 25, 2020 
#   DESCRIPTION   : 
# 		This is the make file for the DR (Data Reader) application.
#


# FINAL BINARY Target
TARGET_DEPENDENCIES := ./obj/DR.o ./obj/receiveMessage.o
TARGET_DEPENDENCIES += ./obj/checkIDinMasterList.o ./obj/manageClients.o
TARGET_DEPENDENCIES += ./obj/messageLogger.o

# Link everything, optionally including the math library (add -lm after -o ./bin/DR)
./bin/DR : $(TARGET_DEPENDENCIES)
	cc $(TARGET_DEPENDENCIES) -o ./bin/DR
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DR.o : ./src/DR.c ./inc/DR.h
	cc -c -g ./src/DR.c -o ./obj/DR.o

./obj/receiveMessage.o : ./src/receiveMessage.c ./inc/DR.h
	cc -c -g ./src/receiveMessage.c -o ./obj/receiveMessage.o

./obj/checkIDinMasterList.o : ./src/checkIDinMasterList.c ./inc/DR.h
	cc -c -g ./src/checkIDinMasterList.c -o ./obj/checkIDinMasterList.o 

./obj/manageClients.o : ./src/manageClients.c ./inc/DR.h
	cc -c -g ./src/manageClients.c -o ./obj/manageClients.o

./obj/messageLogger.o : ./src/messageLogger.c ./inc/DR.h
	cc -c -g ./src/messageLogger.c -o ./obj/messageLogger.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DR

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	

