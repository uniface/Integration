/* @(#)CONT_ID %fv: unilimit.h-20:incl:4 % %dc: Thu Jun 25 11:23:52 2015 % (#)@ */

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
050627 c22005    910102  jdk Included entity support. Defining the max depth of included entities
070805 c22087    910102  ete Increase object name sizes, most to 32 UTF8 characters
050815 e22240    910102  mab Maximum button context size.
060209 b26627    M431    ahn Internal instance name to 64 bytes for TCP6 IP
060528 e23857    910102  mab Maximum fully qualified name size.
070125 c25489    920101  hhe Maximum number of fields in an entity. 
                             Support exclusion of Segmented Fields from fieldlist
130823 b30369    QR21    ete Maximum number of fields in an entity increased to 1024.
150625 b30893    X701    jdk UNIFACE crashes on large value's in the valrep.
date   refnum    version who description
*******************************************************************************/


#ifndef UNILIMIT_H
#define UNILIMIT_H

/*
** Dictionary limits
*/

#define MAXLENGTH_UTF8               4


/*
** The following maximum lengths define the maximum number of characters.
*/
#define MAXLENGTH_FIELD             32
#define MAXLENGTH_ENTITY            32
#define MAXLENGTH_MODEL             32
#define MAXLENGTH_COMPONENT         32
#define MAXLENGTH_INSTANCE          64				/* @b26627 */
#define MAXLENGTH_OPERATION         32
#define MAXLENGTH_PROCENTRY         MAXLENGTH_OPERATION
#define MAXLENGTH_TRIGGERNAME       MAXLENGTH_OPERATION
#define MAXLENGTH_FORMNAME          32
#define MAXLENGTH_UOBJECT           32
#define MAXLENGTH_TEXTID            MAXLENGTH_UOBJECT
#define MAXLENGTH_TEXT              32
#define MAXLENGTH_LIBRARY           32
#define MAXLENGTH_VARIATION         MAXLENGTH_LIBRARY
#define MAXLENGTH_LANGUAGE          3
#define MAXLENGTH_MENUNAME          MAXLENGTH_LIBRARY
#define MAXLENGTH_PANELNAME         MAXLENGTH_MENUNAME
#define MAXLENGTH_PROCLABEL         32                  /* label names within proc */
#define MAXLENGTH_LOCREG            32
#define MAXLENGTH_CENREG            32
#define MAXLENGTH_PARAMETER         32
#define MAXLENGTH_VARIABLE          MAXLENGTH_PARAMETER
#define MAXLENGTH_SUBSYSTEM         MAXLENGTH_VARIATION
#define MAXLENGTH_DTDNAME           32
#define MAXLENGTH_LABEL             MAXLENGTH_LIBRARY
#define MAXLENGTH_UNAME             32                  /* UNAME field */

#define MAXLENGTH_GUID              (8+4+4+4+12 +4)     /* GUID is of format xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx (8+4+4+4+12, +4 dashes) */
#define MAXLENGTH_UUID              MAXLENGTH_GUID      /* $uuid returns the same format as GUID's */
#define MAXLENGTH_CLSID             (MAXLENGTH_GUID+2)  /* A GUID with {} brackets */
#define MAXLENGTH_UTECHID           MAXLENGTH_UUID      /* A techID is a uuid */
#define MAXLENGTH_REPOS_TABLE       20                  /* Our repository tablenames do not exceed 20 characters */
#define MAXLENGTH_UOBJECTID         (MAXLENGTH_REPOS_TABLE+1+MAXLENGTH_UUID) /* An ObjectID is a repository table name, plus '_', plus techID */
#define MAXLENGTH_UTYPE             12
#define MAXLENGTH_CONTEXT           256                 /* Length of button context in characters. -- @e22240 */
#define MAXLENGTH_ASYNCMSG          256                 /**< Length of a message passed with FC_ASYN (not FC_POSTMSG!)*/

/* @e23587 start */

/* Maximum length for a fully qualified name. A fully qualified
** name consists of a field, entity and model name separated by
** the "." character.
*/
#define MAXLENGTH_FQNAME            (MAXLENGTH_FIELD + MAXLENGTH_ENTITY + MAXLENGTH_MODEL + 2)

/* @e23587 end */

