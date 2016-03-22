/* CONT_ID %fv: unipck.h-13:incl:1 % %dc: Tue Sep  9 09:59:07 2014 % */

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
050510 c21598    910102  sse Added pW packing code
070406 c25825    920101  ete Added pE15 packing code for EDB driver
date   refnum    version who description
*******************************************************************************/

#ifndef UNIPCK_H
#define UNIPCK_H

/****************************************************************************
 *
 * List of packing codes suported by DBMS driver interface.
 *
 * pXX defines the packing code.
 * sXX defines the storage size.
 *
 ****************************************************************************/

#define pN0     500                             /* Default Numeric  */
#define pF0     501                             /* Default Float  */
#define pD0     502                             /* Default Date  */
#define pT0     503                             /* Default Time  */
#define pE0     504                             /* Default DateTime  */
#define pB0     505                             /* Default Boolean  */

#define pVARIABLE               1024            /* VCnnn, VRnnn etc  */
#define pSEGMENTED              2048            /* SCnnn, SRnnn etc  */
#define pMASK                   511             /* mask for keep PackingCodes only  */

#define pC      0                               /* Character format 1-126 */
#define pU      1                               /* (U) trx format  32-126 */
#define pR      2                               /* Raw format 0-255 */
#define pX      3                               /* pC for Xnnn packingcodes trn conversion  */
#define pA      4                               /* pC for Annn packingcodes  */
#define pW      6                               /* pW for Wnnn Wide character format */

