/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:30:10 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/08 15:36:25 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_redirections(t_redirect *redir, const char *label)
{
	while (redir)
	{
		printf("  %s: file='%s', type=%d\n", label, redir->file, redir->type);
		redir = redir->next;
	}
}

void print_commands(t_data *data)
{
	t_command	*cmd = data->command_head;
	int			i;
	int			cmd_num = 1;

	if (!cmd)
	{
		printf("No commands to print.\n");
		return;
	}
	while (cmd)
	{
		printf("=== Command #%d ===\n", cmd_num++);
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("  argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		print_redirections(cmd->redir_in, "Input Redirection");
		print_redirections(cmd->redir_out, "Output Redirection");
		cmd = cmd->next;
	}
}

void print_tokens(t_data *data)
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
