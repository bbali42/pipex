/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbali <bbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:06:43 by bbali             #+#    #+#             */
/*   Updated: 2022/05/25 12:10:52 by bbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	openfile(char *filename, int mode)
{
	if (mode == STDIN_FILENO)
	{
		if (access(filename, F_OK))
		{
			write(STDERR_FILENO, "pipex '", 7);
			write(STDERR_FILENO, filename, strlen_chr(filename, 0));
			write(STDERR_FILENO, "' : No such file or directory\n", 30);
			return (STDIN_FILENO);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = str_split(cmd, ' ');
	if (strlen_chr(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	write(STDERR_FILENO, "pipex '", 7);
	write(STDERR_FILENO, cmd, strlen_chr(cmd, 0));
	write(STDERR_FILENO, "' : command not found\n", 22);
	free_split(args);
	free(path);
	exit(127);
}

void	redirect(char *cmd, char **env)
{
	pid_t	child;
	int		end[2];

	pipe(end);
	child = fork();
	if (child)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
	else
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		exec(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 2;
	if (ac >= 5)
	{
		fdin = openfile(av[1], STDIN_FILENO);
		if (fdin < 0)
		{
			write(STDERR_FILENO, av[1], strlen_chr(av[1], 0));
			write(STDERR_FILENO, " : permission denied\n", 21);
		}
		if (fdin == STDIN_FILENO || fdin < 0)
			return (0);
		fdout = openfile(av[ac - 1], STDOUT_FILENO);
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		while (i < ac - 2)
			redirect(av[i++], env);
		exec(av[i], env);
	}
	else
		write(STDERR_FILENO, "Invalid arguments.\n", 19);
	return (0);
}
