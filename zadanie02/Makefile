DIR = `basename $(CURDIR)`

CO = g++
COFLAGS = -O3 -march=native -Wall -Wextra -c
LFLAGS = -s -lm

.PHONY: all clean tar
all: heap
%.x: %.o
	$(CO) $(LFLAGS) -o $@ $^ $(LLIBS)
%.o: %.cpp
	$(CO) $(COFLAGS) -c -o $@ $<
	
clean:
	rm -f *.o *.x *~ heap
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
	
run:
	./heap
