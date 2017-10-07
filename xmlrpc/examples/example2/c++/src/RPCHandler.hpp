/**
 * This file contains the class definitions
 * of the RPC handlers.  Each RPC handler 
 * must be in its own class.  This class must 
 * be a child class of xmlrpc_c::method.  The 
 * execute method of the child class is called
 * by the XML-RPC server when that particular 
 * RPC handler is invoked by a client.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

#ifndef _RPC_HANDLER_HPP
#define _RPC_HANDLER_HPP

// XML-RPC includes
#include <xmlrpc-c/registry.hpp>

// Define the RPC handler classes to be in the cs4513 namespace
namespace cs4513 {

/**
 * Gets the current date.
 * @return Returns the current date.
 */
class DateHandler : public xmlrpc_c::method {
public:
	/**
 	* The server.getDate XML-RPC handler.  It gets and returns the current date.
 	* @param paramList List of RPC parameters.  The client should not pass any parameters.
 	* @param retvalP Pointer to the return value of the method.  Always returns true.
 	*/
	void execute(xmlrpc_c::paramList const&, xmlrpc_c::value* const);
};

/**
 * Performs any tasks necessary to cleanly shut down the server.
 * @return Returns true.
 */
class ShutdownHandler : public xmlrpc_c::method {
public:
	/**
	 * This method is called when the server.shutdown RPC is handled.
	 * Calls the Server::shutdown() method.
	 * @param paramList List of RPC parameters.
	 * @param retvalP Pointer to the return value of the method.  Always returns true.
	 */
	void execute(xmlrpc_c::paramList const&, xmlrpc_c::value* const);
};

} // end namespace cs4513

#endif // #define _RPC_HANDLER_HPP
