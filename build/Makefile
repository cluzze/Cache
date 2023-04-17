CC = g++

ROOT = ..

SRC = $(ROOT)/src
INC = $(ROOT)/include

LIST_DIR = $(ROOT)/list
HASH_DIR = $(ROOT)/hash_table
TEST_DIR = $(ROOT)/tests

LIST_INC = $(LIST_DIR)/include
LIST_SRC = $(LIST_DIR)/src

HASH_INC = $(HASH_DIR)/include
HASH_SRC = $(HASH_DIR)/src

CFLAGS ?= -g -Wall -Wextra -I$(INC) -I$(LIST_INC) -I$(HASH_INC) 

all: list.o hash_table.o ctests.o 
	$(CC) $(CFLAGS) $^ -o main

ctests.o: $(TEST_DIR)/ctests.cc
	$(CC) $(CFLAGS) -c $^

list.o: $(LIST_SRC)/list.cc $(LIST_INC)/list.h
	$(CC) $(CFLAGS) -c $^

hash_table.o: $(HASH_SRC)/hash_table.cc $(HASH_INC)/hash_table.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *o $(LIST_INC)/*.gch $(HASH_INC)/*.gch main