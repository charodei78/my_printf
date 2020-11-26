/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:49:33 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 12:09:23 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

static void				print_int(t_params *node, long long num, int *sign,
																		int z)
{
	unsigned long long	tmp;

	if (*sign != 1)
		*sign = print_sign(node->flags, num);
	if (node->acc <= 0 && num == 0 && z != -1)
		return ;
	wr_c('0', node->acc);
	if (num < 0)
	{
		tmp = num * -1;
		put_llu_nbr(tmp);
	}
	else
		put_llu_nbr(num);
}

static void				cast_num(long long *num, t_params *node,
	long long *tmp)
{
	if (node->size & MOD_L)
		*num = (long)*num;
	else if (!(node->size & MOD_LL))
		*num = (int)*num;
	if (node->size & MOD_H)
		*num = (short)*num;
	else if (node->size & MOD_HH)
		*num = (char)*num;
	*tmp = *num;
}

int						parse_int(t_params *node, long long num, int sign)
{
	long long			l;
	long long			tmp;
	int					z;

	sign = 0;
	z = node->acc;
	node->acc = node->acc < 0 ? 0 : node->acc;
	cast_num(&num, node, &tmp);
	l = node->acc <= 0 && num == 0 && z != -1 ? 0 : 1;
	while (tmp /= 10)
		l++;
	node->acc -= l < node->acc ? l : node->acc;
	if (node->flags & FLAG_MIN)
		print_int(node, num, &sign, z);
	if (node->width > l + node->acc)
	{
		if (!(node->flags & FLAG_MIN) && node->flags & FLAG_NIL && z == -1)
			sign = print_sign(node->flags, num);
		tmp = node->width - l - node->acc - (num < 0 ||
				node->flags & FLAG_PLS || sign ? 1 : 0);
		wr_c(node->flags & FLAG_NIL && z == -1 ? '0' : ' ', tmp);
	}
	if (!(node->flags & FLAG_MIN))
		print_int(node, num, &sign, z);
	return (node->width > (l += node->acc + sign) ? node->width : l);
}
