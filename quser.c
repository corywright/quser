/*******************************************************************************
 *                                                                             *
 * This file is part of quser.                                                 *
 *                                                                             *
 * $Id: quser.c,v 1.4 2002/09/30 13:43:15 cwright Exp $                        *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "quser.h"

int addressmatch(char *sender, char match[MAX_ADDRESS]) {
  char *endofline;
  char *senderdomain;
  int matches=0;
  int i=0;
  int j=0;

  for(i=0;i<sizeof(sender);i++) sender[i] = tolower(sender[i]);
  for(j=0;j<sizeof(match);j++) match[j] = tolower(match[j]);
  printf("s:%s, m:%s\n",sender,match);

  endofline=(strchr(match,'\n'));
  if(endofline!=NULL) *endofline='\0';
  if(strcmp(sender,match) == 0) {
    matches=1;
  } else {
    if(match[0]=='@') match++;
    if(strchr(match,'@')==NULL) {
      if((senderdomain=strrchr(sender,'@'))!=NULL) {
	if(strcmp(++senderdomain,match) == 0) {
	  matches=1;
	}
      }
    }
  }
  return (matches==0) ? 0 : 1;
}

int getMessages(char *fldr) {

  DIR *dir;
  struct dirent *entry;
  int mesg = 0;

  if((dir = opendir(fldr)) != NULL) {
    while((entry = readdir(dir)) != NULL)
      if((entry->d_name)[0] != '.') ++mesg;
    closedir(dir);
  } else {
    fprintf(stderr,"cmaildir: cannot open dir: %s\n",fldr);
    mesg = -1;
  }

  return mesg;
}
