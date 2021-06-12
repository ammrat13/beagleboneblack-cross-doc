import os
import sys


# The file name to patch should be the first command line argument
# The output file name should be the second command line argument
INP = sys.argv[1]
OUT = sys.argv[2]
# The address at which the program will be loaded
# Third command line argument or default
LOAD_ADDR = 0x402f0400 if len(sys.argv) < 4 else int(sys.argv[3])


# Open the input and output files
with open(INP, 'rb') as inp, open(OUT, 'wb') as out:

    # Get input file len
    inp_len = os.fstat(inp.fileno()).st_size;

    # Write length and load address
    out.write(inp_len.to_bytes(4, 'little'))
    out.write(LOAD_ADDR.to_bytes(4, 'little'))

    # Copy the contents
    out.write(inp.read())
