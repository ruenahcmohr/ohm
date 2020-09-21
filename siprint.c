#define _GNU_SOURCE
#include <stdio.h>



char * adoubleToPrefixS(double v) {

  char * r ;

  if(0) {  
  } else if (( v >= 1.0e-15 ) && ( v < 1.0e-12 - 1.0e-34 )) {   asprintf(&r, "%.3ff", v*1.0e+15);     
  } else if (( v >= 1.0e-12 ) && ( v < 1.0e-09 - 1.0e-34 )) {   asprintf(&r, "%.3fp", v*1.0e+12);     
  } else if (( v >= 1.0e-09 ) && ( v < 1.0e-06 - 1.0e-34 )) {   asprintf(&r, "%.3fn", v*1.0e+09);     
  } else if (( v >= 1.0e-06 ) && ( v < 1.0e-03 - 1.0e-34 )) {   asprintf(&r, "%.3fu", v*1.0e+06);     
  } else if (( v >= 1.0e-03 ) && ( v < 1.0e+00 - 1.0e-34 )) {   asprintf(&r, "%.3fm", v*1.0e+03);        
  } else if (( v >= 1.0e+00 ) && ( v < 1.0e+03 - 1.0e-34 )) {   asprintf(&r, "%.3f",  v*1.0e+00);    
  } else if (( v >= 1.0e+03 ) && ( v < 1.0e+06 - 1.0e-34 )) {   asprintf(&r, "%.3fk", v*1.0e-03);    
  } else if (( v >= 1.0e+06 ) && ( v < 1.0e+09 - 1.0e-34 )) {   asprintf(&r, "%.3fM", v*1.0e-06);      
  } else if (( v >= 1.0e+09 ) && ( v < 1.0e+12 - 1.0e-34 )) {   asprintf(&r, "%.3fG", v*1.0e-09);    
  } else if (( v >= 1.0e+12 ) && ( v < 1.0e+15 - 1.0e-34 )) {   asprintf(&r, "%.3fT", v*1.0e-12); 
  } else if (( v >= 1.0e+15 ) && ( v < 1.0e+18 - 1.0e-34 )) {   asprintf(&r, "%.3fP", v*1.0e-15); 
  } else asprintf(&r, "%e", v);
  
  return r;
}


