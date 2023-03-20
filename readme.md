```bash
Usage: ./hdump [OPTIONS] FILE

Description:
  Display the contents of a file in hexadecimal format.

Options:
  --size=SIZE     Maximum number of bytes to read from the file (default: unlimited).
  --start=OFFSET  Starting byte offset to read from (default: 0).
  --string=SIZE   Display strings longer than SIZE.
  -r --raw        Output raw bytes in hexadecimal format, without formatting.
  -c --color      Enable color output
  -h --help       Show this help message
  -               Read file from stdin

```
