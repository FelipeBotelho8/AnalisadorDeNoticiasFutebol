CPP=g++
CPPFLAGS= -Wall
LD=g++
LDFLAGS= -Wall

TRABALHOOBJS= perlWrapper.o criterion.o news.o manager.o main.o
TRABALHO= main

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $< `perl -MExtUtils::Embed -e ccopts`

all: $(TRABALHO)

main: $(TRABALHOOBJS)
	$(LD) $(LDFLAGS) -o $@ $(TRABALHOOBJS) `perl -MExtUtils::Embed -e ldopts`

clean:
	rm -f *.o $(TRABALHO)
