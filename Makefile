# Set a variable LDFLAGS. Use the variable as $(LDFLAGS)
LDFLAGS := -L ~/lib -lsense -lm

all:	EtchaSketch	
EtchaSketch: main.o input.o output.o
	cc -o EtchaSketch main.o input.o output.o $(LDFLAGS)


%.o: %.c project.h
	cc -g -c $< -I ~/include

clean:
	rm -f *.o EtchaSketch
