/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:17:12 by swautele          #+#    #+#             */
/*   Updated: 2022/03/15 14:38:40 by swautele         ###   ########.fr       */
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
	t_read	r;

	if (f_strcmp(argv[1], "here_doc") == 0)
		ft_here_doc(argc, argv, envp);
	if (argc < 4)
		return (0);
	r.i = 1;
	r.fd[r.i] = open(argv[r.i], O_RDONLY);
	r.out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (r.fd[r.i] == -1 || r.out == -1)
	{
		perror("failed to open");
		return (errno);
	}
	while (r.i < argc - 2)
	{
		r.i++;
		if (dup2(r.fd[r.i - 1], 0) == -1)
			exit_error("dup2 failed");
		r.fd[r.i] = prep_command(argv[r.i], envp);
	}
	write_and_exit (r, 1);
}

int	write_and_exit(t_read r, int first)
{
	r.len = read(r.fd[r.i], r.buffer, 999);
	if (r.len == -1)
		perror("failed to read");
	while (r.len > 0)
	{
		write(r.out, r.buffer, r.len);
		r.len = read(r.fd[r.i], r.buffer, 999);
	}
	close(r.out);
	waitpid(-1, &r.len, 0);
	while (r.i >= first)
	{
		close (r.fd[r.i]);
		r.i--;
	}
	exit (0);
}

void	exit_error(char *str)
{
	perror(str);
	exit (errno);
}
