'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Aug 29, 2014
@author: pradeepbarthur
'''
import json
import socket
from zexceptions import ZSException


class Config(object):
    '''
    _conf : config member
    '''
    def __init__(self):
        '''
        @summary: default constructor,
        @param: none taken
        '''
        self._conf = dict()
    
    def __del__(self):
        '''
        @summary: deletes all objects and closes the derived object
        '''

    def __str__(self):
        '''
        @summary: to string method
        @return: 
        '''
        return json.dumps(self._conf, separators=(',',':'))

    
    def __repr__(self):
        '''
        @return: 
        '''
        return '{config:"' + self.__str__() + '"}'
    
    keys = {
            'ZUNK' : 0,
            'ZVER' : 1,
            'ZUSR' : 2,
            'ZPAS' : 3,
            'ZTOK' : 4,
            'ZDAT' : 5,
            'ZDID' : 6,
            'ZMET' : 7,
            'ZADR' : 8,
            'ZPRT' : 9,
            'ZORG' : 10,
            'ZDST' : 11
            }
    
    def get(self,key):
        '''
        @summary: 
        @raise ZSException: will throw an exception if key was not valid
        @return: value given a key, if key not found None is returned
        '''        
        if self.keys.get(key, 0) > 0:
            return self._conf.get(key)
        else:
            raise ZSException('Invalid key %s' % key)

    def set(self,key,val):
        '''
        @summary: 
        @return: returns bool , true if the value was set, else false
        '''
        if self.keys.get(key, 0) > 0:
            self._conf[key] = val
        else:
            raise ZSException('Invalid key %s' % key)

    def getaddress(self):
        '''
        @return: a 2-tuple (ip-address,port-number)
        '''
        ip=socket.gethostbyname(self.get('ZADR'))
        #return socket.getaddrinfo(self.get('ZADR'), int(self.get('ZPRT')), 0, 0, socket.SOL_TCP)
        return (ip,int(self.get('ZPRT')))
        