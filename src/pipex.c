/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:17:12 by swautele          #+#    #+#             */
/*   Updated: 2022/03/08 21:34:19 by swautele         ###   ########.fr       */
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
	i = 0;
	while (possible[i])
	{
		temp = malloc(ft_strlen(str) + ft_strlen(name));
		j = -1;
		while (possible[i][++j])
			temp[j] = possible[i][j];
		k = -1;
		while (name[++k])
			temp[j + k] = name[k];
		if (access(temp, X_OK))
		{
			return (temp);
		}
		else
			free (temp);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pl;
	char	*path;
	char	**arg;

	arg = ft_split(argv[1], ' ');
	pl = find_path_line(envp);
	path = find_path(envp[pl], arg[0]);
}
