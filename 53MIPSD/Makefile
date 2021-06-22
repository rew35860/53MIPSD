# Use gcc as the C Compiler
CC:=gcc

CFLAGS:=-g 
# Include headers from include/
INCLUDE_DIR:=include

# Variables keeping track of objects
OBJS_NO_MAIN:=obj/hw2_p1.o obj/hw2_p3.o obj/hw2_helpers.o obj/linkedList.o
OBJS:=$(OBJS_NO_MAIN) obj/53MIPSD_main.o

# Make targets don't have to just be compilation commands, try this one out when you've written 53MIPSD
diss_1: bin/53MIPSD
	bin/53MIPSD rsrc/instr_map.txt < test1.bin 

# Most of these targets are named as the file they create on purpose to prevent
# make from rebuilding them if no updates are detected
obj/53MIPSD_main.o: src/53MIPSD_main.c
	$(CC) -I $(INCLUDE_DIR) src/53MIPSD_main.c $(CFLAGS) -c -o obj/53MIPSD_main.o

# The percent symbols mean that this is a static rule
# The percents are replacement wildcards; we could do this for all the objects if we really wanted
obj/hw2_p%.o: src/hw2_p%.c
	mkdir -p obj
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -c -o $@

obj/linkedList.o: src/linkedList.c
	mkdir -p obj
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -c -o $@

obj/hw2_helpers.o: src/hw2_helpers.c
	mkdir -p obj
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -c -o $@

# Convinience targets for unittest grading; compiles all the non-main c files
objs: clean $(OBJS_NO_MAIN)

clean_compile: clean #bin/53calc

bin/p1_testing_main: tests/p1_testing_main.c obj/hw2_p1.o obj/hw2_helpers.o
	mkdir -p bin
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -o $@

bin/p3_testing_main: tests/p3_testing_main.c obj/hw2_p3.o obj/hw2_helpers.o obj/linkedList.o obj/hw2_p1.o
	mkdir -p bin
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -o $@


bin/linkedlisttest_main: tests/linkedlisttest_main.c obj/hw2_p1.o obj/linkedList.o obj/hw2_helpers.o
	mkdir -p bin
	$(CC) -I $(INCLUDE_DIR) $^ $(CFLAGS) -o $@

bin/53MIPSD: $(OBJS)
	mkdir -p bin
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf bin obj

.PHONY: clean  linkedlisttest diss_1

# What is run with no arguments
.DEFAULT_GOAL:=bin/53MIPSD
