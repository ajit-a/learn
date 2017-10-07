CC=c++
SRC_DIR=src
OBJ_DIR=obj
INC_DIR=inc
BIN_DIR=bin

all:spSendMail

spSendMail:spSendMail.o main.o
	$(CC) $(OBJ_DIR)/spSendMail.o $(OBJ_DIR)/main.o -o $(BIN_DIR)/spSendMail

spSendMail.o:
	$(CC) -c $(SRC_DIR)/spSendMail.cpp -o $(OBJ_DIR)/spSendMail.o -I$(INC_DIR)

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o -I$(INC_DIR)
