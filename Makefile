DIRS = atomic boot fileFD fileflags FileSharing lseek syncio terminal_size bufferIO\
	MP0

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
	cd lib && $(MAKE) clean || exit 1;
