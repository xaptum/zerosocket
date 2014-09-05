'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Aug 29, 2014
@author: pradeepbarthur
'''
import socket
import ssl
import re
from zsocket import (FileConfig)

def main():
    print ('starting Config test')
    conf = FileConfig.FileConfig()
    conf.set('ZUSR', 'username')
    conf.set('ZPAS', 'password')
    conf.set('ZTOK', 'token')
    conf.set('ZDST', 'destination')
    conf.set('ZORG', 'origination')
    
    print (' ZUSR : %s\n' % conf.get('ZUSR'))
    print (' ZPAS : %s\n' % conf.get('ZPAS'))
    print (' ZTOK : %s\n' % conf.get('ZTOK'))
    
    print ('full object : %s\n' % conf)
    __starthdr_pat_ = re.compile('^\s*\{')
    __endhdr_pat_ = re.compile('^\s*\{.*\}\s*;')
    data = '  { "ZADR":"test 123" } ; more data here'

    if __starthdr_pat_.match(data):
        match = __endhdr_pat_.match(data)
        if match:
            print ('I found zero socket header')
            print ('header  :' + match.group(0))
            print ('payload :' + data[match.end():] )
            #print ('payload :' + "".join(__endhdr_pat_.split(data)) )
        else:
            print ('zero socket header started, more data required to parse the whole header')
    else:
        print ('zero socket header not found')
    
    '''
    sock = socket.socket(socket.SOCK_STREAM)
    
    sock = ssl.wrap_socket(sock, cert_reqs=ssl.CERT_NONE)
    
    sock = zsocket.zsocket(sock)
    
    sock.connect("127.0.0.1")
    sock.send("test")
    '''
    
if __name__ == '__main__':main()