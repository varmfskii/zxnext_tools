# ZXNFTP

ZXNFTP is a client/server pair for transferring files between a
computer (client) and a ZX Spectrum Next (server) inspired by the long
standing FTP protocol. It was created to simplify moving files between
a development machine and a ZX Spectrum Next target machine to speed
up development cycles. 

Configure with mkzxnftpcfg.py

For server end, configuration file, zxnftp.cfg, must be in teh current
directory when the program starts (this will change somewhat one I
decide which locations are best for the configuration file). For the
client end, the configuration file is with zxnftp.conf in the current
directory, .zxnftprc in $HOME, or /etc/zxnftp.conf

