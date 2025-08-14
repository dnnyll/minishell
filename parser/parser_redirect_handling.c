#include "minishell.h"

/*
	information concerning: is_redirection

	purpose: checks if a token type is a redirection operator.

	for: identifying tokens like <, >, >>, or << in a command.

	it returns 1 (true) if the type matches any redirection type:
	- REDIR_IN ('<')
	- REDIR_OUT ('>')
	- APPEND ('>>')
	- HEREDOC ('<<')

	useful when walking through a list of tokens to quickly test
	if the current token is a redirection.
*/
int	is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

/*
	information concerning: set_redir_in

	purpose: sets the input file name for the command from a REDIR_IN token.

	for: commands like cat < file.txt

	it:
	- frees any previously stored infile
	- duplicates the token value following '<'
	- stores it in the command's infile field

	this tells the shell which file should be opened as standard input.
*/
static void	set_redir_in(t_command *command, t_token *current)
{
	if (command->infile)
		free(command->infile);
	command->infile = ft_strdup(current->next->value);
}

/*
	information concerning: set_redir_out

	purpose: sets the output file name for the command from 
		REDIR_OUT or APPEND token.

	for: commands like echo hello > out.txt or echo hello >> out.txt

	it:
	- frees any existing outfile value
	- duplicates the filename token following the redirection
	- stores it in the command's outfile field
	- sets the append flag (0 for '>', 1 for '>>')

	this prepares the redirection settings so output goes to the correct file.
*/
static void	set_redir_out(t_command *command, t_token *current, int append)
{
	if (command->outfile)
		free(command->outfile);
	command->outfile = ft_strdup(current->next->value);
	command->append = append;
}

/*
	information concerning: set_heredoc

	purpose: stores the heredoc delimiter from a HEREDOC (<<) token.w

	for: commands like cat << EOF

	it:
	- frees any previously stored heredoc delimiter
	- duplicates the token value following the '<<' operator
	- stores it in the command’s heredoc_delim field

	this allows later logic to process heredoc input correctly.
*/
static void	set_heredoc(t_command *cmd, t_token *current)
{
	t_heredoc *new = init_heredoc(cmd->heredoc_count); // pass counter
	// printf("heredoc_count = %d\n", cmd->heredoc_count);
	if (!new)
		return ;
	new->delimiter = ft_strdup(current->next->value);
	new->quoted = (current->next->quote != NO_QUOTE);
	if (!cmd->heredoc_head)
		cmd->heredoc_head = new;
	else
	{
		t_heredoc *tmp = cmd->heredoc_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}


/*
	information concerning: handle_redirections

	purpose: parses and stores redirection information inside
		the command structure.

	for: echo hello > file.txt

	it detects redirection tokens (e.g. >, >>, <, <<) and saves
		the corresponding 
	filenames or delimiters into the command structure.

	- infile: for '<'
	- outfile: for '>' and '>>'
	- append: 0 for '>', 1 for '>>'
	- heredoc_delim: for '<<'

	without this, the shell wouldn’t know which files to open for input/output 
	before calling execve().
	it loops from start to end tokens, only handling redirections.
*/
void	handle_redirections(t_command *command, t_token *start, t_token *end)
{
	t_token	*current;

	current = start;
	command->heredoc_count = 0;
	while (current && current != end)
	{
		if (current->next && current->next->type == WORD)
		{
			if (current->type == REDIR_IN)
				set_redir_in(command, current);
			else if (current->type == REDIR_OUT)
				set_redir_out(command, current, 0);
			else if (current->type == APPEND)
				set_redir_out(command, current, 1);
			else if (current->type == HEREDOC)
			{
				command->heredoc_count++;
				set_heredoc(command, current);
			}
			current = current->next;
		}
		current = current->next;
		// print_heredoc(command);

	}
}


// void	handle_redirections(t_command *command, t_token *start, t_token *end)
// {
// 	// printf("handle_redirections\n");
// 	t_token *current = start;
// 	while (current && current != end)
// 	{
// 		if (current->type == REDIR_IN && current->next
//			&& current->next->type == WORD)
// 		{
// 			command->infile = ft_strdup(current->next->value);
// 			current = current->next;
// 		}
// 		else if (current->type == REDIR_OUT && current->next
//			&& current->next->type == WORD)
// 		{
// 			command->outfile = ft_strdup(current->next->value);
// 			command->append = 0;
// 			current = current->next;
// 		}
// 		else if (current->type == APPEND && current->next
//			&& current->next->type == WORD)
// 		{
// 			command->outfile = ft_strdup(current->next->value);
// 			command->append = 1;
// 			current = current->next;
// 		}
// 		else if (current->type == HEREDOC && current->next
//			&& current->next->type == WORD)
// 		{
// 			command->heredoc_delim = ft_strdup(current->next->value);
// 			current = current->next;
// 		}
// 		current = current->next;
// 	}
// }
