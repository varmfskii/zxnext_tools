#include "zxnftp.h"

command commands[]=
  {
   { "?", cmd_help, "? [<cmd>]",
     "a synonym for help (see help help)\n" },
   { "baud", cmd_baud, "baud <bps>",
     "Set the baud rate on the server's UART and ESP8266\n" },
   { "cat", cmd_cat, "cat <file>",
     "display the file on the server named <file> on the client\n" },
   { "cd", cmd_cd, "cd <dir>",
     "change the current working directory on the server to <dir>\n" },
   { "dir", cmd_dir, "dir [<dir>]" ,
     "show an extended file listing on the client\n\n"
     "If there are no parameters, it will show the fles in the server's"
     "current working directory\n\nOtherwise it will show the contents of"
     "the server's indicated directory.\n" },
   { "exit", cmd_exit, "exit",
     "Terminate the client leaving the server running\n" },
   { "get", cmd_get, "get <file> [<file>]", 
     "copies a file from the server to the client\n\n"
     "If there is only one <file> it is the name of both the source and the "
     "destination.\n\nIf there are two files, the first is the source file "
     "on the server and the second is the destination file on the "
     "client.\n\nIf the destination file already exists, it will be"
     "overwritten\n" },
   { "help", cmd_help, "help [<cmd>]",
     "Display online help\n\n"
     "If no parameters are given, show a simple summary of the commands and"
     "their syntax\n\nIf a <cmd> is given, show extended help for that"
     "command\n" },
   { "lcd", cmd_lcd, "lcd <dir>",
     "change the current working on the client to <dir>\n" },
   { "ls", cmd_ls, "ls [<dir>]",
     "show a simple file listing (file names only) on the client\n\n"
     "If there are no parameters, it will show the fles in the server's"
     "current working directory\n\nOtherwise it will show the contents of"
     "the server's indicated directory.\n" },
   { "mget", cmd_mget, "mget <patt> [<patt> ...]",
     "Unimplemented\n"
     "Copy all files matching the given patterns from the server to the"
     "client\n" },
   { "mkdir", cmd_mkdir, "mkdir <dir>",
     "Create a directory named <dir> on the server\n" },
   { "mput", cmd_mput, "mput <patt> [<patt> ...]",
     "Unimplemented\n"
     "Copy all files matching the given patterns from the client to the"
     "server\n" },
   { "put", cmd_put, "put <file>", 
     "copies a file from the client to the server\n\n"
     "If there is only one <file> it is the name of both the source and the "
     "destination.\n\nIf there are two files, the first is the source file "
     "on the client and the second is the destination file on the "
     "server.\n\nIf the destination file already exists, it will not be"
     "overwritten\n" },
   { "pwd", cmd_pwd, "pwd",
     "Display the server's current working directory\n" },
   { "quit", cmd_quit, "quit",
     "Terminate the client and the server\n" },
   { "rm", cmd_rm, "rm <file>",
     "Delete the file <file> on the server\n" },
   { "rmdir", cmd_rmdir, "rmdir <dir>",
     "Delete the directory <dir> on the server\n\n"
     "This will not delete non-empty directories\n"},
   { "script", cmd_script, "script <file>",
     "Execute a script for zxnftp commands\n"},
   { NULL, NULL, NULL, NULL }
};

		     
