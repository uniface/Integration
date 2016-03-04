# NMAKE include makefile with compiler and linker definitions for w2k 
# 
# Search paths 
# 
LIB=$(U3GL)\LIB;$(LIB) 
INCLUDE=$(U3GL)\INCLUDE;$(INCLUDE) 
# 
# Libraries 
# 
W32LIB=msvcrt.lib kernel32.lib user32.lib Winmm.lib 
ULIBS=ucall.lib ulib.lib uenc.lib umfclib.lib umswlib.lib urtl.lib wmswlib.lib yrtl.lib 
LIBS=$(ULIBS) $(W32LIB) 
# 
# Commands 
# 
UCD="cl" -c -nologo -Zl -Ox -W3 -GS- -D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_DEPRECATE -D_CRT_NON_CONFORMING_SWPRINTFS -DWINVER=0x0502 -D_WIN32_WINNT=0x0502 -D_WIN32_WINDOWS=0x0502 -DVC=8 -Du_msw -Du_msw32 -Du_pcint -Du_win4 -DWIN32 -DCTL3D -DNDEBUG -DUCE_REPOSITORY -DRELEASE -MD -EHsc -Zc:wchar_t- -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl 
ULD="link" -NOLOGO -MACHINE:IX86 -DEBUG -OPT:REF -DEBUGTYPE:cv -SUBSYSTEM:windows -DLL 
MT="mt" -nologo 
RC="rc" 
