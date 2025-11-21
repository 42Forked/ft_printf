/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:40:14 by git               #+#    #+#             */
/*   Updated: 2025/11/20 15:40:14 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_getchar(int c, t_config cfg)
{
	int		i;
	int		full_len;
	char	*str;

	i = 0;
	full_len = 1;
	if (cfg.width > 0)
		full_len = cfg.width;
	str = (char *)malloc(sizeof(char) * (full_len + 1));
	while (cfg.width > 0 && !cfg.left_justify && i < cfg.width - 1)
		str[i++] = ' ';
	str[i++] = c;
	while (i < cfg.width)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}
