/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:32 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/05 14:55:13 by mrosset          ###   ########.fr       */
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
**rl_on_new_line() :
**rl_replace_line() :
**rl_redisplay() :
**SIGINT : signal of interrruption, send by ctrl+c
**SIGQUIT : siganl of quit send by ctrl+\
**SIG_DFL : this is the default value of a signal
**SIG_IGN : "signal ignore"
**handle_sigint : this function execute in the parent shell when the user do
	ctrl+c, display a new empty line
*/