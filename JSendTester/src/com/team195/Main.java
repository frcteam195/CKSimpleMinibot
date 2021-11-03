package com.team195;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.*;

public class Main {
    static boolean runThread = true;
    static String targetAddress = "10.0.2.22";
    static DatagramSocket udpSocket;
    static SocketAddress udpSocketAddr;

    public static void main(String[] args) throws Exception {
        udpSocket = new DatagramSocket();
        udpSocketAddr = new InetSocketAddress(targetAddress, 5809);

        Thread t = new Thread(() -> {
            ByteArrayOutputStream baos = new ByteArrayOutputStream(12);
            DataOutputStream dos = new DataOutputStream(baos);
            while (runThread)
            {
                try {
                    baos.reset();
                    dos.writeInt(0x00000001);   //API ID
                    dos.writeFloat(0.2f);   //Left Motor
                    dos.writeFloat(0.2f);   //Right Motor
                    DatagramPacket pack = new DatagramPacket(baos.toByteArray(), 0, baos.size(), udpSocketAddr);
                    udpSocket.send(pack);

                    Thread.sleep(100);
                }
                catch (Exception ex)
                {
                    ex.printStackTrace();
                }
            }
        });
        System.out.println("Starting JTestSend, targeting " + targetAddress);
        t.start();
        System.out.println("Press enter to exit...");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        br.readLine();
        System.out.println("Shutting down services... Please wait...");
        runThread = false;
        t.join(5000);
        System.exit(0);
    }
}
