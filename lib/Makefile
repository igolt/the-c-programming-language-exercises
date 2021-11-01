CC = gcc
CFLAGS = -ansi -W -Wall -pedantic -I ./include

all: libcbook.so

libcbook.so: ./src/* ./include/*
	$(CC) $(CFLAGS) -shared -fPIC -o $@ ./src/*

install: all
	install -Dm 755 libcbook.so ~/.local/lib/cbook/libcbook.so

build:
