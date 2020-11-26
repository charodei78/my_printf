/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charodei <charodei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:13:04 by charodei          #+#    #+#             */
/*   Updated: 2020/07/11 16:32:06 by charodei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_size(const char *format, unsigned char *c)
{
	if (*format == 'l' && *(format + 1) == 'l')
	{
		*c = *c | MOD_LL;
		return (2);
	}
	else if (*format == 'l')
		*c = *c | MOD_L;
	else if (*format == 'h' && *(format + 1) == 'h')
	{
		*c = *c | MOD_HH;
		return (2);
	}
	else if (*format == 'h')
		*c = *c | MOD_H;
	return (1);
}
