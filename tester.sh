#!/bin/bash

export LC_ALL=C

STATUS=0

assert() {
	# テストしようとしている内容をprint
	if [ $1 -eq 1 ]; then
		printf '%-54s:' "\"$2\""
	fi
	# bashの出力をactualに保存
	echo -n -e "$2" | bash >expected 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をexpectedに保存
	echo -n -e "$2" | ./minishell >actual 2>&-
	# minishellのexit statusをactualに代入
	actual=$?
	# bashとminishellの出力を比較
	diff expected actual >/dev/null
	if [ $? -eq 0 ]; then
		echo -n '  diff OK'
	else
		echo -n '  diff NG'
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

print_desc() {
	printf '%-54s:' "\"$1\""
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
assert 1 ''
assert 1 '    '
assert 1 '\t'
assert 1 '$NOVAR'

# Absolute path commands without args
assert 1 '/bin/pwd'
assert 1 '/bin/echo'

# Search command path without args
assert 1 'pwd'
assert 1 'echo'
assert 1 'ls'
assert 1 './a.out'

# no such command
assert 1 'a.out'
assert 1 'nosuchfile'
assert 1 '/nosuchfile'

# Unquoted args
assert 1 'ls /'
assert 1 'echo hello    world'
assert 1 \'\'
assert 1 \''/bin/ls test'\'

# Single quote
assert 1 'echo '\''hello   world'\'' '\''42Tokyo'\'
assert 1 'echo hello'\''      world'\'

# Double quote
assert 1 'echo '\"'hello   world'\"' '\"'42Tokyo'\"
assert 1 'echo hello'\"'      world'\"
assert 1 \"\"
assert 1 \"'/bin/ls test'\"

# Combined quote
assert 1 'echo '\'\"'hello   world'\"\'' '\''42Tokyo'\'
assert 1 'echo '\"\''hello   world'\'\"' '\"'42Tokyo'\"
assert 1 'echo hello'\''  world  '\'\"'  42Tokyo  '\"

## Redirecting output
assert 1 'echo hello >hello.txt'
rm -f hello.txt
assert 1 'echo hello >f1>f2>f3'
rm -f f1 f2 f3
assert 1 'echo hello >hello.txt world'
rm -f hello.txt
assert 1 '>'
assert 1 'echo >'
assert 1 '>>'
assert 1 'echo >>'
assert 1 'echo > >>'
assert 1 '> .'
assert 1 '> asd'
rm -f asd
assert 1 'echo hello > $NOVAR'

## Redirecting input
assert 1 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 1 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 1 'cat <hoge'
assert 1 '<'
assert 1 'cat <'

## Here Document
assert 1 'cat <<EOF\nEOF'
assert 1 'cat <<EOF\nhello\nworld\nEOF'
assert 1 'cat <<EOF\nhello\nworld'
assert 1 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 1 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 1 'cat <<EOF1|cat <<EOF2|ls\nhello\n\EOF1world\nEOF2'
assert 1 'cat <<EOF|"grep foo" <<EOFQ\nfoo\nEOF\nbar\nEOFQ'
assert 1 'cat <<EOF\n\n\nEOF\nNOPRINT'
assert 1 'cat <<EOF1 >out1 <<EOF2 >>out2\nfoo\nEOF1\nbar\nEOF2'
rm -f out1 out2
assert 1 'cat <<EOF\n$USER $HOME $PWD\nEOF'
assert 1 'cat <<EOF\n'\"'$USER $HOME $PWD'\"'\nEOF'
assert 1 'cat <<EOF\n'\''$USER $HOME $PWD'\''\nEOF'
assert 1 'cat <<'\"'EOF'\"'\n$USER $HOME $PWD\nEOF'
assert 1 'cat <<'\"'EOF'\"'\n'\"'$USER $HOME $PWD'\"'\nEOF'
assert 1 'cat <<'\"'EOF'\"'\n'\''$USER $HOME $PWD'\''\nEOF'
assert 1 'cat <<'\''EOF'\''\n$USER $HOME $PWD\nEOF'
assert 1 'cat <<'\''EOF'\''\n'\"'$USER $HOME $PWD'\"'\nEOF'
assert 1 'cat <<'\''EOF'\''\n'\''$USER $HOME $PWD'\''\nEOF'
assert 1 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 1 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 1 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 1 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
export EOF="eof"
assert 1 'cat <<$EOF         \neof\n$EOF\nEOF'
assert 1 'cat <<"$EOF"       \neof\n$EOF\nEOF'
unset EOF
assert 1 '<<'
assert 1 'cat <<'
assert 1 'echo test > .'
assert 1 'echo test | echo test > .'
assert 1 'echo test > . | echo test'

# Pipe
assert 1 'cat Makefile | grep minishell'
assert 1 'cat | cat | ls\n\n'
assert 1 'ls -l | grep test'
assert 1 'echo foo | cat -e'
assert 1 'pwd | cat'
assert 1 '|'
assert 1 'echo foo |'
assert 1 'echo > | ls'

# Expand Variable
assert 1 'echo $USER'
assert 1 'echo $USER$HOME$PWD'
assert 1 'echo "$USER  $HOME   $PWD"'
assert 1 '$NOVAR'
assert 1 '$NOVAR $NOVAR'
export PIPECHAR="|" OUTCHAR=">" INCHAR="<" APPENDCHAR=">>" HEREDOCCHAR="<<"
assert 1 'echo $PIPECHAR'
assert 1 'echo $OUTCHAR'
assert 1 'echo $INCHAR'
assert 1 'echo $APPENDCHAR'
assert 1 'echo $HEREDOCCHAR'
unset PIPECHAR OUTCHAR INCHAR APPENDCHAR HEREDOCCHAR

# Expand Parameter
assert 1 'echo $?'
assert 1 'true\necho $?'
assert 1 'false\necho $?'
assert 1 'true\n\necho $?'
assert 1 'false\n\necho $?'
assert 1 'true\necho "$?"'
assert 1 'false\necho "$?"'

# Word Splitting
export MINISHTESTER1="hello    world"
export MINISHTESTER2="    hello world"
export MINISHTESTER3="hello world    "
assert 1 'echo $MINISHTESTER1 | cat -e'
assert 1 'echo "$MINISHTESTER1" | cat -e'
assert 1 'echo $MINISHTESTER2 | cat -e'
assert 1 'echo "$MINISHTESTER2" | cat -e'
assert 1 'echo $MINISHTESTER3 | cat -e'
assert 1 'echo "$MINISHTESTER3" | cat -e'
unset MINISHTESTER1 MINISHTESTER2 MINISHTESTER3
assert 1 'echo "" | cat -e'
assert 1 '"" ls'
unset NOVAR
assert 1 '$NOVAR ls'
assert 1 '"$NOVAR" ls'
assert 1 'echo $NOVAR | cat -e'
assert 1 'echo "$NOVAR" | cat -e'
assert 1 'echo $NOVAR test | cat -e'
assert 1 'echo "$NOVAR" test | cat -e'
assert 1 'echo $NOVAR test $NOVAR | cat -e'
assert 1 'echo "$NOVAR" test "$NOVAR" | cat -e'

# Signal
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -n -SIGTERM bash;
 sleep 0.01; pkill -n -SIGTERM minishell) &
assert 0 'sleep 10' 2>/dev/null

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -n -SIGQUIT bash; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -n -SIGTERM bash;
 sleep 0.01; pkill -n -SIGQUIT minishell; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -n -SIGTERM minishell) &
