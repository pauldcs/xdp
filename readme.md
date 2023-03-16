```bash
Usage: ./hdump [OPTIONS] FILE

Description:
  Display the contents of a file in hexadecimal format.

Options:
  --size=SIZE		Maximum number of bytes to read from the file (default: unlimited).
  --start=OFFSET	Starting byte offset to read from (default: 0).
  --end=OFFSET		Ending byte offset to read to (default: end of file).
  --raw			Output raw bytes in hexadecimal format, without formatting.

Arguments:
  FILE			The path to the file to be read.
```
