/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:35:45 by git               #+#    #+#             */
/*   Updated: 2025/11/20 04:35:45 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_strlen_custom(const char *s, t_config cfg, int *full_width,
		int *i)
{
	int	str_len;

	*i = 0;
	if (!s)
		str_len = 6;
	else
		str_len = ft_strlen(s);
	if (cfg.precision != -1 && cfg.precision < 6 && !s)
		str_len = 0;
	if (cfg.precision != -1 && cfg.precision < str_len)
		str_len = cfg.precision;
	*full_width = str_len;
	if (cfg.width > str_len)
		*full_width = cfg.width;
	return (str_len);
}

static void	ft_write_null(char *s, int *i)
{
	const char	*null_str;

	null_str = "(null)";
	while (*null_str)
	{
		s[*i] = *null_str;
		*i += 1;
		null_str++;
	}
}

char	*ft_getstr(const char *s, t_config cfg)
{
	int		i;
	int		j;
	int		str_len;
	int		full_width;
	char	*str;

	j = 0;
	str_len = ft_strlen_custom(s, cfg, &full_width, &i);
	str = (char *)malloc(sizeof(char) * (full_width + 1));
	if (!str)
		return (NULL);
	while (!cfg.left_justify && i < full_width - str_len)
		str[i++] = ' ';
	if (!s && str_len == 6)
		ft_write_null(str, &i);
	while (s && s[j] && j < str_len)
	{
		str[i + j] = s[j];
		j++;
	}
	i += j;
	while (cfg.left_justify && i < full_width)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}
