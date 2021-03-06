/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckakuna <ck@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 10:40:24 by ckakuna           #+#    #+#             */
/*   Updated: 2020/08/21 15:34:38 by ckakuna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minish.h"

void		exit_command(t_ptr *ptr)
{
	clear_malloc(ptr);
	ft_free_array(ptr->is_env);
	exit(EXIT_SUCCESS);
}
