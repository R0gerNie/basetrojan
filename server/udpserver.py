import socket
import time
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("",15002))
while True:
	data,addr=s.recvfrom(1024)
	filename='sendback.txt'

	with open(filename,mode='a') as file_obj:
		localtime=time.asctime(time.localtime(time.time()))
		file_obj.write(localtime)
		file_obj.write(" ")
		file_obj.write(str(addr))
		file_obj.write(" ")
		file_obj.write(data.decode())
		file_obj.write("\n")

