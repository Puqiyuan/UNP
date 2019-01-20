IDIR=lib
CC=gcc
CFLAGS1=-I $(IDIR) 
introCODES=intro/example_programs
introExer=intro/exercise

BIN=bin

ODIR=obj
LDIR=lib

LIBS=-lunp
CFLAGS2=-L $(LDIR)
.SECONDARY: $(OBJS)
all: $(BIN)/p36 $(BIN)/p41 $(BIN)/p108 $(BIN)/e1.3 $(BIN)/e1.4


$(ODIR)/%.o: $(introCODES)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS1)

$(ODIR)/%.o: $(introExer)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS1)

$(BIN)/%: $(ODIR)/%.o
	gcc -o $@ $^ $(CFLAGS2) $(LIBS)

clean:
	rm -f $(BIN)/* && rm -f $(ODIR)/* && rm -f $(introCODES)/*~


