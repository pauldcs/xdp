#!/bin/bash

grep \
    -nr                      \
    --color=auto              \
    --exclude-dir={.git,.svn} \
    --include \*".c"          \
    -e "\\<\(free\|malloc\|strdup\|strndup\|realloc\|calloc\|mmap\|munmap\|asprintf\|open\|dup\|dup2\|close\|opendir\|closedir\)\>" "$@" . 2>/dev/null \
        ||  {
                [[ $? -eq 1 ]]                          \
                    && >&2 printf " - OK \n" \
                    || >&2 printf " + Grep returned %d\n" $?
            }