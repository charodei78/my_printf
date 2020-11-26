/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_un_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:48:37 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 12:09:58 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

void						put_llu_nbr(unsigned long long int n)
{
	if (n >= 10)
		put_llu_nbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
}

static void					print_un_int(t_params *node,
	unsigned long long num, int z)
{
	wr_c('0', node->acc);
	if (z != 0 || num > 0)
		put_llu_nbr(num);
}

int							parse_un_int(t_params *node, unsigned long long num)
{
	long long				length;
	unsigned long long		tmp;
	int						z;

	z = node->acc;
	num = node->size & MOD_H ? (unsigned short)num : num;
	num = node->size & MOD_HH ? (unsigned char)num : num;
	if (node->size & MOD_L)
		num = (unsigned long)num;
	else if (!(node->size & MOD_LL))
		num = (unsigned int)num;
	length = z != 0 || num > 0 ? 1 : 0;
	node->acc = node->acc < 0 ? 0 : node->acc;
	tmp = num;
	while (tmp /= 10)
		length++;
	node->acc -= length < node->acc ? length : node->acc;
	if (node->flags & FLAG_MIN)
		print_un_int(node, num, z);
	if (node->width > (length + node->acc))
		wr_c(node->flags & FLAG_NIL && z == -1 ? '0' : ' ', node->width -
			length - node->acc);
	if (!(node->flags & FLAG_MIN))
		print_un_int(node, num, z);
	return (node->width > (length += node->acc) ? node->width : length);
}
