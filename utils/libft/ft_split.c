/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:27:02 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/07 18:18:22 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_big_array(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count + 1);
}

static int	count_little_array(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	void	fill_matrix(char **matrix, int size, const char *s, char c)
{
	int	ex;
	int	skip;

	ex = 0;
	while (size && *s)
	{
		if (*s != c)
		{
			skip = count_little_array(s, c);
			matrix[ex] = ft_substr(s, 0, skip);
			if (!matrix[ex])
			{
				while (ex)
					free(matrix[ex--]);
				free(matrix);
				return ;
			}
			s += skip;
			size--;
			ex++;
			continue ;
		}
		s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		q;

	if (!s)
		return (NULL);
	q = count_big_array(s, c);
	split = ft_calloc(q + 1, sizeof (char *) );
	if (!split)
		return (NULL);
	fill_matrix(split, q, s, c);
	return (split);
}

/*#include <stdio.h>
int	main(void)
{
	int	i = 0;
	char	**split = ft_split("UN_DEUX_TROIS", '_');
	while (i < 4)
	{
		printf("%s\n", split[i]);
		i++;
	}
	free(split);
}*/
