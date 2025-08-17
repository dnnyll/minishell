/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_exit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:01:55 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 18:30:51 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_sign_and_zeros(const char *str, int *sign)
{
	*sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	return (str);
}

static int	count_digits(const char *str)
{
	int	len;

	len = 0;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	return (len);
}

static int	compare_limit(const char *str, const char *limit)
{
	int	i;

	i = 0;
	while (str[i] && limit[i])
	{
		if (str[i] > limit[i])
			return (0);
		if (str[i] < limit[i])
			return (1);
		i++;
	}
	return (1);
}

int	is_long_limit(const char *str)
{
	int			sign;
	int			len;
	const char	*cmp;

	str = skip_sign_and_zeros(str, &sign);
	len = count_digits(str);
	if (len == 0 || str[len] != '\0')
		return (0);
	if (len < 19)
		return (1);
	if (len > 19)
		return (0);
	if (sign == 1)
		cmp = "9223372036854775807";
	else
		cmp = "9223372036854775808";
	return (compare_limit(str, cmp));
}
