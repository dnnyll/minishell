/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:30:10 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/13 15:03:13 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void debug_parser_output(t_data *data)
{
    printf("===== DEBUG PARSER OUTPUT =====\n");

    // Print token list (optional, if you have a token printer)
    printf("\n____________Tokens____________\n");
    print_tokens(data);

    // Print commands
    printf("\n____________Parsed Commands____________\n");
    print_commands(data->command_head);

    printf("===============================\n");
}

void print_commands(t_command *cmd)
{
    int i;
    int cmd_num = 1;

    printf("____________Parsed Commands____________\n");

    while (cmd)
    {
        printf("---- Command %d ----\n", cmd_num);

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

        // Print redirections
        printf("infile: %s\n", cmd->infile ? cmd->infile : "(none)");
        printf("outfile: %s\n", cmd->outfile ? cmd->outfile : "(none)");
        printf("append: %d\n", cmd->append);
        printf("heredoc_delim: %s\n", cmd->heredoc_delim ? cmd->heredoc_delim : "(none)");

        // Print file descriptors
        printf("fd_in: %d\n", cmd->fd_in);
        printf("fd_out: %d\n", cmd->fd_out);

        // Print builtin flag
        printf("is_builtin: %d\n", cmd->is_builtin);

        // Next command
        cmd = cmd->next;
        cmd_num++;
    }

    printf("=======================================\n");
}


