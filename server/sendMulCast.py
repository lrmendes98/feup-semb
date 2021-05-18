import socket
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("id", type=str)
parser.add_argument("state", type=str)
args = parser.parse_args()
id = args.id
state = args.state
space = " "

MCAST_GRP = '239.0.0.1'
MCAST_PORT = 4444
MESSAGE = bytearray((id+space+state).encode())

MULTICAST_TTL = 1

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, MULTICAST_TTL)

sock.sendto(MESSAGE, (MCAST_GRP, MCAST_PORT))

print("Packet sent")