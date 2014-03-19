##OBJECT: dict
#
##LIBRARIES: libxml libxml2l
#
##MODULES:  dict.c 
#
##MACHINE:  op_f 
#
##
VER = 2.0
LIBRMN = rmn_014

EXEC = r.dict
INCLUDE=/usr/include/libxml2
LIBS= xml2 z m
OBJECTS = dict_to_stdout.o 
SRC=dict_to_stdout.c parseDictionary.c parseMetvar.c parseTypvar.c changeEncoding.c strmatch.c
#
#

dict: 
	s.compile -src $(SRC) -o $(EXEC)_$(VER)-$(BASE_ARCH) -includes $(INCLUDE) -libappl $(LIBS) -librmn $(LIBRMN) -conly

clean:
	/bin/rm -f  $(OBJECTS) *.o $(EXEC)_$(VER)-$(BASE_ARCH) 

