/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:39:04 by maiboyer          #+#    #+#             */
/*   Updated: 2024/06/05 13:35:47 by maiboyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "me/str/str.h"
#include "me/types.h"
#include "me/vec/vec_token.h"
#include "tok/tokens.h"

typedef struct s_tok_build_state t_tok_build_state;
typedef enum e_quote_type		 t_quote_type;

enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

struct s_tok_build_state
{
	t_vec_token *tokens;
	t_quote_type qtype;
	t_usize		 idx;
	t_usize		 llen;
	bool		 unfinished;
	t_const_str	 leftovers;
};

void token_free(t_token tok)
{
	(void)(tok);
}

t_error into_tokens(t_str line, t_tok_build_state *s)
{

	if (line == NULL || s == NULL)
		return (ERROR);
	s->idx = 0;
	s->llen = str_len(line);
	if (s->llen >= 2 && line[s->llen - 1] == '\n' && line[s->llen - 2] == '\\' && (s->llen >= 3 && line[s->llen - 3] != '\\'))
		line[s->llen - 1] = '\0';
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
			t_usize sq_len;
			sq_len = 0;
			while (line[s->idx + sq_len] != '\'' && line[s->idx + sq_len])
				sq_len++;
			if (line[s->idx + sq_len] != '\'')
			{
				s->unfinished = true;
				s->leftovers = str_join(s->leftovers, str_substring(line, s->idx, sq_len));
			}
			else
			{
			}
		}
	}

	return (NO_ERROR);
}
