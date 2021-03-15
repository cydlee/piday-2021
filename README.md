# Pi Day 2021
Pi calculator in C to celebrate Pi Day 2021. Uses GMP library and the Bailey–Borwein–Plouffe formula to calculate pi.
It rounds the last digit and only goes up to 1 million digits of pi.

## Build (Ubuntu-based Linux distros):
Install GMP if you don't already have it: `sudo apt install libgmp-dev` <br />
Compile: `gcc pi.c -lgmp -o pi`

## Usage:
<code>
Usage: pi [OPTION]...<br/>
Calculates the value of pi (rounded).<br/>
<br/>
  -d \<digits\>    Specify the number of decimal places to calculate. Default is 10, maximum is 1000000.<br/>
      --help     Display this help message and exit.<br/>
</code>
