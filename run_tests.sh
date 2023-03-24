#!/bin/bash

set -x -e
make prod
(cd tests && ./tester.sh)