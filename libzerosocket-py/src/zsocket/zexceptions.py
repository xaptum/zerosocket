'''
@copyright: Copyright (C) 2014-2014 Zero Socket
@license: http://www.gnu.org/licenses/gpl.html GPL version 2

Created on Aug 29, 2014
@author: pradeepbarthur
'''

class ZSError(Exception):
    pass
    def __init__( self, why , exception = None):
        self.why = why
        self.origin = exception
        Exception.__init__(self, 'Zero Socket Library Error : %s' % why)

    def __str__(self):
        if self.origin is None:
            return ': '.join(self.args)
        else:
            
            return ': '.join(self.args)+"\n because: ".join(self.origin.args)

class ZSException(Exception):
    pass
    def __init__( self, why, exception = None):
        self.why = why
        self.origin = exception
        Exception.__init__(self, 'Zero Socket Library Error : %s' % why)

    def __str__(self):
        if self.origin is None:
            return ': '.join(self.args)
        else:
            
            return ': '.join(self.args)+"\n because: ".join(self.origin.args)