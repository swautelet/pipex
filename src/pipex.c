/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:17:12 by swautele          #+#    #+#             */
/*   Updated: 2022/03/10 19:38:42 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

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
	char	**possible;
	int		i;
	char	*temp;
	int		j;
	int		k;

	possible = ft_split(str, ':');
	i = -1;
	while (possible[++i])
	{
		temp = ft_calloc(ft_strlen(possible[i]) + ft_strlen(name) + 2, 1);
		j = -1;
		while (possible[i][++j])
			temp[j] = possible[i][j];
		temp[j] = '/';
		j++;
		k = -1;
		while (name[++k])
			temp[j + k] = name[k];
		if (access(temp, X_OK) == 0)
		{
			free_table(possible);
			return (temp);
		}
		else
			free (temp);
	}
	free_table(possible);
	return (NULL);
}

int	command(char *path, char **arg, char **env, int pip[2])
{
	(void) pip;
	close(pip[0]);
	dup2(pip[1], 1);
	return (execve(path, arg, env));
}

int	prep_command(char *argv, char **envp)
{
	int		pl;
	char	*path;
	char	**arg;
	int		pip[2];
	int		id;
	int		w;
//	int		end;
//	char	buffer[1000];

	arg = ft_split(argv, ' ');
	pl = find_path_line(envp);
	path = find_path(&envp[pl][5], arg[0]);
	pipe(pip);
	id = fork();
	if (id == 0)
		command(path, arg, envp, pip);
	else
		wait(&w);
	close(pip[1]);
//	end = read(pip[0], buffer, 999);
//	buffer[end] = '\0';
//	close(pip[0]);
//	printf("%s", buffer);
	free(path);
	free_table(arg);
	return (pip[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	get[FOPEN_MAX];
	char	buffer[1000];
	int	out;
	int	len;
	
	if (argc < 4)
		return (0);
	i = 1;
	get[i] = open(argv[i], O_RDONLY);
	while (++i < argc - 2)
	{
		dup2(get[i - 1], 0);
		get[i] = prep_command(argv[i], envp);
	}
	out = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	// close(out);
	// out = open("outfile", O_WRONLY);
	// printf("%d\n", out);
	len = read(get[i], buffer, 999);
	while(len)
	{
		write(out, buffer, len);
		len = read(get[i], buffer, 999);
	}
	write(out, buffer, 1);
	close(out);
	// read(get2, buffer, 999);
	// printf("%s", buffer);
	while(i >= 1)
	{
		close(get[i]);
		i--;
	}
}
