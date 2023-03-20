#include "libstringf.h"

void __usage(void)
{
	fputstr(1,
		"Usage: ./hdump [OPTIONS] FILE\n\n"
		"Description:\n"
		"    Display the contents of a file in hexadecimal format.\n\n"
		"Options:\n"
		"    -               Read file from stdin\n"
		"    --size=EXPR     Maximum number of bytes to read from the file (default: unlimited).\n"
		"    --start=EXPR    Starting byte offset to read from (default: 0).\n"
		"    --string=EXPR   Display strings longer than SIZE.\n"
		"    -r --raw        Output raw bytes in hexadecimal format, without formatting.\n"
		"    -c --color      Enable color output\n"
		"    -h --help       Show this help message\n\n"
	);
}