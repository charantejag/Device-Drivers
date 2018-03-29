obj-m := debdrive.o
KERNEL_DIR = /usr/src/linux-headers-$(shell uname -r)
all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
	gcc -w -o user_app1 -pthread user_app1.c
	gcc -w -o user_app2 -pthread user_app2.c
	gcc -w -o user_app3 -pthread user_app3.c
	gcc -w -o user_app4 -pthread user_app4.c
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~
user_app:
	gcc -w -o user_app1 -pthread user_app1.c
	gcc -w -o user_app2 -pthread user_app2.c
	gcc -w -o user_app3 -pthread user_app3.c
	gcc -w -o user_app4 -pthread user_app4.c
