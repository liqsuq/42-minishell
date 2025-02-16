#!/bin/bash

STATUS=0

assert() {
	# テストしようとしている内容をprint
	printf '%-30s:' "\"$1\""
	# bashの出力をactualに保存
	echo -n -e "$1" | bash >expected 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をexpectedに保存
	echo -n -e "$1" | ./minishell >actual 2>&-
	# minishellのexit statusをactualに代入
	actual=$?
	# bashとminishellの出力を比較
	diff expected actual >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'
	if [ $? -ne 0 ]; then
		STATUS=1
	fi
	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
		STATUS=1
	fi
	echo
}

clean() {
	rm -f expected actual
}

echo "+-------------------------------------------------+"
echo "|  minishell test                                 |"
echo "+-------------------------------------------------+"

# Empty line (EOF)
assert ''

# Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

# no such command
assert 'a.out'
assert 'nosuchfile'

echo "==================================================="
if [ $STATUS -eq 0 ]; then
	echo "All tests passed"
else
	echo "Some tests failed"
fi
clean
exit $STATUS
