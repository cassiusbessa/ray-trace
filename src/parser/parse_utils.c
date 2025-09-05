/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:01:53 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 19:01:53 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


float parse_float(char *str)
{
	float result = 0.0;
	float decimal_part = 0.0;
	int i, sign, decimal_places, in_decimal;

	i = 0;
	sign = 1;
	decimal_places = 0;
	in_decimal = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (in_decimal)
			{
				decimal_part = decimal_part * 10 + (str[i] - '0');
				decimal_places++;
			}
			else
				result = result * 10 + (str[i] - '0');
		}
		else if (str[i] == '.' && !in_decimal)
			in_decimal = 1;
		else
			break;
		i++;
	}

	while (decimal_places > 0)
	{
		decimal_part /= 10.0;
		decimal_places--;
	}

	result += decimal_part;
	return result * sign;
}

int count_tokens(char **tokens)
{
	int count;

	count = 0;
	if (!tokens)
		return 0;
	while (tokens[count])
		count++;
	return count;
}

int validate_parameter_count(char **tokens, char *element_type, int expected_count)
{
	int actual_count;

	if (!tokens)
		return 0;

	actual_count = count_tokens(tokens);
	if (actual_count != expected_count)
		return 0;

	return 1;
}
