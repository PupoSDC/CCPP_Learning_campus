####################   DIRECTORIES   ##########################################

SRCDIR       = ./src/
PROG         = ./run/HiPS.run

######################## SOURCE FILES ##########################

SRC  =  $(SRCDIR/main.cpp                 \
        $(SRCDIR)/mesh/tree.cpp           

######################## OBJECT FILES ##########################

OBJS   = $(SRC:.cpp=.o)

######################## BUILD TARGETS ##########################

default : $(PROG)

all : default

$(PROG) : $(OBJS) 
	$(LINK) $(OBJS) -o $@ 

%.o: %.cpp 
	g++ $< -o $@

clean :
	rm -f $(OBJS)
	rm -f ../run/

   

####################### OBJECT DEPENDENCIES #####################

DEPENDS   = $(SRC:.cpp=.d)

depend :  $(DEPENDS) 
	cat   $(DEPENDS) > .depend
	rm -f $(DEPENDS) 
