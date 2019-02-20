OBJ=hello_world.o
CC=g++ -std=c++0x
CFLAGS=
XAPIANROOTDIR=/usr/local/app/cswuyg/xapian_proj/install/
INCLUDE=-I$(XAPIANROOTDIR)include/
LIBS=-lxapian
hello_world: $(OBJ)
	    $(CC) $(CFLAGS) -o hello_world $(OBJ)  -L$(XAPIANROOTDIR)lib $(LIBS)
hello_world.o: hello_world.cpp
	    $(CC) $(CFLAGS) -c hello_world.cpp $(INCLUDE)
clean:
	    rm *.o
