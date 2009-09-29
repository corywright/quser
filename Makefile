# $Id: Makefile,v 1.8 2002/10/01 04:46:56 cwright Exp $

all: validate-sender validate-recipient mybadmailfrom mybadrcptto cmaildir

validate-sender: validate.c quser.o
	gcc -Wall -DSENDER -o validate-sender quser.o validate.c

validate-recipient: validate.c quser.o
	gcc -Wall -DRECIPIENT -o validate-recipient quser.o validate.c

mybadmailfrom: mybadenvelope.c quser.o
	gcc -Wall -DMAILFROM -o mybadmailfrom quser.o mybadenvelope.c

mybadrcptto: mybadenvelope.c quser.o
	gcc -Wall -DRCPTTO -o mybadrcptto quser.o mybadenvelope.c

cmaildir: cmaildir.c quser.o
	gcc -o cmaildir quser.o cmaildir.c

quser.o: quser.c quser.h
	gcc -Wall -O1 -c quser.c

install: validate-sender validate-recipient \
	mybadmailfrom mybadrcptto cmaildir
	/usr/bin/install -s -g qmail -c validate-sender /var/qmail/bin/
	/usr/bin/install -s -g qmail -c validate-recipient /var/qmail/bin/
	/usr/bin/install -s -g qmail -c mybadmailfrom /var/qmail/bin/
	/usr/bin/install -s -g qmail -c mybadrcptto /var/qmail/bin/
	/usr/bin/install -s -c cmaildir /usr/local/bin/

clean:
	rm -f core validate-sender validate-recipient mybadmailfrom \
	mybadrcptto cmaildir quser.o

test: validate-sender validate-recipient mybadmailfrom mybadrcptto test.sh
	bash test.sh
