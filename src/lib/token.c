/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:39:04 by maiboyer          #+#    #+#             */
/*   Updated: 2024/06/05 16:09:52 by maiboyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "me/mem/mem.h"
#include "me/str/str.h"
#include "me/string/string.h"
#include "me/types.h"
#include "me/vec/vec_token.h"
#include "tok/tokens.h"

typedef struct s_tok_build_state   t_tok_build_state;
typedef enum e_quote_type		   t_quote_type;
typedef enum e_tok_subtokens_state t_tok_subtokens_state;

enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

enum e_tok_subtokens_state
{
	STS_NONE,
	STS_ARITH,
	STS_CMD_SUB,
	STS_EXPENSION,
};

struct s_tok_build_state
{
	t_vec_token			 *tokens;
	t_quote_type		  qtype;
	t_usize				  idx;
	t_usize				  llen;
	bool				  unfinished;
	t_string			  current_word;
	t_str				  line;
	t_tok_build_state	 *subtokens;
	t_tok_subtokens_state substate;
};

void token_free(t_token tok)
{
	(void)(tok);
}

void error_msg(t_str msg)
{
	me_abort(msg);
}

/// @brief	joins two string, freeing them
/// @param	left a nullable string
/// @param	right a nullable string
/// @return	a string that is '<left><right>' with null values discarded
/// @note	passing tok_str_len(NULL, NULL) returns an empty string that needs
/// @note	to be freed
t_str tok_str_join(t_str left, t_str right)
{
	t_str	tmp;
	t_usize len;

	if (left == NULL && right == NULL)
		return (str_clone(""));
	if (left == NULL)
		return (tmp = str_clone(right), mem_free(right), tmp);
	if (right == NULL)
		return (tmp = str_clone(left), mem_free(left), tmp);
	len = str_len(left) + str_len(right) + 1;
	tmp = mem_alloc(len);
	return (str_l_cat(tmp, left, len), str_l_cat(tmp, right, len), mem_free(left), mem_free(right), tmp);
}

t_error into_tokens(t_tok_build_state *s)
{
	if (s == NULL)
		return (ERROR);
	s->unfinished = false;
	s->idx = 0;
	if (s->substate != STS_NONE)
	{
		s->subtokens->line = s->line;
		if (into_tokens(s->subtokens))
			return (ERROR);
		s->idx = s->subtokens->idx;
	}
	if (s->line == NULL)
	{
		if (s->qtype != NO_QUOTE)
			error_msg("Missing delimiter !\n");
		if (s->substate != STS_NONE)
			error_msg("Missing delimiter !\n");
	}
	s->llen = str_len(s->line);
	if (s->llen >= 2 && s->line[s->llen - 1] == '\n' && s->line[s->llen - 2] == '\\' && (s->llen >= 3 && s->line[s->llen - 3] != '\\'))
	{
		s->line[s->llen - 1] = '\0';
		s->line[s->llen - 2] = '\0';
	}
	while (s->idx < s->llen)
	{
		if (s->qtype == NO_QUOTE)
		{
		}
		else if (s->qtype == DOUBLE_QUOTE)
		{
		}
		else if (s->qtype == SINGLE_QUOTE)
		{
			if (s->line[s->idx] == '\'')
				string_push_char(&s->current_word, s->line[s->idx]);
		}
		s->idx++;
	}
	return (NO_ERROR);
}
