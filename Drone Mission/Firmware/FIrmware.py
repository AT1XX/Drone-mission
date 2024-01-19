import socket
import serial
import time

class Network:
    def __init__(self):
        self.net = None

    def connect(self):
        IP = "127.0.0.1"
        PORT = 2222
        if self.net is None:
            print("Connecting...")
            print(IP)
            print(PORT)
            self.net = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.net.bind((IP, PORT))
            print("Connection done")
    
    def killConnection(self):
        self.net.close()
        self.net = None

    def getPacket(self) -> str:
        if self.net is not None:
            return str(self.net.recvfrom(1024))
        return ""

if __name__ == "__main__":
    net = Network()
    net.connect()
    serialcomm = serial.Serial('COM4', 9600)
    serialcomm.timeout = 1
    while True:
        packet = net.getPacket()
        packet = packet.split("'")
        packet = packet[1]
        print(packet)
        if packet is not "":
            serialcomm.write(packet.encode())
            time.sleep(0.5)
            print(serialcomm.readline().decode('ascii'))
    serialcomm.close()
    
