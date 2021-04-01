CC = gcc
CC_FLAGS = -W -Wall -pedantic -ansi

LIB_DIR = ../../lib
LIB_INC_DIR = $(LIB_DIR)/include
LIB_SRC_DIR = $(LIB_DIR)/src

LIB_SRC = $(wildcard $(LIB_SRC_DIR)/*.c)

qsort: qsort.c $(LIB_SRC)
	$(CC) $(CC_FLAGS) -o $@ $^ -I $(LIB_INC_DIR) 
	
