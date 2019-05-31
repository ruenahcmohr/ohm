#include <math.h>
#include <stdio.h>
#include "cmnCmdOptions2.h"

#define nothing      0
#define power        1
#define current      2
#define voltage      4
#define resistance   8


void calcVR(float P, float I, float *V, float *R) ;
void calcIR(float P, float *I, float V, float *R) ;
void calcIV(float P, float *I, float *V, float R);
void calcPR(float *P, float I, float V, float *R) ;
void calcPV(float *P, float I, float *V, float R) ;
void calcPI(float *P, float *I, float V, float R);

int Help (char * argv) ;
void setupParams(CLOSet_t ** options) ;
int SetP  (char * argv) ;
int SetI  (char * argv) ;
int SetV  (char * argv) ;
int SetR  (char * argv) ;

unsigned char given, helpOnly;
float P, I, V, R;


int main(int argc, char** argv) {
  CLOSet_t * options;
  
  options  = NULL;
  given    = nothing;
  helpOnly = 0;
  
  setupParams(&options); // define the arguments
  parseOptions(options, argc-1, &argv[1]);   // then parse the command line
  
  if (helpOnly)
    return 0;
  
  switch(given) {
    case nothing:
      printf("You need to know about the paramiter --help.\n");
      return 1;
    break;
  
    case (power+current):
      calcVR(P, I, &V, &R);
    break;
    
    case (power+voltage):
      calcIR(P, &I, V, &R);
    break;    
    
    case (power+resistance):
      calcIV(P, &I, &V, R);
    break;          
    
    case (current+voltage):
      calcPR(&P, I, V, &R);
    break;
    
    case (current+resistance):
      calcPV(&P, I, &V, R);
    break;   
    
    case (voltage+resistance):
      calcPI(&P, &I, V, R);
    break;
        
    default:
      printf("You need to specify two of the paramiters\n");
      return 2;
    break;    
    
  }  
    
  printf("Wattage is:       %f\n", P);
  printf("Current is:       %f\n", I);
  printf("Voltage is:       %f\n", V);
  printf("Resistance is :   %f\n", R);

  
  cmdLineOptionFini(&options);
  return 0;

}

void setupParams(CLOSet_t ** options) {

  // this is outright ugly, but we have to because of limits to C
  static char* optsPower[2] =       {"-p","--power"};
  static char* optsCurrent[2] =     {"-i","--current"};
  static char* optsVoltage[2] =     {"-v","--voltage"};
  static char* optsResistance[2] =  {"-r","--resistance"};
  static char* optsHelp[2] =        {"-h","--help"};

  // first init 
  cmdLineOptionInit(options);
  // then add your options (note I ignore any errors (BAD! BAD!))
  addCmdLineOption(*options, optsPower,      2, SetP);
  addCmdLineOption(*options, optsCurrent,    2, SetI);
  addCmdLineOption(*options, optsVoltage,    2, SetV);
  addCmdLineOption(*options, optsResistance, 2, SetR);
  addCmdLineOption(*options, optsHelp,       2, Help);
}

int Help (char * argv) {
  printf("This program solves resistance stuff.\n\n");
  printf("-h --help            is the help your looking at\n");
  printf("-p --power            watts from load\n");
  printf("-i --current          current thru load\n");
  printf("-v --voltage          voltage across load\n");
  printf("-r --resistance       resistance of load\n");
 
  
  helpOnly = 1;
  return 0;
}

int SetP (char * argv) {
  P = atof(argv);
  given |= power;
  return 1;
}

int SetI (char * argv) {
  I = atof(argv);
  given |= current;
  return 1;
}

int SetV (char * argv) {
  V = atof(argv);
  given |= voltage;
  return 1;
}

int SetR (char * argv) {
  R = atof(argv);
  given |= resistance;
  return 1;
}


// ----=====| sphere conversions |=====-----

void calcVR(float P, float I, float *V, float *R) {
   *V = P/I;
   *R = (*V)/I;
}


void calcIR(float P, float *I, float V, float *R) {
   *I = P/V;
   *R = V/(*I);
}


void calcIV(float P, float *I, float *V, float R) {
   *I = sqrt(P/R);
   *V = P/(*I);
}


void calcPR(float *P, float I, float V, float *R) {
   *P = I*V;
   *R = V/I;
}

void calcPV(float *P, float I, float *V, float R) {
   *V = I*R;
   *P = (*V)*I;
}


void calcPI(float *P, float *I, float V, float R) {
   *I = V/R;
   *P = V*(*I);
}

