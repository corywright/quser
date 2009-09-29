/*******************************************************************************
 *                                                                             *
 * This file is part of quser.   http://projects.standblue.net/software/quser  *
 *                                                                             *
 * $Id: validate.c,v 1.2 2002/10/01 01:22:19 cwright Exp $                     *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quser.h"

#ifdef SENDER
 #define QUSERPROG "validate-sender"
 #define ENVVAR "SENDER"
#endif

#ifdef RECIPIENT
 #define QUSERPROG "validate-recipient"
 #define ENVVAR "RECIPIENT"
#endif

int main(int argc, char **argv) {
  FILE *fp;
  char match[MAX_ADDRESS];
  char *address;
  int accept=0;

  if(argc < 2) {
    fprintf(stderr,"%s: No address list file given",QUSERPROG);
    exit(0);
  }

  if((address=getenv(ENVVAR))==NULL) {
    fprintf(stderr,"%s: No %s set",QUSERPROG,ENVVAR);
    exit(0);
  }

  if((fp=fopen(*++argv,"r"))==NULL) {
    fprintf(stderr,"%s: Could not open %s",QUSERPROG,*argv);
    exit(111);
  }

  while(fgets(match,MAX_ADDRESS,fp)) {
    if(addressmatch(address,match)) {
      accept=1;
      break;
    }
  }
  fclose(fp);

  /* output results to go into qmail logs */
  printf("%s: Found %smatch ",QUSERPROG,((accept==1)?"":"no "));
  printf("for address %s, %s",address,((accept==1)?"accepting.":"rejecting.  "));
  return (accept==1) ? 1 : 0;

}
