/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charodei <hheimerd@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 18:51:50 by charodei          #+#    #+#             */
/*   Updated: 2020/05/01 18:52:08 by charodei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	return ((c == '\t' || c == '\n' || c == ' ' || c == '\v' ||
		c == '\f' || c == '\r') ? 1 : 0);
}

int			ft_atoi(const char *nptr)
{
	unsigned	dec;
	int			sign;
	long		res;

	sign = 0;
	res = 0;
	while (is_space(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		sign = *(nptr++) == '-' ? 1 : 0;
	while (*nptr && *nptr == '0')
		nptr++;
	while (*nptr)
	{
		dec = *(nptr++) - '0';
		if (dec > 9)
			break ;
		if ((res = res * 10 + dec) < 0)
			return (sign ? 0 : -1);
	}
	return ((int)(res * (sign ? -1 : 1)));
}
