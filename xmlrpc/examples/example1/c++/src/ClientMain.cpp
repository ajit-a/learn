/**
 * This is the XML-RPC client for Example 1.  It reads the server
 * address and two integers from the command line (as arguments), 
 * which it then sends to the server as strings.  The server attempts 
 * to add them and return the sum, throwing an exception if the 
 * strings did not represent valid integers.  Normally the client 
 * would perform the validation and convert the strings to integers 
 * before sending them to the server, but this example is designed 
 * to show how exception handling works with XML-RPC.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

// System includes
#include <iostream>
#include <cstdlib>

// Local includes
#include "Client.hpp"

// Declare which objects from std we're using.
using std::string;
using std::cout;
using std::cerr;
using std::endl;

// Use our namespace
using namespace cs4513;

/**
 * Prints the usage and exits.
 */
void printUsageAndExit() {
	cout << "Usage: Client host:port [num1 num2] | [shutdown]" << endl;
	cout << "\thost - The hostname or IP of the server." << endl;
	cout << "\tport - The server port." << endl;
	cout << "\tnum1/num2 - The two numbers to add." << endl;
	cout << "\tshutdown - Shuts down the server via an XML-RPC call." << endl;
	cout << "Example: Client localhost:9382 1 2" << endl;
	cout << "Example: Client localhost:9382 shutdown" << endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
	if (argc == 3) {
		if (strcasecmp(argv[2], "shutdown") != 0)
			printUsageAndExit();
	}
	else if (argc != 4)
		printUsageAndExit();

	// Build the server URL.
	// It should always have the form: http://host:port/RPC2
	string serverAddr = "http://" + string(argv[1]) + "/RPC2";

	// Initialize the client.
	Client client(serverAddr);

	// Execute the XML-RPC.
	if (argc == 4) {
		cout << "Client: Adding " << argv[2] << " and " << argv[3] << "." << endl;
		int sum = client.executeAddRPC(argv[2], argv[3]);
		cout << "Client: The server returned " << sum << "." << endl;
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
