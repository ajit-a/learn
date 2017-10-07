EXPENDABLES = bin/Client.class bin/RPCHandler.class bin/Server.class

all: bin/Client.class bin/Server.class

bin/Client.class: src/Client.java
	javac -classpath "lib/xmlrpc-2.0.jar:lib/commons-codec-1.3.jar" -nowarn -d bin src/Client.java

bin/Server.class: src/Server.java src/RPCHandler.java
	javac -classpath "lib/xmlrpc-2.0.jar:lib/commons-codec-1.3.jar" -nowarn -d bin src/RPCHandler.java src/Server.java

clean:
	rm -f $(EXPENDABLES)

