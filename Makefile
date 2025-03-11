CC = gcc
OBJFILES = main.o array.o multidim_array.o
CFLAGS = -Wall
TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGET)  

main.o: main.c array.h multidim_array.h
	$(CC) $(CFLAGS) -c main.c -o main.o  

multidim_array.o: multidim_array.h multidim_array.c array.h 
	$(CC) $(CFLAGS) -c multidim_array.c -o multidim_array.o  
    
array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c -o array.o  

clean:
	rm -f $(OBJFILES) $(TARGET)  

    
				