
/* UCMS_VERSION_ID("@(#)metaphone.c 71B1:1 readonly 24-sep-96 15:01:00(#)@") */
//---------------------------------------------------------------------------
// METAPHONE
//
// This DLL provides SOUNDEX like functionality via metaphone
//
// Copyright (c) Uniface 1997. All rights reserved.
//
// You have a royalty-free right to use, modify, reproduce and distribute
// this sample code (and/or any modified version) in any way you find useful,
// provided that you agree that Uniface has no warranty obligations or
// liability for any sample code which has been modified.
//
//
// The original author is unknown but all credit goes to him/her for the implementation.
//
//
//-seq--chg#--date----who--description---------------------------------------
//   0  6042  970703  tss  created
//---------------------------------------------------------------------------

#include <windows.h>            
#include <windef.h>
#include <windowsx.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <owimsw.h>
#include <owi.h>
#include <umsw3gl.h>
#include <errno.h>
#include <ctype.h>






/* Character coding array */
static char vsvfn[26] = {
		1,16,4,16,9,2,4,16,9,2,0,2,2,2,1,4,0,2,4,4,1,0,0,0,8,0};
/*  A  B C  D E F G  H I J K L M N O P Q R S T U V W X Y Z */

/* Macros to access character coding array */
#define vowel(x)  (vsvfn[(x) - 'A'] & 1)  /* AEIOU */
#define same(x)   (vsvfn[(x) - 'A'] & 2)  /* AEIOU */
#define varson(x) (vsvfn[(x) - 'A'] & 4)  /* AEIOU */
#define frontv(x) (vsvfn[(x) - 'A'] & 8)  /* AEIOU */
#define noghf(x)  (vsvfn[(x) - 'A'] & 16) /* AEIOU */
/* End of Metaphone */

//---------------------------------------------------------------------------
// CONSTANTS
//---------------------------------------------------------------------------

#define MAXMETAPH  4

#define REG0  50                       // Register numbers for communication
#define REG1  REG0 + 1
#define REG2  REG0 + 2
#define REG3  REG0 + 3
#define REG4  REG0 + 4
#define REG_RESULT	101

#define MS 80


