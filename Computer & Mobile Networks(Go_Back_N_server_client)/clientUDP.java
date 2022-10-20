import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

public class clientUDP {
	
	//=================================================================================================
	//This part defines all variable required for setting up the client (server port set to 9876) 
	
	//Break the file into segments with size in byte
	public static final byte SEGMENTS_SIZE =8;

	// Probability of loss during packet sending (for testing package lost) 0 = no lost
	public static final double PROBABILITY = 0.3;

	// Window size - the number of udp packets allowed0 to send before STOP and WAIT for ACK
	public static final int WINDOW_SIZE = 5;
	
	//Time before resending non-ACKed packets within window
	public static final int TIMER = 20;
	
	//Location of the text file.
	public static final String FILE_PATH = "umbrellaData.txt";
	//==================================================================================================

	public static void main(String[] args) throws Exception{

		// Sequence number of the next packet sent
		byte nextSend = 0;
		
		// Sequence number of the next ACKpacket
		byte waitingForAck = 0;

		// Last packet sequence number
		int lastSeq;
		
		//String Variable  to store the data
		String dataTosend = null;
		
		//List to store all the packet that is sent, use for go back n
		ArrayList<byte []> sentPacket = new ArrayList<byte []>();

		//open the file and load all the data in to one long string 
		try {
		String file = FILE_PATH;
		dataTosend = new String( Files.readAllBytes(Paths.get(file)),StandardCharsets.UTF_8); 
		}
		catch (IOException e) {
            e.printStackTrace();
        }
		
	    // Calculate the last packet sequence number
		
		lastSeq =  (byte) Math.ceil( (double) dataTosend.length() / SEGMENTS_SIZE);
		
		//System.out.println("Number of packets to send: " + lastSeq);
		
		//Create Socket
		DatagramSocket toServer = new DatagramSocket();
		
		// Server address
		InetAddress serverAddres  = InetAddress.getByName(args[0]);
		
		//Server port
		int portServer = -1;
        try {
            // Parse the string argument into an integer value.
        	portServer = Integer.parseInt(args[1]);
        }
        catch (NumberFormatException nfe) {
            //port must be a number
            System.out.println("Port must be a int.");
            System.exit(1);
        }

		
		
		while(true){
			/*==============================================================================
			 * Sending loop
			 * 
			 * //This while loop will send up to the WINDOW size worth of packets wait and
			 * wait for ACK before //moving the window forward until all the data are sent
			 */
			while(nextSend - waitingForAck < WINDOW_SIZE && nextSend < lastSeq){

				// Byte array to store part of the data to send
				byte[] filePacketBytes = new byte[SEGMENTS_SIZE];
				
				// Copy segment of data bytes to array
				filePacketBytes = Arrays.copyOfRange(dataTosend.getBytes(), nextSend*SEGMENTS_SIZE,
						nextSend*SEGMENTS_SIZE + SEGMENTS_SIZE);
				
				
				// Create byte array to store each segment, the extra byte(first) is for the sequencing number
				byte[] segment = new byte[SEGMENTS_SIZE+1];
				
				//put the S.N. into the first byte and copy the data segments to fill up the byte array
				segment[0] = nextSend;  
				System.arraycopy(filePacketBytes, 0, segment , 1, filePacketBytes.length);
				
				//create the data packet
				DatagramPacket packet = new DatagramPacket(segment , segment.length, serverAddres, portServer);	
				
				// Add packet to the sent list
				sentPacket.add(segment);
				
				// Send with some probability of loss (for testing)
				if(Math.random() > PROBABILITY){
					System.out.println("Sending "+ segment[0]);
					toServer.send(packet);
				}else{
					System.out.println("Packet lost S.N. =  " + nextSend);
				}
				
				//move to the next segment
				nextSend++; 
			
			}
			//========================End of the send part ===================================
			
			/*
			 * =============================================================================
			 * This part handle the go back n
			 * =============================================================================
			 */
			
			// Byte array to get ACK  from the receiver
			byte[] ackBytes = new byte[4];
			
			// Creating packet for the ACK
			DatagramPacket ack = new DatagramPacket(ackBytes, ackBytes.length);
			
			try{
				// If no ACK after TIMER throw timeoutException
				toServer.setSoTimeout(TIMER);
				
				// Receive the packet
				toServer.receive(ack);
				
				System.out.println("Received ACK for " + ackBytes[0]);
				
				
				// If ack byte is for the last packet, stop the client
				if(ackBytes[0] >= lastSeq-1){
					toServer.close();
					break;
				}

				//Update the not acked byte as new ACK comes in 
				if (waitingForAck <= ackBytes[0]) {
				//if the ack is bigger than what we waiting for set the the next wait for
				//byte to the ack waitingForAck = (byte) +1  
					waitingForAck = (byte) (Math.max(waitingForAck, ackBytes[0])+1);
				}

			}catch(SocketTimeoutException e){
				//If ACK time out, send all the non-acked packets again
				
				for(int i = waitingForAck; i < nextSend; i++){

					// get the stored packet in byte array
					byte[] sendData = (sentPacket.get(i));

					// Create the packet
					DatagramPacket packet = new DatagramPacket(sendData, sendData.length, serverAddres, portServer );
					
					// Send it again with some probability(testing)
					if(Math.random() > PROBABILITY){
						System.out.println("Resending packet S.N. " + sentPacket.get(i)[0] +  " and size " +
									        sendData.length + " bytes");
						toServer.send(packet);		
					}else{
						System.out.println("Lost packet S.N. = " + sentPacket.get(i)[0]);
					}
				}
			}
			
		}
		System.out.println("Finished transmission");
	}

}
