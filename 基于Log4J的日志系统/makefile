make_dir:=$(shell pwd)
.PHONY:all
all:
	make clean;\
	mkdir build; \
	cd build; \
	cmake ..; \
	make;
.PHONY:clean	
clean:
	rm -rf build;\

.PHONY:run
run:
	make clean;\
	make;\
	source $(make_dir)/run.sh;

