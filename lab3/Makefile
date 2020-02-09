CC=gcc
CFLAGS=-lpthread -lm

N=400
NReps=1
printLevel=0
P=8

.PHONY: clean all

all: seq_multiply par_multiply_outer par_multiply_second par_multiply_inner seq_strassen par_strassen hw_ex1 hw_ex2

seq_multiply: seq_multiply.c
	$(CC) $? -o $@

par_multiply_outer: par_multiply_outer.c
	$(CC) $? -o $@ $(CFLAGS)

par_multiply_second: par_multiply_second.c
	$(CC) $? -o $@ $(CFLAGS)

par_multiply_inner: par_multiply_inner.c
	$(CC) $? -o $@ $(CFLAGS)

seq_strassen: seq_strassen.c
	$(CC) $? -o $@

par_strassen: par_strassen.c
	$(CC) $? -o $@ $(CFLAGS)

hw_ex1: hw_ex1.c
	$(CC) -o $@ $^ $(CFLAGS)

hw_ex2: hw_ex2.c
	$(CC) -o $@ $^ $(CFLAGS)

run_mult_seq: seq_multiply
	time ./$< $(N) $(NReps) $(printLevel) 

run_mult_outer: par_multiply_outer
	time ./$< $(N) $(NReps) $(printLevel) $(P)

run_mult_second: par_multiply_second
	time ./$< $(N) $(NReps) $(printLevel) $(P) 

run_mult_inner: par_multiply_inner
	time ./$< $(N) $(NReps) $(printLevel) $(P)

run_strassen_seq: seq_strassen
	time ./$< $(N) $(NReps) $(printLevel)

run_strassen_par: par_strassen
	time ./$< $(N) $(NReps) $(printLevel)

test_mult_outer: seq_multiply par_multiply_outer
	./testCorrectnessIntensive.sh $^ $(N) $(NReps) 1

test_mult_second: seq_multiply par_multiply_second
	./testCorrectnessIntensive.sh $^ $(N) $(NReps) 1

test_mult_inner: seq_multiply par_multiply_inner
	./testCorrectnessIntensive.sh $^ $(N) $(NReps) 1

test_mult_strassen: seq_strassen par_strassen
	./testCorrectnessIntensive.sh $^ $(N) $(NReps) 1

clean:
	rm -f seq_multiply par_multiply_outer par_multiply_second par_multiply_inner seq_strassen par_strassen hw_ex1 hw_ex2
