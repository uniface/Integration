/* @(#)CONT_ID %fv: wsciapi.h-4:incl:1 % %dc: Tue Sep  9 10:05:31 2014 % (#)@ */

/*******************************************************************************
Copyright © 2014 Uniface B.V. All rights reserved.
U.S. GOVERNMENT RIGHTS-Use, duplication, or disclosure by the U.S. Government
is subject to restrictions as set forth inapplicable license agreement with
Uniface B.V. and/or its predecessor in interest and as provided in DFARS
227.7202-1(a) and 227.7202-3(a) (1995), DFARS 252.227-7013(c)(1)(ii)(OCT 1988),
FAR 12.212(a)(1995), FAR 52.227-19, or FAR 52.227-14(ALTIII), as applicable.
Uniface B.V.

You have a royalty-free right to use, modify, reproduce and distribute
this sample code (and/or any modified version) in any way you find useful,
provided that you agree that Uniface B.V. has no warranty obligations or
liability for any sample code which has been modified.
*******************************************************************************/
/*******************************************************************************
date   refnum    version who description
041112 b26006    M411    ahn initial version
date   refnum    version who description
*******************************************************************************/

#ifndef _1_wsciapi_h_H
#define _1_wsciapi_h_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* values for which buffer is to be free'ed or released */
enum UWSCI_BUF_TYPE
{
    WSCIAPI_OUTBUF = 0,
    WSCIAPI_CONTEXT = 1
};

/*****************************************************************************
@NAME	
       soap_pre_request
@FUNCTION
       This function called prior to Uniface processing of the web service
request. It may perform validation on the basis of the web server variables
it receives or using information in the soap envelope itself. This function
may return a new soap envelope for Uniface to use, or an error message that
will be packed into a soap fault and returned to the caller.

@PARAMETERS 
       Type             Name      Use   Description 
       ----------------------------------------------------------------------
@PARM  char *           vars      In    null-terminated string containing a list
                                        of web server variables in the form:-
                                        name=value[[LEV...]SEPname=value...]
                                        where LEV is a level indication byte of value 0x15.
                                        At level 1, no LEV byte is present, at level 2, 1 LEV
                                        byte is present, at level 3, 2 LEV bytes are present...
                                        This string is in UTF-8.
                                        where SEP is a seperator byte of value 0x1b
@PARM  unsigned char *  in        In    received null-terminated soap envelope in UTF-8
                                        or UTF-16 character set.
@PARM  unsigned char ** out       Out   On success, *out is a pointer to the amended
                                        null-terminated soap envelope in UTF-8 or UTF-16
                                        character set. If the soap envelope is not amended,
                                        set it to NULL. It is assumed this buffer is dynamically
                                        allocated and a call to the soap_rel_buf() function will
                                        be made to release the buffer.
                                        On error, *out is a pointer to a null-terminated
                                        error string that will be packed into a soap
                                        fault and returned to the caller. It is assumed
                                        that this is a static buffer that does NOT need to be
                                        deallocated. The error string should be UTF-8 character set.
@PARM  long *           len       InOut initially contains  the length of in. On output 
                                        contains  the length of *out, if it contains an amended
                                        soap envelope.
@PARM  void **          context   InOut *context may be used to store a pointer
                                        to an area of memory used by these api
                                        functions. It will be passed to all the
                                        subsequent api calls. If you need to
                                        deallocate the memory provide the 
                                        soap_rel_buf() function

@RETURNS    
       Value         Description
       ----------------------------------------------------------------------
@FLAG  0             Success, out may contain an amended soap envelope
@FLAG  1             Error, out may contain an error string
@COMMENTS
       
******************************************************************************/
int soap_pre_request(char *, unsigned char *, unsigned char **, int *, void **);


/*****************************************************************************
@NAME	
       soap_post_request
@FUNCTION
       This function is called just after Uniface processing of the web service
request. This function may return a new soap envelope for Uniface to use,
or an error message that will be packed into a soap fault and returned to the caller.

@PARAMETERS 
       Type             Name      Use   Description 
       ----------------------------------------------------------------------
@PARM  char *           vars      In    null-terminated string containing a list
                                        of web server variables in the form:-
                                        name=value[[LEV...]SEPname=value...]
                                        where LEV is a level indication byte of value 0x15.
                                        At level 1, no LEV byte is present, at level 2, 1 LEV
                                        byte is present, at level 3, 2 LEV bytes are present...
                                        This string is in UTF-8.
                                        where SEP is a seperator byte of value 0x1b
@PARM  unsigned char *  in        In    received null-terminated soap envelope in UTF-8
                                        character set.
@PARM  unsigned char ** out       Out   On success, *out is a pointer to the amended
                                        null-terminated soap envelope in UTF-8
                                        character set. If the soap envelope is not amended,
                                        set it to NULL. It is assumed this buffer is dynamically
                                        allocated and a call to the soap_rel_buf() function will
                                        be made to release the buffer.
                                        On error, *out is a pointer to a null-terminated
                                        error string that will be packed into a soap
                                        fault and returned to the caller. It is assumed
                                        that this is a static buffer that does NOT need to be
                                        deallocated. The error string should be UTF-8 character set.
@PARM  long *           len       InOut initially contains  the length of in. On output 
                                        contains  the length of *out, if it contains an amended
                                        soap envelope.
@PARM  void **          context   InOut *context may be used to store a pointer
                                        to an area of memory used by these api
                                        functions. It will be passed to all the
                                        subsequent api calls. If you need to
                                        deallocate the memory provide the 
                                        soap_rel_buf() function

@RETURNS    
       Value         Description
       ----------------------------------------------------------------------
@FLAG  0             Success, out may contain an amended soap envelope
@FLAG  1             Error, out may contain an error string
@COMMENTS
       
******************************************************************************/
int soap_post_request(char *, unsigned char *, unsigned char **, long *, void **);

/*****************************************************************************
@NAME	
       soap_rel_buf
@FUNCTION
       This function is called to free buffers that may have been allocated
by the other api functions. Uniface tries to free the out parameter from the pre
and post request functions once it is no longer needed. When Uniface is exiting
it will try to free the context buffer

@PARAMETERS 
       Type       Name      Use   Description 
       ----------------------------------------------------------------------
@PARM  int        which     In    Describes which buffer is being freed
                                  0 means it is an out parameter buffer
                                  1 means it is the context buffer, the same
                                  one as in parameter 3
@PARM  void *     buf       In    the buffer to be freed
@PARM  void *     context   In    context area

@RETURNS    
       Value         Description
       ----------------------------------------------------------------------
@FLAG  0             Success
@FLAG  >1            Error, address of buf
@COMMENTS
       
******************************************************************************/
void *soap_rel_buf(int, void *, void *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
