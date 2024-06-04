/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:39:04 by maiboyer          #+#    #+#             */
/*   Updated: 2024/06/04 23:21:55 by maiboyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "me/str/str.h"
#include "me/types.h"
#include "me/vec/vec_str.h"
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
	t_vec_str	*lines;
	t_vec_token *out_vec;
	t_quote_type qtype;
	bool		 stop;
	bool		 error;
	t_usize		 line_len;
};

void token_free(t_token tok)
{
	(void)(tok);
}

void build_tok_line(t_usize l_idx, const t_str *line, t_tok_build_state *s)
{
	t_usize i;

	(void)(l_idx);
	if (s->stop || s->error)
		return;
	s->line_len = str_len(*line);
	i = 0;
	while (i < s->line_len)
		i++;
}

t_error into_tokens(t_vec_str *lines, t_vec_token *out)
{
	t_vec_token		  vec;
	t_tok_build_state state;

	if (lines == NULL || out == NULL)
		return (ERROR);
	vec = vec_token_new(1024, token_free);
	if (vec.buffer == NULL)
		return (ERROR);
	state = (t_tok_build_state){};
	state.out_vec = &vec;
	state.lines = lines;
	state.stop = false;
	state.error = false;
	vec_str_iter(lines, (void (*)())build_tok_line, &state);
	if (state.error)
		return (vec_token_free(vec), ERROR);
	return (*out = vec, NO_ERROR);
}
