ALL: ascii_hex.o
	g++ ascii_hex.o -o ascii_hex

clean:
	rm -f ascii_hex.o ascii_hex
