/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 19:00:30 by magouin           #+#    #+#             */
/*   Updated: 2015/12/17 19:00:32 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.hpp>

static int	ft_read(char *buf, int fd, int type, char ***buff)
{
	int i;
	int r;

	if (type)
	{
		bzero(buf, BUFF_SIZE + 1);
		r = read(fd, buf, BUFF_SIZE);
		if (r < 0)
			return (-1);
		return (r);
	}
	*buff = (char **)malloc(50 * sizeof(char *));
	i = 0;
	while (i < 49)
	{
		(*buff)[i] = (char*)malloc((BUFF_SIZE + 1) * sizeof(char));
		bzero((*buff)[i], BUFF_SIZE + 1);
		i++;
	}
	(*buff)[i] = NULL;
	return (0);
}

 static char    *ft_strcpy(char *dest, const char *src)
 {
     int c;

     c = 0;
     while (src && src[c] != '\0')
     {
         dest[c] = src[c];
         c++;
     }
     dest[c] = '\0';
     return (dest);
 }

static void	edit(char **rez, char *buff, int i)
{
	int		len;
	char	*tmp;
	int		p;

	p = 0;
	len = 0;
	if (*rez)
		len = strlen(*rez);
	tmp = (char *)malloc(len + 1 + i);
	bzero(tmp, len + 1 + i);
	ft_strcpy(tmp, *rez);
	strncpy(tmp + len, buff, i);
	free(*rez);
	*rez = tmp;
}

static void	bufle(char *buff, int i)
{
	int r;

	r = 0;
	while (buff[r + i] != '\0')
	{
		buff[r] = buff[r + i];
		r++;
	}
	while (r < BUFF_SIZE + 1)
	{
		buff[r] = '\0';
		r++;
	}
}

static int	find(char *buff, char *rez, int fd, char **line)
{
	int i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
		{
			edit(&rez, buff, i);
			bufle(buff, i + 1);
			*line = rez;
			return (1);
		}
		i++;
	}
	edit(&rez, buff, strlen(buff));
	*line = rez;
	if (ft_read(buff, fd, 1, NULL) != 0)
		find(buff, rez, fd, line);
	else if (!(rez[0]))
		return (0);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char	**buff = NULL;
	char		*rez;
	int			r;

	rez = NULL;
	free(*line);
	*line = NULL;
	if (buff == NULL)
		ft_read(NULL, fd, 0, &buff);
	if (fd < 0 || fd > 49)
		return (-1);
	if (buff[fd][0] == '\0')
	{
		bzero(buff[fd], BUFF_SIZE + 1);
		r = ft_read(buff[fd], fd, 1, NULL);
		if (r < 0)
			return (-1);
	}
	if (find(buff[fd], rez, fd, line) == 1)
		return (1);
	return (0);
}
