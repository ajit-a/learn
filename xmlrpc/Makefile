SRCDIR = $(CURDIR)/..
BLDDIR = $(SRCDIR)
XMLRPC_C_CONFIG = $(BLDDIR)/xmlrpc-c-config.test

all: server

server : server.o
	gcc -Wall -g -o server server.o   $(shell $(XMLRPC_C_CONFIG) abyss-server --libs) 

server.o : server.c
	gcc -Wall -g -c -I. $(shell $(XMLRPC_C_CONFIG) client abyss-server --cflags)    server.c 

