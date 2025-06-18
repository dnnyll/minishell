=====================================================
   Diagram: Token Creation Flow with t_token_result
=====================================================

Concerns: structure in lexer.h:

/*
	helper struct that temporarily holds the result of a token extraction
	to help the lexer keep track of where it is and what it just parsed.
	
	saves the extracted input strings directly to t_tokens struc in tokens.h
	saves the index end position of every string.
*/


typedef struct s_lexer_result
{
	t_token	*token;		//	the string is stored in tokens.h's structure
	int		index;		//	the index position of the input string's end
}	t_lexer_result;


Example:

[Input string]:  "echo hello > file"

           [extract_word()]
             ┌────────────┐
 index = 0 → │ echo       │
             └────────────┘
     returns:
     t_token_result
     {
         token: [t_token* ("echo")],
         index: 4
     }

          [extract_word()]
             ┌────────────┐
 index = 5 → │ hello      │
             └────────────┘
     returns:
     t_token_result
     {
         token: [t_token* ("hello")],
         index: 10
     }

      [extract_operator()]
             ┌────────────┐
 index = 11 →│ >          │
             └────────────┘
     returns:
     t_token_result
     {
         token: [t_token* (REDIR_OUT)],
         index: 12
     }


---------------------------------------- // ----------------------------------------


Example FULL of lexer flow:

+-------------------------------+
|           main()              |
+-------------------------------+
|                               |
| input_line = readline();      |
| lexer(&data, input_line);     |
+-------------------------------+
                |
                v
+-------------------------------+
|           lexer()             |
+-------------------------------+
| index = 0;                    |
| while (input_line[index])     |
| {                             |
|   result = extract_word(...); |       <-- returns t_lexer_result
|   token  = result.token;      |       <-- comes from inside result
|   index  = result.index;      |       <-- also from inside result
|   append_token(&data, token); |       <-- add token to linked list
| }                             |
+-------------------------------+
                |
                v
+-------------------------------+
|        extract_word()         |
+-------------------------------+
| Scans input_line[index]       |
| Allocates new t_token         |
|   -> value = strdup(...)      |
|   -> type  = WORD             |
|   -> quote = NO_QUOTE         |
|   -> next  = NULL             |
| Returns:                      |
|   t_lexer_result              |
|   {                           |
|     .token = [t_token*],      | <-- the new token
|     .index = new_index        | <-- where lexer should continue
|   }                           |
+-------------------------------+

After extract_word() returns:
               |
               v
+-------------------------------+
|      result: t_lexer_result   |
+-------------------------------+
| .token  ---> +-------------+  |
|              |  t_token    |  |
|              +-------------+  |
|              | value: "ls" |  |
|              | type : WORD |  |
|              | quote: NONE |  |
|              | next : NULL |--+  <-- linked later in list
|              +-------------+  |
|                               |
| .index = 2 (next char pos)    |
+-------------------------------+

Then used in lexer():
               |
               v
+-------------------------------+
|       append_token()          |
+-------------------------------+
| If data.token_head == NULL:   |
|   data.token_head = token;    |
| Else:                         |
|   Traverse to last .next      |
|   and append new token        |
+-------------------------------+

Final result in memory:
+------------+     +-------------+     +-------------+
|  "echo"    | --> |  "hello"    | --> |     "|"     |
+------------+     +-------------+     +-------------+
     ^
     |
data.token_head

____________________________________________________________________________________


=====================================================
   Flow of lexer.c
=====================================================

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

_____________________________________________________________________________________


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


Environment single and double quote behaviour

altera@ALTERA:~/42_home/minishell$ echo $USER
altera
altera@ALTERA:~/42_home/minishell$ echo "$USER"
altera
altera@ALTERA:~/42_home/minishell$ echo "hello $USER"
hello altera
altera@ALTERA:~/42_home/minishell$ echo "hello '$USER'"
hello 'altera'
altera@ALTERA:~/42_home/minishell$ echo 'hello "$USER"'
hello "$USER"
altera@ALTERA:~/42_home/minishell$ echo "$USER"
altera
altera@ALTERA:~/42_home/minishell$ echo '$USER'
$USER
altera@ALTERA:~/42_home/minishell$ echo hello "  '$USER' "
hello   'altera'
altera@ALTERA:~/42_home/minishell$

# ╔════════════════════════════════════════════════════════════════════╗
# ║                   QUOTE HANDLING CASES IN MINISHELL                ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 1: Unquoted variable expands                                  ║
# ║   echo $USER                                                       ║
# ║   → expands to: echo altera                                        ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 2: Variable in double quotes expands                          ║
# ║   echo "$USER"                                                     ║
# ║   → expands to: echo altera                                        ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 3: Text and variable in double quotes                         ║
# ║   echo "hello $USER"                                               ║
# ║   → expands to: echo hello altera                                  ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 4: Quoted variable inside double quotes(literal single quotes)║
# ║   echo "hello '$USER'"                                             ║
# ║   → expands to: echo hello 'altera'                                ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 5: Double quotes inside single quotes (no expansion)          ║
# ║   echo 'hello "$USER"'                                             ║
# ║   → stays literal: echo hello "$USER"                              ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 6: Pure single quotes (no expansion)                          ║
# ║   echo '$USER'                                                     ║
# ║   → stays literal: echo $USER                                      ║
# ╠════════════════════════════════════════════════════════════════════╣
# ║ Case 7: Mixed: plain text + quoted var                             ║
# ║   echo hello "  '$USER' "                                          ║
# ║   → expands to: echo hello   'altera'                              ║
# ╚════════════════════════════════════════════════════════════════════╝
