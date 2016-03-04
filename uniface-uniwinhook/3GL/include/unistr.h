/* CONT_ID %fv: unistr.h-34:incl:1 % %dc: Tue Sep  9 09:59:31 2014 % */

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
041123 c21118    910102  ete String functions and macros moved here, from ustdlib.h
041214 c21431    910102  ete String functions and macros renamed and added
050228 c21692    910102  ete Removed most UXI... functions and macro's
050426 c21753    910102  ete All non-ASCII characters are legal in field/entity/etc names
050518 c21924    910102  ete Added u[v]sscanf
050530 c21973    910102  ete Added ustrlegal(), which checks a UTF8 string for well-formedness.
050915 c22455    910102  sse Stronger type checking with more const USTRING *
060201 c22781    910102  sse Changed BOM handling for Unicode file
080212 c26398    930101  ahn SMTP AUTH LOGIN driver
080219 c26405    930101  ete User written SMTP security drivers must deliver UTF8 to Uniface
                             Therefore more UTF8 string functions must be made available
100730 b28814      P214  ete CHAR_SUBSTITUTION: UTF8-to-Meta conversion now checks input UTF8
                             for well-formed-ness, and replaces each bad byte with this
                             substitution character ('?', not 0x1a, as the Unicode book says
                             because we already use it for frames; that would cause crashes
                             when the kernel starts scanning for a 2nd frame character).
101025 b28953      P216  ete Added ustrcount(), which is similar to ustrlegal(), except it
                             returns the nr of legal characters, not bytes.
120220 b29613      E104  ete Added usnprintf()
date   refnum    version who description
*******************************************************************************/

#ifndef UNISTR_H
#define UNISTR_H

#ifndef TRUE
# define TRUE 1
# define FALSE 0
#endif

#include <string.h>
#include <stdlib.h>

#ifndef UNITYP_H
# include "unityp.h"
#endif



