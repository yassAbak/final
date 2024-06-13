/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:48:41 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:43 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_alnum(char *to_search)
{
	int	i;

	i = 0;
	while (to_search[i])
	{
		if (!ft_isalnum(to_search[i]) && !ft_isspace(to_search[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strcpy_env(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFFER_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp_bis(char *s1, char s2)
{
	unsigned char	*ss1;

	ss1 = (unsigned char *)s1;
	if (!s2)
		return (0);
	if (ss1[0] == s2)
		return (0);
	return (1);
}

void	printf_err(char *s1, char *s2, char *arg)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
}

void	free_all(int pipeflag)
{
	if (g_data->token)
		free_token(&(g_data->token));
	g_data->token = NULL;
	if (g_data->cmd)
		free_cmd(&(g_data->cmd));
	if (!pipeflag)
	{
		if (g_data->env)
			free_env(&(g_data->env));
		g_data->env = NULL;
		if (g_data)
			free(g_data);
		g_data = NULL;
	}
}
