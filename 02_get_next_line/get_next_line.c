/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:42:20 by jwon              #+#    #+#             */
/*   Updated: 2020/06/03 20:35:40 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int				idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

char	*ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	int		idx;
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	idx = 0;
	while (str[idx])
	{
		buf[idx] = str[idx];
		idx++;
	}
	buf[idx] = '\0';
	return (buf);
}


char	*ft_substr(char *str, int start, int len)
{
	int				idx;
	char			*buf;

	if (!(buf = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		buf[idx] = str[start + idx];
		idx++;
	}
	buf[idx] = '\0';
	return (buf);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int				idx;
	char			*buf;

	if (!(buf = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	idx = 0;
	while (*s1)
		buf[idx++] = *s1++;
	while (*s2)
		buf[idx++] = *s2++;
	buf[idx] = '\0';
	return (buf);
}

int		get_next_line(char **line)
{
	int				len; // ��������� ���� ������ ����
	int				bytes; // read �Լ� ���� �� ������ ����
	char			*tmp; // ��Ȯ�� free�� ���� ����� �ӽ� ����
	char			buf[2]; // read �� ����, 0���� �ʱ�ȭ
	static char		*store; // read �� ���� ������ ����

	store = (store == NULL) ? ft_strdup("") : store;
	bytes = 1; // bytes �� �ʱ�ȭ
	while (bytes > 0 && !ft_strchr(store, '\n')) // eof �ƴϰ�, store�� ������ ������
	{
		bytes = read(0, buf, 1); // buf�� 1byte�� read
		buf[bytes] = '\0';
		tmp = ft_strjoin(store, buf); // store�� buf �̾���̱�
		free(store);
		store = tmp;
	}
	if (ft_strchr(store, '\n')) // store�� ������ ������
	{
		len = ft_strchr(store, '\n') - store; // ��������� ���� ���� �� len�� ����
		*line = ft_substr(store, 0, len); // line�� store�� ������������ ����
		tmp = ft_substr(store, len + 1, ft_strlen(store) - len); // store�� ���� ���ĺ��͸� �ٽ� store�� ����
		free(store);
		store = tmp;
	}
	if (bytes == 0) // eof �̸�
	{
		*line = ft_strdup(store); // line�� store ����
		free(store);
		store = NULL;
	}
	return (bytes); // read �Լ� ��ȯ���� gnl ��ȯ������ ���
}
