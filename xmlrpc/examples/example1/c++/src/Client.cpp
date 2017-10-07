/**
 * This file contains the implementation of the Client class.
 * The Client class initializes the XML-RPC client and executes
 * the server.add RPC.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

// System includes
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>

// XML-RPC includes
#include <xmlrpc-c/client_simple.hpp>

// Local includes
#include "Client.hpp"

// Declare which objects from std we're using.
using std::string;
using std::cout;
using std::cerr;
using std::endl;

// Define Client to be in the cs4513 namespace
namespace cs4513 {

// Initialize constants...
// Define the RPC_NAME constants, which are the names of the
// RPCs on the server to execute.
const string cs4513::Client::ADD_RPC_NAME = "server.add";
const string cs4513::Client::SHUTDOWN_RPC_NAME = "server.shutdown";

/**
 * Constructor accepting the URL of the 
 * XML-RPC server in the form: http://host:port/RPC2.
 * @param addr The URL of the XML-RPC server.
 */
Client::Client(string addr) : serverAddr(addr) {
	initializeXMLRPCClient();
}

/**
 * The destructor.  Frees memory allocated to 
 * the XML-RPC objects.
 */
Client::~Client() {
	delete xmlrpcTransport;
	delete xmlrpcClient;
}

/**
 * Initializes the XML-RPC client.
 */
void Client::initializeXMLRPCClient() {
	/*
	 * The XML transport specifies what library to use for 
	 * sending the XML over HTTP.  Some options include 
	 * libwww and curl.  The libwww library has worked 
	 * best for me.
	 */
	xmlrpcTransport = new xmlrpc_c::clientXmlTransport_libwww();

	// This is the XML-RPC client that will be used to 
	// execute the XML-RPCs.
	xmlrpcClient = new xmlrpc_c::client_xml(xmlrpcTransport);
}

/**
 * Executes the given XML-RPC.  If any error occurs, this
 * method will throw a string containing the error description.
 * @param xmlrpc The XML-RPC to execute.
 * @return Returns the XML-RPC value returned by the server.
 */
xmlrpc_c::value Client::executeRPC(xmlrpc_c::rpcPtr xmlrpc) {
	xmlrpc_c::value result;

	/*
	 * The carraigeParm supplies the URL of the XML-RPC
	 * server to the XML-RPC library.  The URL has the 
	 * form: http://host:port/RPC2
	 */
	xmlrpc_c::carriageParm_libwww0 cParm(serverAddr);

	// Try the XML-RPC call.  Note: The server will throw
	// an exception if the given strings are not valid integers.
	try {
		xmlrpc->call(xmlrpcClient, &cParm);
	} catch (std::exception const e) {
		/*
		 * There was some other error, usually caused by 
		 * the connection being refused (i.e. the server
		 * was not running or was listening on a different
		 * port than we connected to).
		 */
		//cerr << e.what() << endl;	// We can print the error description if it helps
		string error = "Error: Could not connect to the server.";
		throw error;
	} catch (...) {
		string error = "An unknown error occurred while executing the RPC.";
		throw error;
	}

	// We can only proceed if xmlrpc->isSuccessful() returns true
	if (xmlrpc->isSuccessful() == true) {
		/*
		 * WARNING: Calling any of the methods below when 
		 * xmlrpc->isSuccessful() returns false, including
		 * xmlrpc->isFinished(), will probably crash your 
		 * program.
		 */

		// xmlrpc->isFinished() must be true before we can 
		// access the return value of the RPC.
		assert(xmlrpc->isFinished());

		/*
		 * Get the return value of the RPC, which will
		 * initially be an xmlrpc_c::value.  We will 
		 * have to cast it to the expected type.
		 */
		result = xmlrpc->getResult();
	}
	else {
		/*
		 * Some other XML-RPC error occurred.
		 * If xmlrpc->isFinished() is true, we can 
		 * get the error code and description.  If 
		 * the error code is zero, it means that the
		 * server threw some exception while executing 
		 * the RPC.
		 */
		if (xmlrpc->isFinished()) {
			xmlrpc_c::fault err = xmlrpc->getFault();
			if (err.getCode() == 0) {
				/*
				 * The server threw an exception because
				 * it could not convert one of the given
				 * strings into an int.
				 */
				string error = "The server threw an exception: " + err.getDescription();
				throw error;
			}
			else {
				string error = "XML-RPC error " + err.getCode() + err.getDescription();
				throw error;
			}
		}
		else {
			string error = "An unknown XML-RPC error occurred";
			throw error;
		}
	}

	return result;
}

