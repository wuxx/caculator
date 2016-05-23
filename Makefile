OBJ=caculator

#CFLAGS = -m32
.PHONY: clean

all: clean
	gcc $(CFLAGS) $(OBJ).c expr_pc.c expr_sy.c expr_sl.c -o $(OBJ)

test:
	./$(OBJ) "1+2"
	./$(OBJ) "1+2+3"
	./$(OBJ) "1+2+3+4"
	./$(OBJ) "1+2*3+4"
	./$(OBJ) "1+2*3+4*5"
	./$(OBJ) "1+2*3*4*5"
	./$(OBJ) "1+2*3*4-5"
	./$(OBJ) "1+2+(3+4)"
	./$(OBJ) "1+2+(3+4)"
	./$(OBJ) "1+2+(3*4)"
	./$(OBJ) "(1+2)+(3*4)"
	./$(OBJ) "(1*2)+(3*4)"
	./$(OBJ) "(1+2)*(3+4)"
	./$(OBJ) "10/(7/7+8/8*4)*(7*(((5/(9*3*6)-5)+8)-7))"

clean:	
	rm -f $(OBJ)
