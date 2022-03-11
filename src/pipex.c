/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:17:12 by swautele          #+#    #+#             */
/*   Updated: 2022/03/11 15:16:38 by swautele         ###   ########.fr       */
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

	if (argc < 4)
		return (0);
	r.i = 1;
	r.fd[r.i] = open(argv[r.i], O_RDONLY);
	r.out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
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
	while (r.i >= 1)
	{
		close (r.fd[r.i]);
		r.i--;
	}
}
