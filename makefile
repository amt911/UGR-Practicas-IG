.PHONY: x clean tar

EJECUTABLE= practica_objetos_B2.out

MODULOS:= practica_objetos_B2.o\
         objetos_B2.o\
         file_ply_stl.o\
      
LIBS:= -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

all: clean x

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(CPPFLAGS) $(LDFLAGS) $(MODULOS) $(LIBS) 

clean:
	rm -rf *.o $(EJECUTABLE)

