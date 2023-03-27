```bash
Usage: xdp [OPTIONS] FILE

Description:
    Display the contents of a file in hexadecimal format.

Options:
    -r   EXPR  Maximum number of bytes to read from the file (default: unlimited).
    -s   EXPR  Starting byte offset to read from (default: 0).
    -h         Show this help message
```

# Feartures
    - Fast
    - Arguments parsed as arithmetic expressions
    - Not so retarded memory management

# Install MacOs / Linux
```bash
$ export PATH=/usr/local/bin:$PATH
$ make && ln -s xdp "/usr/local/bin/xdp"

# For debug there is a builtin logging and memory tracking
# system and that you can enable by running
$ make g 
# or
$ make g2 #to enable ASAN as well
```