#!/bin/bash

STATUS=0

assert() {
	# テストしようとしている内容をprint
	printf '%-49s:' "\"$1\""
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

gen_aout() {
	cat <<EOF >a.out
#!/bin/bash
echo "Hello, world!"
EOF
	chmod +x a.out
}

del_aout() {
	rm -f a.out
}

clean() {
	rm -f expected actual
	del_aout
}

gen_aout

echo "+--------------------------------------------------------------------+"
echo "|  minishell test                                                    |"
echo "+--------------------------------------------------------------------+"

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

# Unquoted args
assert 'ls /'
assert 'echo hello    world'

# Single quote
assert 'echo '\''hello   world'\'' '\''42Tokyo'\'
assert 'echo hello'\''      world'\'

# Double quote
assert 'echo '\"'hello   world'\"' '\"'42Tokyo'\"
assert 'echo hello'\"'      world'\"

# Combined quote
assert 'echo '\'\"'hello   world'\"\'' '\''42Tokyo'\'
assert 'echo '\"\''hello   world'\'\"' '\"'42Tokyo'\"
assert 'echo hello'\''  world  '\'\"'  42Tokyo  '\"

## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
rm -f hello.txt
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'
rm -f f1 f2 f3

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3' # 環境設定が必要execve()でNULLを渡しているから通らない
rm -f f1 f2 f3
assert 'cat <hoge'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
# assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT' //「クォートを解除して文字列を連結する」機能が未実装
# assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF' //環境変数が必要
# assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF' //環境変数が必要
# assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF' //環境変数が必要
# export EOF="eof"
# assert 'cat <<$EOF         \neof\n$EOF\nEOF'　//環境変数が必要
# assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'　//環境変数が必要

echo "======================================================================"
if [ $STATUS -eq 0 ]; then
	echo "All tests passed"
else
	echo "Some tests failed"
fi
clean
exit $STATUS
