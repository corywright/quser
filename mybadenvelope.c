/*******************************************************************************
 *                                                                             *
 * This file is part of quser.   http://projects.standblue.net/software/quser  *
 *                                                                             *
 * $Id: mybadenvelope.c,v 1.1 2002/10/01 04:01:20 cwright Exp $                *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quser.h"

#ifdef MAILFROM
 #define QUSERPROG "mybadmailfrom"
 #define ENVVAR "SENDER"
#endif

#ifdef RCPTTO
 #define QUSERPROG "mybadrcptto"
 #define ENVVAR "RECIPIENT"
#endif

int main(int argc, char **argv) {
  FILE *fp;
  char match[MAX_ADDRESS];
  char *address;
  int accept=1;

  if(argc < 2) {
    fprintf(stderr,"%s: No address file given",QUSERPROG);
    exit(100);
  }

  if((address=getenv(ENVVAR))==NULL) {
    fprintf(stderr,"%s: No %s set",QUSERPROG,ENVVAR);
    exit(100);
  }

  if((fp=fopen(*++argv,"r"))==NULL) {
    fprintf(stderr,"%s: Could not open %s",QUSERPROG,*argv);
    exit(111);
  }

  while(fgets(match,MAX_ADDRESS,fp)) {
    if(addressmatch(address,match)) {
      accept=0;
      break;
    }
  }
  fclose(fp);

  return (accept==1) ? 0 : 100;

}
