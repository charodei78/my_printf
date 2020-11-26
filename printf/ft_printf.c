/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:21:04 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 10:49:58 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		handler(t_params *node, va_list ap)
{
	if (node->type == 'c')
		return (parse_char(node, (char)va_arg(ap, int)));
	if (node->type == '%')
		return (parse_char(node, '%'));
	if (node->type == 's')
		return (parse_string(node, va_arg(ap, int *)));
	if (node->type == 'p')
	{
		node->type = 'x';
		node->flags = node->flags | FLAG_HAS;
		node->size = node->size | MOD_LL;
		return (parse_hex(node, va_arg(ap, unsigned long long), 0));
	}
	if (node->type == 'd' || node->type == 'i')
		return (parse_int(node, va_arg(ap, long long), 0));
	if (node->type == 'u')
		return (parse_un_int(node, va_arg(ap, unsigned long long)));
	if (node->type == 'x' || node->type == 'X')
		return (parse_hex(node, va_arg(ap, unsigned long long), 0));
	return (0);
}

static int		parse_format(const char **format, va_list ap, t_params *node)
{
	clear_node(node);
	(*format)++;
	while (**format)
	{
		if (ft_strchr("-+ #0", **format))
			(*format) += check_flags(*format, &node->flags);
		else if (ft_strchr("0123456789*", **format))
			*format += num_width(*format, node, ap, 0);
		else if (**format == '.')
		{
			node->acc = 0;
			if (ft_isdigit(*(++(*format))) || **format == '*')
				*format += num_width(*format, node, ap, 1);
		}
		else if (ft_strchr("lh", **format))
			*format += check_size(*format, &node->size);
		else if (ft_strchr("cspdiuxXnfge%", **format))
		{
			node->type = (char)*((*format)++);
			break ;
		}
		else
			(*format)++;
	}
	return (handler(node, ap));
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_params	*fs;
	int			ret;
	int			temp;

	if (!(fs = (t_params*)malloc(sizeof(t_params))))
		return (-1);
	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			temp = parse_format(&format, ap, fs);
		else
		{
			temp = write(1, format, ft_strlen_c((char *)format, '%'));
			format += temp;
		}
		ret += temp;
	}
	va_end(ap);
	free(fs);
	return (ret);
}
