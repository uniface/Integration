#-----------------------------------------------------------------------------
# Microsoft Visual C++ NMAKE script for demo sample
#-----------------------------------------------------------------------------

!include $(U3GL)\makefile.inc 

#- TARGET --------------------------------------------------------------------

all: metaphone.dll

CFLAGS=$(CFLAGS)
metaphone.obj : metaphone.c
    cl /c $(cflags)   metaphone.c

metaphone.dll: metaphone.obj   metaphone.def
   LINK -DLL -out:metaphone.dll  -def:metaphone.def -NODEFAULTLIB:library /libpath:$(U3GL) urtl.lib ulib.lib yrtl.lib metaphone.obj  
 

 

#- CLEANUP -------------------------------------------------------------------

clean:
   del metaphone.dll
   del metaphone.exp
   del metaphone.ilk
   del metaphone.lib
   del metaphone.obj
   del metaphone.pdb
   del vc??.pdb
