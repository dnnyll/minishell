#ifndef MINISHELL_H
# define MINISHELL_H

//	authosized libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>

/*

//	libraries/directories of programs
# include "input/input.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "executor/executor.h"
# include "env/env.h"
# include "signals/signals.h"
# include "utils/utils.h"
*/

//	prompt default
# define PROMPT "minishell$ "


//	structure for tokens
typedef struct s_token
{
	t_token_type    type;
	struct s_token  *next;
}	t_token;

#endif
