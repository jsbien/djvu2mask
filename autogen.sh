#!/bin/sh

# Ensure we're in the source directory
srcdir=$(dirname "$0")
test -n "$srcdir" && cd "$srcdir"

# Clean previous configuration
rm -f config.cache

# Run autoreconf to regenerate configure and other build files
autoreconf --force --install --verbose

# Run configure with the --prefix option to ensure relative paths
./configure --prefix=$PWD/build "$@"
