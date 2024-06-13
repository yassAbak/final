/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:11:58 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:12:01 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_len_malloc(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len++;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char			*dest;
	unsigned int	newnbr;
	int				lennbr;
	int				i;

	if (nbr < 0)
		newnbr = -nbr;
	else
		newnbr = nbr;
	lennbr = ft_len_malloc(newnbr);
	if (nbr < 0)
		lennbr++;
	dest = malloc(sizeof(char) * (lennbr + 1));
	if (!dest)
		return (NULL);
	i = lennbr;
	dest[i] = '\0';
	while (i-- > 0)
	{
		dest[i] = 48 + (newnbr % 10);
		newnbr /= 10;
	}
	if (nbr < 0)
		dest[0] = '-';
	return (dest);
}
