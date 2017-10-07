/**
 * This is the Client class definition.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */

#ifndef _CLIENT_HPP
#define _CLIENT_HPP

// XML-RPC includes
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

// Declare which objects from std we're using.
using std::string;

// Define Client to be in the cs4513 namespace
namespace cs4513 {

/**
 * The Client class is responsible for initializing XML-RPC
 * and making all XML-RPC requests.  Note: methods are 
 * implemented/documented in Client.cpp.
 */
class Client {
	private:
		static const string ADD_RPC_NAME;
		static const string SHUTDOWN_RPC_NAME;
		string serverAddr;
		xmlrpc_c::clientXmlTransport_libwww* xmlrpcTransport;
		xmlrpc_c::client_xml* xmlrpcClient;
		void initializeXMLRPCClient();
		xmlrpc_c::value executeRPC(xmlrpc_c::rpcPtr);
	public:
		Client(string);
		~Client();
		int executeAddRPC(string,string);
		bool executeShutdownRPC();
};

} // end namespace cs4513

#endif // #define _CLIENT_HPP
