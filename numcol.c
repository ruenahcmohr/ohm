/*
15
1.2
4.7k
10M
1.5u
104p
15n
1.2m
1k2
-10.5k
-0.4k
+10


(+-)(dig?)(. | m)(dig?)(m?)(e?(+|-)dig*)
*/

#include "numcol.h"

uint8_t numColIsMult(char c) {
  return (strchr("pnumkMGTP", c) != 0);
}

double numColMultVal(char p) {
   switch(p) {
     case 'p': return 1/1000000000000.0;
     case 'n': return 1/1000000000.0;
     case 'u': return 1/1000000.0;
     case 'm': return 1/1000.0;
     case 'k': return 1000.0;
     case 'M': return 1000000.0;
     case 'G': return 1000000000.0;
     case 'T': return 1000000000000.0;
     case 'P': return 1000000000000000.0;
   }
   return 1; // hey error! error!
}

// needs to already be filtered!
double numColDigitVal(char p) {
  return (p - '0') * 1.0;
}

//  If there is a parse error this reuturns NAN
//  this function is a *bit* longer than I like, and this comment isn't helping.
double NumColExtract(const char *p) {

  double  sign          = 1.0,  // read carefully....
          answer        = 0.0,
          multp         = 10., 
          fract         = 1.0,
	  exp           = 0.0;
  uint8_t haveMult      = 0.0;
  float   exps          = 1.0;

  if (! *p) return 0;

  switch(*p) {
    case '-':   sign = -1;   p++;   break;
    case '+':                p++;   break;
  }

  for (; *p; p++) {
    if (0) {
    } else if ( isdigit(*p)) {
      answer *= multp;
      answer += numColDigitVal(*p)*fract;
      if (fract != 1) fract /= 10;
    } else if ( *p == '.') {
      if (fract != 1) return NAN;              // its already a fraction of some kind!
      multp = 1;  fract = 0.1;
    } else if ( numColIsMult(*p)) {
      if (haveMult != 0) return NAN;           // only one...
      haveMult = 1;
      sign *= numColMultVal(*p);
      if (fract != 1) return answer*sign;      // there was already a '.', so were done.
      multp = 1;   fract = 0.1;
    } else if ( (*p == 'e') || (*p == 'E' )) { // scientific notation, dead end street!
      if (haveMult != 0) return NAN;           // cant mix those
      p++; 
      if        (*p == '+') { p++;
      } else if (*p == '-') { p++;
        exps = -1;
      } else return NAN;
      for (; *p; p++) {                        // I know eh? but its not *QUITE* recursion @$!@%!@#$
        if (isdigit(*p)) {
	  exp *= 10;
	  exp += numColDigitVal(*p);
	} else return NAN;                     // only regular digits from here!
      } 
      return answer*sign*pow(10, exp*exps);    // and now you have to compile with -lm HA.HA.
    } else {                                   
      return NAN;                              // garbage!!!!
    }
  }
  return answer*sign;                          // must have been an easy one
}
