=====================================================
   General Parsing Logic
=====================================================

While there are tokens:
    If this is the first token or after a pipe:
        create new t_cmd
        link it to the previous one (if any)

    For each token type:
        - WORD: add to argv
        - REDIR_IN: set infile from next token
        - REDIR_OUT: set outfile from next token, append = 0
        - APPEND: set outfile from next token, append = 1
        - HEREDOC: set heredoc_delim from next token
        - PIPE: end current command (prepare to create a new one next loop)

    Move to next token


---------------------------------------- // ----------------------------------------


⚠️ What to Watch Out For
Missing argument after redirection (< with nothing after it).

Pipe at the end of the input (echo hi | → syntax error).

Two redirections without a WORD in between.

Quoting is usually already handled by the lexer,
so you shouldn’t need to track it again here unless you're expanding variables.

____________________________________________________________________________________


┌──────────────────────────────────────────────────────────────────────────────┐
│                          MINISHELL PARSING CHECKLIST                         │
├──────────────────────────────────────────────────────────────────────────────┤
│ 1. COMMAND SEGMENTATION                                                      │
│   • Split the token list using PIPE ('|') tokens.                            │
│   • For each segment (between pipes), create a new `t_cmd` structure.        │
│   • Store these in a linked list or array (e.g., `t_data->cmd_list`).        │
│                                                                              │
│ 2. ARGUMENT VECTOR (argv)                                                    │
│   • For each `t_cmd`, collect all `WORD` tokens not part of redirections.    │
│   • These tokens form the `char **argv` array:                               │
│       - argv[0] = command name (e.g., "echo")                                │
│       - argv[1..n] = arguments (e.g., "hello", "world")                      │
│   • Must be NULL-terminated for execve compatibility.                        │
│                                                                              │
│ 3. REDIRECTION HANDLING                                                      │
│   • Detect and process these token pairs:                                    │
│       - '<'  (REDIR_IN)   → set `cmd->infile`                                │
│       - '>'  (REDIR_OUT)  → set `cmd->outfile` (append = 0)                  │
│       - '>>' (APPEND)     → set `cmd->outfile` (append = 1)                  │
│       - '<<' (HEREDOC)    → set `cmd->heredoc_delim`                         │
│   • Validate that each redirection is followed by a `WORD`.                  │
│   • Do not include these WORDs in argv.                                      │
│                                                                              │
│ 4. SYNTAX VALIDATION                                                         │
│   • Detect common syntax errors:                                             │
│       - Pipe at start or end (e.g., `| ls`, `ls |`)                          │
│       - Consecutive pipes (e.g., `ls || grep`)                               │
│       - Redirection with no following argument (e.g., `cat <`)               │
│       - Missing command between pipes or redirs                              │
│   • If any error is found, stop parsing and print an error message.          │
│                                                                              │
│ 5. COMMAND LINKAGE                                                           │
│   • All `t_cmd` nodes should be chained (linked list or array).              │
│   • Link them in order of appearance.                                        │
│   • Needed for later execution (e.g., setting up pipes).                     │
│                                                                              │
│ 6. PIPE COUNT (OPTIONAL)                                                     │
│   • Count the number of PIPE tokens during parsing.                          │
│   • Useful for setting up pipes between commands later.                      │
│                                                                              │
│ 7. QUOTE CONTEXT (FROM LEXER)                                                │
│   • Each token carries a `t_quote_type`.                                     │
│   • Parsing doesn’t need to act on this, but expansion may use it.           │
│                                                                              │
│ 8. ENV VARIABLE TAGGING (OPTIONAL)                                           │
│   • If lexer marks `$VAR` as ENV token, parser can keep that info.           │
│   • Expansion happens after parsing.                                         │
│                                                                              │
│ 9. BUILTIN COMMAND DETECTION (OPTIONAL)                                      │
│   • If `argv[0]` is a builtin (e.g., "cd", "echo"), mark it as such.         │
│   • Store a `bool is_builtin` flag in `t_cmd`.                               │
│                                                                              │
│ 10. DEFAULT FD SETUP (FOR LATER EXECUTION)                                   │
│   • Initialize:                                                              │
│       - `cmd->fd_in = STDIN_FILENO`                                          │
│       - `cmd->fd_out = STDOUT_FILENO`                                        │
│   • These may later be changed by redirections or pipe setup.                │
└──────────────────────────────────────────────────────────────────────────────┘

____________________________________________________________________________________







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

