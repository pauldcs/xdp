# XDP - a nice hexdump
This is my go to hexdump, the `-c` option shows helpful colors and makes reading much easier.
the offset option `-o` also supports arithmetic expressions, eg. `-o '0x200 * (0x7 + 4)'`.

xdp is also extremely fast

```
usage: xdp [-hncs] [-o offset] [-n length] ... [file] ...

description:
    touch the very fabric of creation itself, follow the
    darkest depths and wield a power that few can comprehend

options:
    -n  EXPR  the range of bytes to read from the file (default: until EOF)
    -o  EXPR  starting byte offset to read from (default: 0)
    -s        dump strings at least 4 characters long
    -c        enable colored output
    -r        dump as a stream of hex characters
    -h        show this help message
```