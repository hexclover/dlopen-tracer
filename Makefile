CFLAGS += -Wall -fPIC -shared
LDFLAGS += -ldl

.PHONY: clean all

all: dltracer.so
dltracer.so: dltracer.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
clean:
	rm -f *.o *.so
