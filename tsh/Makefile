# Makefile for the CS:APP Shell Lab

DRIVER = ./sdriver.pl
TSH = ./tsh
TSHREF = ./tshref
TSHARGS = "-p"
CC = gcc
CFLAGS = -Wall -O2
SRC_FILES= tsh.c jobs.c helper_wrapper_functions.c shell_command_line.c signal_handlers.c

##################
# Regression tests
##################

# Compile tsh resources
tsh:
	$(CC) $(CFLAGS) $(SRC_FILES) -o $@


# Run tests using the student's shell program
test01:
	$(DRIVER) -t traces/trace01.txt -s $(TSH) -a $(TSHARGS)
test02:
	$(DRIVER) -t traces/trace02.txt -s $(TSH) -a $(TSHARGS)
test03:
	$(DRIVER) -t traces/trace03.txt -s $(TSH) -a $(TSHARGS)
test04:
	$(DRIVER) -t traces/trace04.txt -s $(TSH) -a $(TSHARGS)
test05:
	$(DRIVER) -t traces/trace05.txt -s $(TSH) -a $(TSHARGS)
test06:
	$(DRIVER) -t traces/trace06.txt -s $(TSH) -a $(TSHARGS)
test07:
	$(DRIVER) -t traces/trace07.txt -s $(TSH) -a $(TSHARGS)
test08:
	$(DRIVER) -t traces/trace08.txt -s $(TSH) -a $(TSHARGS)
test09:
	$(DRIVER) -t traces/trace09.txt -s $(TSH) -a $(TSHARGS)
test10:
	$(DRIVER) -t traces/trace10.txt -s $(TSH) -a $(TSHARGS)
test11:
	$(DRIVER) -t traces/trace11.txt -s $(TSH) -a $(TSHARGS)
test12:
	$(DRIVER) -t traces/trace12.txt -s $(TSH) -a $(TSHARGS)
test13:
	$(DRIVER) -t traces/trace13.txt -s $(TSH) -a $(TSHARGS)
test14:
	$(DRIVER) -t traces/trace14.txt -s $(TSH) -a $(TSHARGS)
test15:
	$(DRIVER) -t traces/trace15.txt -s $(TSH) -a $(TSHARGS)
test16:
	$(DRIVER) -t traces/trace16.txt -s $(TSH) -a $(TSHARGS)

# Run the tests using the reference shell program
rtest01:
	$(DRIVER) -t traces/trace01.txt -s $(TSHREF) -a $(TSHARGS)
rtest02:
	$(DRIVER) -t traces/trace02.txt -s $(TSHREF) -a $(TSHARGS)
rtest03:
	$(DRIVER) -t traces/trace03.txt -s $(TSHREF) -a $(TSHARGS)
rtest04:
	$(DRIVER) -t traces/trace04.txt -s $(TSHREF) -a $(TSHARGS)
rtest05:
	$(DRIVER) -t traces/trace05.txt -s $(TSHREF) -a $(TSHARGS)
rtest06:
	$(DRIVER) -t traces/trace06.txt -s $(TSHREF) -a $(TSHARGS)
rtest07:
	$(DRIVER) -t traces/trace07.txt -s $(TSHREF) -a $(TSHARGS)
rtest08:
	$(DRIVER) -t traces/trace08.txt -s $(TSHREF) -a $(TSHARGS)
rtest09:
	$(DRIVER) -t traces/trace09.txt -s $(TSHREF) -a $(TSHARGS)
rtest10:
	$(DRIVER) -t traces/trace10.txt -s $(TSHREF) -a $(TSHARGS)
rtest11:
	$(DRIVER) -t traces/trace11.txt -s $(TSHREF) -a $(TSHARGS)
rtest12:
	$(DRIVER) -t traces/trace12.txt -s $(TSHREF) -a $(TSHARGS)
rtest13:
	$(DRIVER) -t traces/trace13.txt -s $(TSHREF) -a $(TSHARGS)
rtest14:
	$(DRIVER) -t traces/trace14.txt -s $(TSHREF) -a $(TSHARGS)
rtest15:
	$(DRIVER) -t traces/trace15.txt -s $(TSHREF) -a $(TSHARGS)
rtest16:
	$(DRIVER) -t traces/trace16.txt -s $(TSHREF) -a $(TSHARGS)


# clean up
clean:
	rm -f *.o *~ tsh
