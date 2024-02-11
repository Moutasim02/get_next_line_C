/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:43:57 by arosado-          #+#    #+#             */
/*   Updated: 2023/12/06 18:27:59 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_full_line(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 2));
	if (res == NULL)
		return (NULL);
	res[i + 1] = '\0';
	while (i != -1)
	{
		res[i] = str[i];
		i--;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		k;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (s2 == NULL || s1 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	k = -1;
	while (s2[++k] != '\0')
		new[i + k] = s2[k];
	new[i + k] = '\0';
	free(s1);
	return (new);
}

void	read_file_buffer(char *str[], int fd)
{
	char	*temp;
	int		r_count;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp == NULL)
		return ;
	r_count = -1;
	while (!ft_strchr(str[fd], '\n') && r_count != 0)
	{
		r_count = read(fd, temp, BUFFER_SIZE);
		if (r_count == -1)
		{
			free(temp);
			temp = NULL;
			free(str[fd]);
			str[fd] = NULL;
			return ;
		}
		temp[r_count] = '\0';
		str[fd] = ft_strjoin(str[fd], temp);
	}
	free(temp);
}

void	remove_full_line(char *str[], int fd)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	while (str[fd][i] != '\0' && str[fd][i] != '\n')
		i++;
	if (str[fd][i] == '\0')
	{
		free(str[fd]);
		str[fd] = NULL;
		return ;
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str[fd]) + 1 - i++));
	if (new == NULL)
		return ;
	new[ft_strlen(str[fd]) - i] = '\0';
	k = 0;
	while (str[fd][i + k] != '\0')
	{
		new[k] = str[fd][i + k];
		k++;
	}
	free(str[fd]);
	str[fd] = new;
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	read_file_buffer(str, fd);
	if (str[fd] == NULL)
		return (NULL);
	res = get_full_line(str[fd]);
	remove_full_line(str, fd);
	return (res);
}
