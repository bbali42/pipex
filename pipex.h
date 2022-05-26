/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbali <bbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:04:54 by bbali             #+#    #+#             */
/*   Updated: 2022/05/25 12:06:12 by bbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

char	*get_path(char *cmd, char **env);
int		str_ncmp(char *str1, char *str2, int n);
int		strlen_chr(char *str, char c);
char	*str_ndup(char *str, unsigned int n);
char	**str_split(char *str, char sep);
void	free_split(char **args);

#endif