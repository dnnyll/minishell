#include "minishell.h"

/*

+-----------------------------------------+
|          PIPE HANDLING OVERVIEW         |
+-----------------------------------------+

Input command line tokens:
  [ls][ ][-l][ ][|][ ][grep][ ][txt][ ][|][ ][wc][ ][-l]

Token stream with types (WORD, PIPE, etc.):
  WORD(- ls) --> WORD(-l) --> PIPE(|) --> WORD(grep) --> WORD(txt) --> PIPE(|) --> WORD(wc) --> WORD(-l)

Parsing steps:

1. Split tokens into segments separated by PIPE tokens:
   Segment 1: [ls][-l]
   Segment 2: [grep][txt]
   Segment 3: [wc][-l]

2. For each segment:
   - Create a new t_command node with new_command()
   - Fill argv, redirections, heredocs for this segment with fill_command_segment()
   - Append the new command node to the linked list using add_command_to_data()

3. Link the t_command nodes via the `next` pointer to form pipeline chain:
   [t_command for "ls -l"] --> [t_command for "grep txt"] --> [t_command for "wc -l"] --> NULL

4. Execution phase:
   - For each command in the linked list:
     - Setup pipes (pipe())
     - Connect fd_in and fd_out properly (STDIN_FILENO, STDOUT_FILENO, or pipe ends)
     - Fork a process for each command
     - Use dup2() to redirect input/output according to pipes
     - Execute command or builtin
     - Close unused pipe ends in parent process

Summary of `t_command` linked list structure after parsing pipes:

+--------------------+      +-----------------------+      +--------------------+
|  argv: ["ls", "-l"]| ---> |  argv: ["grep","txt"]| ---> | argv: ["wc", "-l"] |
|  infile: NULL      |      |  infile: NULL        |      | infile: NULL       |
|  outfile: NULL     |      |  outfile: NULL       |      | outfile: NULL      |
|  next -------------|      |  next ---------------|      |  next: NULL        |
+--------------------+       +---------------------+     +--------------------+






╔══════════════════════════════════════════════════════════════════════╗
║                 REQUIRED DATA TO HANDLE PIPES IN PARSING             ║
╠══════════════════════════════════════════════════════════════════════╣
║ 1. int pipe_count in t_data                                          ║
║    • Tracks how many '|' tokens appear during parsing.               ║
║    • Needed later to create the correct number of pipe() fds.        ║
║    • Increment every time you find a PIPE token.                     ║
║      Example:                                                        ║
║         if (token->type == PIPE)                                     ║
║             data->pipe_count++;                                      ║
╠══════════════════════════════════════════════════════════════════════╣
║ 2. int command_count in t_data (optional but useful)                 ║
║    • Keeps track of how many separate commands are parsed.           ║
║    • Used for allocating space for pids, managing loops, etc.        ║
║    • Increment every time you create a new t_command.                ║
╠══════════════════════════════════════════════════════════════════════╣
║ 3. t_command *next in each command                                   ║
║    • Links commands together to form a pipeline.                     ║
║    • Required to know the next command during execution.             ║
║    • You already have this implemented correctly.                    ║
╠══════════════════════════════════════════════════════════════════════╣
║ 4. (Optional) bool in_pipeline in t_command                          ║
║    • Marks if this command is part of a pipe chain.                  ║
║    • Not strictly required but helps you debug / simplify exec.      ║
║    • Set this true if pipe_count > 0.                                ║
╠══════════════════════════════════════════════════════════════════════╣
║ 5. (Optional) bool is_first / is_last in t_command                   ║
║    • Helps distinguish special setup for first/last commands.        ║
║    • First: uses stdin or heredoc; Last: uses stdout or outfile.     ║
║    • You can set this during parsing based on position in list.      ║
╚══════════════════════════════════════════════════════════════════════╝






*/

//	WTF? standby, it's perhaps too early to do pipes yet - i am not aware of everything I need in order to get this done

void	handle_pipes(t_data *data, t_token *start, t_token *end)
{
	// printf("handle_pipes\n");
	t_token	*segment_start = start;
	t_token	*current = start;
	t_command	*new_pipe_command;
	
	while (current && current != end)
	{
		if (current->type == PIPE)
		{
			data->pipe_count++;
			// create new command for segment [segment_start ... current)
			new_pipe_command = init_command();
			if (!new_pipe_command)
				return (perror("Error: malloc sizeof t_command @ parser_piepes_handling.c\n"));
			fill_command_segment(new_pipe_command, segment_start, current);	// segment end is current (pipe token)
			add_command_to_data(&data->command_head, new_pipe_command);	// next segment starts after PIPE
			segment_start = current->next;
		}
		current = current->next;
	}
	// handle last segment after last PIPE (or whole command if no PIPE)
	if (segment_start && segment_start != end)
	{
		new_pipe_command = init_command();
		if (!new_pipe_command)
			return(perror("Error: initi new_command @ handle_pipes\n"));
		fill_command_segment(new_pipe_command, segment_start, end);
		add_command_to_data(&data->command_head, new_pipe_command);
	}
}
