█████████████████████████████████████████████████████████████████████████████
█                               PARSING CHECKLIST                           █
█                "What the Parser Must Do Before Execution"                 █
█████████████████████████████████████████████████████████████████████████████

1. LEXING (Tokenization)
   - Split the raw input string into lexical tokens.
   - Delimiters: white space (outside quotes), redirection operators, pipes.
   - Each token must be either:
     - A word (command or argument)
     - A redirection operator (`>`, `>>`, `<`, `<<`)
     - A pipe (`|`)
   - Whitespaces between tokens are separators unless inside quotes.
   - Must maintain the original order of tokens for context-sensitive parsing.
   - Edge case: consecutive operators like `>>>`, `<<>>` must trigger syntax errors.

2. QUOTING RULES
   - SINGLE QUOTES `'...'`
     - Everything between quotes is literal.
     - No variable expansion, no backslash interpretation.
     - Must preserve all characters inside.
   - DOUBLE QUOTES `"..."`:
     - Preserve white space inside.
     - Allow variable expansion inside.
     - Escape characters (`\$`, `\"`, `\\`, `\n`) are recognized.
     - No escape for most other characters.
   - Unclosed quotes must raise a syntax error.
   - Quotes **must not** be passed to `execve()` (they’re used to modify parsing, not part of args).

3. VARIABLE EXPANSION ($)
   - Detect variables starting with `$` outside single quotes.
   - Recognize:
     - `$VAR` → from the environment or internal export list.
     - `$?` → exit status of the last executed command.
     - `$0`, `$1`, `$_`, etc., are not required in 42 but worth understanding.
     - `$$` → current PID (not required but bonus).
   - Inside double quotes: expand.
   - Inside single quotes: **no** expansion.
   - Variables with invalid names (e.g., `$!`) expand to nothing.
   - Must support variable expansion in heredocs unless quoted:
     - `<<EOF` → expand
     - `<<'EOF'` → don’t expand
   - Variable expansion must occur *after* tokenization and quoting resolution, before building args.

4. ESCAPING
   - `\` escapes the next character (context-sensitive).
     - Outside quotes: escapes any character (`\|`, `\$`, `\n`, etc.).
     - Inside double quotes: only escapes `"`, `$`, `\`, and newline.
     - Inside single quotes: no effect; backslashes are literal.
   - Must remove escape characters during token construction, unless escaped themselves (e.g., `\\`).
   - Escaping in the final arguments must reflect what bash would interpret (no extra backslashes).

5. SYNTAX VALIDATION
   - Unclosed quotes → syntax error.
   - Unexpected tokens:
     - `|` at start or end → error.
     - Consecutive `||`, `|||`, or `><` → error.
     - Redirections without a following word token.
     - Heredoc with no delimiter → error.
   - Cannot execute if syntax errors are detected.
   - Must print Bash-like error messages: `minishell: syntax error near unexpected token '|'`.

6. REDIRECTION HANDLING
   - Detect redirection operators and associate them with the correct command.
   - Parse the filename (or delimiter for heredoc) **after** redirection operator.
   - Only one input `<` and one output `>` or `>>` allowed per command (overwriting previous ones).
   - Special handling:
     - `>>` → open in append mode.
     - `<<` → heredoc:
       - Read from stdin until delimiter line is found.
       - If delimiter is unquoted → perform variable expansion.
       - If delimiter is quoted → treat content literally.
     - Redirection targets must not be operators or empty.
   - Save the resolved filenames/delimiters in your command struct.

7. COMMAND STRUCTURE CONSTRUCTION
   - Group tokens between pipes into separate `t_command` structures.
   - For each command:
     - First token is typically the command name.
     - Following tokens: arguments, redirections.
   - Redirections are attached to the command, not treated as arguments.
   - Create a doubly- or singly-linked list (or array) of commands in pipeline order.
   - Each command node should contain:
     - `char *cmd_name`
     - `char **argv`
     - `int is_builtin`
     - `int infile_fd`, `int outfile_fd`
     - `int heredoc_flag`
     - And any other execution context

8. PIPELINE MANAGEMENT
   - Detect pipe characters and correctly split input into pipeline segments.
   - Order matters:
     - `cmd1 | cmd2 | cmd3` → cmd1 stdout goes to cmd2 stdin, cmd2 stdout goes to cmd3 stdin.
   - The number of pipes = number of commands - 1.
   - Each command in pipeline must be parsed independently but connected logically.
   - Must ensure that heredoc or redirections only affect the command they belong to.

9. ENVIRONMENT MANAGEMENT
   - When parsing `export VAR=value`, split into key/value and update internal environment.
   - When parsing `unset VAR`, remove key from internal env.
   - Support `env` to print the internal environment.
   - Variable expansion (`$VAR`) pulls from this structure.
   - Must manage memory:
     - No duplicates in env.
     - Use linked list or hash table depending on preference.
   - When calling `execve()`, prepare the `char **envp` array from the internal env.

10. BUILTIN DETECTION
    - Compare command name to list of built-ins:
      - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
    - Mark command as `is_builtin = 1` or via enum (BUILTIN_CD, etc.).
    - Builtins like `cd`, `exit`, `export`, `unset` should be executed in parent context.
    - Builtins like `echo`, `pwd`, `env` can be executed in forked child (e.g., in pipelines).
    - Avoid `execve()` for built-ins; call internal functions instead.
    - If you use a function pointer table, match and assign it during parsing.

11. ERROR HANDLING
    - Syntax errors: unmatched quotes, invalid tokens.
    - Semantic errors: redirection to nothing, bad variable name.
    - Runtime preparation errors:
      - File permissions for redirections
      - Nonexistent commands (`minishell: command not found`)
    - Must set correct `$?` values:
      - 0 = success
      - 1 = general error
      - 127 = command not found
      - 126 = permission denied / cannot execute

12. MEMORY ALLOCATION
    - Every malloc'd piece of data (tokens, command structs, args, env list) must be trackable.
    - Build a centralized cleanup system:
      - On parsing failure, free all partial structures.
    - Free heredoc buffers, temp files if used.
    - At end of parsing, return a fully valid `t_command *` list/tree to the executor.

13. BONUS CONSIDERATIONS (Optional but Advanced)
    - Parentheses for subshells: `(...)` → run in child shell environment.
    - Logical operators:
      - `cmd1 && cmd2` → cmd2 only runs if cmd1 succeeds.
      - `cmd1 || cmd2` → cmd2 only runs if cmd1 fails.
      - These modify execution flow, not just parsing.
    - Wildcard expansion (globbing):
      - Detect `*`, `?`, `[...]` in args.
      - Expand them to matching filenames via `opendir/readdir` or `glob.h` (if allowed).
    - Command substitution:
      - Backticks: `` `cmd` `` or `$()` → run `cmd` and capture output into the calling command.
      - Not required but complex and educational.
    - Quoting + wildcard edge cases: `"*.c"` should not expand.

█████████████████████████████████████████████████████████████████████████████










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

