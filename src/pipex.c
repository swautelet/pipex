/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:17:12 by swautele          #+#    #+#             */
/*   Updated: 2022/03/11 15:08:39 by swautele         ###   ########.fr       */
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



int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[FOPEN_MAX];
	char	buffer[1000];
	int		out;
	int		len;

	if (argc < 4)
		return (0);
	i = 1;
	fd[i] = open(argv[i], O_RDONLY);
	out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	while (i < argc - 2)
	{
		i++;
		dup2(fd[i - 1], 0);
		fd[i] = prep_command(argv[i], envp);
	}
	len = read(fd[i], buffer, 999);
	while (len > 0)
	{
		write(out, buffer, len);
		len = read(fd[i], buffer, 999);
	}
	close(out);
	while (i >= 1)
	{
		close (fd[i]);
		i--;
	}
}
