/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiboyer <maiboyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:20:06 by maiboyer          #+#    #+#             */
/*   Updated: 2024/06/04 21:58:29 by maiboyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBTOKENS_H
#define SUBTOKENS_H

#ifdef SUBTOKENS_H_FORCE_IMPORT
# undef VEC_TOKEN_H
#endif

#include "me/types.h"
#include "me/vec/vec_token.h"
#include "tok/tokens.h"

typedef enum e_subtokens_type t_subtokens_type;
enum e_subtokens_type
{
	STT_ARITHMETIC,
	STT_EXPENSION,
	STT_SIMPLE_EXPENSION,
	STT_SUBCOMMAND,
};

struct s_subtokens
{
	t_vec_token		 tokens;
	t_subtokens_type ty;
};

#endif /* SUBTOKENS_H */
