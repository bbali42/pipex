/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbali <bbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:06:08 by bbali             #+#    #+#             */
/*   Updated: 2022/05/25 15:13:41 by bbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	str_ncmp(char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*str_ndup(char *str, unsigned int n)
{
	char				*res;
	unsigned int		i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	while (i < n)
		res[i++] = *str++;
	res[n] = 0;
	return (res);
}

char	**str_split(char *str, char sep)
{
	char	**tab;
	int		count;
	int		i;
	int		j;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j++] == sep)
			count++;
	}
	tab = malloc(sizeof(char *) * (count + 2));
	tab[count + 1] = NULL;
	i = 0;
	while (i < count + 1)
	{
		j = 0;
		while (str[j] && str[j] != sep)
			j++;
		tab[i++] = str_ndup(str, j);
		str = str + j + 1;
	}
	return (tab);
}

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (!args[0][0])
		free(args[0]);
	else
	{	
		while (i > 0)
			free(args[i--]);
	}
	free(args);
}
