/**
   Request.c (c)1999 brn
   
   This file is used only during development, ignore it. It is used to compare
   this version to the new development version....
   
   Shit, rand() takes much longer than a request, hmm..
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "Hermes.h"


// Prime number of random (for colour formats) values
int rval[17]={0xf,0xff123,0x5348,0x12,0x1,0x7e80,0xff0000,0xff,0x185,0x987,
	      0xffccdd,0xeeff88,0x250e,0x091,0xfe1000,0xf000000,0xf0f0f0};


int main()
{
  HermesHandle conv;
  HermesFormat fmt_source,fmt_dest;
  int i,r;
  unsigned long timediff;
  struct timeval tv;


  srand(time(NULL));

  if (!Hermes_Init()) {
    printf("Can't initalise Hermes!");
    exit(0);
  }

  conv=Hermes_ConverterInstance(HERMES_CONVERT_NORMAL);
  if (!conv) {
    printf("Could not obtain converter instance from Hermes!\n");
    exit(1);
  }


  printf("Requesting 1000000 non-existing converters, bypassing cache\n");

  gettimeofday(&tv,NULL);
  timediff=(unsigned long)tv.tv_sec*(unsigned long)1000000+
           (unsigned long)tv.tv_usec;

  fmt_source.indexed=0;
  fmt_dest.indexed=0;

  r=1;

  for (i=0;i<1000000;i++) {
    fmt_source.bits=rand()%32;
    fmt_source.r=rval[r++]; if(r==17) r=0;
    fmt_source.g=rval[r++]; if(r==17) r=0;
    fmt_source.b=rval[r++]; if(r==17) r=0;
    fmt_source.a=rval[r++]; if(r==17) r=0;

    fmt_dest.bits=rand()%32;
    fmt_dest.r=rval[r++]; if(r==17) r=0;
    fmt_dest.g=rval[r++]; if(r==17) r=0;
    fmt_dest.b=rval[r++]; if(r==17) r=0;
    fmt_dest.a=rval[r++]; if(r==17) r=0; 

    Hermes_ConverterRequest(conv,&fmt_source,&fmt_dest);
  }

  gettimeofday(&tv,NULL);
  timediff=((unsigned long)tv.tv_sec*(unsigned long)1000000+
            (unsigned long)tv.tv_usec)-timediff;

  printf("Time elapsed: %d microseconds\n",(int)timediff);
  printf("Requests per second: %f\n",(1000000.0/(float)timediff)*1000000.0);

  Hermes_ConverterReturn(conv);
  //  Hermes_Done();

  return 0;
}






