#include "minishell.h"


// TEMPORARY FUNCTIONS FOR DEBUGGING TOKENS
const	char *token_type_str(t_token_type type)
{
	if (type == CMD) return "COMMAND";
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == HEREDOC) return "HEREDOC";
	if (type == APPEND) return "APPEND";
	if (type == ERROR) return "ERROR";
	return ("UNKNOWN");
}

const char *quote_type_str(t_quote_type quote)
{
	if (quote == NO_QUOTE)
		return ("None");
	if (quote == SINGLE_QUOTE)
		return ("Single");
	if (quote == DOUBLE_QUOTE)
		return ("Double");
	return ("Unknown");
}

void print_data(t_data *data)
{
	printf("==== Parser Output ====\n");
	print_commands(data->command_head);
}

void    print_tokens(t_data *data)
{
    t_token	*tokens = data->token_head;

    if (!tokens)
    {
        printf("No tokens to print.\n");
        return;
    }

    printf("\n--- Token List ---\n");
    while (tokens)
    {
        printf("Value: %-20s | Type: %-10s | Quote: %s\n",
            tokens->value,
            token_type_str(tokens->type),
            quote_type_str(tokens->quote));
        tokens = tokens->next;
    }
    printf("-------------------\n\n");
}

void print_commands(t_command *cmd)
{
    int i;
    int cmd_num = 1;

    while (cmd)
    {
        printf("\n\033[1;32m---- Command %d ----\033[0m\n", cmd_num);

        // Print argv
        printf("argv:\n");
        if (cmd->argv)
        {
            i = 0;
            while (cmd->argv[i])
            {
                printf("  argv[%d]: %s\n", i, cmd->argv[i]);
                i++;
            }
        }
        else
            printf("  (null)\n");
        // Print redirections and flags
        printf("infile:         %s\n", cmd->infile ? cmd->infile : "(none)");
        printf("outfile:        %s\n", cmd->outfile ? cmd->outfile : "(none)");
        printf("append:         %s\n", cmd->append ? "true" : "false");

        // Print file descriptors
        printf("fd_in:          %d %s\n", cmd->fd_in,
               (cmd->fd_in != STDIN_FILENO) ? "(!= STDIN)" : "");
        printf("fd_out:         %d %s\n", cmd->fd_out,
               (cmd->fd_out != STDOUT_FILENO) ? "(!= STDOUT)" : "");

        // Print path and value
        printf("path:           %s\n", cmd->path ? cmd->path : "(none)");
        printf("value:          %s\n", cmd->value ? cmd->value : "(none)");

        // Print token type (you may want to adapt this based on your enum)
        printf("type:           %d\n", cmd->type);

        // Pipe connection visualization
        if (cmd->next)
            printf("(==== pipe separation ====)\n\n");

        cmd = cmd->next;
        cmd_num++;
    }
}


void    debug_environment_variables_printer(t_data *data)
{
    int i;

    i = 0;
    printf("===== DEBUG ENVIRONMENT_variables COPY =====\n");
    if (data->environment_var[i])
    {
        while (data->environment_var[i])
        {
            printf("%s\n", data->environment_var[i++]);
        }
    }
    else
        printf("Error: data->environment_var = NULL\n");
    printf("===============================\n");

}
void print_env_list(t_env *env)
{
	int i = 1;
	printf("\n\033[1;33m---- Environment Variables ----\033[0m\n");
	while (env)
	{
		printf("  [%d] key: '%s', value: '%s'\n", i,
			env->key ? env->key : "(null)",
			env->value ? env->value : "(null)");
		env = env->next;
		i++;
	}
	if (i == 1)
		printf("  (empty)\n");
}
void    print_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
	{
		printf("\n\033[1;31m[HEREDOC] (null pointer)\033[0m\n");
		return ;
	}

	printf("\n\033[1;35m---- Heredoc Debug ----\033[0m\n");
	printf("filename: %s\n", heredoc->filename ? heredoc->filename : "(null)");
	printf("fd:       %d\n", heredoc->fd);
	printf("counter:  %d\n", heredoc->counter);
	printf("pid:      %d\n", heredoc->pid);
	printf("\033[1;35m-----------------------\033[0m\n");
}

void print_data_debug(t_data *data)
{
	printf("\n\033[1;36m==== DATA DEBUG ====\033[0m\n");

	// Environment variables (linked list)
	print_env_list(data->env_head);

	// Environment variables (array copy)
	printf("\n\033[1;33m---- Environment Array ----\033[0m\n");
	if (data->environment_var)
	{
		int i = 0;
		while (data->environment_var[i])
		{
			printf("  [%d]: %s\n", i, data->environment_var[i]);
			i++;
		}
		if (i == 0)
			printf("  (empty)\n");
	}
	else
		printf("  (null)\n");

	// Last exit code
	printf("\nlast_exit_code_status: %d\n", data->last_exit_code_status);

	// // Temporary counts
	// printf("pipe_count:    %d\n", data->pipe_count);
	// printf("command_count: %d\n", data->command_count);

	printf("\033[1;36m===================\033[0m\n");
}

//  this is the main debug function that calls all the other printers

void debug_parser_output(t_data *data)
{
    printf("===== DEBUG PARSER OUTPUT =====\n");

    // Print token list (optional, if you have a token printer)
    printf("\n____________ Tokens ____________\n");
    print_tokens(data);

    // Print commands
    printf("\n____________ Parsed Commands ____________\n");
    print_commands(data->command_head);

    // Print environment variables (linked list + array + counters)
    // print_data_debug(data);

    // Print heredoc list
    // print_heredoc(data->heredoc_head);

    // Print counters (already handled inside print_data_debug, optional if you want redundancy)
    printf("\npipe_count = %d | command_count = %d\n", data->pipe_count, data->command_count);
    printf("\nheredoc_count = %d\n", data->command_head->heredoc_count);
    // Print heredoc structure
    // print_heredoc(data->heredoc_head);
    printf("===============================\n");
}
