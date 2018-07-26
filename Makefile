
win:
	bash get-headers.sh
	cd src && make all ARCH=x86 -f Makefile.win

win-64:
	bash get-headers.sh
	cd src && make all ARCH=x86_64 -f Makefile.win

clean:
	rm -f ld64 ld64.exe *.bc *.o src/*.o src/ld/*.o src/ld/parsers/*.o src/ld/parsers/libunwind/*.o src/ld/passes/*.o src/ld/passes/stubs/*.o ../md5/*.o ../libgw32c/*.o xplatform-hacks/*.o src/other/*.o
	#rm -rf osxinclude
