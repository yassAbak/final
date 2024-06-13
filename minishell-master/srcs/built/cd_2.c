/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:10 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:16 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env(t_env *env, char *str)
{
	char	var_value[BUFFER_SIZE];
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		ft_strcpy_env(var_value, tmp->str);
		if (ft_strncmp("OLDPWD=", var_value, 7) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strndup(str, ft_strlen(str));
			return (1);
		}
		tmp = tmp->next;
	}
	if (ft_strncmp("OLDPWD=", tmp->str, 7) != 0)
		add_env(&tmp, str);
	else
	{
		free(tmp->str);
		tmp->str = ft_strndup(str, ft_strlen(str));
		return (1);
	}
	return (0);
}

char	*get_path(t_env *env, char *location, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;

	while (env)
	{
		if (ft_strncmp(env->str, location, len) == 0)
		{
			oldpwd = malloc(sizeof(char) * (ft_strlen(env->str) - len) + 1);
			if (!oldpwd)
				return (NULL);
			i = len;
			j = 0;
			while (env->str[i])
				oldpwd[j++] = env->str[i++];
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

int	oldpwd_change(t_env *env)
{
	char	path_now[PATH_MAX];
	char	*oldpwd;

	if (getcwd(path_now, PATH_MAX) == NULL)
		return (0);
	oldpwd = ft_strjoin_no_free("OLDPWD=", path_now);
	if (oldpwd == NULL)
		return (0);
	is_env(env, oldpwd);
	free(oldpwd);
	return (1);
}

int	pwd_change(t_env *env)
{
	t_env	*tmp;
	char	path_now[PATH_MAX];
	char	*path;

	tmp = env;
	if (getcwd(path_now, PATH_MAX) == NULL)
		return (0);
	path = ft_strjoin_no_free("PWD=", path_now);
	while (tmp)
	{
		if (ft_strncmp("PWD=", tmp->str, 4) == 0)
		{
			free(tmp->str);
			tmp->str = ft_strndup(path, ft_strlen(path));
			free(path);
			return (1);
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_env(&env, path);
	free(path);
	return (0);
}

int	change_path(t_env *env, char *s1, char *s2, int lencmp)
{
	char	*env_path;

	env_path = NULL;
	if (ft_strcmp(s1, "HOME") == 0)
		oldpwd_change(env);
	env_path = get_path(env, s2, lencmp);
	if (!env_path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(" not set\n", 2);
		g_data->exit_value = 1;
		return (-1);
	}
	if (ft_strcmp(s1, "OLDPWD") == 0)
		oldpwd_change(env);
	if (chdir(env_path) == -1)
	{
		free(env_path);
		return (-1);
	}
	pwd_change(env);
	free(env_path);
	return (0);
}
