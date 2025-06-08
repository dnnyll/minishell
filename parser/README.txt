


remember to handle:

Detect invalid starting tokens like ||, &&, >>, |, etc.

Only allow redirections (>, >>, <, <<) attached to valid commands.

Detect missing file names or missing commands around operators.

╔════════════════════════════════════════════════════════════════╗
║                           MAIN LOOP                            ║
╚════════════════════════════════════════════════════════════════╝
→ Begins an infinite loop to wait for user input:

1. input_line = readline(PROMPT)
   - Waits for user to type a command (e.g., echo hello > out.txt)
   - Stores it in input_line

2. add_history(input_line)
   - Adds the command to history (readline feature)

3. tokens = lexer(input_line)
   - Tokenizes the string into a linked list of t_token
   - Example:
     Input: "echo hello > out.txt | grep h"
     Token List:
     [WORD: echo] → [WORD: hello] → [REDIR_OUT: >] → [WORD: out.txt] → 
     [PIPE: |] → [WORD: grep] → [WORD: h]

4. cmds = parse_tokens(tokens)
   - This is where the core parsing happens to build commands.
   - Returns a linked list of t_command nodes

5. print_commands(cmds)
   - For debugging: prints each command's argv and redirections

6. free_commands(cmds)
   - Frees the memory of the command list

7. print_tokens(tokens)
   - Optional: prints the tokens for debugging

8. free_tokens(tokens)
   - Frees the memory for tokens

9. free(input_line)
   - Frees input line string

══════════════════════════════════════════════════════════════════
                    parse_tokens(t_token *token_list)
══════════════════════════════════════════════════════════════════
Parses the full token list into a linked list of t_command structs

┌───────────────────────────────────────────────────────────────┐
│ STEP 1: Initialize pointers                                    │
│    t_command *command_list = NULL                              │
│    t_command *last_command = NULL                              │
│    t_token   *current = token_list                             │
└───────────────────────────────────────────────────────────────┘

┌───────────────────────────────────────────────────────────────┐
│ STEP 2: Loop through the token list                            │
│    while (current)                                             │
└───────────────────────────────────────────────────────────────┘

Each loop iteration = one full command segment (until PIPE)

→ Call create_new_command_node():
   - malloc a new t_command node
   - Initialize:
     command->argv = NULL
     command->redir_in = NULL
     command->redir_out = NULL
     command->next = NULL

→ command->argv = argument_collect(current)
   (builds argument list from current token segment)

  ╔════════════════════════════════════════════════════════════╗
  ║              argument_collect(t_token *head)              ║
  ╚════════════════════════════════════════════════════════════╝
   1. count_nodes():
      - Loops through tokens and counts only WORDs (arguments)
      - Skips redirection tokens and their targets
      - e.g., for "echo hello > out.txt", returns 2

   2. alloc_argv(size):
      - Allocates a char **argv with (size + 1) space
      - argv[size] = NULL

   3. argument_fill(argv, head):
      - Loops through tokens:
        → If token is WORD: ft_strdup(token->value) → argv[i]
        → If token is REDIR: skips it and the next token
      - Fills argv[] with the actual arguments

   Returns the argv[] for this command

→ detect_redirections(current, command)

  ╔════════════════════════════════════════════════════════════╗
  ║          detect_redirections(t_token *head, cmd)           ║
  ╚════════════════════════════════════════════════════════════╝
   - Loops through the same tokens again (up to PIPE)
   - For each REDIR_IN, REDIR_OUT, APPEND, HEREDOC:
     1. Check that next token is WORD (target)
     2. Create a t_redirect node:
        → redir->type = REDIR_IN / REDIR_OUT / etc.
        → redir->file = ft_strdup(token->next->value)
        → redir->next = NULL
     3. Append to the correct list in t_command:
        → if input type → redir_in
        → if output type → redir_out
     4. Move 2 steps ahead: skip redir and filename

→ Add command to command_list:
   if command_list is NULL:
     → this is the first command
     → command_list = command
   else:
     → last_command->next = command
   last_command = command

→ Skip over the PIPE if any:
   → current = current->next (to get next segment)

→ Loop continues until current == NULL

══════════════════════════════════════════════════════════════════
                Final Structure After Parsing:
══════════════════════════════════════════════════════════════════

Example input: echo hello > out.txt | grep h

t_command list:

[COMMAND 1]
+----------------------------------+
| argv      → ["echo", "hello"]    |
| redir_in  → NULL                 |
| redir_out → [out.txt] (REDIR_OUT)|
| next      → ptr to command 2     |
+----------------------------------+

[COMMAND 2]
+----------------------------------+
| argv      → ["grep", "h"]        |
| redir_in  → NULL                 |
| redir_out → NULL                 |
| next      → NULL                 |
+----------------------------------+

══════════════════════════════════════════════════════════════════
      This structure is returned to main for further use
══════════════════════════════════════════════════════════════════

