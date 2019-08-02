# ZXNFTP

- Description

ZXNFTP is a client/server pair for transferring files between a
computer (client) and a ZX Spectrum Next (server) inspired by the long
standing FTP protocol. It was created to simplify moving files between
a development machine and a ZX Spectrum Next target machine to speed
up development cycles. 

- Usage

Configure with mkzxnftpcfg.py

For server end, configuration file, zxnftp.cfg, must be in teh current
directory when the program starts (this will change somewhat one I
decide which locations are best for the configuration file). For the
client end, the configuration file is with zxnftp.conf in the current
directory, .zxnftprc in $HOME, or /etc/zxnftp.conf

- Notes

The protocol used for ZXNFTP is designed to be as dependable as
possible when commmunicating with the ZX Spectrum Next through an
ESP8266 and the builtin UART. In particular the protocol is designed
to avoid potential buffer overflows in the UART. This is accomplished
by having a fully synchronous protocol that involved blocks that,
including the overhead of the signaling prefix, will be no larger than
the 512 byte UART buffer. In addition, the server is set up to only
serve a single connection at a time and anything linked to a
connection other than connection 0 is ignored.