/*
** The following maximum lengths define the maximum number of bytes.
*/
#define MAX_FIELD_SIZE              (MAXLENGTH_FIELD*MAXLENGTH_UTF8)
#define MAX_ENTITY_SIZE             (MAXLENGTH_ENTITY*MAXLENGTH_UTF8)
#define MAX_MODEL_SIZE              (MAXLENGTH_MODEL*MAXLENGTH_UTF8)
#define MAX_COMPONENT_SIZE          (MAXLENGTH_COMPONENT*MAXLENGTH_UTF8)
#define MAX_INSTANCE_SIZE           (MAXLENGTH_INSTANCE*MAXLENGTH_UTF8)
#define MAX_OPERATION_SIZE          (MAXLENGTH_OPERATION*MAXLENGTH_UTF8)
#define MAX_PROCENTRY_SIZE          (MAXLENGTH_PROCENTRY*MAXLENGTH_UTF8)
#define MAX_TRIGGERNAME_SIZE        (MAXLENGTH_TRIGGERNAME*MAXLENGTH_UTF8)
#define MAX_FORMNAME_SIZE           (MAXLENGTH_FORMNAME*MAXLENGTH_UTF8)
#define MAX_UOBJECT_SIZE            (MAXLENGTH_UOBJECT*MAXLENGTH_UTF8)
#define MAX_TEXTID_SIZE             (MAXLENGTH_TEXTID*MAXLENGTH_UTF8)
#define MAX_TEXT_SIZE               (MAXLENGTH_TEXT*MAXLENGTH_UTF8)
#define MAX_LIBRARY_SIZE            (MAXLENGTH_LIBRARY*MAXLENGTH_UTF8)
#define MAX_VARIATION_SIZE          (MAXLENGTH_VARIATION*MAXLENGTH_UTF8)
#define MAX_LANGUAGE_SIZE           MAXLENGTH_LANGUAGE /* Languages always consist only of single byte UTF8 characters */
#define MAX_MENUNAME_SIZE           (MAXLENGTH_MENUNAME*MAXLENGTH_UTF8)
#define MAX_PANELNAME_SIZE          (MAXLENGTH_PANELNAME*MAXLENGTH_UTF8)
#define MAX_PROCLABEL_SIZE          (MAXLENGTH_PROCLABEL*MAXLENGTH_UTF8)
#define MAX_LOCREG_SIZE             (MAXLENGTH_LOCREG*MAXLENGTH_UTF8)
#define MAX_CENREG_SIZE             (MAXLENGTH_CENREG*MAXLENGTH_UTF8)
#define MAX_PARAMETER_SIZE          (MAXLENGTH_PARAMETER*MAXLENGTH_UTF8)
#define MAX_VARIABLE_SIZE           (MAXLENGTH_VARIABLE*MAXLENGTH_UTF8)
#define MAX_SUBSYSTEM_SIZE          (MAXLENGTH_SUBSYSTEM*MAXLENGTH_UTF8)
#define MAX_DTDNAME_SIZE            (MAXLENGTH_DTDNAME*MAXLENGTH_UTF8)
#define MAX_LABEL_SIZE              (MAXLENGTH_LABEL*MAXLENGTH_UTF8)
#define MAX_UNAME_SIZE              (MAXLENGTH_UNAME*MAXLENGTH_UTF8)
#define MAX_FQNAME_SIZE             (MAXLENGTH_FQNAME*MAXLENGTH_UTF8) /* @e23857 */

#define MAX_GUID_SIZE               MAXLENGTH_GUID        /* GUID's always consist only of single byte UTF8 characters */
#define MAX_CLSID_SIZE              MAXLENGTH_CLSID       /* CLSID's always consist only of single byte UTF8 characters */
#define MAX_UUID_SIZE               MAXLENGTH_UUID        /* uuid's ($uuid) always consist only of single byte UTF8 characters */
#define MAX_UTECHID_SIZE            MAXLENGTH_UTECHID     /* TechID's always consist only of single byte UTF8 characters */
#define MAX_REPOS_TABLE_SIZE        MAXLENGTH_REPOS_TABLE /* All our repository table names consist only of single byte UTF8 characters */
#define MAX_UOBJECTID_SIZE          (MAX_REPOS_TABLE_SIZE+1+MAX_UTECHID_SIZE)
#define MAX_UTYPE_SIZE              MAXLENGTH_UTYPE       /* These types always consist only of single byte UTF8 characters */

/** Maximum button/operation context size. This is the maximum length of a button
*** context passed on as parameter to the operation attached to the button
*** a panel.
*/
#define MAX_CONTEXT_SIZE            (MAXLENGTH_CONTEXT*MAXLENGTH_UTF8)

/** Maximum async message (not postmessage!) size. 
*/
#define MAX_ASYNCMSG_SIZE           MAXLENGTH_ASYNCMSG   /* Always sungle-byte only....*/           

/**
*** MAX_COMPILESIZE is on 32bit systems equal to INT_MAX. But since INT_MAX varies 
*** on different platforms it cannot be used in UNIFACE.
*/
#define MAX_COMPILESIZE             2147483647

#define MAX_ENTITY_LEVEL            32

/*
** Maximum allowed number of fields in an entity. 
*/
#define MAX_NUMBER_FIELDS_ENTITY    1024 /* @c25489, @b30369 */

/* maximum number of characters in the value of a valrep list */
/*@b30893-@b30892 - never change the following number without changing all valrep widgets*/
#define MAXVR_VALSIZE               512


#endif   /* UNILIMIT_H */
/* End of File unilimit.h */
