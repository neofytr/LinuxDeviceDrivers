obj-m = jiff.o  # The obj-m variable is used by the kernel build system to specify modules to be built.
# The kernel build system automatically handles the compilation of .c files into .o files.
# To build a module, add its corresponding .c file to the obj-m variable using the .o extension.

PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build
BINARY_DIR := $(PWD)/binaries

default:
	mkdir -p $(BINARY_DIR)
	make -C $(KDIR) M=$(PWD) modules
	mv $(PWD)/*.ko $(PWD)/*.o $(PWD)/*.mod* $(PWD)/.*.cmd $(PWD)/Module.symvers $(PWD)/modules.order $(BINARY_DIR)/ 2>/dev/null || true

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf $(BINARY_DIR)

transfer:
	multipass transfer -r ~/Desktop/LinuxDeviceDrivers/* primary:/home/ubuntu/Driver/