/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:11:45 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:11:45 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_strlencpy(const char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (dest);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_lenforcpy(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		lencpy;
	int		lentab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	lentab = ft_count(s, c);
	tab = malloc(sizeof(char *) * (lentab + 1));
	if (!tab)
		return (0);
	while (j < lentab)
	{
		while (s[i] == c)
			i++;
		lencpy = ft_lenforcpy(&s[i], c);
		tab[j] = ft_strlencpy(&s[i], lencpy);
		j++;
		i += lencpy;
	}
	tab[j] = 0;
	return (tab);
}
