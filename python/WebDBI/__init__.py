from colored_msg import info,error
try:
    from ROOT import webdb
except ImportError:
    error("Failed to import WebInterface package")
    
