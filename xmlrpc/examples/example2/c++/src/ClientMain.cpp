/**
 * This is the XML-RPC client for Example 2.
 * It executes the server.getDate RPC on the 
 * server and prints out the date returned 
 * by the server.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

// System includes
#include <cstdlib>
#include <iostream>
#include <time.h>

// Local includes
#include "Client.hpp"

// Declare which objects from std we're using.
using std::string;
using std::cout;
using std::cerr;
using std::ctime;
using std::endl;
using std::time_t;

// Use our namespace
using namespace cs4513;

/**
 * Prints the usage and exits.
 */
void printUsageAndExit() {
	cout << "Usage: Client host:port [shutdown]" << endl;
	cout << "\thost - The hostname or IP of the server." << endl;
	cout << "\tport - The server port." << endl;
	cout << "\tshutdown - Shuts down the server via an XML-RPC call." << endl;
	cout << "Example: Client localhost:9382" << endl;
	cout << "Example: Client localhost:9382 shutdown" << endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
	if (argc == 3) {
		if (strcasecmp(argv[2], "shutdown") != 0)
			printUsageAndExit();
	}
	else if (argc != 2)
		printUsageAndExit();

	// Build the server URL.
	// It should always have the form: http://host:port/RPC2
	string serverAddr = "http://" + string(argv[1]) + "/RPC2";

	// Initialize the client.
	Client client(serverAddr);

	// Execute the XML-RPC.
	if (argc == 2) {
		cout << "Client: Getting the current date." << endl;
		time_t now = client.executeDateRPC();
		cout << "Client: The server returned " << ctime(&now);
	}
	else if (argc == 3) {
		cout << "Client: Sending shutdown command to server." << endl;
		bool success = client.executeShutdownRPC();
		cout << "Client: The server returned ";
		if (success == true)
			cout << "true." << endl;
		else
			cout << "false." << endl;
	}

	return EXIT_SUCCESS;
}
