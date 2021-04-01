CC = gcc
CC_FLAGS = -W -Wall -ansi -pedantic

LIB_DIR = ../../lib
LIB_INC_DIR = $(LIB_DIR)/include
LIB_SRC_DIR = $(LIB_DIR)/src

DCL_H = $(LIB_INC_DIR)/iolib.h
DCL_C = $(LIB_SRC_DIR)/iolib.c dcl.c gettoken.c

dcl: $(DCL_H) $(DCL_C)
	$(CC) $(CC_FLAGS) -o $@ $(DCL_C) -I $(LIB_INC_DIR)