assert 0 'sleep 10' 2>/dev/null

print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -n -SIGINT bash; # SIGINT should not kill the shell
 sleep 0.01; pkill -n -SIGTERM bash;
 sleep 0.01; pkill -n -SIGINT minishell; # SIGINT should not kill the shell
 sleep 0.01; pkill -n -SIGTERM minishell) &
assert 0 'sleep 10' 2>/dev/null

# Signal to child processes
print_desc "SIGTERM to child process"
(sleep 0.1; pkill -n -SIGTERM -f "sleep 10";
 sleep 0.1; pkill -n -SIGTERM -f "sleep 10") &
assert 0 'sleep 10'

print_desc "SIGINT to child process"
(sleep 0.1; pkill -n -SIGINT -f "sleep 10";
 sleep 0.1; pkill -n -SIGINT -f "sleep 10") &
assert 0 'sleep 10'

print_desc "SIGQUIT to child process"
(sleep 0.1; pkill -n -SIGQUIT -f "sleep 10";
 sleep 0.5; pkill -n -SIGQUIT -f "sleep 10") &
assert 0 'sleep 10'

# Manual
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF <<EOF
# >
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
# 
# $ ./minishell
# $ cat
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D
# 
# $ ./minishell
# $ cat | cat | ls
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D

# Environment variables
print_desc "(LC_ALL=ja_JP.UTF-8) ls -l minishell"
export LC_ALL="ja_JP.UTF-8"
assert 0 'ls -l minishell'
export LC_ALL="C"

