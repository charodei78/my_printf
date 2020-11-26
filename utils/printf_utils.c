/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:15:00 by charodei          #+#    #+#             */
/*   Updated: 2020/07/17 12:10:13 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

int					print_sign(unsigned char flags, long long num)
{
	if (flags & FLAG_PLS && num >= 0)
		return (write(1, "+", 1));
	if (num < 0)
		return (write(1, "-", 1));
	if (flags & FLAG_SPS)
		return (write(1, " ", 1));
	return (0);
}

static int			parse_star(t_params *node,
		va_list ap, int mode)
{
	long int		tmp2;

	tmp2 = va_arg(ap, int);
	if (!mode)
	{
		if (tmp2 < 0)
			node->flags = (node->flags | FLAG_MIN) & ~FLAG_NIL;
		node->width = tmp2 * (tmp2 < 0 ? -1 : 1);
	}
	else
		node->acc = tmp2 < 0 ? -1 : tmp2;
	return (1);
}

size_t				num_width(const char *str, t_params *node,
		va_list ap, int mode)
{
	size_t			tmp;
	size_t			count;

	if (*str == '*')
		return (parse_star(node, ap, mode));
	count = 0;
	tmp = ft_atoi((const char *)str);
	if (mode)
		node->acc = tmp;
	else
		node->width = tmp;
	while (*(str++) == '0')
		count++;
	while (tmp)
	{
		tmp /= 10;
		count++;
	}
	return (count ? count : 1);
}

void				clear_node(t_params *node)
{
	node->flags = 0;
	node->width = 0;
	node->acc = -1;
	node->size = 0;
	node->type = 0;
}

int					ft_strlen_c(char *str, int c)
{
	int				count;

	if (!str)
		return (-1);
	count = 0;
	while (*str != c && *(str++))
		count++;
	return (count);
}
