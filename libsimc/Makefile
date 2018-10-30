# Target library
lib := libsimc.a
CFLAGS = -Wall -Werror -c

all: $(lib)

# $< means name of first prerequisite of target
# $@ means target
# $^ means all prerequisites of target
# %.o: %.c generates any file from from another file

%.o: %.c functions.h array.h
	gcc $(CFLAGS) $<

# %.o: %.c tps.h
# 	gcc $(CFLAGS) $<

# libuthread.a: queue.o sem.o thread.o tps.o   # using all .o files created above add to libsimc.a here
# 	ar rcs libuthread.a $^
libsimc.a: functions.o array.o   
	ar rcs libsimc.a $^

# rm -f sem.o tps.o *.a  # for all .o files created from above, delete here
clean:
	rm -f functions.o array.o *.a