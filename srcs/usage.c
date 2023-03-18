#include "libstringf.h"

void __usage(void)
{
	fputstr(1,
		"Usage: ./hdump [OPTIONS] FILE\n\n"
		"Description:\n"
		"    Display the contents of a file in hexadecimal format.\n\n"
		"Options:\n"
		"    --size=SIZE     Maximum number of bytes to read from the file (default: unlimited).\n"
		"    --start=OFFSET  Starting byte offset to read from (default: 0).\n"
		"    --end=OFFSET    Ending byte offset (default: end of file).\n"
		"    --raw           Output raw bytes in hexadecimal format, without formatting.\n\n"
		"Arguments:\n"
		"    FILE            The path to the file to be read.\n\n"
	);
}