/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:47:44 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 12:09:10 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

static void			put_hex(size_t num, int mode)
{
	int				tmp;

	if (num > 15)
		put_hex(num / 16, mode);
	if ((tmp = num % 16) == 10)
		write(1, mode ? "A" : "a", 1);
	else if (tmp == 11)
		write(1, mode ? "B" : "b", 1);
	else if (tmp == 12)
		write(1, mode ? "C" : "c", 1);
	else if (tmp == 13)
		write(1, mode ? "D" : "d", 1);
	else if (tmp == 14)
		write(1, mode ? "E" : "e", 1);
	else if (tmp == 15)
		write(1, mode ? "F" : "f", 1);
	else if (tmp += '0')
		write(1, &tmp, 1);
}

static void			print_hex(t_params *node, unsigned long long num, int z)
{
	write(1, "0x", node->flags & FLAG_HAS &&
		!(node->flags & FLAG_NIL) ? 2 : 0);
	wr_c('0', node->acc += (node->flags & FLAG_HAS && node->acc > 0 ? 2 : 0));
	if (z != 0 || num > 0)
		put_hex((size_t)num, node->type == 'x' ? 0 : 1);
}

static void			cast_num(unsigned long long *num, t_params *node)
{
	if (node->size & MOD_L)
		*num = (unsigned long)*num;
	else if (!(node->size & MOD_LL))
		*num = (unsigned int)*num;
	if (node->size & MOD_H)
		*num = (unsigned short)num;
	else if (node->size & MOD_HH)
		*num = (unsigned char)*num;
}

int					parse_hex(t_params *node, unsigned long long num,
	unsigned long long tmp)
{
	long long		l;
	int				z;

	z = node->acc;
	cast_num(&num, node);
	node->acc = node->acc < 0 ? 0 : node->acc;
	if (node->acc <= 0 && num == 0 && z != -1)
		l = node->flags & FLAG_HAS ? 2 : 0;
	else
		l = node->flags & FLAG_HAS ? 3 : 1;
	tmp = num;
	write(1, "0x", node->flags & FLAG_HAS && node->flags & FLAG_NIL ? 2 : 0);
	while (tmp /= 16)
		l++;
	node->acc -= l < node->acc ? l : node->acc;
	if (node->flags & FLAG_MIN)
		print_hex(node, num, z);
	if (node->width > (l + node->acc))
		wr_c(node->flags & FLAG_NIL && z == -1 ? '0' : ' ', node->width -
			l - node->acc);
	if (!(node->flags & FLAG_MIN))
		print_hex(node, num, z);
	return (node->width > l + node->acc ? node->width : l + node->acc);
}
