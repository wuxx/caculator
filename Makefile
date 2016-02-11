OBJ=caculator

all:
	gcc -m32 $(OBJ).c -o $(OBJ)

clean:	
	rm -f $(OBJ)
