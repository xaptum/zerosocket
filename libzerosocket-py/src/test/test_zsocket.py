'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Sep 2, 2014
@author: pradeepbarthur
'''
import socket
import ssl
from zsocket import (zsocket,FileConfig)

def main():
    rsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    ssock = ssl.wrap_socket(rsock, cert_reqs=ssl.CERT_NONE)
    conf = FileConfig.FileConfig('sock.conf')
    
    sock = zsocket.zsocket(conf,ssock)
    sock.connect()
    sock.send("hello world")
    
    buf = sock.recv(4096)
    
    print "received : %s" % buf
    sock.close()

if __name__ == '__main__':
    main()