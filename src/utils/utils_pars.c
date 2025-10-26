/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:09:23 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/26 16:25:07 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_skipspace(char *str)
{
	size_t	i;
	char	*ptr;

	ptr = str;
	i = 0;
	while (ptr[i] != '\0' && (ptr[i] == ' ' || ptr[i] == '\t' || ptr[i] == '\n'
			|| ptr[i] == '\v' || ptr[i] == '\f' || ptr[i] == '\r'))
		i++;
	return (&ptr[i]);
}

int	ft_endwith(char *str, char *suffix)
{
	size_t	len_str;
	size_t	len_suffix;
	size_t	start_i;

	if (!str || !suffix)
		return (0);
	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	if (len_suffix > len_str)
		return (0);
	start_i = len_str - len_suffix;
	if (ft_strncmp(&str[start_i], suffix, len_suffix) != 0)
		return (0);
	return (1);
}

int	ft_checkspace(char *line)
{
	if (line == NULL)
		return (1);
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
