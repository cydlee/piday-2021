# Pi Day 2021
Pi calculator in C to celebrate Pi Day 2021. Uses GMP library and the Bailey–Borwein–Plouffe formula to calculate pi.
It rounds the last digit and only goes up to 1 million digits of pi.

## Build (Ubuntu-based Linux distros):
Install GMP if you don't already have it: `sudo apt install libgmp-dev` <br />
Compile: `gcc pi.c -lgmp -o pi`

## Usage:
`./pi -d [DIGITS]`    Calculates pi to a precision of [DIGITS]. <br />
Currently, there is no `--help` option (may add in the future).
