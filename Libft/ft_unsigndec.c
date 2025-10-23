/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigndec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:18:15 by fsaffiri          #+#    #+#             */
/*   Updated: 2024/06/15 17:01:03 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsigndec(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len = ft_unsigndec(n / 10);
		if (len == -1)
			return (-1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar_pf(('0' + n)) == -1)
			return (-1);
		len++;
	}
	return (len);
}
