/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:45:30 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 12:11:55 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

void				wr_c(int c, unsigned int n)
{
	while (n--)
		write(1, &c, 1);
}

int					parse_char(t_params *node, int c)
{
	node->acc = node->acc < 0 ? 0 : node->acc;
	if (node->size == MOD_L)
		c = (unsigned char)c;
	else
		c = (char)c;
	if (node->flags & FLAG_MIN)
		write(1, &c, 1);
	if (node->width > 1)
		wr_c(node->flags & FLAG_NIL && !(node->flags & FLAG_MIN)
		? '0' : ' ', node->width - 1);
	if (!(node->flags & FLAG_MIN))
		write(1, &c, 1);
	return (node->width ? node->width : 1);
}