#define pN1     8                               /* String Numeric digits (plus, minus and decimal point) */
#define pN2     9
#define pN3     10
#define pN4     11
#define pN5     12
#define pN6     13
#define pN7     14
#define pN8     15
#define pN9     16
#define pN10    17
#define pN11    18
#define pN12    19
#define pN13    20
#define pN14    21
#define pN15    22
#define pN16    23
#define pN17    24
#define pN18    25
#define pN19    26
#define pN20    27
#define pN21    28
#define pN22    29
#define pN23    30
#define pN24    31
#define pN25    32
#define pN26    33
#define pN27    34
#define pN28    35
#define pN29    36
#define pN30    37
#define pN31    38
#define pN32    39
#define pP1     40                              /* Packed decimal format nibbles */
#define pP2     41
#define pP3     42
#define pP4     43
#define pP5     44
#define pP6     45
#define pP7     46
#define pP8     47
#define pP9     48
#define pP10    49
#define pP11    50
#define pP12    51
#define pP13    52
#define pP14    53
#define pP15    54
#define pP16    55
#define pQ1     56                              /* Packed decimal format nibbles  */
#define pQ2     57
#define pQ3     58
#define pQ4     59
#define pQ5     60
#define pQ6     61
#define pQ7     62
#define pQ8     63
#define pQ9     64
#define pQ10    65
#define pQ11    66
#define pQ12    67
#define pQ13    68
#define pQ14    69
#define pQ15    70
#define pQ16    71
#define pI1     72                              /* Integer 1 */
#define pI2     73                              /* Integer 2 */
#define pI3     74                              /* Integer 3 */
#define pI4     75                              /* Integer 4 */
#define pI8     76                              /* Integer 8 */
#define pF4     77                              /* Float 4 (Real) */
#define pF8     78                              /* Float 8 (Double) */
#define pG8     79                              /* G_Float 8 (Double) */
#define pD1     80                              /* Date DD-MMM-YYYY */
#define sD1     11
#define pD2     81                              /* Date YYYYMMDD */
#define sD2     8
#define pD3     82                              /* Date DDMMYYYY */
#define sD3     8
#define pD4     83                              /* Date YYMMDD */
#define sD4     6
#define pD5     84                              /* Date DDMMYY */
#define sD5     6
#define pD6     85                              /* Date YYMD(binary) */
#define sD6     -4
#define pD7     86                              /* Date DMYY(binary) */
#define sD7     -4
#define pD8     87                              /* Date YMD(binary) */
#define sD8     -3
#define pD9     88                              /* Date DMY(binary) */
#define sD9     -3
#define pD10    89                              /* Date YYMMDD(binary) */
#define sD10    -6
#define pD11    90                              /* Date DDMMYY(binary) */
#define sD11    -6
#define pD12    91                              /* Date MM/DD/YYYY */
#define sD12    10
#define pD13    92                              /* Date YYYY-MM-DD  */
#define sD13    10
#define pD14    93                              /*  */
#define sD14    0
#define pD15    94                              /*  */
#define sD15    0
#define pD16    95                              /*  */
#define sD16    0
#define pT1     96                              /* Time HH:MM:SS */
#define sT1     8
#define pT2     97                              /* Time HHMMSS */
#define sT2     6
#define pT3     98                              /* Time pE4 */
#define sT3     15
#define pT4     99                              /* Time HH:MM:SS  Rdb 4.1 */
#define sT4     8
#define pT5     100                             /* Time HH:MM:SS.S Rdb 4.1  */
#define sT5     10
#define pT6     101                             /* Time HH:MM:SS.SS Rdb 4.1  */
#define sT6     11
#define pT7     102                             /*  */
#define sT7     0
#define pT8     103                             /*  */
#define sT8     0
#define pT9     104                             /*  */
#define sT9     0
#define pT10    105                             /*  */
#define sT10    0
#define pT11    106                             /*  */
#define sT11    0
#define pT12    107                             /*  */
#define sT12    0
#define pT13    108                             /*  */
#define sT13    0
#define pT14    109                             /*  */
#define sT14    0
#define pT15    110                             /*  */
#define sT15    0
#define pT16    111                             /*  */
#define sT16    0
#define pE1     112                             /*  DateTime Sybase Linear */
#define sE1     -8
#define pE2     113                             /* DateTime RDB/RMS Linear */
#define sE2     -8
#define pE3     114                             /* DateTime DDMMYYYY HH:MM:SS */
#define sE3     17
#define pE4     115                             /* DateTime DDMMYYYY HHMMSS */
#define sE4     15
#define pE5     116                             /* DateTime Ingres DD-MMM-YYYY HH:MM:SS */
#define sE5     25
#define pE6     117                             /* DateTime Oracle packed */
#define sE6     -7
#define pE7     118                             /* DateTime MM/DD/YYYY HH:MM:SS.TT */
#define sE7     22
#define pE8     119                             /* DateTime YYYYMMDD HHMMSS */
#define sE8     15
#define pE9     120                             /* DateTime Sybase */
#define sE9     -4
#define pE10    121                             /* Date-Time YYYY-MM-DD HH:MM:SS */
#define sE10    19
#define pE11    122                             /* Date-Time YYYY-MM-DD:HH:MM:SS */
#define sE11    19
#define pE12    123                             /* Date-Time YYYY-MM-DD:HH:MM:SS.S */
#define sE12    21
#define pE13    124                             /* Date-Time YYYY-MM-DD:HH:MM:SS.SS */
#define sE13    22
#define pE14    125                             /* Date-Time 8 shorts */
#define sE14    -16
#define pE15    126                             /* Date-Time Windows FILETIME struct for EDB (@c25825) */
#define sE15    8                               /* sizeof(FILETIME) = 8 (@c25825) */
#define pE16    127                             /* Unused */
#define sE16    0
#define pB1     128                             /* Boolean 0/1 */
#define sB1     1
#define pB2     129                             /* Boolean T/F */
#define sB2     1
#define pB3     130                             /* Boolean Y/N */
#define sB3     1
#define pB4     131                             /* Boolean 0/1 (binary) */
#define sB4     -1
#define pB5     132                             /* Boolean 0=TRUE, -1=FALSE */
#define sB5     -2
#define pB6     133                             /*  */
#define sB6     0
#define pB7     134                             /*  */
#define sB7     0
#define pB8     135                             /*  */
#define sB8     0
#define pM1     136                             /* Money Sybase */
#define sM1     -8
#define pM2     137                             /* Money */
#define sM2     -8
#define pM3     138                             /* Money */
#define sM3     -8
#define pM4     139                             /* Money */
#define sM4     -8
#define pM5     140                             /* Money */
#define sM5     -8
#define pM6     141                             /* Money */
#define sM6     -4
#define pM7     142                             /* Money */
#define sM7     -8
#define pM8     143                             /* Money */
#define sM8     -8
#define pJ1     144                             /* Number digit format (excl decimal point) */
#define pJ2     145
#define pJ3     146
#define pJ4     147
#define pJ5     148
#define pJ6     149
#define pJ7     150
#define pJ8     151
#define pJ9     152
#define pJ10    153
#define pJ11    154
#define pJ12    155
#define pJ13    156
#define pJ14    157
#define pJ15    158
#define pJ16    159
#define pJ17    160
#define pJ18    161
#define pJ19    162
#define pJ20    163
#define pJ21    164
#define pJ22    165
#define pJ23    166
#define pJ24    167
#define pJ25    168
#define pJ26    169
#define pJ27    170
#define pJ28    171
#define pJ29    172
#define pJ30    173
#define pJ31    174
#define pJ32    175
#define pO1     176                             /* Number digit format  (DIBOL format) */
#define pO2     177
#define pO3     178
#define pO4     179
#define pO5     180
#define pO6     181
#define pO7     182
#define pO8     183
#define pO9     184
#define pO10    185
#define pO11    186
#define pO12    187
#define pO13    188
#define pO14    189
#define pO15    190
#define pO16    191
#define pO17    192
#define pO18    193
#define pO19    194
#define pO20    195
#define pO21    196
#define pO22    197
#define pO23    198
#define pO24    199
#define pO25    200
#define pO26    201
#define pO27    202
#define pO28    203
#define pO29    204
#define pO30    205
#define pO31    206
#define pO32    207
#define pY1     208                             /* Number USER format */
#define pY2     209
#define pY3     210
#define pY4     211
#define pY5     212
#define pY6     213
#define pY7     214
#define pY8     215
#define pY9     216
#define pY10    217
#define pY11    218
#define pY12    219
#define pY13    220
#define pY14    221
#define pY15    222
#define pY16    223
#define pY17    224
#define pY18    225
#define pY19    226
#define pY20    227
#define pY21    228
#define pY22    229
#define pY23    230
#define pY24    231
#define pY25    232
#define pY26    233
#define pY27    234
#define pY28    235
#define pY29    236
#define pY30    237
#define pY31    238
#define pY32    239
#define pZ1     240                             /* Date-time USER format */
#define pZ2     241
#define pZ3     242
#define pZ4     243
#define pZ5     244
#define pZ6     245
#define pZ7     246
#define pZ8     247
#define pH8     248                             /* IEEE 8 bytes floating point */
#define pH4     249                             /* IEEE 4 bytes floating point */
#define pI16    250                             /* Integer 16 */
#define pFD8    251
#define pF16    252                             /* 16-byte float */
#define pFG8    pG8
#define pE17    253                             /* @pr4 ISO8061 Date-Time format */
#define sE17    0


/* @pr2 -----------------------------------------*/
/* Uniface internal packing codes                */
/* moved from libpack.h to here for URB-CC Split */
/*-----------------------------------------------*/
#define F4LE    1                               /* IEEE F4 float little endian */
#define F8LE    2                               /* IEEE F8 float little endian */
#define F16LE   3                               /* IEEE F16 float little endian */
#define F4BE    4                               /* IEEE F4 float big endian */
#define F8BE    5                               /* IEEE F8 float big endian */
#define F16BE   6                               /* IEEE F16 float big endian */
#define F4VMS   7                               /* VMS private F4 floating point */
#define F8VMS   8                               /* VMS private F8 floating point */
#define G8VMS   9                               /* VMS private G8 floating point */
#define F4IBM   10                              /* IBM mainframe  private F4 floating point */
#define F8IBM   11                              /* IBM mainframe private F8 floating point */
#define F16IBM  12                              /* IBM mainframe private G8 floating point */

/*************************************************/
/* Defines specific to specific packingcodes     */
/*************************************************/
/* @c25825 : */
#define E15_NO_DATE_YEAR     1753
#define E15_NO_DATE_MONTH    1
#define E15_NO_DATE_DAY      1

#endif /* UNIPCK_H */
