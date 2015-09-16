all:
	cd src && make
	cp src/arb bin/arb

clear:
	cd src && make clear

mrproper: clear
	rm -f bin/arb

install:
	cp bin/arb /usr/bin/arb
	cp bin/3dshow.py /usr/bin/3dshow.py
	cp doc/arb.man /usr/share/man/man1/arb.1

uninstall:
	rm -f /usr/bin/arb /usr/bin/3dshow.py /usr/share/man/man1/arb.1
