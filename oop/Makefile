cc=gcc
LDFLAGS= -lstdc++ 
EXEC=linkedlist
DEPS = $(wildcard *.h) Makefile
all:$(EXEC)
OBJ = linked_main.o linkedlist.o

$(EXEC):$(OBJ)
	$(cc)  $^ -o $@ $(LDFLAGS)

%.o:%.cpp $(DEPS)
	$(cc) -c $< -o $@

.PHONY:clean

clean:
	rm -rf $(OBJ) $(EXEC)