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
EXEC = r.dict
INCLUDE=/usr/include/libxml2
LIBS= xml2 z m
OBJECTS= dict_to_stdout.o c_ccard.o
SRC=dict_to_stdout.c c_ccard.c parseDictionary.c parseMetvar.c parseTypvar.c changeEncoding.c strmatch.c
#
#

dict: 
	s.compile -src $(SRC) -o $(EXEC)_$(VER)-$(BASE_ARCH) -includes $(INCLUDE) -libappl $(LIBS) -conly

clean:
	/bin/rm -f  $(OBJECTS) *.o $(EXEC)_$(VER)-$(BASE_ARCH) 

