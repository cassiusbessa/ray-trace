/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:01:53 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 20:41:06 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	parse_float_continue(char *str, t_parse_data data);
static float	apply_decimal_places(t_parse_data data, int decimal_places);

float	parse_float(char *str)
{
	t_parse_data	data;

	data.result = 0.0;
	data.decimal_part = 0.0;
	data.i = 0;
	data.sign = 1;
	if (str[data.i] == '-')
	{
		data.sign = -1;
		data.i++;
	}
	else if (str[data.i] == '+')
		data.i++;
	return (parse_float_continue(str, data));
}

static float	parse_float_continue(char *str, t_parse_data data)
{
	int	decimal_places;
	int	in_decimal;

	decimal_places = 0;
	in_decimal = 0;
	while (str[data.i])
	{
		if (str[data.i] >= '0' && str[data.i] <= '9')
		{
			if (in_decimal)
			{
				data.decimal_part = data.decimal_part * 10 + (str[data.i]
						- '0');
				decimal_places++;
			}
			else
				data.result = data.result * 10 + (str[data.i] - '0');
		}
		else if (str[data.i] == '.' && !in_decimal)
			in_decimal = 1;
		else
			break ;
		data.i++;
	}
	return (apply_decimal_places(data, decimal_places));
}

static float	apply_decimal_places(t_parse_data data, int decimal_places)
{
	while (decimal_places > 0)
	{
		data.decimal_part /= 10.0;
		decimal_places--;
	}
	data.result += data.decimal_part;
	return (data.result * data.sign);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

int	validate_parameter_count(char **tokens,
		char *element_type __attribute__((unused)), int expected_count)
{
	int	actual_count;

	if (!tokens)
		return (0);
	actual_count = count_tokens(tokens);
	if (actual_count != expected_count)
		return (0);
	return (1);
}
