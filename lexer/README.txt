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


What is the lexer supposed to handle:

+--------------------------+------------------------------+
| WHAT                     | RESPONSIBILITY                |
+--------------------------+------------------------------+
| Splitting tokens         | yes (respecting quotes)      |
| Handling quotes          | yes                          |
| Detecting open quotes    | yes (error if unclosed)      |
| Recognizing operators    | yes: |, >, >>, <, <<         |
| Token classification     | yes: WORD, PIPE, REDIR_IN…   |
| Escaping with \          | yes                          |
| Word boundaries          | yes: space, redirs, pipes    |
+--------------------------+------------------------------+

What is the lexer supposed to partly handle:

+--------------------------+------------------------------+
| WHAT                     | LEXER DOES…                   |
+--------------------------+------------------------------+
| Variable expansion       | May optionally mark $VAR     |
|                          | or do basic expansion        |
| Heredoc recognition      | Detect << token, store info  |
|                          | but read content later       |
| Handling \$, \" in ""    | Lexer keeps them safe        |
|                          | Expansion/parser handles use |
+--------------------------+------------------------------+

What is the lexer NOT supposed to handle:

+--------------------------+------------------------------+
| WHAT                     | WHO HANDLES IT               |
+--------------------------+------------------------------+
| Variable expansion       | Often done in "expander"     |
| Heredoc content reading  | Done before execution        |
| Execution flow           | executor                     |
| File handling (open/dup) | executor                     |
| Error messages on exec   | executor                     |
+--------------------------+------------------------------+



Handle behaviour of \ and \\

+-------------------------------------------------------------+
|              BACKSLASH HANDLING CHEAT SHEET                 |
+------------------+------------------------------------------+
| Context          | Meaning of \                             |
+------------------+------------------------------------------+
| Outside quotes   | Escapes ANY character                    |
|                  | Examples:                                |
|                  |   \a → a,  \$ → $,  \| → |,  \  → space  |
+------------------+------------------------------------------+
| Inside 'single'  | NO escaping, backslash is literal        |
| quotes           | Examples:                                |
|                  |   '\$USER' → \$USER (not expanded)       |
+------------------+------------------------------------------+
| Inside "double"  | \ escapes ONLY these:                    |
| quotes           |   - \\ → \                               |
|                  |   - \" → "                               |
|                  |   - \$ → $                               |
|                  | (others stay as-is, e.g., \n → \n)       |
+------------------+------------------------------------------+
| Special cases    |                                          |
|                  | - \\ → \  (everywhere except '...')      |
|                  | - \n, \t etc. are NOT special:           |
|                  |   they're just \ + letter                |
|                  | - No need to convert them to newlines    |
+------------------+------------------------------------------+
| Lexer Rule       | Check if you're:                         |
|                  |   - Outside quotes → escape anything     |
|                  |   - In "..." → escape only ", \, $       |
|                  |   - In '...' → nothing is escaped        |
+------------------+------------------------------------------+

Handle behaviour of " and ""

+-------------------------------------------------------------+
|               🔹 QUOTE HANDLING CHEAT SHEET 🔹              |
+------------------+------------------------------------------+
| Type            | Behavior                                  |
+------------------+------------------------------------------+
| No quote        | Words split by space                      |
|                 | Special chars (|, <, >, $, etc.) are seen |
+------------------+------------------------------------------+
| 'single quotes' | EVERYTHING is literal                     |
|                 | No variable expansion, no escaping        |
|                 | Example: '$HOME' → $HOME (not expanded)   |
+------------------+------------------------------------------+
| "double quotes" | Partial interpretation:                   |
|                 | - Variables expanded: "$HOME" → /home/... |
|                 | - Escaping with \ allowed (\", \\, \$)    |
|                 | - Space and special chars are preserved   |
+------------------+------------------------------------------+
| Open quotes     | If quote is not closed, show error        |
+------------------+------------------------------------------+


Handle tokens

+-------------------------------------------------------------+
|              🔹 TOKEN SPLITTING CHEAT SHEET 🔹              |
+------------------+------------------------------------------+
| Spaces           | Split tokens unless inside quotes        |
| Redirections     | >, >>, <, << must be separate tokens     |
| Pipes            | | must be its own token                  |
| Words            | Everything else is a WORD token          |
+------------------+------------------------------------------+
| Example          | echo "hi | bye" > file                   |
| Tokenized        | ["echo", "hi | bye", ">", "file"]        |
+------------------+------------------------------------------+

Handle var

+-------------------------------------------------------------+
|            🔹 VARIABLE EXPANSION CHEAT SHEET 🔹             |
+------------------+------------------------------------------+
| Outside quotes   | Expand normally                          |
| Inside "quotes"  | Expand normally                          |
| Inside 'quotes'  | DO NOT expand                            |
+------------------+------------------------------------------+
| Special cases    |                                          |
|   $?             | Last command exit code                   |
|   $              | Alone is a word: "$" → "$"               |
|   $ followed by  | Alpha-numeric or underscore = valid var  |
+------------------+------------------------------------------+


Handle Heredoc

+-------------------------------------------------------------+
|                🔹 HEREDOC HANDLING CHEAT SHEET 🔹           |
+------------------+------------------------------------------+
| Syntax           | command << limiter                       |
| Collect lines    | Until a line matches `limiter` exactly   |
| With quotes      | If limiter is quoted: no expansion       |
| Unquoted limiter | Expand variables inside heredoc          |
+------------------+------------------------------------------+
| Example          | cat << EOF                               |
| Input            | hello $USER                              |
| End              | EOF                                      |
| Expansion        | → expands $USER if EOF is not quoted     |
+------------------+------------------------------------------+

Handle Redirections

+-------------------------------------------------------------+
|              🔹 REDIRECTION CHEAT SHEET 🔹                  |
+------------------+------------------------------------------+
| >  (out)         | Truncate and write output                |
| >> (append)      | Append output                            |
| <  (in)          | Read from file                           |
| << (heredoc)     | Read from stdin until limiter line       |
+------------------+------------------------------------------+
| Tokenize         | Always as separate tokens                |
| Example          | cat < file >> out.txt                    |
| Result           | ["cat", "<", "file", ">>", "out.txt"]    |
+------------------+------------------------------------------+


handle operators  and metacharacters

+-------------------------------------------------------------+
|         🔹 METACHARACTER & OPERATOR CHEAT SHEET 🔹         |
+------------------+------------------------------------------+
| Metacharacters   | ; | < > ( ) &                            |
| Must be tokens   | Unless quoted or escaped                 |
| Combination ops  | <<, >> must be parsed together           |
| Escaped ones     | \| → literal pipe                       |
+------------------+------------------------------------------+
