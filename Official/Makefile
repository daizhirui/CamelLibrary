all:
	cd src;\
	make;\
	cd ..;\
	cp lib/M2/*.a release/lib/M2;\
	cp lib/M2/entry.o release/lib/M2;\
	cp lib/M2/gdbentry.o release/lib/M2;\
	cp src/*.h release/include/M2

.PHONY:clean
clean:
	rm release/lib/M2/*
	rm release/include/M2/*
	rm lib/M2/*