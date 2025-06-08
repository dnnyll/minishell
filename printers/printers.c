/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:30:10 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/06 13:45:45 by daniefe2         ###   ########.fr       */
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

void	print_commands(t_command *cmd)
{
	int			i;
	int			cmd_num;
	t_redirect	*in;
	t_redirect	*out;

	cmd_num = 1;
	while (cmd)
	{
		printf("=== Command #%d ===\n", cmd_num);
		cmd_num++;
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("  argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}

		in = cmd->redir_in;
		while (in)
		{
			printf("  Input Redirection: %s (type: %d)\n", in->file, in->type);
			in = in->next;
		}

		out = cmd->redir_out;
		while (out)
		{
			printf("  Output Redirection: %s (type: %d)\n", out->file, out->type);
			out = out->next;
		}

		cmd = cmd->next;
	}
}

void print_tokens(t_token *tokens)
{
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