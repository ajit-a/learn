INC_DIR=inc
SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin
OBJ_DIR=obj
CXX=c++
CXXFLAGS=-fPIC
LIB_FLAG=-shared -fPIC -shared-libgcc

all:shape 

#call:call.o

main:
	$(CXX) -g -o $(BIN_DIR)/main $(SRC_DIR)/main.cpp -I$(INC_DIR) -L$(LIB_DIR) -ldragLib -Wl,-rpath=./$(LIB_DIR)

shape:shape.o square.o circle.o rectangle.o
	$(CXX) $(LIB_FLAG) -o $(LIB_DIR)/libdragLib.so $(OBJ_DIR)/* -lcall -L$(LIB_DIR)
call:call.o
	$(CXX) $(LIB_FLAG) -o $(LIB_DIR)/libcall.so $(OBJ_DIR)/call.o

shape.o:$(SRC_DIR)/Shape.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $(OBJ_DIR)/shape.o $(SRC_DIR)/Shape.cpp -I$(INC_DIR)
square.o:$(SRC_DIR)/Square.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $(OBJ_DIR)/square.o $(SRC_DIR)/Square.cpp -I$(INC_DIR)
circle.o:$(SRC_DIR)/Circle.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $(OBJ_DIR)/circle.o $(SRC_DIR)/Circle.cpp -I$(INC_DIR)
rectangle.o:$(SRC_DIR)/Rectangle.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $(OBJ_DIR)/rectangle.o $(SRC_DIR)/Rectangle.cpp -I$(INC_DIR)

call.o:$(SRC_DIR)/Call.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $(OBJ_DIR)/call.o $(SRC_DIR)/Call.cpp -I$(INC_DIR)

clean:
	rm -f $(OBJ_DIR)/*
	rm -f $(LIB_DIR)/*
	rm -f $(BIN_DIR)/*
