all:Main.o main.o
	c++ c/Main.o cpp/main.o -o run -lpthread
Main.o:
	cd c && make
main.o:
	cd cpp && make
