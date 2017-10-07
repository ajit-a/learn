import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Vector;

import org.apache.xmlrpc.XmlRpcClient;
import org.apache.xmlrpc.XmlRpcException;

/**
 * This is the XML-RPC client for Example 1.  It reads two integers
 * from the command line (as arguments), which it then sends to the 
 * server as strings.  The server attempts to add them and return 
 * the answer, throwing an Exception if the strings did not represent 
 * valid integers.  Normally the client would perform the validation 
 * and convert the strings to integers before sending them to the 
 * server, but this example shows how Exception handling works 
 * with XML-RPC. 
 * @author James Baldassari (jdb@cs.wpi.edu)
 */
public class Client {
	private static final int EXIT_SUCCESS = 0;
	private static final int EXIT_ERROR = 1;
	private static final String ADD_RPC_NAME = "server.add";
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
	 * Executes the "server.add" XML-RPC, and returns the result.
	 * @param num1 The first number to add.
	 * @param num2 The second number to add.
	 * @return Returns the sum calculated by the server.
	 */
	public Integer executeAddRPC(String num1, String num2) {
		/*
		 * Note: There is no validation performed here on num1 and num2.
		 * Instead, the server will try to convert the strings to integers.
		 * If the given strings are not integers, the server will throw an 
		 * exception.  This is not the best way to handle input validation.
		 * Even thin clients usually do their own validation.  The purpose
		 * of having the server do the validation is to demonstrate how to 
		 * send strings over XML-RPC and how to handle Exceptions that are 
		 * thrown during the execution of an RPC. 
		 */
		
		/*
		 * Build the list of parameters for the RPC.
		 * RPC parameters will always be inside a vector.
		 * The order of the parameters should match the signature of
		 * the XML-RPC handler on the server.
		 * In this case, the signature of the XML-RPC handler is:
		 * Integer server.add(String,String)
		 * so it doesn't really matter for this example.  If the RPC
	 	 * had been something like Integer server.add(int, double) 
	 	 * then we would have to add the variables to the vector
	 	 * in that order: first the int, then the double.
		 * Note: for an RPC that takes no paramters, it is still
	 	 * necessary to pass a Vector object.  However, if the RPC 
		 * takes no parameters, the Vector should be empty.
		 */
		Vector<String> parameters = new Vector<String>();
		parameters.add(num1);
		parameters.add(num2);
		
		// The sum returned by the server.
		Integer sum = null;
		
		try {
			// Execute the RPC.
			System.out.println("Client: Executing the " + ADD_RPC_NAME + " RPC...");
			Object result = xmlrpcClient.execute(ADD_RPC_NAME, parameters);
			
			/*
			 * The result object should be an Integer.
			 * If it is not, then an error occurred, and 
			 * result is an Exception object.  To determine
			 * whether the RPC was successful, try to cast 
			 * result to an Integer.
			 */
			try {
				sum = (Integer)result;
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
		
		return sum;
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
		System.out.println("Usage: Client host:port [num1 num2] | [shutdown]");
		System.out.println("\thost - The hostname or IP of the server.");
		System.out.println("\tport - The server port.");
		System.out.println("\tnum1/num2 - The two numbers to add.");
		System.out.println("\tshutdown - Shuts down the server via an XML-RPC call.");
		System.out.println("Example: Client localhost:9382 1 2");
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
		else if (args.length != 3)
			printUsageAndExit();
		
		try {
			// The form of the server URL is always:
			// http://host:port/RPC2
			String serverURL = "http://" + args[0] + "/RPC2";

			// Create a new client with the given server address.
			Client client = new Client(serverURL);
			
			if (args.length == 3) {
				System.out.println("Client: Adding " + args[1] + " and " + args[2] + ".");

				// Execute the RPC on the server.
				Integer sum = client.executeAddRPC(args[1], args[2]);
			
				// Print the sum.
				System.out.println("Client: The server returned " + sum + ".");
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
