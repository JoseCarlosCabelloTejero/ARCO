DIREXE := exec/
DIRSRC := src/
LDLIBS := -fopenmp

CC := dpcpp

all : dirs dpc

dirs:
	mkdir -p $(DIREXE)

dpc: $(DIRSRC)dpc.cpp 
	$(CC) $^ -o $(DIREXE)$@ $(LDLIBS)

run:
	./$(DIREXE)dpc "data/homer.png"

clean: 
	rm -rf *~ core $(DIREXE) $(DIRSRC)*~ *.png
