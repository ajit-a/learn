import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Date;
import java.util.Vector;

import org.apache.xmlrpc.XmlRpcClient;
import org.apache.xmlrpc.XmlRpcException;

/**
 * This is the XML-RPC client for Example 2.
 * It executes the server.getDate RPC on the 
 * server and prints out the date returned 
 * by the server.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */
public class Client {
	private static final int EXIT_SUCCESS = 0;
	private static final int EXIT_ERROR = 1;
	private static final String DATE_RPC_NAME = "server.getDate";
	private static final String SHUTDOWN_RPC_NAME = "server.shutdown";
	private String serverURL = null;
	private XmlRpcClient xmlrpcClient = null;
	
	/**
	 * Constructor specifying the server address.
	 * @param serverURL The address (host:port) of the server.
	 * @throws MalformedURLException 
	 */
	public Client(String serverURL) throws MalformedURLException {
		this.serverURL = serverURL;
		initializeXMLRPCClient();
	}
	
	/**
	 * Initializes the XML-RPC client.
	 * @throws MalformedURLException 
	 */
	private void initializeXMLRPCClient() throws MalformedURLException {
		xmlrpcClient = new XmlRpcClient(serverURL);
	}
	
	/**
	 * Executes the "server.getDate" XML-RPC, and returns the result.
	 * @return Returns the current date.
	 */
	public Date executeDateRPC() {
		// Even though the server.getDate takes no parameters,
		// we still need a Vector to pass to xmlrpcClient.execute().
		// This Vector is empty.
		Vector parameters = new Vector();
		
		// The sum returned by the server.
		Date now = null;
		
		try {
			// Execute the RPC.
			System.out.println("Client: Executing the " + DATE_RPC_NAME + " RPC...");
			Object result = xmlrpcClient.execute(DATE_RPC_NAME, parameters);
			
			/*
			 * The result object should be an Integer.
			 * If it is not, then an error occurred, and 
			 * result is an Exception object.  To determine
			 * whether the RPC was successful, try to cast 
			 * result to an Integer.
			 */
			try {
				now = (Date)result;
			} catch (ClassCastException e) {
				// An error occurred and the server
				// returned an Exception.
				XmlRpcException e2 = (XmlRpcException)result;
				System.err.println("The server threw an exception: " + e2.getMessage());
				System.exit(EXIT_ERROR);
			}
		} catch (XmlRpcException e) {
			// An XML-RPC exception occurred.  For example, a handler  
			// for the requested RPC was not found on the server
			System.err.println("XML-RPC error: " + e.getCause());
			System.exit(EXIT_ERROR);
		} catch (IOException e) {
			// An error with the HTTP connection occurred.  For example,
			// the connection was refused.
			System.err.println("Could not connect to XML-RPC server at " + serverURL + '.');
			System.exit(EXIT_ERROR);
		}
		
		return now;
	}

	/**
	 * Executes the "server.shutdown" XML-RPC, and returns the result.
	 * @return The server should always return true.
	 */
	public boolean executeShutdownRPC() {
		// The result returned by the server.
		boolean success = false;

		/*
		 * The server.shutdown RPC takes zero parameters, so 
		 * we just pass an empty Vector.
		 */
		Vector parameters = new Vector();
		
		try {
			// Execute the RPC.
			System.out.println("Client: Executing the " + SHUTDOWN_RPC_NAME  + " RPC...");
			Object result = xmlrpcClient.execute(SHUTDOWN_RPC_NAME, parameters);
			
			/*
			 * The result object should be a Boolean.
			 * If it is not, then an error occurred, and 
			 * result is an Exception object.  To determine
			 * whether the RPC was successful, try to cast 
			 * result to a Boolean.
			 */
			try {
				success = ((Boolean)result).booleanValue();
			} catch (ClassCastException e) {
				// An error occurred and the server
				// returned an Exception.
				XmlRpcException e2 = (XmlRpcException)result;
				System.err.println("The server threw an exception: " + e2.getMessage());
				System.exit(EXIT_ERROR);
			}
		} catch (XmlRpcException e) {
			// An XML-RPC exception occurred.  For example, a handler  
			// for the requested RPC was not found on the server
			System.err.println("XML-RPC error: " + e.getCause());
			System.exit(EXIT_ERROR);
		} catch (IOException e) {
			// An error with the HTTP connection occurred.  For example,
			// the connection was refused.
			System.err.println("Could not connect to XML-RPC server at " + serverURL + '.');
			System.exit(EXIT_ERROR);
		}
		
		return success;
	}
	
	/**
	 * Prints the usage and exits.
	 */
	private static void printUsageAndExit() {
		System.out.println("Usage: Client host:port [shutdown]");
		System.out.println("\thost - The hostname or IP of the server.");
		System.out.println("\tport - The server port.");
		System.out.println("\tshutdown - Shuts down the server via an XML-RPC call.");
		System.out.println("Example: Client localhost:9382");
		System.out.println("Example: Client localhost:9382 shutdown");
		System.exit(EXIT_SUCCESS);
	}
	
	/**
	 * Executes the XML-RPC using the supplied command-line arguments.
	 * @param args Command-line arguments.  There should be three:
	 * the server address (host:port) and the two numbers to add.
	 */
	public static void main(String[] args) {
		if (args.length == 2) {
			if (args[1].equalsIgnoreCase("shutdown") == false)
				printUsageAndExit();
		}
		else if (args.length != 1)
			printUsageAndExit();
		
		try {
			// The form of the server URL is always:
			// http://host:port/RPC2
			String serverURL = "http://" + args[0] + "/RPC2";

			// Create a new client with the given server address.
			Client client = new Client(serverURL);
			
			if (args.length == 1) {
				System.out.println("Client: Getting the current date.");

				// Execute the RPC on the server.
				Date now = client.executeDateRPC();
			
				// Print the date.
				System.out.println("Client: The server returned " + now + ".");
			}
			else if (args.length == 2) {
				System.out.println("Client: Sending shutdown command to server.");
				boolean success = client.executeShutdownRPC();
				System.out.println("Client: The server returned " + success + ".");
			}
		} catch (MalformedURLException e) {
			System.err.println("Client: Invalid server address: " + args[0]);
			System.exit(EXIT_ERROR);
		}
	}
}
