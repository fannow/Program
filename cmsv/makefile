
.PHONY:all
all:
	mkdir build; \
	cd build; \
	cmake ..; \
	make; \
	cd main; \
	cp /home/linux/cmsv/build/cgi/cgi /home/linux/cmsv/webroot/;
.PHONY:clean	
clean:
	rm -rf build;\
	rm ./webroot/cgi;
