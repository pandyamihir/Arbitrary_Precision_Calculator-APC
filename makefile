OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))

re.exe: $(OBJ)
	gcc -o $@ $^ 
	 
clean:
	rm *.o *.exe