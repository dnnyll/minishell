/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:32 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/09 09:54:04 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
**rl : readline
**rl_on_new_line() : it start a new line, use after a '\n'
**rl_replace_line() : Clear the line the user is currently typing and replace
	it with an empty string " ".
**rl_redisplay() : redesplay the shell command, use it after rl_replace_line.
**SIGINT : signal of interrruption, send by ctrl+c
**SIGQUIT : siganl of quit send by ctrl+\
**SIG_DFL : this is the default value of a signal
**SIG_IGN : "signal ignore"
**handle_sigint : this function execute in the parent shell when the user do
	ctrl+c, display a new empty line
*/