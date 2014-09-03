'''
Created on Aug 29, 2014

@author: pradeepbarthur
'''

class ZSError(Exception):
    pass
    def __init__( self, why ):
        self.why = why
        Exception.__init__(self, 'Zero Socket Library Error : %s' % why)


class ZSException(Exception):
    pass
    def __init__( self, why ):
        self.why = why
        Exception.__init__(self, 'Zero Socket Library Error : %s' % why)