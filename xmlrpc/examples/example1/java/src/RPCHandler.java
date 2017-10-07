/**
 * This is the XML-RPC handler for the server.
 * Any public methods in this class can be called as XML-RPCs by clients.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */
public class RPCHandler {
	/**
	 * The server.add XML-RPC handler.  Converts the given strings to integers,
	 * adds them together, and returns the sum.  Throws an Exception if there 
	 * is an error converting the strings to integers.
	 * @param num1 The first number to add.
	 * @param num2 The second number to add.
	 * @return Returns the sum of the two given numbers.
	 * @throws NumberFormatException
	 */
	public Integer add(String num1, String num2) throws NumberFormatException {
		int firstInt;
		int secondInt;
		
		System.out.println("Server: Handling \"" + Server.ADD_RPC_NAME + "\" RPC.");
		
		// Try to convert the first string into an integer.
		// If num1 does not represent a valid integer, throw an exception.
		try {
			firstInt = Integer.parseInt(num1);
		} catch (NumberFormatException e) {
			String error = Server.ADD_RPC_NAME + ": \"" + num1 + "\" is not a valid integer.";
			System.err.println("Server: " + error);
			throw new NumberFormatException(error);
		}

		// Try to convert the second string into an integer.
		// If num2 does not represent a valid integer, throw an exception.
		try {
			secondInt = Integer.parseInt(num2);
		} catch (NumberFormatException e) {
			String error = Server.ADD_RPC_NAME + "server.add: \"" + num2 + "\" is not a valid integer.";
			System.err.println("Server: " + error);
			throw new NumberFormatException(error);
		}
		
		System.out.println("Server: Adding " + firstInt + " and " + secondInt + ".");
		// At this point, both integers are valid, so compute the sum.
		int sum = firstInt + secondInt;
		System.out.println("Server: Returning " + sum + ".");
		
		// Return the sum.
		return new Integer(sum);
	}
	
	/**
	 * Sets the server's running flag to false, causing it to halt.
	 * @return Always returns true.  (RPC handlers cannot be void)
	 */
	public boolean shutdown() {
		System.out.println("Server: Handling \"" + Server.SHUTDOWN_RPC_NAME + "\" RPC.");
		Server.instance().shutdown();
		// Note: All XML-RPC handlers must have a return value.
		return true;
	}
}
