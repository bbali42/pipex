/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbali <bbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:45:34 by bbali             #+#    #+#             */
/*   Updated: 2022/05/25 12:01:45 by bbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_format(char *path, char *bin)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (strlen_chr(path, 0) + strlen_chr(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		res[i++] = path[j++];
	res[i++] = '/';
	j = 0;
	while (bin[j])
		res[i++] = bin[j++];
	res[i] = 0;
	return (res);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && strlen_chr(path, ':') > -1)
	{
		dir = str_ndup(path, strlen_chr(path, ':'));
		bin = path_format(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += strlen_chr(path, ':') + 1;
	}
	return (cmd);
}