/**
 * Executes the server.add RPC, sending the given strings as parameters.
 * @param num1 The first number to add.
 * @param num2 The second number to add.
 * @return The sum of two numbers calculated by the server.
 */
int Client::executeAddRPC(string num1, string num2) {
	int sum;

	/*
	 * Note: There is no validation performed here on num1 and num2.
	 * Instead, the server will try to convert the strings to integers.
	 * If the given strings are not integers, the server will throw an 
	 * exception.  This is not the best way to handle input validation.
	 * Even thin clients usually do their own validation.  The purpose
	 * of having the server do the validation is to demonstrate how to 
	 * send strings over XML-RPC and how to handle exceptions that are 
	 * thrown during the execution of an RPC. 
	 */

	// First we need to convert our string types
	// to types compatible with the XML-RPC library.
	xmlrpc_c::value_string xmlrpcString1(num1);
	xmlrpc_c::value_string xmlrpcString2(num2);

	// Now we build a parameter list (basically a vector)
	// that will store our XML-RPC types.
	xmlrpc_c::paramList parameters;

	/*
	 * Add the parameters to the list in the order
	 * specified by the RPC signature of the server's
	 * RPC handler.  In this case: int server.add(string, string)
	 * so it doesn't really matter for this example.  If the RPC
	 * had been something like int server.add(int, double) 
	 * then we would have to add the variables to the parameter
	 * list in that order: first the int, then the double.
	 */
	parameters.add(xmlrpcString1);
	parameters.add(xmlrpcString2);

	/*
	 * Build the RPC object with the name of the RPC to 
	 * execute and the list of parameters to pass.
	 * Note: for an RPC that takes no paramters, it is still
	 * necessary to pass an xmlrpc_c::paramList object.
	 * However, if the RPC takes no parameters, the 
	 * paramList should be empty.
	 */
	xmlrpc_c::rpcPtr xmlrpc(cs4513::Client::ADD_RPC_NAME, parameters);
	cout << "Client: Executing the " << cs4513::Client::ADD_RPC_NAME << " RPC..." << endl;

	try {
		// Execute the RPC.
		xmlrpc_c::value result = executeRPC(xmlrpc);

		// Create an xmlrpc_c::value_int from the xmlrpc_c::value,
		// then cast the xmlrpc_c::value_int to an int.
		sum = (int) xmlrpc_c::value_int(result);
	} catch (string e) {
		cerr << e << endl;
		exit(EXIT_FAILURE);
	}

	return sum;
}

bool Client::executeShutdownRPC() {
	bool success = false;

	/*
	 * This RPC takes zero parameters, but we still
	 * need an xmlrpc_c::paramList to use for initializing
	 * the xmlrpc_c::rpcPtr.  If an RPC takes no parameters, 
	 * just use an empty paramList.
	 */
	xmlrpc_c::paramList parameters;

	/*
	 * Build the RPC object with the name of the RPC to 
	 * execute and the list of parameters to pass.
	 * Note: for an RPC that takes no paramters, it is still
	 * necessary to pass an xmlrpc_c::paramList object.
	 * However, if the RPC takes no parameters, the 
	 * paramList should be empty.
	 */
	xmlrpc_c::rpcPtr xmlrpc(cs4513::Client::SHUTDOWN_RPC_NAME, parameters);
	cout << "Client: Executing the " << cs4513::Client::SHUTDOWN_RPC_NAME << " RPC..." << endl;

	try {
		// Execute the RPC.
		xmlrpc_c::value result = executeRPC(xmlrpc);

		// Create an xmlrpc_c::value_int from the xmlrpc_c::value,
		// then cast the xmlrpc_c::value_int to an int.
		success = (bool) xmlrpc_c::value_boolean(result);
	} catch (string e) {
		cerr << e << endl;
		exit(EXIT_FAILURE);
	}

	return success;
}

} // end namespace 4513
