NBubble=1000
NMerge=1024
NReps=1
printLevel=1
PBubble=8
PMerge=8

all: bubbleSort par_bubbleSort mergeSort par_mergeSort shearSort par_shearSort

shearSort: shearSort.c
	gcc $? -o $@ -lm

bubbleSort: bubbleSort.c
	gcc $? -o $@ -lm

par_bubbleSort: par_bubbleSort.c
	gcc $? -o $@ -lpthread -lm

par_shearSort: par_shearSort.c
	gcc $? -o $@ -lpthread -lm

par_mergeSort: par_mergeSort.c
	gcc $? -o $@ -lpthread -lm

mergeSort: mergeSort.c
	gcc $? -o $@ -lm

run_mergeSort: mergeSort
	time ./$< $(NMerge) $(PMerge) $(printLevel)

run_bubbleSort: bubbleSort
	time ./$< $(NBubble) $(PBubble) $(printLevel)

test_merge: mergeSort par_mergeSort 
	 ./testCorrectnessIntensive.sh $^ $(NMerge) $(NReps) 1

test_bubble: bubbleSort par_bubbleSort
	 ./testCorrectnessIntensive.sh $^ $(NBubble) $(NReps) 1

.PHONY: clean
clean:
	rm -f bubbleSort par_bubbleSort mergeSort par_mergeSort par_shearSort shearSort

