

class ConnError(Exception):

    def __init__(self,v):
        self.v = "[Connection Error] " + v

    def __str__(self):
        return repr(self.v)
