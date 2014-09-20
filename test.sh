#!/bin/sh

echo '$Id: test.sh,v 1.5 2002/10/01 04:01:20 cwright Exp $'
echo

total=$((0))
passed=$((0))
failed=$((0))

chret() {
    should=$1
    actual=$2
    shift
    shift
    echo
    total=$(($total+1))
    echo -n "Should return $should: "
    if [ "$should" = "$actual" ]; then
	passed=$((passed+1))
	echo "Passed"
    else
	failed=$((failed+1))
	echo "Failed ($actual)"
    fi
    echo
}

echo " * Testing the validate-sender program"
echo

echo "Testing empty \$SENDER"
./validate-sender list
chret "0" $?

echo "Testing with no parameters"
env SENDER="a@b.com" ./validate-sender
chret "0" $?

echo "Testing nonexistant file"
env SENDER="a@b.com" ./validate-sender nolist
chret "111" $?

echo "Testing a@a.com"
env SENDER="a@a.com" ./validate-sender addylist
chret "0" $?

echo "Testing a@b.com"
env SENDER="a@b.com" ./validate-sender addylist
chret "1" $?

echo "Testing a@c.com"
env SENDER="a@c.com" ./validate-sender addylist
chret "1" $?

echo "Testing a@d.com"
env SENDER="a@d.com" ./validate-sender addylist
chret "1" $?

echo " * Testing the validate-recipient program"
echo

echo "Testing empty \$RECIPIENT"
./validate-recipient list
chret "0" $?

echo "Testing with no parameters"
env RECIPIENT="a@b.com" ./validate-recipient
chret "0" $?

echo "Testing nonexistant file"
env RECIPIENT="a@b.com" ./validate-recipient nolist
chret "111" $?

echo "Testing a@a.com"
env RECIPIENT="a@a.com" ./validate-recipient addylist
chret "0" $?

echo "Testing a@b.com"
env RECIPIENT="a@b.com" ./validate-recipient addylist
chret "1" $?

echo "Testing a@c.com"
env RECIPIENT="a@c.com" ./validate-recipient addylist
chret "1" $?

echo "Testing a@d.com"
env RECIPIENT="a@d.com" ./validate-recipient addylist
chret "1" $?

echo " * Testing the mybadmailfrom program"
echo

echo "Testing empty \$SENDER"
./mybadmailfrom list
chret "100" $?

echo "Testing with no parameters"
env SENDER="a@b.com" ./mybadmailfrom
chret "100" $?

echo "Testing nonexistant file"
env SENDER="a@b.com" ./mybadmailfrom nolist
chret "111" $?

echo "Testing a@a.com"
env SENDER="a@a.com" ./mybadmailfrom addylist
chret "0" $?

echo "Testing a@b.com"
env SENDER="a@b.com" ./mybadmailfrom addylist
chret "100" $?

echo "Testing a@c.com"
env SENDER="a@c.com" ./mybadmailfrom addylist
chret "100" $?

echo "Testing a@d.com"
env SENDER="a@d.com" ./mybadmailfrom addylist
chret "100" $?

echo " * Testing the mybadrcptto program"
echo

echo "Testing empty \$RECIPIENT"
./mybadrcptto list
chret "100" $?

echo "Testing with no parameters"
env RECIPIENT="a@b.com" ./mybadrcptto
chret "100" $?

echo "Testing nonexistant file"
env RECIPIENT="a@b.com" ./mybadrcptto nolist
chret "111" $?

echo "Testing a@a.com"
env RECIPIENT="a@a.com" ./mybadrcptto addylist
chret "0" $?

echo "Testing a@b.com"
env RECIPIENT="a@b.com" ./mybadrcptto addylist
chret "100" $?

echo "Testing a@c.com"
env RECIPIENT="a@c.com" ./mybadrcptto addylist
chret "100" $?

echo "Testing a@d.com"
env RECIPIENT="a@d.com" ./mybadrcptto addylist
chret "100" $?



echo " * Results *"
echo " Tests Taken:  $(($total-0))"
echo " Tests Passed: $(($passed-0))"
echo " Tests Failed: $(($failed-0))"
