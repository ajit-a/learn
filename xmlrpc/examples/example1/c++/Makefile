EXPENDABLES = bin/Client bin/Server obj/Client.o obj/Server.o obj/RPCHandler.o

# Add any necessary include directories here.
INCLUDE_DIRS = #-I /usr/local/include

# The following line is needed so that the
# system knows where to find the XML-RPC
# libraries at run time.
LD_OPTS = -Wl,-rpath=/usr/local/lib

# Add any necessary library directories here.
LIB_DIRS = #-L /usr/local/lib

XML_LIBS = -lxmltok -lxmlparse

SYS_LIBS = -lmd5 -ldl -lz -lssl -lcrypto

CURL_LIBS = -lcurl -lidn -lssl -lcrypto -ldl -lz -lpthread

WWW_LIBS = -lwwwinit -lwwwapp -lwwwxml $(XML_LIBS) -lwwwzip -lwwwhtml -lwwwtelnet -lwwwnews -lwwwhttp -lwwwmime -lwwwgopher -lwwwftp -lwwwfile -lwwwdir -lwwwcache -lwwwstream -lwwwmux -lwwwtrans -lwwwcore -lwwwutils

COMMON_LIBS = $(WWW_LIBS) $(SYS_LIBS) $(CURL_LIBS)

XMLRPC_COMMON_LIBS = -lxmlrpc++ -lxmlrpc -lxmlrpc_xmlparse -lxmlrpc_xmltok

# Libraries needed for programs that only
# act as XML-RPC clients
XMLRPC_CLIENT_LIBS = -lxmlrpc_client++ $(COMMON_LIBS) -lxmlrpc_client

# Libraries needed for programs that act
# as both a server and a client
XMLRPC_SERVER_LIBS = -lxmlrpc_server_abyss++ -lxmlrpc_server_abyss++ -lxmlrpc_server++ -lxmlrpc_server_abyss -lxmlrpc_server -lxmlrpc_abyss

# Libraries needed for clients
CLIENT_LIBS = $(XMLRPC_CLIENT_LIBS) $(XMLRPC_COMMON_LIBS)

# Libraries needed for servers
SERVER_LIBS = $(XMLRPC_SERVER_LIBS) $(XMLRPC_COMMON_LIBS) 

# Libraries needed for servers that are also clients
SERVER_CLIENT_LIBS = $(XMLRPC_CLIENT_LIBS) $(XMLRPC_SERVER_LIBS) $(XMLRPC_COMMON_LIBS)

all: bin/Client bin/Server

bin/Client: src/ClientMain.cpp obj/Client.o
	g++ -Wall -g $(LD_OPTS) $(LIB_DIRS) -o bin/Client src/ClientMain.cpp obj/Client.o $(CLIENT_LIBS)

bin/Server: src/ServerMain.cpp obj/Server.o obj/RPCHandler.o
	g++ -Wall -g $(LD_OPTS) $(LIB_DIRS) -o bin/Server src/ServerMain.cpp obj/Server.o obj/RPCHandler.o $(SERVER_LIBS)

obj/Client.o: src/Client.hpp src/Client.cpp
	g++ -Wall -g $(INCLUDE_DIRS) -c src/Client.cpp -o obj/Client.o 

obj/Server.o: src/Server.hpp src/Server.cpp
	g++ -Wall -g $(INCLUDE_DIRS) -c src/Server.cpp -o obj/Server.o

obj/RPCHandler.o: src/RPCHandler.hpp src/RPCHandler.cpp
	g++ -Wall -g $(INCLUDE_DIRS) -c src/RPCHandler.cpp -o obj/RPCHandler.o

clean:
	rm -f $(EXPENDABLES)

