CC = gcc
CC_FLAGS = -W -Wall -ansi -pedantic

LIB_DIR = ../../lib
LIB_INC_DIR = $(LIB_DIR)/include
LIB_SRC_DIR = $(LIB_DIR)/src

UNDCL_H = $(LIB_INC_DIR)/iolib.h
UNDCL_C = $(LIB_SRC_DIR)/iolib.c undcl.c ../exercise18/gettoken.c

undcl: $(UNDCL_H) $(UNDCL_C)
	$(CC) $(CC_FLAGS) -o $@ $(UNDCL_C) -I $(LIB_INC_DIR) -I ../exercise18
