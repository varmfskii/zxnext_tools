# zxnftp - ZX Next Server

A server which allows file operations between a computer and this ZX
Spectrum Next. Server commands are meant to be sent by a client, but
interaction is human readable.

- Commands

    - BD \<dir> - set baudrate on the ZX Next

    - CD \<dir> - change directory on ZX Next

    - DR \<drive> - change drive on ZX Next

    - GT \<file> => \<data> - copy file from ZX Next to client

    - ID => <id> - get server id
    
    - LS \<dir> => \<data> - get contents of directory on ZX Next

    - MD \<dir> - create directory on ZX Next

    - PD => \<data> - get current directory from ZX Next

    - PT \<file> \<= \<data> - copy file from client to ZX Next
      (unimplemented)

    - QU - kill server

    - RD \<dir> - delete directory on ZX Next

    - RM \<file> - delete file on ZX Next

    - XX - close session

- Responses

    - OK - No error

    - EX - File/directory exists

    - ID - Is a directory (should be a file)
    
    - N0 - Directory not empty

    - ND - Is not a directory
    
    - NE - File/directory does not exist

    - RR - Continue (intermediate command)

    - UK - Unrecognized command

    - XX - Unidentified error
    
Configuration is in a file produced by mkzxnftpcfg.py called
zxnftp.cfg. The server looks for the configuration file 1) in the
current directory, 2) in c:/sys/, and finally in /sys/ on the current
drive. The configuration file contains a set of commands for the
ESP8266 WiFi module which are simply executed on startup to configure
and start the server.
