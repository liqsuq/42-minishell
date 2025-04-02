#!/bin/bash

STATUS=0

assert() {
	# テストしようとしている内容をprint
	printf '%-54s:' "\"$1\""
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

debug() {
	printf '%-54s:  DEBUG\n' "\"$1\""
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

echo "+-------------------------------------------------------------------------+"
echo "|  minishell test                                                         |"
echo "+-------------------------------------------------------------------------+"

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
assert 'echo hello >hello.txt'
rm -f hello.txt
assert 'echo hello >f1>f2>f3'
rm -f f1 f2 f3
assert 'echo hello >hello.txt world'
rm -f hello.txt

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<EOF1|cat <<EOF2|ls\nhello\n\EOF1world\nEOF2'
assert 'cat <<EOF|"grep foo" <<EOFQ\nfoo\nEOF\nbar\nEOFQ'
assert 'cat <<EOF\n\n\nEOF\nNOPRINT'
assert 'cat <<EOF1 >out1 <<EOF2 >>out2\nfoo\nEOF1\nbar\nEOF2'
rm -f out1 out2
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# export EOF="eof"
# assert 'cat <<$EOF         \neof\n$EOF\nEOF'　//環境変数が必要
# assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'　//環境変数が必要

# Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'
assert 'ls -l | grep test'
assert 'echo foo | cat -e'
assert 'pwd | cat'

# Expand Variable
assert 'echo $USER'
assert 'echo $USER$HOME$PWD'
assert 'echo "$USER  $HOME   $PWD"'

# Expand Parameter
assert 'echo $?'
assert 'true\necho $?'
assert 'false\necho $?'
assert 'true\n\necho $?'
assert 'false\n\necho $?'

# Word Splitting
export MINISHTESTER1="hello    world"
export MINISHTESTER2="    hello world"
export MINISHTESTER3="hello world    "
assert 'echo $MINISHTESTER1 | cat -e'
assert 'echo "$MINISHTESTER1" | cat -e'
assert 'echo $MINISHTESTER2 | cat -e'
assert 'echo "$MINISHTESTER2" | cat -e'
assert 'echo $MINISHTESTER3 | cat -e'
assert 'echo "$MINISHTESTER3" | cat -e'
unset MINISHTESTER1 MINISHTESTER2 MINISHTESTER3

echo "==========================================================================="
if [ $STATUS -eq 0 ]; then
	echo "All tests passed"
else
	echo "Some tests failed"
fi
clean
exit $STATUS
