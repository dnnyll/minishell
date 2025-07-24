/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:32 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/17 16:28:26 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;				// suppress unused parameter warning
	g_signal_status = sig;	// Convention: 130 = SIGINT + 128
	write(1, "\n", 1);		// print a newline to stdout (file descriptor 1)
	rl_on_new_line();		// tell readline library that we are on a new line
	rl_replace_line("", 0);	// clear the current input line
	rl_redisplay();			// redraw the prompt and input line
}


void	setup_parent_signals(void)
{
	signal(SIGINT, handle_sigint);  // Ctrl-C triggers handle_sigint
	signal(SIGQUIT, SIG_IGN);       // Ctrl-\ (SIGQUIT) is ignored
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);  // Ctrl-C behaves default (usually terminate)
	signal(SIGQUIT, SIG_DFL); // Ctrl-\ behaves default (usually terminate)
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
	ctrl+c, display a new empty line.
	**g_signals_status pour main:
		//if (g_signal_status == 130) //if Ctrl-C
		// {
		// 	g_signal_status = 0; //reset the variable
		// 	free(input_line); // free the empty or partial line
		// 	continue ;         // repeat the loop to display the prompt
		//}
*/