import socket
import time
import threading
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("",15002))

def listen():
	while True:
		data,addr=s.recvfrom(1024)
		filename='sendback.txt'
		with open(filename,mode='a') as file_obj:
			localtime=time.asctime(time.localtime(time.time()))
			file_obj.write(str(addr))
			file_obj.write(" ")
			file_obj.write(localtime)
			file_obj.write(" ")
			file_obj.write(data.decode("utf8","ignore"))
			file_obj.write("\n")


def send():
	while True:
		sr=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		b=input()
		b=str(b)
		iptable=["223.21.44.198","192.168.195.131"]
		for i in range(len(iptable)):
			sr.sendto(b.encode(),(iptable[i],15003))

def main():
	"""创建启动线程"""
	t_l = threading.Thread(target=listen, args=())
	t_l.start()

	t_s = threading.Thread(target=send, args=())
	t_s.start()

if __name__ == '__main__':
    main()