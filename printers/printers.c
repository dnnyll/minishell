#include "minishell.h"

// void print_redirections(t_redirect *redir, const char *label)
// {
// 	while (redir)
// 	{
// 		printf("  %s: file='%s', type=%d\n", label, redir->file, redir->type);
// 		redir = redir->next;
// 	}
// }

// void print_commands(t_data *data)
// {
// 	t_command	*cmd = data->command_head;
// 	int			i;
// 	int			cmd_num = 1;

// 	if (!cmd)
// 	{
// 		printf("No commands to print.\n");
// 		return;
// 	}
// 	while (cmd)
// 	{
// 		printf("=== Command #%d ===\n", cmd_num++);
// 		i = 0;
// 		while (cmd->argv && cmd->argv[i])
// 		{
// 			printf("  argv[%d]: %s\n", i, cmd->argv[i]);
// 			i++;
// 		}
// 		print_redirections(cmd->redir_in, "Input Redirection");
// 		print_redirections(cmd->redir_out, "Output Redirection");
// 		cmd = cmd->next;
// 	}
// }
// void print_commands(t_command *cmd_list)
// {
// 	int cmd_num = 1;
// 	while (cmd_list)
// 	{
// 		printf("---- Command %d ----\n", cmd_num);
// 		print_single_command(cmd_list);
// 		cmd_list = cmd_list->next;
// 		cmd_num++;
// 	}
// }

void print_single_command(t_command *cmd)
{
    // Print argv
    printf("argv:\n");
    if (cmd->argv)
    {
        for (int i = 0; cmd->argv[i]; i++)
            printf("  argv[%d]: %s\n", i, cmd->argv[i]);
    }

    // Print redirections
    if (cmd->infile)
        printf("infile: %s\n", cmd->infile);
    if (cmd->outfile)
        printf("outfile: %s\n", cmd->outfile);
    if (cmd->heredoc_delim)
        printf("heredoc_delim: %s\n", cmd->heredoc_delim);
    printf("append: %d\n", cmd->append);
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
        printf("heredoc_delim:  %s\n", cmd->heredoc_delim ? cmd->heredoc_delim : "(none)");
        printf("heredoc_quoted: %s\n", cmd->heredoc_quoted ? "true" : "false");

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

        // Print if prev exists (for debugging double linked list)
        printf("prev:           %s\n", cmd->prev ? "(exists)" : "(null)");

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

//  this is the main debug function that calls all the other printers

void debug_parser_output(t_data *data)
{
    printf("===== DEBUG PARSER OUTPUT =====\n");

    // Print token list (optional, if you have a token printer)
    printf("\n____________Tokens____________\n");
    print_tokens(data);

    // Print commands
    printf("\n____________Parsed Commands____________\n");
    print_commands(data->command_head);

    // Print counters
    printf("\npipes_count = %d | commands_count = %d\n", data->pipe_count, data->command_count);

    printf("===============================\n");
}