#ifdef __cplusplus
extern "C"
{
#endif



#define  UTF8_BOM           "\xEF\xBB\xBF"  /** The Byte Order Mark FEFF in UTF-8 */
#define  UTF16_BOM          0xfeff          /** The Byte Order Mark FEFF in UTF-16 */
#define  UTF16_ESWAP_BOM    0xfffe          /** The Byte Order Mark in UTF-16 with other endian */
#define  UTF32_BOM          0x0000feff      /** The Byte Order Mark FEFF in UTF-32 */
#define  UTF32_ESWAP_BOM    0xfffe0000      /** The Byte Order Mark in UTF-32 with other endian */
#define  UTF_NO_SWAP        0               /** No endian swap needed */
#define  UTF_ENDIAN_SWAP    1               /** Endian swap needed */

/* Special UTF32 values: */
#define CHAR_EOS                0

#define CHAR_BELL               7
#define CHAR_BS                 8
#define CHAR_HT                 9
#define CHAR_LF                 10
#define CHAR_VT                 11
#define CHAR_FF                 12
#define CHAR_CR                 13
#define CHAR_UNUSED_14          14
#define CHAR_UNUSED_15          15
/* Profile BEGIN = 16 */
#define PROFILE_WILD            16              /**  Wild card character Any(*)  */
#define PROFILE_WILD1           17              /**  Wild card character One(?)  */
#define PROFILE_EQUAL           18              /**  Profile equal character (=)  */
#define PROFILE_GREATER         19              /**  Profile greater than character (>)  */
#define PROFILE_LESS            20              /**  Profile less than character (<)  */
#define PROFILE_NOT             21              /**  Profile not character (!)  */
#define PROFILE_AND             22              /**  Profile and character (&)  */
#define PROFILE_OR              23              /**  Profile or character (|)  */
/* Profile END   = 23 */
#define CHAR_RULER              24              /**  Ruler definition  */
#define CHAR_SHIFT              25              /**  Dbms output shift flag  */
#define CHAR_FRAME              26              /**  Frame definiton  */
#define CHAR_SEPARATOR          27              /**  SubField Separator  */
#define CHAR_ESC                27              /**  ESC character (usynchk, usynsub)  */
#define CHAR_POSTSEP            27              /**  post message separator component / operation / data */
#define CHAR_UNUSED_28          28
#define CHAR_TYP_DATA           29              /**  Self identified DataItem; variations of TYP_DATA is following  */
#define CHAR_UNUSED_30          30
#define CHAR_UNUSED_31          31

/* Additional types of newline (UTF32)
 * (See "The Unicode standard 4.0" book, table 5-3, p.116)
*/
#define CHAR_NEL              0x85              /** Next line */
#define CHAR_LS             0x2028              /** Line separator */
#define CHAR_PS             0x2029              /** Paragraph separator */

/* Different types of spaces in Unicode (UTF32)
 * (See "The Unicode standard 4.0" book, table 6-2, p.155)
*/
#define CHAR_SPACE              32              /** Normal space */
#define CHAR_NO_BREAK_SPACE   0xa0              /** No break space */
#define CHAR_EN_QUAD        0x2000              /** En Quad */
#define CHAR_EM_QUAD        0x2001              /** Em Quad */
#define CHAR_EN_SPACE       0x2002              /** En Space */
#define CHAR_EM_SPACE       0x2003              /** Em Space */
#define CHAR_3_PER_EM_SPACE 0x2004              /** Three-per-em space */
#define CHAR_4_PER_EM_SPACE 0x2005              /** Four-per-em space */
#define CHAR_6_PER_EM_SPACE 0x2006              /** Six-per-em space */
#define CHAR_FIGURE_SPACE   0x2007              /** Figure space, i.e. in between digits */
#define CHAR_PUNCT_SPACE    0x2008              /** Punctuation space */
#define CHAR_THIN_SPACE     0x2009              /** Thin space, half the width */
#define CHAR_HAIR_SPACE     0x200a              /** Really thin space */
#define CHAR_ZERO_W_SPACE   0x200b              /** Zero width space, an invisible space */
#define CHAR_N_NO_BRK_SPACE 0x202f              /** Narrow no break space */
#define CHAR_MED_MATH_SPACE 0x205f              /** Medium mathematical space */
#define CHAR_IDEOGR_SPACE   0x3000              /** Ideographical space */

#define CHAR_NOT_A_CHAR1    0xfffe              /** In UTF32 this is Not A Character */
#define CHAR_NOT_A_CHAR2    0xffff              /** In UTF32 this is Not A Character */

#define CHAR_SUBSTITUTION     0x3f              /** Uniface's substitution character (0x1A is already taken) (@b28814) */

#define AT_EOS(cp)  (*cp==CHAR_EOS)

#ifndef umemchr
#  define umemchr(a,b,c)          memchr((char *)(a), (int)(b), (int)(c))
#endif
#ifndef ustrcpy
#  define ustrcpy(a,b)            strcpy((char *)(a), (char *)(b))
#endif
#ifndef ustrcat
#  define ustrcat(a,b)            strcat((char *)(a), (char *)(b))
#endif
#ifndef ustrcmp
#  define ustrcmp(a,b)            strcmp((char *)(a), (char *)(b))
#endif
#ifndef ustrlen
#  define ustrlen(a)               ((int) strlen((char *)(a)))
#endif

/**
Convert a string representation of a decimal number to an int
@param str   [IN] Pointer to the UTF8 string containing the string representation of the number
@return The integer number that the string represents, or 0
*/
extern int  uatoi     (const USTRING* str);

/**
Convert a string representation of a decimal number to a long
@param str   [IN] Pointer to the UTF8 string containing the string representation of the number
@return The long integer number that the string represents, or 0
*/
extern long uatol     (const USTRING* str);

/**
Count the number of bytes left in the UTF8 string that remain when all blanks
would be stripped starting at position len
@param Begin [IN] Pointer to begin of UTF8 string
@param len   [IN] Where to start stripping. If bigger than the length of the string,
                  the end of the string is taken.
@return Length of string in bytes after stripping; no actual stripping takes place.
*/
extern int ustrtrail(const USTRING* Begin, int len);

/**
Strips trailing blanks from the provided string, starting at byte-position len.
An EOS character is placed after the last non-blank character before position len.
@param string [IN] Pointer to begin of UTF8 string
@param len    [IN] Where to start stripping. If bigger than the length of the string,
                   the end of the string is taken.
@return Length of string in bytes after stripping.
*/
extern int ustrim(USTRING* string, int len);

/**
Copies n bytes from src to dst and then strips trailing spaces from the result.
@param dst   [OUT] The resulting string will be copied
@param src    [IN] The UTF8 string to be copied and stripped
@param length [IN] How many bytes to copy from src to dst.
@return Length of string in bytes after copying and stripping stripping.
*/
extern int ustrncpytrim(USTRING *dst, const USTRING *src, int length);

/**
Compares two UTF8 strings case-sensitive, up to byte nr n, or EOS.
@param str1   [IN] UTF8 string one
@param str2   [IN] UTF8 string two, to be compared with str1
@param maxlen [IN] How many characters to compare
@return 0 if equal in the first 'length' bytes; <> 0 if not.
*/
extern int ustrncmp(const USTRING* str1, const USTRING* str2, int length);

/**
Compares two ASCII strings case-insensitive, up to the EOS.
@param str1   [IN] ASCII string one
@param str2   [IN] ASCII string two, to be compared with str1
@param maxlen [IN] How many bytes to compare
@return 0 if equal in the first 'length' bytes; <> 0 if not.
*/
extern int ustricmpASC(const USTRING* str1, const USTRING* str2);

/**
Compares two UTF8 strings case-insensitive, up to the EOS.
@param str1   [IN] UTF8 string one
@param str2   [IN] UTF8 string two, to be compared with str1
@param maxlen [IN] How many bytes to compare
@return 0 if equal in the first 'length' bytes; <> 0 if not.
*/
extern int ustricmp(const USTRING* str1, const USTRING* str2);

/**
Compares two ASCII strings case-insensitive, up to byte nr n, or EOS.
@param str1   [IN] ASCII string one
@param str2   [IN] ASCII string two, to be compared with str1
@param maxlen [IN] How many bytes to compare
@return 0 if equal in the first 'length' bytes; <> 0 if not.
*/
extern int ustrnicmpASC(const USTRING* str1, const USTRING* str2, int length);

/**
Compares two UTF8 strings case-insensitive, up to byte nr n, or EOS.
@param str1   [IN] UTF8 string one
@param str2   [IN] UTF8 string two, to be compared with str1
@param maxlen [IN] How many characters to compare
@return 0 if equal in the first 'length' bytes; <> 0 if not.
*/
extern int ustrnicmp(const USTRING* s1, const USTRING* s2, int length);

/**
Compares two strings case-insensitive, up to byte nr n, or the first space,
whichever comes first
@param str1   [IN] ASCII string one
@param str2   [IN] ASCII string two, to be compared with str1
@param maxlen [IN] How many bytes to compare
@return 0 if equal in the first 'maxlen' bytes; <>0 if not.
*/
extern int ustrnicmp_spcASC(const USTRING *str1, const USTRING *str2, int maxlen);

/**
Copies a maximum of 'n' bytes from 'src' to 'dst'. It observes UTF8 character
boundaries, so if a character does not fit, it is not copied and less than 'n'
bytes are stored in 'dst'. The resulting string is EOS terminated if this happens
or if 'dst' is less than 'n' bytes long.
@param dst    [OUT] UTF8 result string
@param src    [IN]  UTF8 string that is to be copied
@param n      [IN]  nr of bytes to copy
@return It just returns 'dst'.
*/
#ifndef ustrncpy
#define ustrncpy(dst,src,n)     strncpy((char*)(dst), (const char*)(src), n)
#endif

/**
Appends a maximum of 'n' bytes from 'src' to 'dst'.
The resulting string is always EOS terminated, so n+1 bytes could be written.
@param dst    [OUT] ASCII result string
@param src    [IN]  ASCII string that is to be appended
@param n      [IN]  nr of bytes to append
@return It just returns 'dst'.
*/
#define ustrncat(dst,src,n)  strncat((char*)dst, (const char*)src, n)


/**
UTF8 equivalent of C function ustrupr(), which works on the ASCII range only.
@param string [IN] The string to convert to uppercase (ASCII only)
@return pointer to string. string has been converted to uppercase.
*/
extern USTRING* ustruprASC(USTRING* string);

/**
UTF8 equivalent of C function ustrupr(), which works on the entire Unicode range.
@param string [IN] The UTF8 string to convert to uppercase
@return pointer to string. string has been converted to uppercase.
*/
extern USTRING* ustrupr(USTRING* string);

/**
UTF8 equivalent of C function ustrlow(), which works on the ASCII range only.
@param string [IN] The UTF8 string to convert to lowercase (ASCII only)
@return pointer to string. string has been converted to lowercase.
*/
extern USTRING* ustrlwrASC(USTRING* string);

/**
UTF8 equivalent of C function ustrlow(), which works on the entire Unicode range.
@param string [IN] The UTF8 string to convert to lowercase
@return pointer to string. string has been converted to lowercase.
*/
extern USTRING* ustrlwr(USTRING* string);

/**
Searches for a UTF8 string inside another UTF8 source string.
@param source  [IN]  The UTF8 string in which to search
@param pattern [IN]  The UTF8 string for which to search
@return NULL if not found, else a pointer to the place inside the source
 string were the other string first occurs.
*/
extern USTRING* ustrstr(const USTRING *source, const USTRING *pattern);

/**
Searches for an ASCII string inside another UTF8 source string, disregarding case
@param source  [IN]  The UTF8 string in which to search
@param pattern [IN]  The ASCII string for which to search case insensitively
@return NULL if not found, else a pointer to the place inside the source
 string were the other string first occurs.
*/
extern USTRING* ustrstriASC(const USTRING *source, const USTRING *pattern);

/**
Searches for a UTF8 string inside another UTF8 source string, disregarding case
@param source  [IN]  The UTF8 string in which to search
@param pattern [IN]  The UTF8 string for which to search case insensitively
@return NULL if not found, else a pointer to the place inside the source
 string were the other string first occurs.
*/
extern USTRING* ustrstri(const USTRING *source, const USTRING *pattern);

/**
Splits a string into tokens by searching for the UTF8 characters specified in the second
 parameter and replacing them with 0 (EOS). The first call must provide the string that
 is to be tokenized in parameter 1 and will return a pointer to the first token; subsequent calls
 have NULL for the first parameter and will return the next token.
 To make this function reentrant (i.e. thread-safe), provide as the third parameter a pointer to
 a pointer to a USTRING (USTRING**); ustrtok() will use it to store a pointer to the next token.
@param str        [IN]  The UTF8 string that is to be tokenized, or NULL for subsequent tokens
@param delimiters [IN]  A pointer to one or more UTF8 characters that serve as token delimiters and
                         that must be replaced by EOS.
@param state      [IN-OUT] USTRING** parameter used to store the current state of ustrtok(), for use
                           by the next invocation of ustrtok(NULL, .., ..)
@return NULL if there are no more tokens, else a pointer to the first (when str != NULL) or
        next (when str == NULL) token.
*/
extern USTRING* ustrtok (USTRING* str, const char* delimiters, USTRING** state);

/**
Scan a UTF8 string up to the first illegal (not well-formed) UTF8 character, and return the length of
 the substring that constitutes a legal well-formed UTF8 string. In other words, return the (byte) index
 of the first byte of this illegal character, or the length of the string if there are no illegal chars.
@param str        [IN]  The UTF8 string that is to be scanned for illegal / not well-formed UTF8 chars
@param len        [IN]  The maximum number of bytes to scan. If it is zero, the entire string is scanned,
                         up to EOS. If the specified length turns out to be in the middle of a UTF8
                         character sequence, that entire character will not be counted.
@return NULL if there are no more tokens, else a pointer to the first (when str != NULL) or
        next (when str == NULL) token.
*/
extern int ustrlegal (const USTRING *str, int len);

/**
Scan a UTF8 string up to the first illegal (not well-formed) UTF8 character, and return the number of
 legal well-formed UTF8 characters in the string. The difference with ustrlegal is that it returns the
 number of characters in stead of the number of bytes of the legal substring.
@param str        [IN]  The UTF8 string that is to be scanned for illegal / not well-formed UTF8 chars
@param len        [IN]  The maximum number of bytes to scan. If it is zero, the entire string is scanned,
                         up to EOS. If the specified length turns out to be in the middle of a UTF8
                         character sequence, that entire character will not be counted.
@return NULL if there are no more tokens, else a pointer to the first (when str != NULL) or
        next (when str == NULL) token.
*/
extern int ustrcount (const USTRING *str, int len);

/**
UTF8 version of standard C function sprintf
@param buffer [OUT]  The resulting UTF8 string
@param format [IN]   The format string in UTF8
@return A string formatted according to the specified format.
@remarks See manual page of sprintf on Unix, or
 MSDN library. Platform specific extensions are not implemented.
 Extra Uniface specific extensions:
  %#s     inserts a string which is in external charset, by converting it to UTF8
          The supplied argument must be a pointer to a string which is encoded in $SYS_CHARSET.
  %#c     inserts a single byte character which is in external charset, by converting it to UTF8
  %#C     inserts a UTF8 character. The supplied argument must be a pointer to a UTF8 character.
  %C      inserts a UTF32 character by converting it to UTF8
*/
extern int usprintf(USTRING* buffer, const char * format, ...);

/**
UTF8 version of standard C function snprintf
@param buffer [OUT]  The resulting UTF8 string
@param max    [IN]   Maximum nr of bytes to write (incl. EOS)
@param format [IN]   The format string in UTF8
@return A string formatted according to the specified format.
@remarks See manual page of sprintf on Unix, or
 MSDN library. Platform specific extensions are not implemented.
 Extra Uniface specific extensions:
  %#s     inserts a string which is in external charset, by converting it to UTF8
          The supplied argument must be a pointer to a string which is encoded in $SYS_CHARSET.
  %#c     inserts a single byte character which is in external charset, by converting it to UTF8
  %#C     inserts a UTF8 character. The supplied argument must be a pointer to a UTF8 character.
  %C      inserts a UTF32 character by converting it to UTF8
*/
extern int usnprintf(USTRING *outbuf, int max, const char* format, ...);

/**
Converts a UTF8 string to UTF16
@param utf16   [OUT] The resulting UTF16 string. The pointer provided must point to a large enough area to hold the resulting UTF16 string and the EOS character, which is always appended.
@param utf8    [IN]  The UTF8 string that is to be converted to UTF16.
@param lenutf8 [IN]  The length of the provided UTF8 string in bytes.
@return The number of resulting UTF16 characters (excluding the EOS) is returned (Note: surrogate pairs are counted as two characters, eventhough technically they represent one unicode character).
*/
extern int ustrUTF8toUTF16 (UTF16* utf16, const USTRING* utf8,   int lenutf8);

/**
Converts a UTF16 string to UTF8
@param utf8     [OUT] The resulting UTF8 string. The pointer provided must point to a large enough area to hold the resulting UTF8 string and the EOS character, which is always appended.
@param utf16    [IN]  The UTF16 string that is to be converted to UTF8.
@param lenutf16 [IN]  The length of the provided UTF16 string in 2 byte units, i.e. the number of bytes divided by 2.
@return The number of resulting UTF8 characters (excluding the EOS) is returned.
*/
extern int ustrUTF16toUTF8 (USTRING*  utf8,  const UTF16* utf16, int lenutf16);

/* @c26398 */
/**
@internal
Predict tle length in bytes of Unicode value in UTF-8 format
@param FirstByte First UTF-8 byte
@return Predicted length in bytes
*/
extern int utf8len(int FirstByte);

/**
Get length of next ::UXCODE character in META stream
@param ptr [IN] Pointer to meta stream
@return Length of next character in META stream
@remarks The length in 1-4 for the mext character (plus additional 4 bytes for attribute prefix character)
*/
extern int umLen(const USTRING* ptr);

/**
Go forward to next character in META stream
@param ptr [IN] Pointer to META stream
@return Pointer to next character in META stream
*/
extern USTRING* umForwards(const USTRING* ptr);
/**
Go backward to previous character in META stream
@param Begin [IN] Pointer to begin of META stream
@param ptr [IN] Pointer to current position in META stream
@return Pointer to previous character in META stream
*/
extern USTRING* umBackwards(const USTRING* Begin, const USTRING* ptr);

#ifdef __cplusplus
}
#endif


#endif /* UNISTR_H */
