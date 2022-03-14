/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:19:49 by swautele          #+#    #+#             */
/*   Updated: 2022/03/14 14:42:56 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_path{
	int		pl;
	char	*path;
	char	**arg;
	int		pip[2];
	int		id;
	int		w;
}	t_path;

typedef struct s_read{
	int		i;
	int		fd[FOPEN_MAX];
	char	buffer[1000];
	int		out;
	int		len;
}	t_read;

typedef struct s_fuck{
	char	**possible;
	int		i;
	char	*temp;
	int		j;
	int		k;
}	t_explore;

typedef struct s_exit{
	int	fd;
	int	excod;
}	t_exit;

char	**ft_split(char const *str, char c);
int		find_path_line(char **envp);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_strlen(char *str);
void	free_table(char **str);
char	*find_path(char *str, char *name);
int		prep_command(char *argv, char **envp);
int		f_strcmp(char *str1, char *str2);
int		ft_here_doc(int argc, char **argv, char **envp);

#endif