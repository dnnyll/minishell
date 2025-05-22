input_line (raw string)
      ↓
[skip whitespace]
[handle quotes]
[detect operators]
[extract words]
[build tokens]
[return linked list of tokens]

# Lexer Reference Sheet (Detailed)

1. input_line (raw string)
   - The full command line string returned from readline()
   - Example: char *input_line = readline(PROMPT);

2. [Skip whitespace]
   - Ignore spaces and tabs between tokens.
   - Don't skip spaces inside quotes.
   - while (isspace(*line)) line++;

3. [Handle quotes]
   - Single quotes: 'content'
     * Treat literally, no expansion, no interpretation.
   - Double quotes: "content"
     * Preserve spaces.
     * Allow environment variable expansion (e.g., "$HOME")
   - Ensure closing quote exists; else return syntax error.

4. [Detect operators]
   - Recognize and isolate the following operators as individual tokens:
     * |     → PIPE
     * >     → REDIR_OUT
     * >>    → REDIR_APPEND
     * <     → REDIR_IN
     * <<    → HEREDOC
   - Use lookahead to differentiate single vs. double character operators.

5. [Extract words]
   - Words are sequences of non-whitespace, non-operator characters.
   - Stop at space, operator, or end of string unless inside quotes.
   - Handle escaping (e.g., \") inside quoted strings.

6. [Build tokens]
   - For each word or operator found, create a token node:
     * typedef struct s_token {
         char *value;
         int   type;
         struct s_token *next;
       } t_token;
   - Allocate memory and store the token value and its type.
   - Link each new token to the list.

7. [Return linked list of tokens]
   - Return the head of the token list to the parser.
   - Ensure cleanup in case of lexer error (free list).
