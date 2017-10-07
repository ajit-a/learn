import java.util.Date;

/**
 * This is the XML-RPC handler for the server.
 * Any public methods in this class can be called as XML-RPCs by clients.
 * @author James Baldassari (jdb@cs.wpi.edu)
 */
public class RPCHandler {
	/**
	 * The server.getDate XML-RPC handler.  It gets and returns the current date.
	 * @return Returns the current date.
	 */
	public Date getDate() {
		System.out.println("Server: Handling \"" + Server.DATE_RPC_NAME + "\" RPC.");
		
		Date now = new Date();
		System.out.println("Server: Returning " + now + ".");
		
		// Return the date;
		return now;
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
