/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upphexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:27:09 by fsaffiri          #+#    #+#             */
/*   Updated: 2024/06/15 17:19:14 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hexa_trick(char *s, int point, int len)
{
	int	lung;

	lung = ft_strlen_pf(s);
	if (point >= lung)
	{
		len = hexa_trick(s, point / lung, len);
		if (len == -1)
			return (-1);
		if (write (1, &s[point % lung], 1) == -1)
			return (-1);
		len++;
	}
	if (point < lung)
	{
		if (write (1, &s[point], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

int	ft_upphexa(int n)
{
	int		len;

	len = 0;
	len = hexa_trick("0123456789ABCDEF", n, len);
	return (len);
}
