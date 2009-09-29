/*******************************************************************************
 *                                                                             *
 * This file is part of quser.                                                 *
 *                                                                             *
 * $Id: quser.h,v 1.4 2002/09/30 13:43:15 cwright Exp $                        *
 *                                                                             *
 ******************************************************************************/

#ifndef QUSER_H
#define QUSER_H

#define MAX_ADDRESS 1024

int addressmatch(char *sender, char match[100]);
int getMessages(char *fldr);

#endif
