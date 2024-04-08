.PHONY: all proto examples test install deps clean

default: all

all: 
	@$(MAKE) -f make_base.mk

proto:
	@$(MAKE) -C internal
	@echo -e "\033[32m\nBuilt Proto Successfully\n\033[0m"

examples:
	@$(MAKE) -C examples/get
	@$(MAKE) -C examples/pullkvs
	@$(MAKE) -C examples/watch
	@echo -e "\033[32m\nBuilt Examples Successfully\n\033[0m"

test:
	@$(MAKE) -C test
	@echo -e "\033[32m\nBuilt Test Successfully\n\033[0m"

install:
	@$(MAKE) install -f make_base.mk
	@echo -e "\033[32m\nInstalled bscp-cpp-sdk Successfully\n\033[0m"

deps:
	@sh third-party/install.sh

clean:
	@$(MAKE) clean -s -f make_base.mk
	@$(MAKE) clean -C examples/get
	@$(MAKE) clean -C examples/pullkvs
	@$(MAKE) clean -C examples/watch
	@$(MAKE) clean -C test
	@echo -e "\033[32m\nClean bscp-cpp-sdk Successfully\n\033[0m"
