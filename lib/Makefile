CC = gcc
CFLAGS = -ansi -W -Wall -pedantic -I ./include
INSTALL_DIR = ~/.local/lib/cbook

libcbook.so: ./src/* ./include/*
	$(CC) $(CFLAGS) -shared -fPIC -o $@ ./src/*

install: libcbook.so
	mkdir -p $(INSTALL_DIR)
	install -Dm 755 libcbook.so $(INSTALL_DIR)/libcbook.so

.PHONY: install
