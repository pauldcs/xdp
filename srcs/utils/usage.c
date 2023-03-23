#include "libs/libstringf.h"

void usage(void)
{
	fputstr(1,
		"Usage: ./hdump [OPTIONS] FILE\n\n"
		"Description:\n"
		"    Display the contents of a file in hexadecimal format.\n\n"
		"Options:\n"
		"    --range=EXPR    Maximum number of bytes to read from the file (default: unlimited).\n"
		"    --start=EXPR    Starting byte offset to read from (default: 0).\n"
		"    -h --help       Show this help message\n\n"
	);
}