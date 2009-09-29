/*******************************************************************************
 *                                                                             *
 * This file is part of quser.   http://projects.standblue.net/software/quser  *
 *                                                                             *
 * $Id: cmaildir.c,v 1.4 2002/09/30 15:04:48 cwright Exp $                     *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quser.h"

int main(int argc, char **argv) { 

  char *newdir=NULL;
  char *curdir=NULL;
  char *home=NULL;
  char *homemaildir=NULL;
  int strsize=0;
  int newmessages=0;
  int curmessages=0;
  int tnew,tcur;

  if(argc == 1) {
    if((home=getenv("HOME")) == NULL) {
      fprintf(stderr,"cmaildir: $HOME is undefined\n");
      exit(1);
    }
    strsize=(strlen(home)*sizeof(char))+9;
    homemaildir=malloc(strsize);
    sprintf(homemaildir,"%s%s",home,"/Maildir");
    *argv = homemaildir;
  } else {
    *argv++;
  }

  while(*argv != NULL) {
    strsize=(strlen(*argv)*sizeof(char))+6;
    newdir=malloc(strsize);
    curdir=malloc(strsize);
    sprintf(newdir,"%s%s",*argv,"/new/");
    sprintf(curdir,"%s%s",*argv,"/cur/");
    tnew = getMessages(newdir);
    tcur = getMessages(curdir);
    newmessages += (tnew > 0) ? tnew : 0;
    curmessages += (tcur > 0) ? tcur : 0;
    free(newdir);
    free(curdir);
    *argv++;
  }

  printf("You have ");
  if(newmessages > 0)
    printf("\033[1;32m%i\033[m",newmessages);
  else
    printf("%i",newmessages);

  printf(" new messages, %i saved\n",curmessages);
  return 0;

}
