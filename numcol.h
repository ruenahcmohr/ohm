#ifndef __numcol2
  #define __numcol2


  #include <stdint.h>
  #include <string.h>
  #include <ctype.h>
  #include <math.h>

  uint8_t numColIsMult  ( char c );
  double  numColMultVal ( char p );
  double  numColDigitVal( char p );
  double  NumColExtract ( const char *p );


#endif
