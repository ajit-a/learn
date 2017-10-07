import org.apache.xmlrpc.WebServer;

/**
 * This is the XML-RPC server for Example 1.  It waits for client requests 
 * for the "server.add" RPC.  If the two strings passed to the RPC cannot be
 * converted to valid integers, the server throws an exception.  Otherwise, 
 * it returns the sum of the two integers. 
 * @author James Baldassari (jdb@cs.wpi.edu)
 */
public class Server implements Runnable {
	private static final int EXIT_SUCCESS = 0;
	private static final int EXIT_ERROR = 1;
	private static final int SLEEP_DELAY = 500;
	public static final String DATE_RPC_NAME = "server.getDate";
	public static final String SHUTDOWN_RPC_NAME = "server.shutdown";
	private static Server serverInstance = null;
	private int serverPort = 9382;
	private WebServer xmlrpcServer = null;
	private boolean running = false;	// Is the server running?
	
	/**
	 * Private constructor because Server is a singleton class.
	 */
	private Server() {
		
	}
	
	/**
	 * Sets the port on which the server will listen.
	 * @param serverPort The server port.
	 */
	public void setServerPort(int serverPort) {
		this.serverPort = serverPort;
	}
	
	/**
 	* Shuts down the server by setting the running flag to false.
 	*/
	public void shutdown() {
		this.running = false;
	}
	
	/**
	 * @return Returns true if the server is running, false otherwise.
	 */
	public boolean isRunning() {
		return running;
	}
	
	/**
	 * Initializes the XML-RPC server.
	 */
	private void initializeXMLRPCServer() {
		// Instantiate a new XML-RPC server.
		xmlrpcServer = new WebServer(serverPort);
		
		/*
		 * Add the RPCHandler class as a handler for XML-RPC requests.
		 * The parameter "server" is the name of the handler.  This means 
		 * that the name of each RPC will consist of "server." followed by 
		 * the name of the public method in RPCHandler.
		 */
		xmlrpcServer.addHandler("server", new RPCHandler());
	}

	/**
	 * Initializes and starts the XML-RPC server.
	 */
	public void run() {
		// Initialize the server
		initializeXMLRPCServer();
		
		// Start the server in its own thread.
		System.out.println("Server: Starting XML-RPC server.");
		xmlrpcServer.start();
		
		// The server is now running.
		running = true;
	}
	
	/** 
	 * @return Returns the singleton instance of the Server class.
	 */
	public static Server instance() {
		if (serverInstance == null)
			serverInstance = new Server();
		return serverInstance; 
	}
	
	/**
	 * Prints the usage and exits.
	 */
	private static void printUsageAndExit() {
		System.out.println("Usage: Server port");
		System.out.println("\tport - The port on which to listen.");
		System.out.println("Example: Server 9382");
		System.exit(EXIT_SUCCESS);
	}
	
	/**
	 * Starts the XML-RPC server, registers the RPC handlers, 
	 * and begins listening for client requests.
	 * @param args Command-line arguments.  There should be one:
	 * the port number on which to listen for XML-RPC requests.
	 */
	public static void main(String[] args) {
		if (args.length != 1)
			printUsageAndExit();
		
		int port = -1;
		// Convert the command line argument to an integer,
		// then set the port number.
		try {
			port = Integer.parseInt(args[0]);
			Server.instance().setServerPort(port);
		} catch (NumberFormatException e) {
			System.err.println("Invalid port number: " + args[0]);
			System.exit(EXIT_ERROR);
		}

		System.out.println("Server: Using port " + port);
		
		// Start the server.
		Server.instance().run();
		
		System.out.println("Server: Waiting for client connections.");
		
		// The XML-RPC server is in its own thread, so the main thread
		// can just sleep until the runing flag is set to false, which 
		// happens when the server.shutdown RPC is called.
		while (Server.instance().isRunning() == true) {
			try {
				Thread.sleep(SLEEP_DELAY);
			} catch (InterruptedException e) {
				
			}
		}
		
		System.out.println("Server: Halted.");
		System.exit(0);
	}
}
