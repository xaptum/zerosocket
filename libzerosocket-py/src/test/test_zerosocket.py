'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Sep 2, 2014
@author: pradeepbarthur
'''
from zsocket import (FileConfig,zerosocket)

def main():
    print ('starting zerosocket test')
    conf = FileConfig.FileConfig('sock.conf')
    
    zsock = zerosocket.zerosocket(conf)
    zsock.socket('TCP')
    zsock.connect()
    
    zsock.send("test")
    
    buf = zsock.recv(10000)
    print ("buff:'%s'" % buf);
    zsock.close()
    
if __name__ == '__main__':
    main()