CCFLAGS = -Wall -Wshadow -O3 -Ofast -g $(LIB) $(INC)
LFLAGS = -lm


all: example1 example2 example3 example4 example5

test: test.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)
	./$@


example1: example1.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example2: example2.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example3: example3.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example4: example4.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example5: example5.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@


clean:
	rm *.o
	rm example?
	rm persist.txt test
