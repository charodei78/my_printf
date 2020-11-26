/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charodei <charodei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:12:00 by charodei          #+#    #+#             */
/*   Updated: 2020/07/11 16:32:10 by charodei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_flags(const char *format, unsigned char *c)
{
	int			counter;

	counter = 0;
	while (ft_strchr("-+ #0", *format) && *format)
	{
		if (*format == '-')
			*c = *c | FLAG_MIN;
		else if (*format == ' ')
			*c = *c | FLAG_SPS;
		else if (*format == '+')
			*c = *c | FLAG_PLS;
		else if (*format == '#')
			*c = *c | FLAG_HAS;
		else if (*format == '0')
			*c = *c | FLAG_NIL;
		format++;
		counter++;
	}
	return (counter);
}
