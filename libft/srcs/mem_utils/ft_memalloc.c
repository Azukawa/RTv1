/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 20:26:56 by eniini            #+#    #+#             */
/*   Updated: 2022/02/22 12:26:09 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Allocates [size] bytes of new memory initialized to 0's and returns it.
**	Note: malloc(0) would result in implementation-dependent behavior,
*	and therefore passing 0 as argument will always return NULL.
*/
void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!size)
		return (NULL);
	mem = (void *)malloc(size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
