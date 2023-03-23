#include "libs/libstringf.h"

void usage(void)
{
	fputstr(1,
		"Usage: ./xdp [OPTIONS] FILE\n\n"
		"Description:\n"
		"    Display the contents of a file in hexadecimal format.\n\n"
		"Options:\n"
		"    -r   --range  EXPR    Maximum number of bytes to read from the file (default: unlimited).\n"
		"    -s   --start  EXPR    Starting byte offset to read from (default: 0).\n"
		"    -str --string EXPR    Dump strings of size EXPR or more\n"
		"    -c   --color          Display the dump with colors\n"
		"    -h   --help           Show this help message\n\n"
	);
}