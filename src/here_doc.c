/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:12:31 by swautele          #+#    #+#             */
/*   Updated: 2022/03/14 19:45:47 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	f_strcmp(char *str1, char *str2)
{
	if (str1 == NULL && str2 == NULL)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return (-1000);
	while (*str2)
	{
		str1++;
		str2++;
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char )*str2);
	}
	return ((unsigned char)*str1 - (unsigned char )*str2);
}

int	endhere(char *buffer, char *end)
{
	while (*end && *buffer && *buffer == *end)
	{
		end++;
		buffer++;
	}
	if (!*end && *buffer == '\n')
		return (0);
	else
		return (1);
}

void	wr_heredoc(int fd, char *end)
{
	char	buffer[10];
	int		len;

	len = read (0, buffer, 10);
	write (fd, buffer, len);
	while (len != 0)
	{
		len = read(0, buffer, 10);
		if (endhere(buffer, end) == 0)
			break ;
		write (fd, buffer, len);
	}
}

int	ft_here_doc(int argc, char **argv, char **envp)
{
	t_read	r;
	int		id;

	if (argc < 5)
		return (0);
	r.i = 2;
	r.fd[r.i] = open("iwehiuwfiewchu.tmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
	wr_heredoc(r.fd[r.i], argv[r.i]);
	close (r.fd[r.i]);
	r.fd[r.i] = open("iwehiuwfiewchu.tmp", O_RDONLY, 00777);
	r.out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (r.fd[r.i] == -1 || r.out == -1)
		return (-1);
	while (r.i < argc - 2)
	{
		r.i++;
		dup2(r.fd[r.i - 1], 0);
		r.fd[r.i] = prep_command(argv[r.i], envp);
	}
	id = fork();
	if (id == 0)
		execve("/bin/rm", ft_split("rm iwehiuwfiewchu.tmp", ' '), envp);
	write_and_exit(r, 2);
	return (0);
}
