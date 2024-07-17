import socket
import struct

def send_spoofed_packet(src_ip, dst_ip, port, data):
    # Creazione della socket raw
    raw_sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_RAW)

    # Costruzione dell'intestazione IP
    ip_header = struct.pack("!BBHHHBBH4s4s",
        0x45,   # Versione (4) e lunghezza dell'intestazione (5)
        0,      # TOS - Type of Service
        0,      # Lunghezza totale
        0,      # ID pacchetto
        0x4000, # Flags e posizione fragment
        255,    # TTL
        socket.IPPROTO_UDP, # Protocollo
        0,      # Checksum (inizializzato a zero)
        socket.inet_aton(src_ip), # Indirizzo IP sorgente falso
        socket.inet_aton(dst_ip)  # Indirizzo IP destinazione
    )

    # Costruzione del pacchetto (intestazione IP + dati)
    packet = ip_header + data

    # Invio del pacchetto
    raw_sock.sendto(packet, (dst_ip, port))
    
    
from scapy.all import *

# Imposta l'indirizzo IP sorgente (spoofato) e la porta sorgente
src_ip = "192.168.1.2"
src_port = 1234

# Imposta l'indirizzo IP di destinazione e la porta di destinazione
dst_ip = "127.0.0.1"
dst_port = 1234

# Crea il pacchetto IP con indirizzi IP sorgente e destinazione
ip = IP(src=src_ip, dst=dst_ip)

# Crea il pacchetto TCP con porte sorgente e destinazione
tcp = TCP(sport=src_port, dport=dst_port)

# Combina i pacchetti IP e TCP
packet = ip / tcp

# Invia il pacchetto spoofato
send(packet)





def main():
    
    #mock my ip address
    


    # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # s.connect(('localhost', 1234))

    # Utilizzo della funzione per inviare un pacchetto contraffatto
    send_spoofed_packet("1.2.3.4", "127.0.0.1", 1234, b'Hello, world')
    
    # data = s.recv(1024)
    
    # print(data)
    
    # s.close()

if __name__ == '__main__':
    pass
    # main()  