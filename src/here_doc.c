/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:12:31 by swautele          #+#    #+#             */
/*   Updated: 2022/03/11 19:27:31 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	f_strcmp(char *str1, char *str2)
{
	if (str1 == NULL && str2 == NULL)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return (-1000);
	while(*str1 == *str2)
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char )*str2);
}

void	wr_heredoc(int fd, char *end)
{
	char buffer[1000];
	int	len;

	len = read (0, buffer, 999);
	buffer[len] = '\0';
	write (fd, buffer, ft_strlen(buffer));
	while (f_strcmp(buffer, end) != 0)
	{
		len = read(0, buffer, 10);
		buffer[len] = '\0';
		write (fd, buffer, ft_strlen(buffer));
	}
}

void	ft_here_doc(int argc, char **argv, char **envp)
[
	t_read	r;

	if (argc < 5)
		return (0);
	r.i = 2;
	// modifier l entree pour prendre here_doc 
	r.fd[r.i] = open(argv[r.i], O_TMPFILE | O_RDWR);
	wr_heredoc(r.fd[r.i], argv[r.i]);
	r.out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (r.fd[r.i] == -1 || r.out == -1)
		return (-1);
	while (r.i < argc - 2)
	{
		r.i++;
		dup2(r.fd[r.i - 1], 0);
		r.fd[r.i] = prep_command(argv[r.i], envp);
	}
	r.len = read(r.fd[r.i], r.buffer, 999);
	while (r.len > 0)
	{
		write(r.out, r.buffer, r.len);
		r.len = read(r.fd[r.i], r.buffer, 999);
	}
	close(r.out);
	while (r.i >= 2)
	{
		close (r.fd[r.i]);
		r.i--;
	}
]