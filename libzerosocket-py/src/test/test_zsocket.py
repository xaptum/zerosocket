'''
Created on Sep 2, 2014

@author: pradeepbarthur
'''
import socket
from zsocket import (zsocket,FileConfig)

def main():
    rsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    conf = FileConfig.FileConfig('sock.conf')
    
    sock = zsocket.zsocket(conf,rsock)
    sock.connect()
    sock.send("hello world")
    
    buf = sock.recv(4096)
    
    print "received : %s" % buf
    sock.close()

if __name__ == '__main__':
    main()