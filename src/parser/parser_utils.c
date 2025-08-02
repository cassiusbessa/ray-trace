/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 20:00:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int line_is_empty_or_comment(const char *line)
{
    while (*line)
    {
        if (*line == '#')
            return 1;
        if (!isspace(*line))
            return 0;
        line++;
    }
    return 1;
}

int starts_with(const char *line, const char *prefix)
{
    while (*prefix)
    {
        if (*line != *prefix)
            return 0;
        line++;
        prefix++;
    }
    return 1;
}

void print_error(const char *msg)
{
    fprintf(stderr, "Parser Error: %s\n", msg);
}