/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:50:45 by swautele          #+#    #+#             */
/*   Updated: 2022/03/08 21:12:19 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"



static void	ft_free(char **r, int l)
{
	while (l >= 0)
	{
		free(r[l]);
		l--;
	}
	free(r);
}

static size_t	ft_count(const char *str, const char c)
{
	size_t	l;

	l = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str != c && *str)
			l++;
		while (*str && *str != c)
			str++;
	}
	return (l);
}

static int	ft_len(const char *str, const char c)
{
	int	d;

	d = 1;
	while (*str && *str != c)
	{
		d++;
		str++;
	}
	return (d);
}

static void	alloc_memory(char **r, const char *str, char c)
{
	size_t	i;
	size_t	l;

	l = -1;
	while (*str)
	{
		while (*str == c)
			str++;
		if (!*str)
			break ;
		i = 0;
		l++;
		r[l] = malloc (sizeof(char) * (ft_len(str, c)));
		if (r[l] == NULL)
		{
			ft_free(r, l);
			return ;
		}
		while (*str && *str != c)
			r[l][i++] = *str++;
		if (*str == c || *str == '\0')
			r[l][i] = '\0';
	}
}

char	**ft_split(char const *str, char c)
{
	char	**r;

	if (!str)
		return (0);
	r = ft_calloc (sizeof(char *), ft_count(str, c) + 1);
	if (r == NULL)
		return (NULL);
	alloc_memory(r, str, c);
	return (r);
}
