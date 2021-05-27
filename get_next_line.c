/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaxmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:57:31 by mbaxmann          #+#    #+#             */
/*   Updated: 2020/08/31 14:12:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stock2(char **stock, char **line, int *i, int *j)
{
	if (stock[0][0] == '\n')
	{
		if (!(line[0] = (char *)malloc(2)))
			return (-1);
		line[0][0] = '\0';
		(*j)++;
	}
	else
	{
		if (stock[0][0] == '\n')
			(*i)++;
		while (stock[0][*i + *j] != '\n' && stock[0][*i + *j])
			(*j)++;
		if (!(line[0] = (char *)malloc(sizeof(char) * (*j + 1))))
			return (-1);
		ft_memmove(line[0], &stock[0][*i], *j);
		(*i)++;
		line[0][*j] = '\0';
	}
	return (0);
}

int		ft_stock(char **stock, char **line)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = 0;
	if (ft_stock2(stock, line, &i, &j) == -1)
		return (-1);
	len = ft_strlen(stock[0]) - j - i;
	ft_memmove(stock[0], &(stock[0][j + i]), len + 1);
	len = ft_strlen(line[0]);
	len = (len == 0) ? 1 : len;
	if (line[0][len - 1] == 3)
	{
		line[0][len - 1] = '\0';
		return (0);
	}
	return (1);
}

int		ft_getbuffer2(char **buffer, char **stock, int *rd_return, int fd)
{
	int i;

	i = 0;
	if (!(*rd_return = read(fd, *buffer, BUFF_SIZE)))
	{
		buffer[0][0] = 3;
		buffer[0][1] = '\0';
	}
	else
		buffer[0][*rd_return] = '\0';
	*stock = ft_strjoin(*stock, ft_strdup(*buffer));
	i = 0;
	while (i < *rd_return && buffer[0][i] != '\n')
		i++;
	i = (buffer[0][i] == '\n') ? i : 0;
	return (i);
}

int		ft_getbuffer(int fd, char **stock)
{
	int		i;
	int		rd_return;
	char	*buffer;

	i = 0;
	rd_return = 1;
	if (!(buffer = (char *)malloc(BUFF_SIZE + 2)))
		return (-1);
	ft_bzero(buffer, BUFF_SIZE);
	while (buffer[i] != '\n' && buffer[0] != 3 && rd_return > 0)
		i = ft_getbuffer2(&buffer, stock, &rd_return, fd);
	free(buffer);
	return (rd_return);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	int			c;

	c = 0;
	if (!line || BUFF_SIZE < 1)
		return (-1);
	if (stock)
		while (stock[c] && stock[c] != 3)
			c++;
	else
		c = ft_getbuffer(fd, &stock);
	if (!stock[c])
		c = ft_getbuffer(fd, &stock);
	if (c == -1)
		return (-1);
	c = ft_stock(&stock, line);
	if (!c)
	{
		free(stock);
		stock = NULL;
		return (0);
	}
	if (c == -1)
		return (-1);
	return (1);
}
