all: hello

hello: sort.out rand.out

sort.out: sort.c
	gcc sort.c -o sort.out

rand.out: rand.c
	gcc rand.c -o rand.out

clean:
	rm *.out
