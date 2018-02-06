CC = cc
CFLAGS = -g
PROGS = 03_test_linear_probe 03_test_quad_probe prime_num \
		03_test_double_hash \

03_DOBJ = dhash.o 03_test_double_hash.o
03_LOBJ = lhash.o 03_test_linear_probe.o
03_QOBJ = qhash.o 03_test_quad_probe.o

all: $(PROGS)

prime_num: prime_num.o 
	$(CC) $(CFLAGS) -o $@ prime_num.o -lm 

03_test_double_hash: $(03_DOBJ)
	$(CC) $(CFLAGS) -o $@ $(03_DOBJ)

03_test_linear_probe: $(03_LOBJ)
	$(CC) $(CFLAGS) -o $@ $(03_LOBJ)

03_test_quad_probe: $(03_QOBJ)
	$(CC) $(CFLAGS) -o $@ $(03_QOBJ)

make clean:
	rm -rf *.o $(PROGS)
