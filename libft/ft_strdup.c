/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:34:11 by lregenar          #+#    #+#             */
/*   Updated: 2020/05/12 18:41:29 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char *dest;

	if (!(dest = malloc((ft_strlen(src) + 1) * sizeof(char))))
		return (NULL);
	return (ft_strcpy(dest, src));
}
