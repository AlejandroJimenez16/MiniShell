/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:11:29 by alejanjiga        #+#    #+#             */
/*   Updated: 2025/01/23 12:39:13 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c)
{
	int	i;
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static void	initialize_vars(int *i, int *n_times, int *num_chara)
{
	*i = 0;
	*num_chara = 0;
	*n_times = 0;
}

static	void	obtain_num_chara(char const *s, char c, int *num_chara, int *i)
{
	*num_chara = 0;
	while (s[*i] != '\0' && s[*i] != c)
	{
		(*num_chara)++;
		(*i)++;
	}
}

static void	*freestr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

/**
 * @brief Splits a string into substrings based on a delimiter.
 *
 * This function divides a given string into multiple substrings based on a
 * specified delimiter character. It returns an array of strings (each string
 * being a substring) and the array is terminated with a NULL pointer.
 *
 * @param s The string to be split. This is the input string that will
 * be divided into substrings.
 * @param c The character used to split the string.
 * @return A dynamically allocated array of substrings (NULL-terminated).
 */
char	**ft_split(char const *s, char c)
{
	int		i;
	int		n_times;
	int		num_words;
	int		num_chara;
	char	**arr;

	initialize_vars(&i, &n_times, &num_chara);
	num_words = words_count(s, c);
	arr = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (n_times < num_words)
	{
		obtain_num_chara(s, c, &num_chara, &i);
		if (num_chara > 0)
		{
			arr[n_times] = ft_substr(s, i - num_chara, num_chara);
			if (!arr[n_times++])
				return (freestr(arr));
		}
		while (s[i] == c)
			i++;
	}
	arr[n_times] = NULL;
	return (arr);
}
/*

int	main()
{
	char *src = "^^^1^^2a,^^^^3^^^^--h^^^^";

	char **arr = ft_split("xxxxxxxxhello!", 'x');

	int n = words_count(src, 'x');

	for (int i = 0; i < n; i++)
	{
		printf("%s", arr[i]);
		printf("\n");
		free(arr[i]);
	}
	free(arr);
}
*/
