
/****** METAPHONE */

int metaphone(char *,char *, int);
#include <ctype.h>

#define MAXMETAPH  4


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
