out=0

function test_rule()
{
	if [ -z "$1" ]; then
		printf "rule: (default) "
	else
		printf "rule: "$1" "
	fi
	make -q $1 > /dev/null 2> /dev/null;
	if [ "$?" = "2" ]; then
		printf "does not exist\n"
		out=4
	else
		printf "ok\n"
	fi
}

test_rule clean
test_rule fclean
test_rule re
test_rule all
test_rule $1

echo "testing build..."

make > /dev/null
make -q > /dev/null 2> /dev/null;

if [ $? = 1 ]; then
	echo "potential relink"
	out+=2
fi

exit $out
