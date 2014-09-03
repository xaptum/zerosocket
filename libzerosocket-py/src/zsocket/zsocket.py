'''
Created on Jul 27, 2014

@author: pradeepbarthur
'''
import FileConfig
import zerosocket
from zexceptions import ZSError, ZSException


class zsocket(object):
    '''
    members:
    _sock : zerosocket
    conf : [fileconfig] type config
    '''

    def __init__(self, conf = None, sock = None):
        '''
        Constructor
        '''
        if conf is None:
            self.__conf = FileConfig()
        else:
            self.__conf = conf
        
        if sock is None:
            self.__zsock = zerosocket.zerosocket(self.__conf)
            self.__zsock.socket('TCP')
        else:
            self.__zsock = zerosocket.zerosocket(self.__conf)
            self.__zsock.setSocket(sock)


    def __del__(self):
        '''
        Destructor
        '''
        
    def connect(self,address = None):
        '''
        @param address: requires a 2-Tuple (ip-address,port-number), optionally the address is picked up from conf
        '''
        return self.__zsock.connect(address)
    
    def recv(self,bufsize,flags = 0):
        '''
        
        '''
        return self.__zsock.recv(bufsize,flags)
        
    def recvfrom(self, bufsize,flags = 0):
        '''
        '''
        return self.__zsock.recvfrom(bufsize,flags)

    def recv_into(self, buff , nbytes = None, flags = 0):
        '''
        buff: type buffer
        '''
        return self.__zsock.recv_into(buff,nbytes,flags)
        
    def send(self, string , flags = 0):
        '''
        '''
        return self.__zsock.send(string,flags)
        
    def sendall(self, string, flags = 0):
        '''
        '''
        return self.__zsock.sendall(string,flags)
        
    def sendto(self, string, flags, address = 0):
        '''
        if (address is None):
            def sendto(self, string, address):
        '''
        return self.__zsock.sendto(string,flags,address)
    
    def shutdown(self,how):
        '''
        @param how: 
        '''
        return self.__zsock.shutdown(how)

    def close(self):
        self.__zsock.close()
