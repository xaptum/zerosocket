'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Jul 27, 2014
@author: pradeepbarthur
'''
import FileConfig
import zerosocket


class zsocket(object):
    '''
    @version: 1.0
    @contact: pradeep@xaptum.com
    @summary: zsocket is a wrapper class for socket or ssl class object.
                implements an interface pattern inorder to detect and extract zero socket header
                
     
    private members:
    __sock : zerosocket
    __conf : [fileconfig] type config
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
            self.__zsock.socket('TLS')
        else:
            self.__zsock = zerosocket.zerosocket(self.__conf)
            self.__zsock.setSocket(sock)


    def __del__(self):
        '''
        Destructor
        '''
    
    def bind(self,address):
        '''
        '''
        self.__zsock.bind(address)
    
    def accept(self):
        '''
        '''
        self.__zsock.accept()
    
    def listen(self,backlog):
        '''
        '''
        self.__zsock.listen(backlog)
        
    def connect(self,address = None):
        '''
        @param address: requires a 2-Tuple (ip-address,port-number), optionally the address is picked up from conf
        '''
        return self.__zsock.connect(address)
    
    def recv(self,bufsize,flags = 0):
        '''
        @param bufsize: 
        @param flags:  
        '''
        return self.__zsock.recv(bufsize,flags)
        
    def recvfrom(self, bufsize,flags = 0):
        '''
        @param bufsize: 
        @param flags: 
        '''
        return self.__zsock.recvfrom(bufsize,flags)

    def recv_into(self, buff , nbytes = None, flags = 0):
        '''
        @param buff: type buffer
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
