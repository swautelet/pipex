/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:08:19 by swautele          #+#    #+#             */
/*   Updated: 2022/03/14 21:01:37 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	find_path_line(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' &&
			env[i][3] == 'H' && env[i][4] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_path(char *str, char *name)
{
	t_explore	e;

	e.possible = ft_split(str, ':');
	e.i = -1;
	while (e.possible[++e.i])
	{
		e.temp = ft_calloc(ft_strlen(e.possible[e.i]) + ft_strlen(name) + 2, 1);
		e.j = -1;
		while (e.possible[e.i][++e.j])
			e.temp[e.j] = e.possible[e.i][e.j];
		e.temp[e.j] = '/';
		e.j++;
		e.k = -1;
		while (name[++e.k])
			e.temp[e.j + e.k] = name[e.k];
		if (access(e.temp, X_OK) == 0)
		{
			free_table(e.possible);
			return (e.temp);
		}
		else
			free (e.temp);
	}
	free_table(e.possible);
	return (NULL);
}

int	command(char *path, char **arg, char **env, int pip[2])
{
	close(pip[0]);
	if (path == NULL)
		exit_error("command not found");
	if (dup2(pip[1], 1) == -1)
		exit_error("failed to dup2");
	return (execve(path, arg, env));
}

int	prep_command(char *argv, char **envp)
{
	t_path	p;

	p.arg = ft_split(argv, ' ');
	p.pl = find_path_line(envp);
	p.path = find_path(&envp[p.pl][5], p.arg[0]);
	if (p.path == NULL)
		perror("command not found");
	if (pipe(p.pip) == -1)
		exit_error("failed to pipe");
	p.id = fork();
	if (p.id == -1)
		exit_error("failed to fork");
	if (p.id == 0)
		command(p.path, p.arg, envp, p.pip);
	else
		wait(&p.w);
	close(p.pip[1]);
	free(p.path);
	free_table(p.arg);
	return (p.pip[0]);
}
