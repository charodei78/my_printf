/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:21:56 by hheimerd          #+#    #+#             */
/*   Updated: 2020/07/17 11:47:02 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define MOD_L		1
# define MOD_LL		2
# define MOD_H		4
# define MOD_HH		8
# define FLAG_MIN	1
# define FLAG_PLS	2
# define FLAG_SPS	4
# define FLAG_HAS	8
# define FLAG_NIL	16

# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct			s_params
{
	unsigned char		flags;
	long long			width;
	long long			acc;
	unsigned char		size;
	char				type;
}						t_params;

int						ft_printf(const char *format, ...);
int						check_size(const char *format, unsigned char *c);
int						check_flags(const char *format, unsigned char *c);
int						parse_char(t_params *node, int c);
int						parse_hex(t_params *node, unsigned long long num,
														unsigned long long tmp);
int						parse_int(t_params *node, long long num, int sign);
int						parse_string(t_params *node, int *s);
int						parse_un_int(t_params *node, unsigned long long num);
void					put_llu_nbr(unsigned long long int n);
void					wr_c(int c, unsigned int n);
void					clear_node(t_params *node);
int						ft_strlen_c(char *str, int c);
int						print_sign(unsigned char flags, long long num);
size_t					num_width(const char *str, t_params *node,
								va_list ap, int mode);

#endif
