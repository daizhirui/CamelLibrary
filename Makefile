all:
	cd src;\
	make;\
	cd ..

.PHONY:clean
clean:
	rm release/lib/*
	rm release/include/*
