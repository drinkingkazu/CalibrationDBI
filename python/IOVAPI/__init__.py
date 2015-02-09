from colored_msg import error
try:
    from IOVAPI import IOVDB, IOVFolder, IOVSnapshot, IOVCache
except ImportError:
    error('Failed to import IOVAPI module...')
    raise
