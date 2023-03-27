#!/bin/bash

set -x -e
make && ln -s xdp "/usr/local/bin/xdp"