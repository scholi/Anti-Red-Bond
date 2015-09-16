GXX=g++

OBJS=lattice3d.o list.o blist.o buffer.o vect.o stat.o arb.o
APP=arb
OPTS=#-pg

$(APP): $(OBJS)
	$(GXX) $(OPTS) -o $@ $^

%.o: %.cpp %.h CONFIG.h
	$(GXX) -c $(OPTS) -o $@ $<

clear:
	rm -f *.o $(APP) output.dat arb.dat pointer.dat bridges.dat

