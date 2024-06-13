/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:47:17 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:20 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr_bis(const char *haystack, const char *needle, int len)
{
	int	i;
	int	j;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (0);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (haystack[i + j] == needle[j] && needle[j] \
			&& haystack[i + j] != '=')
				j++;
			if (needle[j] == '\0' && i + j <= len && haystack[i + j] == '=')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
