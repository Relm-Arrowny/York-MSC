import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.util.Arrays;
import java.io.*;
public class ServerUDP {
	
	//Randomly pretend to lose package
	private static final double PROBABILITY = 0.3;
	
	//Server will shut down after fix number of time out,
	// if SHUTDOWN_COUNTER is < 0 it will never close!!  
	private static final int SHUTDOWN_COUNTER = 2;

	//Server Time out
	private static final int TIME_OUT = 8000;
	//Server Port 
	private static final int SERVER_PORT = 9876;
	
	
	public static void main(String[] args) throws Exception{
		//Create data socket with port
		DatagramSocket serverSocket = new DatagramSocket(SERVER_PORT);
		serverSocket.setSoTimeout(TIME_OUT);
		int timeOutCounter = 0;
		//  Set The array to store data 
		byte[] receivedData = new byte[1024];
		byte[] ackReply = " ACK".getBytes();
		//
		DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
		int clientPort;
		InetAddress clientIPAddress;
		//set wait for Sequence number
		byte waitForSeq = 0;
		//last Acked
		byte lastAck = -1;
		
		String storedData = "";
		
		
		//Flag to end server 
		boolean end = false;
		
		//loop to keep the server listening and process data
		while(!end){
			System.out.println("Waiting for packet");
			
			// Receive packet
			try {
				serverSocket.receive(receivedPacket);

				//extract the data
				receivedData = receivedPacket.getData();
				//The first byte is Sequence number
				byte seq = receivedData [0];

				
				String dataStr = new String(Arrays.copyOfRange(receivedData, 1, receivedPacket.getLength()));
				
				clientIPAddress = receivedPacket.getAddress();
				clientPort = receivedPacket.getPort();
				/*=================================================================================
				//This part handle the go back n 
				====================================================================================
				*/
				
				//When the expected packet arrived
				if(seq == waitForSeq){
					lastAck = waitForSeq;
					waitForSeq++; 
					//append the data
					storedData = storedData + dataStr;
					clientPort = receivedPacket.getPort();
					//System.out.println("Packed stored in buffer");
								
					
					System.out.printf("SN : %d Data : %s\nData receved so far : %s\n\n", seq, dataStr, storedData);
					
					ackReply[0] =  seq;
					
					DatagramPacket sendPacket = new DatagramPacket(ackReply,
							ackReply.length, clientIPAddress, clientPort);
					
					// Send ACK but with a chance of skipping  ACK to similar lost ACK
					if(Math.random() > PROBABILITY){
						System.out.println("Ack with sequence number " + ackReply[0] );
						serverSocket.send(sendPacket);
						
					}else{
						System.out.println("Lost ack with sequence number " + seq);
					}
					
				}
				//Drop the packet if it is not expected
				else{
					//Send the last in sequence ACK 
					
					ackReply[0] =  (byte) (lastAck);
					DatagramPacket sendPacket = new DatagramPacket(ackReply,
							ackReply.length, clientIPAddress, clientPort);
					if(Math.random() > PROBABILITY){
						serverSocket.send(sendPacket);
					}
					System.out.println("Packet discarded (not in order)");
				}
			}			
			catch (SocketTimeoutException e) {
	            // timeout exception.
	            System.out.println("Timeout reached!!! Server resetting\n final data : " + storedData);
	            
	            waitForSeq = 0;
	            lastAck = -1;
	    		storedData = "";
	    		//This part will shut down the server if maximum number of time out is reached 
	    		timeOutCounter++;
	    		if (timeOutCounter > SHUTDOWN_COUNTER  && SHUTDOWN_COUNTER  > 0) {
	            	serverSocket.close();
	            	System.out.println("Closing server.");
	            	break;
	            }
	            
	        }
					
		}

	}
	
}
