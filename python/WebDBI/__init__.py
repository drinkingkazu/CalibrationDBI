from colored_msg import info,error
try:
    from ROOT import lariov
except ImportError:
    error("Failed to import WebInterface package")
    
