/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:35:12 by sadarnau          #+#    #+#             */
/*   Updated: 2019/12/05 20:22:53 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_1nl_2len(char **ptr, const char *s, int choice, int fd)
{
	int	i;

	i = 0;
	if (choice == 1)
	{
		while (ptr[fd][i])
		{
			if (ptr[fd][i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
	else
	{
		while (s[i])
			i++;
		return (i);
	}
}

char	*ft_str_1join_2dup(char **ptr, char *s2, int choice, int fd)
{
	char	*str;
	int		l;
	int		j;

	j = -1;
	if (choice == 1)
	{
		l = ft_1nl_2len(NULL, ptr[fd], 2, 0) + ft_1nl_2len(NULL, s2, 2, 0);
		if ((str = malloc(sizeof(char) * (l + 1))) == 0)
			return (NULL);
		while (ptr[fd][++j])
			str[j] = ptr[fd][j];
		l = 0;
		while (s2[l])
			str[j++] = s2[l++];
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (ft_1nl_2len(NULL, s2, 2, 0) + 1))))
			return (NULL);
		while (s2[++j])
			str[j] = s2[j];
	}
	str[j] = '\0';
	return (str);
}

int		ft_nl(char **ptr, char **line, int fd, int i)
{
	int		j;
	char	*tmp;

	j = -1;
	if (ft_1nl_2len(ptr, NULL, 1, fd))
		while (ptr[fd][++i])
		{
			if (ptr[fd][i] == '\n')
			{
				if ((*line = malloc(sizeof(char) * (i + 1))) == 0)
					return (-1);
				(*line)[i] = '\0';
				while (++j < i)
					(*line)[j] = ptr[fd][j];
				if ((tmp = ft_str_1join_2dup(NULL, ptr[fd] + i + 1, 2, 0)) == 0)
					return (-1);
				free(ptr[fd]);
				ptr[fd] = tmp;
				return (1);
			}
		}
	else
		return (ft_last_line(ptr, line, fd));
	return (-1);
}

int		ft_last_line(char **ptr, char **line, int fd)
{
	int	j;
	int	l;

	j = 0;
	l = ft_1nl_2len(NULL, ptr[fd], 2, 0);
	if ((*line = malloc(sizeof(char) * (l + 1))) == 0)
		return (-1);
	while (j < l)
	{
		(*line)[j] = ptr[fd][j];
		j++;
	}
	(*line)[j] = '\0';
	free(ptr[fd]);
	ptr[fd] = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			lu;
	static char	*ptr[10241];
	char		*tempptr;

	if (fd < 0 || line == NULL)
		return (-1);
	if (ptr[fd] == NULL)
	{
		if ((ptr[fd] = malloc(sizeof(char))) == 0)
			return (-1);
		ptr[fd][0] = '\0';
	}
	while ((lu = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[lu] = '\0';
		tempptr = ft_str_1join_2dup(ptr, buf, 1, fd);
		free(ptr[fd]);
		ptr[fd] = tempptr;
		if (ft_1nl_2len(ptr, NULL, 1, fd))
			break ;
	}
	if (lu < 0)
		return (-1);
	return (ft_nl(ptr, line, fd, -1));
}