# Built-in commands
## exit
assert 1 'exit'
assert 1 'exit 42'
assert 1 'exit -42'
assert 1 'exit --42'
assert 1 'exit +42'
assert 1 'exit ++42'
assert 1 'exit ""'
assert 1 'exit hello'
assert 1 'exit hello world'
assert 1 'exit 42Tokyo'
assert 1 'exit 42 Tokyo'
assert 1 'exit Tokyo 42'
assert 1 'exit 1 2'
assert 1 'exit 1024'
assert 1 'exit 9223372036854775805'
assert 1 'exit 9223372036854775806'
assert 1 'exit 9223372036854775807'
assert 1 'exit 9223372036854775808'
assert 1 'exit 9223372036854775809'
assert 1 'exit -9223372036854775806'
assert 1 'exit -9223372036854775807'
assert 1 'exit -9223372036854775808'
assert 1 'exit -9223372036854775809'
assert 1 'exit -9223372036854775810'
assert 1 'exit 3141592653589793238462643383279'

## export
export BLKLST="^OLDPWD|^SHLVL|^_="
assert 1 'export TEST=test'
assert 1 'export HOGE=test\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export HOGE=te FUGA=st\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export [NG]'
assert 1 'export [NG]\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export [NG]=test\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export [NG]=te =st\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export HO=[OK] GE=tst\nenv|sort|grep -vE "$BLKLST"'
assert 1 'export HO="HO=hoge"\nenv|sort|grep -vE "$BLKLST"'
unset BLKLST

## echo
assert 1 'echo'
assert 1 'echo hello'
assert 1 'echo hello world'
assert 1 'echo "42tokyo !#$%&()=~|{}[];:,.<>?"'
assert 1 'echo hello "    " world'
assert 1 'echo -n'
assert 1 'echo -n hello world'
assert 1 'echo -nnnnnnnn hello world'
assert 1 'echo -n -n -n -n hello world'
assert 1 'echo --n hello world'
assert 1 'echo -na hello world'
assert 1 'echo -n-n hello world'
assert 1 'echo hello world -n'
assert 1 'echo -n -n hello world -n -n'

## unset
export TEST1="hello" TEST2="world"
assert 1 'unset TEST1\necho $TEST1 $TEST2'
assert 1 'unset TEST1 TEST2\necho $TEST1 $TEST2'
assert 1 'unset NOVAR\necho $TEST1 $TEST2'
assert 1 'unset novar\necho $TEST1 $TEST2'
assert 1 'unset TEST1 TEST2\necho $TEST1 $TEST2'
assert 1 'unset TEST1 NOVAR TEST2\necho $TEST1 $TEST2'
unset TEST1 TEST2

# env
assert 1 'env | vgrep "OLDPWD|SHLVL|_="'
print_desc "export TEST1=42tokyo TEST2=; env"
export TEST1="42tokyo" TEST2=""
assert 0 'env | vgrep "OLDPWD|SHLVL|_="'
unset TEST1 TEST2

## cd
assert 1 'cd'
assert 1 'cd .'
assert 1 'cd ..'
assert 1 'cd ///'
assert 1 'cd /tmp'
assert 1 'cd /tmp/'
assert 1 'cd /tmp///'
assert 1 'cd /../../../././.././'
assert 1 'cd src'
assert 1 'cd \n echo $PWD'
assert 1 'cd \n echo $PWD'
assert 1 'cd .\n echo $PWD'
assert 1 'cd ..\n echo $PWD'
assert 1 'cd ///\n echo $PWD'
assert 1 'cd /tmp\n echo $PWD'
assert 1 'cd /tmp/\n echo $PWD'
assert 1 'cd /tmp///\n echo $PWD'
assert 1 'cd /../../../././.././\n echo $PWD'
assert 1 'cd src\n echo $PWD'
assert 1 'unset HOME\ncd \n echo $PWD'

## pwd
assert 1 'pwd'
assert 1 'cd\npwd'
assert 1 'cd src\npwd'
assert 1 'cd /etc\npwd'
assert 1 'unset PWD\npwd\ncd /etc\npwd'

echo "==========================================================================="
if [ $STATUS -eq 0 ]; then
	echo "All tests passed"
else
	echo "Some tests failed"
fi
clean
exit $STATUS
