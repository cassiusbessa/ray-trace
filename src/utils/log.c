/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 18:41:55 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_error(char *message, char **to_free)
{
    if (to_free)
        ft_free_split(to_free);

    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(message, 2);
    ft_putchar_fd('\n', 2);
    exit(EXIT_FAILURE);
}


void log_debug(char *msg)
{
    #ifdef DEBUG
        ft_putstr_fd("[DEBUG] ", 1);
        ft_putstr_fd(msg, 1);
        ft_putchar_fd('\n', 1);
    #else
        (void)msg;
    #endif
}



