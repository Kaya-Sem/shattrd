obj-m += shattrd.o
CFLAGS_shattrd.o := -O0 -g

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load:
	sudo insmod shattrd.ko

unload:
	sudo rmmod shattrd

compile_commands.json:
	bear -- make -j$(nproc) all
