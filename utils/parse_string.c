/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 10:46:23 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 12:09:36 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/ft_printf.h"

int				parse_string(t_params *node, int *s)
{
	long long	length;

	length = 0;
	if (!s)
		s = (int *)"(null)";
	length = ft_strlen((const char *)s);
	if (node->acc != -1 && node->acc < length)
		length = node->acc;
	if (node->flags & FLAG_MIN)
		write(1, s, length);
	if (node->width > length)
		wr_c(' ', node->width - length);
	if (!(node->flags & FLAG_MIN))
		write(1, s, length);
	return (node->width > length ? node->width : length);
}
