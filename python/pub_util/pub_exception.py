
class BaseException(Exception):

    def __init__(self,v):
        self.v = v

    def __str__(self):
        return repr(self.v)



        

