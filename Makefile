obj-m += shattrd.o
CFLAGS_shattrd.o := -O0 -g

all: ## Build the kernel module
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean: ## Clean build artifacts
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: ## Load kernel module
	sudo insmod shattrd.ko

unload: ## Unload kernel module
	sudo rmmod shattrd

commands: ## Generate compile_commands.json using bear
	bear -- make -j$(nproc) all


.PHONY: help

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .+' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
