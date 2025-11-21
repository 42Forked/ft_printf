/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:17:22 by git               #+#    #+#             */
/*   Updated: 2025/11/20 16:17:22 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_getptr(uintptr_t ptr, t_config *cfg)
{
	int		i;
	char	*str;
	char	*nil;

	cfg->alt_form = 1;
	if (ptr != 0)
		return (ft_gethex(ptr, cfg, 0, 1));
	nil = "(nil)";
	if (cfg->width <= 5)
		str = (char *)malloc(sizeof(char) * (5 + 1));
	else
		str = (char *)malloc(sizeof(char) * (cfg->width + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (!cfg->left_justify && i < cfg->width - 5)
		str[i++] = ' ';
	while (*nil)
		str[i++] = *nil++;
	while (cfg->left_justify && i < cfg->width)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}
