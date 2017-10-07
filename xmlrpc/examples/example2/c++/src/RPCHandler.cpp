/**
 * This file contains the implementation of the RPC handler 
 * classes.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

// System includes
#include <iostream>
#include <time.h>

// Local includes
#include "RPCHandler.hpp"
#include "Server.hpp"

// Declare which objects from std we're using.
using std::cout;
using std::cerr;
using std::ctime;
using std::endl;
using std::localtime;
using std::mktime;
using std::time_t;

// The RPC handlers may need to access the Server.
using cs4513::Server;

// Define the RPC handler classes to be in the cs4513 namespace
namespace cs4513 {

/**
* The server.getDate XML-RPC handler.  It gets and returns the current date.
* The time is converted to the local time zone instead of using UTC.  This is mostly
* due to the fact that the Apache XML-RPC library for Java converts all times to the 
* local time and expects to receive times in the local time.  It probably should 
* not do that, but for compatibility this method will convert to local time.
* @param params List of RPC parameters.  The client should not pass any parameters.
* @param retvalP Pointer to the return value of the method.  Always returns true.
*/
void DateHandler::execute(xmlrpc_c::paramList const& params, xmlrpc_c::value* const retvalP) {
	cout << "Server: Handling \"" << cs4513::Server::DATE_RPC_NAME << "\" RPC." << endl;

	// Get the current date .
	time_t now = time(NULL);

	// Calculate our local time zone's offset from UTC (GMT).
	tm* gmt = gmtime(&now);
	int gmtOffset = (int) (difftime(now, mktime(gmt))/(60 * 60));

	// Make a new time using the local time zone.
	time_t adjustedTime = now;
	adjustedTime += (60 * 60 * gmtOffset);

	// Note: The use of "now" instead of "adjustedTime" here is intentional.
	// ctime will convert the given time to local time, and adjustedTime is
	// already local, so converting it again would produce the wrong time.
	cout << "Server: Returning " << ctime(&now);

	// Values are returned from the execute method by setting *retvalP equal to any xmlrpc_c::value.
	// Return the date by creating an xmlrpc_c::value_datetime and setting *retvalP equal to it.
	*retvalP = xmlrpc_c::value_datetime(adjustedTime);
}

/**
 * This method is called when the sciapp.shutdown RPC is handled.
 * Calls the Server::shutdown() method.
 * @param params List of RPC parameters.
 * @param retvalP Pointer to the return value of the method.  Always returns true.
 */
void ShutdownHandler::execute(xmlrpc_c::paramList const& params, xmlrpc_c::value* const retvalP) {
	cout << "Server: Handling \"" << cs4513::Server::SHUTDOWN_RPC_NAME << "\" RPC." << endl;
	Server::instance()->shutdown();
	*retvalP = xmlrpc_c::value_boolean(true);
}

} // end namespace cs4513
