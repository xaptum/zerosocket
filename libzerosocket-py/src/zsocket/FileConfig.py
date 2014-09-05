'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Aug 29, 2014
@author: pradeepbarthur
'''
import Config
import json
from zexceptions import (ZSError,ZSException)

class FileConfig(Config.Config):
    '''
    classdocs
    '''

    def __init__(self, filepath = None):
        '''
        Constructor
        '''
        super(FileConfig,self).__init__()
        if filepath is None:
            self._filepath = 'sock.conf'#'/etc/zeroconfig/sock.conf'
        else:
            self._filepath = filepath
            self.read()
        self.__dirty = False
    
    def __del__(self):
        '''
        Constructor
        '''
        self.close()

    def read(self):
        '''
        @summary: reads the configuration form file
        '''
        try:
            with open(self._filepath, 'r') as _file:
                jobj = json.load(_file)
                for key,value in jobj.iteritems():
                    self.set(key, value)
        except IOError as ioe:
            raise ZSError( "I/O error({0}): {1}".format(ioe.errno, ioe.strerror),ioe)
        except:
            raise ZSException( "Unexpected error:",ioe)
    
    def set(self,key,val):
        lval = super(FileConfig, self).get(key)
        if lval is None or lval != val:
            super(FileConfig, self).set(key,val)
            self.__dirty = True

    def write(self):
        '''
        @summary: write configuration to file
        '''
        try:
            with open(self._filepath, 'w') as _file:
                _file.write(str(self))
        except IOError as ioe:
            raise ZSError( "I/O error({0}): {1}".format(ioe.errno, ioe.strerror),ioe)
        except:
            raise ZSException( "Unexpected error:",ioe)

    def close(self):
        if self.__dirty:
            self.write()
        