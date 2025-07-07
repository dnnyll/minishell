# empty inputs
																												FINAL VERIFICATION
""										okay, return value is 127	Leaks because of env, normal				okay, return value is 127
""""									okay, return value is 127	Leaks because of env, normal				okay, return value is 127
''										okay, return value is 127	Leaks because of env, normal				okay, return value is 127
" "										okay, return value is 127	Leaks because of env, normal				okay, return value is 127
"	"									okay, return value is 127	Leaks because of env, normal				okay, return value is 127
# builtin commands
echo									okay, return value is 0		No leaks									okay, return value is 0
echo ""									okay, return value is 0		No leaks									okay, return value is 0
echo Hello World						okay, return value is 0		No leaks									okay, return value is 0
echo "Hello World"						okay, return value is 0		No leaks									okay, return value is 0
echo -n Hello World						okay, return value is 0		No leaks									okay, return value is 0
echo -n									okay, return valus is 0		No leaks									okay, return value is 0
echo -n -n Hello World					okay, return value is 0		No leaks									okay, return value is 0
echo -nnnnnnnnnnnnn Hello World			okay, return value is 0		No leaks									okay, return value is 0
echo Hello -n World						okay, return value is 0		No leaks									okay, return value is 0
cd										okay, return value is 0		No leaks									okay, return value is 0
cd ""									okay, return value is 0		No leaks									okay, return value is 0
cd " "									okay, return value is 1		No leaks									okay, return value is 1
cd Hello								okay, return value is 1		No leaks									okay, return value is 1
cd ..									okay, return value is 0		No leaks									okay, return value is 0
cd /home								okay, return value is 0		No leaks									okay, return value is 0
pwd										okay, return value is 0		No leaks									okay, return value is 0
pwd Hello World							okay, return value is 0		No leaks									okay, return value is 0
export									okay, return value is 0		No leaks									okay, return value is 0
export ""								okay, return value is 1		No leaks									okay, return value is 1
export TEST								okay, return value is 0		No leaks									okay, return value is 0
export TEST=Hello						okay, return value is 0		No leaks									okay, return value is 0
export TEST+=World						okay, return value is 0		No leaks									okay, return value is 0
export TEST++=World						okay, return value is 1		No leaks									okay, return value is 1
export TEST=Hello World					okay, return value is 0		No leaks									okay, return value is 0
export TEST="Hello World"				okay, return value is 0		No leaks									okay, return value is 0
export TEST??							should fail																okay, return value is 1
export TEST??="Hello World"				should fail																okay, return value is 1
export +								should fail																okay, return value is 1
export =								should fail																okay, return value is 1
export +=								should fail																okay, return value is 1
export ++								should fail																okay, return value is 1
export T++								should fail																okay, return value is 1
unset									okay, return value is 0		No leaks									okay, return value is 0
unset ""								okay, return value is 0		No leaks									okay, return value is 0
unset TEST								okay, return value is 0		No leaks									okay, return value is 0
env										okay, return value is 0		No leaks									okay, return value is 0
exit									okay, exit value is 0		No leaks									okay, exit value is 0
exit ""									okay, exit value is 2		No leaks									okay, exit value is 2
exit 42abc								okay, exit value is 2		No leaks									okay, exit value is 2
exit Hello World						okay, exit value is 2		No leaks									okay, exit value is 2
exit 42									okay, exit value is 42		No leaks									okay, exit value is 42
exit 1 2								Shouldn't exit, return value is 1										okay, return value is 1
# environment variables
echo $HOME								okay, return value is 0		No leaks									okay, return value is 0
echo $ABCDEF							okay, return value is 0		No leaks									okay, return value is 0
echo $42								okay, return value is 0		No leaks									okay, return value is 0
echo $%+								okay, return value is 0		No leaks									okay, return value is 0
echo $?									okay, return value is 0		No leaks									okay, return value is 0
echo '$HOME'							okay, return value is 0		No leaks									okay, return value is 0
echo "$HOME"							okay, return value is 0		No leaks									okay, return value is 0
# syntax errors (exit code 2)
| echo Hello World
echo Hello World |									# bash diff
echo Hello World >
echo ||| Hello World
> | echo Hello World
# non-builtin command
ls
ls -l
/bin/ls -l
# redirections
cat minishell.c > out.txt
< minishell.c awk '{print "42"}' >> out.txt						?????
cat > out.txt minishell.c
cat > out.txt > out2.txt minishell.c							?????
# pipes
echo Hello World | cat
cat minishell.c | wc -l > out.txt								?????
cat < minishell.c | awk '{print "42"}' | wc -l					?????
< minishell.c cat | >> out.txt wc -l							?????
cat /dev/random | cat
cat > out.txt minishell.c | wc -l								?????
cat minishell.c | << end cat									?????
cat nonexistant | ls
# errors (exit code 1)
ls "-l -a"
cat > nopermout.txt
cat nonexistant
ls | cat nonexistant
# no path || no env
env -i ./minishell
# command not found (exit code 127)
# command found but not executable (exit code 126)
no permission
path is a dir