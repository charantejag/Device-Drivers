
obj-m := harshassg.o

KERNEL_DIR = /usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(shell pwd)
	
app: 
	gcc -o user_app user_app.c

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~
