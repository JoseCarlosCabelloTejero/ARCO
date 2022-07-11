DIREXE := exec/
DIRSRC := src/
LDLIBS := -fopenmp

CC := dpcpp

all : dirs serie

dirs:
	mkdir -p $(DIREXE)

serie: $(DIRSRC)serie.cpp 
	$(CC) $^ -o $(DIREXE)$@ $(LDLIBS)

run:
	./$(DIREXE)serie "data/homer.png"

clean: 
	rm -rf *~ core $(DIREXE) $(DIRSRC)*~ *.png