XEXPORT(long)   metaphone(char *Word, char *Metaph)
{
	char *n, *n_start, *n_end;  /* pointers to string */
	char *metaph, *metaph_end;  /* pointers to metaph */
	char ntrans[32];            /* word with uppercase letters */
	char newm[8];               /* new metaph for comparison */
	int KSflag;                 /* state flag for X translation */
	int Flag = 1;
	/*
	** Copy Word to internal buffer, dropping non-alphabetic
	** charactes and converting to uppercase.
	*/
	for(n = ntrans + 1, n_end = ntrans + 30;
		*Word && n < n_end; Word++)
		if(isalpha(*Word)) *n++ = toupper(*Word);

	if(n == ntrans + 1) return -1;  /* return if 0 bytes */
	n_end = n;                      /* set n_end to end of string */

	/* ntrans[0] will always be == 0 */
	*n++ = 0; *n = 0; /* pad with nulls */
	n = ntrans + 1;   /* assign pointer to start */

	/* if doing a comparision, redirect pointers */
	if(!Flag) { metaph = Metaph; Metaph = newm; }

	/* check for PN KN GN AE WR WH and X at start */
	switch(*n) {
		case 'P': case 'K': case 'G':
			if(*(n + 1) == 'N') *n++ = 0;
			break;
		case 'A':
			if(*(n + 1) == 'E') *n++ = 0;
			break;
		case 'W':
			if(*(n + 1) == 'R') *n++ = 0;
			else if(*(n + 1) == 'H') {
				*(n + 1) = *n;
				*n++ = 0;
			}
			break;
		case 'X':
			*n = 'S';
			break;
	}

	/*
	** Now, loop step through string, stopping at end of string
	** or when the computed 'metaph' is MAXMETAPH characters long
	*/
	KSflag = 0; /* state flag for KS translation */
	for(metaph_end = Metaph + MAXMETAPH, n_start = n;
		n <= n_end && Metaph < metaph_end; n++) {

		if (KSflag) {
			KSflag = 0;
			*Metaph++= *n;
		}
		else {
			/* drop duplicates except for CC */
			if(*(n - 1) == *n && *n != 'C') continue;

			/* check for F J L M N R or first letter vowel */
			if(same(*n) || (n == n_start && vowel(*n)))
				*Metaph++ = *n;
			else switch(*n) {
				case 'B':
					if(n < n_end || *(n - 1) != 'M')
						*Metaph++ = *n;
					break;
				case 'C':
					if(*(n - 1) != 'S' || !frontv(*(n + 1))) {
						if(*(n + 1) == 'I' && *(n + 2) == 'A')
							*Metaph++ = 'X';
						else if(frontv(*(n + 1))) *Metaph++ = 'S';
						else if(*(n + 1) == 'H')
							*Metaph++ = ((n == n_start &&
							!vowel(*(n + 2))) ||
							*(n - 1) == 'S')
							? (char)'K' : (char)'X';
						else *Metaph++ = 'K';
					}
					break;
				case 'D':
					*Metaph++ = (*(n + 1) == 'G' && frontv(*(n + 2)))
						? (char)'J' : (char)'T';
					break;
				case 'G':
					if((*(n + 1) != 'H' || vowel(*(n + 2))) &&
						(*(n + 1) != 'N' || ((n + 1) < n_end &&
						(*(n + 2) != 'E' || *(n + 3) != 'D'))) &&
						(*(n - 1) != 'D' || !frontv(*(n + 1))))
						*Metaph++ = (frontv(*(n + 1)) &&*(n + 2) != 'G')
						? (char)'J' : (char)'K';
					else if(*(n + 1) == 'H' && !noghf(*(n - 3))
						&& *(n - 4) != 'H') *Metaph++ = 'F';
					break;
				case 'H':
					if(!varson(*(n - 1)) && (!vowel(*(n - 1)) ||
						vowel(*(n + 1)))) *Metaph++ = 'H';
					break;
				case 'K':
					if(*(n - 1) != 'C') *Metaph++ = 'K';
					break;
				case 'P':
					*Metaph++ = *(n + 1) == 'H'
						? (char)'F' : (char)'P';
					break;
				case 'Q':
					*Metaph++ = 'K';
					break;
				case 'S':
					*Metaph++ = (*(n + 1) == 'H' || (*(n + 1) == 'I'
						&& (*(n + 2) == 'O' || *(n + 2) == 'A')))
						? (char)'X' : (char)'S';
					break;
				case 'T':
					if(*(n + 1) == 'I' && (*(n + 2) == 'O'
						|| *(n + 2) == 'A'))
						*Metaph++ = 'X';
					else if(*(n + 1) == 'H') *Metaph++ = 'O';
					else if(*(n + 1) != 'C' || *(n + 2) != 'H')
						*Metaph++ = 'T';
					break;
				case 'V':
					*Metaph++ = 'F';
					break;
				case 'W': case 'Y':
					if(vowel(*(n + 1))) *Metaph++ = *n;
					break;
				case 'X':
					if(n == n_start) *Metaph++ = 'S';
					else {
						*Metaph++ = 'K'; /* insert K, then S */
						KSflag = 1; /* this flag will cause S to be
													 inserted on next pass thru loop */
					}
					break;
				case 'Z':
					*Metaph++ = 'S';
					break;
			}
		}

		/* compare new metaph with old */
		if(!Flag && *(Metaph - 1) != metaph[(Metaph - newm) - 1])
			return -1;
	}

	/* If comparing, check if metaphs were equal in length. */
	if(!Flag && metaph[Metaph - newm])
		return -1;

	*Metaph = 0; /* null terminate return value */
	return 0;
}
