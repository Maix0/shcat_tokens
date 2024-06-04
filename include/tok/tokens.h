/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:40:18 by maiboyer          #+#    #+#             */
/*   Updated: 2024/06/04 21:55:29 by maiboyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H

/*
%start program
%%
program          : linebreak complete_commands linebreak
				 | linebreak
				 ;
complete_commands: complete_commands newline_list complete_command
				 |                                complete_command
				 ;
complete_command : list separator_op
				 | list
				 ;
list             : list separator_op and_or
				 |                   and_or
				 ;
and_or           :                         pipeline
				 | and_or AND_IF linebreak pipeline
				 | and_or OR_IF  linebreak pipeline
				 ;
pipeline         :      pipe_sequence
				 | Bang pipe_sequence
				 ;
pipe_sequence    :                             command
				 | pipe_sequence '|' linebreak command
				 ;
command          : simple_command
				 | compound_command
				 | compound_command redirect_list
				 | function_definition
				 ;
compound_command : brace_group
				 | subshell
				 | for_clause
				 | case_clause
				 | if_clause
				 | while_clause
				 | until_clause
				 ;
subshell         : '(' compound_list ')'
				 ;
compound_list    : linebreak term
				 | linebreak term separator
				 ;
term             : term separator and_or
				 |                and_or
				 ;
for_clause       : For name                                      do_group
				 | For name                       sequential_sep do_group
				 | For name linebreak in          sequential_sep do_group
				 | For name linebreak in wordlist sequential_sep do_group
				 ;
name             : NAME                     // Apply rule 5
				 ;
in               : In                       // Apply rule 6
				 ;
wordlist         : wordlist WORD
				 |          WORD
				 ;
case_clause      : Case WORD linebreak in linebreak case_list    Esac
				 | Case WORD linebreak in linebreak case_list_ns Esac
				 | Case WORD linebreak in linebreak              Esac
				 ;
case_list_ns     : case_list case_item_ns
				 |           case_item_ns
				 ;
case_list        : case_list case_item
				 |           case_item
				 ;
case_item_ns     :     pattern ')' linebreak
				 |     pattern ')' compound_list
				 | '(' pattern ')' linebreak
				 | '(' pattern ')' compound_list
				 ;
case_item        :     pattern ')' linebreak     DSEMI linebreak
				 |     pattern ')' compound_list DSEMI linebreak
				 | '(' pattern ')' linebreak     DSEMI linebreak
				 | '(' pattern ')' compound_list DSEMI linebreak
				 ;
pattern          :             WORD         // Apply rule 4
				 | pattern '|' WORD         // Do not apply rule 4
				 ;
if_clause        : If compound_list Then compound_list else_part Fi
				 | If compound_list Then compound_list           Fi
				 ;
else_part        : Elif compound_list Then compound_list
				 | Elif compound_list Then compound_list else_part
				 | Else compound_list
				 ;
while_clause     : While compound_list do_group
				 ;
until_clause     : Until compound_list do_group
				 ;
function_definition : fname '(' ')' linebreak function_body
				 ;
function_body    : compound_command                     // Apply rule 9
				 | compound_command redirect_list       // Apply rule 9
				 ;
fname            : NAME                                 // Apply rule 8
				 ;
brace_group      : Lbrace compound_list Rbrace
				 ;
do_group         : Do compound_list Done                // Apply rule 6
				 ;
simple_command   : cmd_prefix cmd_word cmd_suffix
				 | cmd_prefix cmd_word
				 | cmd_prefix
				 | cmd_name cmd_suffix
				 | cmd_name
				 ;
cmd_name         : WORD                                 // Apply rule 7a
				 ;
cmd_word         : WORD                                 // Apply rule 7b
				 ;
cmd_prefix       :            io_redirect
				 | cmd_prefix io_redirect
				 |            ASSIGNMENT_WORD
				 | cmd_prefix ASSIGNMENT_WORD
				 ;
cmd_suffix       :            io_redirect
				 | cmd_suffix io_redirect
				 |            WORD
				 | cmd_suffix WORD
				 ;
redirect_list    :               io_redirect
				 | redirect_list io_redirect
				 ;
io_redirect      :           io_file
				 | IO_NUMBER io_file
				 |           io_here
				 | IO_NUMBER io_here
				 ;
io_file          : '<'       filename
				 | LESSAND   filename
				 | '>'       filename
				 | GREATAND  filename
				 | DGREAT    filename
				 | LESSGREAT filename
				 | CLOBBER   filename
				 ;
filename         : WORD                      // Apply rule 2
				 ;
io_here          : DLESS     here_end
				 | DLESSDASH here_end
				 ;
here_end         : WORD                      // Apply rule 3
				 ;
newline_list     :              NEWLINE
				 | newline_list NEWLINE
				 ;
linebreak        : newline_list
				 | // empty
				 ;
separator_op     : '&'
				 | ';'
				 ;
separator        : separator_op linebreak
				 | newline_list
				 ;
sequential_sep   : ';' linebreak
				 | newline_list
				 ;
*/

#include "me/types.h"

typedef struct s_token		   t_token;
typedef struct s_token_literal t_token_literal;
typedef struct s_subtokens	   t_subtokens;

typedef enum e_token_kind	 t_token_kind;
typedef enum e_builtin_flags t_builtin_flags;

typedef union u_token_data t_token_data;

enum e_token_kind
{
	TOK_SPECIAL_BUILTIN,

	TOK_WORD,
	TOK_ASSIGNMENT_WORD,
	TOK_NAME,
	TOK_NEWLINE,
	TOK_IO_NUMBER,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_DOUBLE_SEMI,
	TOK_DOUBLE_LESS,
	TOK_DOUBLE_GREAT,
	TOK_LESS_AND,
	TOK_GREAT_AND,
	TOK_LESS_GREAT,
	TOK_DOUBLE_LESS_DASH,
	TOK_CLOBBER,

	TOK_If,
	TOK_Then,
	TOK_Else,
	TOK_Elif,
	TOK_Fi,
	TOK_Do,
	TOK_Done,

	TOK_Case,
	TOK_Esac,
	TOK_While,
	TOK_Until,
	TOK_For,

	TOK_Lbrace,
	TOK_Rbrace,
	TOK_Bang,
	TOK_In,

	TOK_SUBTOKENS,
};

enum e_builtin_flags
{
	BF_EMPTY = 0,
	BF_LINESEP = 1,
};

struct s_token_literal
{
	t_u8   *data;
	t_usize len;
};

union u_token_data {
	t_token_literal literal;
	t_builtin_flags flags;
	t_subtokens	   *subtokens;
};

struct s_token
{
	t_token_kind kind;
	t_token_data data;
};

#if (!defined(VEC_TOKEN_H)) && (!defined(SUBTOKENS_H))
# define SUBTOKENS_H_FORCE_IMPORT
# include "tok/subtokens.h"
# undef SUBTOKENS_H_FORCE_IMPORT
#endif

#endif /* TOKENS_H */
