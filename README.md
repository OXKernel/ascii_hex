# ascii\_hex
C++ Conversion tool to convert binaries to ascii\_hex and back.

# Usage
## ascii\_hex -e filename # Generate ascii hex encoded data.
## ascii\_hex -d filename.ahex # Generate decoded ascii hex data.

# Purpose
Another way to convert binaries into ascii.
It's similar to base64, except it doesn't grab 6 bits
at a time, it graps a byte and splits it into two 4 bit
characters which it then encodes using the ascii equivalent 
of the hex value.

# Pros
Simple to implement and very fast.

# Cons
Expands data to 2x the original size always.

But, this data can be compressed nicely, almost to
the same compression size that the original data compresses to.

