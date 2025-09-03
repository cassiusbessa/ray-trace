#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"

t_rgb parse_rgb(char *rgb_str)
{
	char r_str[32], g_str[32], b_str[32];
	float r, g, b;
	int i = 0, j = 0;
	
	// Parse first number (r)
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		r_str[j] = rgb_str[i];
		i++;
		j++;
	}
	r_str[j] = '\0';
	
	if (rgb_str[i] != ',') // Missing comma
		return (new_rgb(0, 0, 0));
	
	i++; // Skip comma
	j = 0;
	
	// Parse second number (g)
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		g_str[j] = rgb_str[i];
		i++;
		j++;
	}
	g_str[j] = '\0';
	
	if (rgb_str[i] != ',') // Missing comma
		return (new_rgb(0, 0, 0));
	
	i++; // Skip comma
	j = 0;
	
	// Parse third number (b)
	while (rgb_str[i] && rgb_str[i] != '\0')
	{
		b_str[j] = rgb_str[i];
		i++;
		j++;
	}
	b_str[j] = '\0';
	
	r = parse_float(r_str);
	g = parse_float(g_str);
	b = parse_float(b_str);

	return (new_rgb(r / 255.0, g / 255.0, b / 255.0));
}

t_tuple parse_tuple(char *tuple_str, int is_point)
{
	char x_str[32], y_str[32], z_str[32];
	float x, y, z;
	int i = 0, j = 0;
	
	// Parse first number (x)
	while (tuple_str[i] && tuple_str[i] != ',')
	{
		x_str[j] = tuple_str[i];
		i++;
		j++;
	}
	x_str[j] = '\0';
	
	if (tuple_str[i] != ',') // Missing comma
	{
		if (is_point)
			return (point(0, 0, 0));
		else
			return (vector(0, 0, 0));
	}
	
	i++; // Skip comma
	j = 0;
	
	// Parse second number (y)
	while (tuple_str[i] && tuple_str[i] != ',')
	{
		y_str[j] = tuple_str[i];
		i++;
		j++;
	}
	y_str[j] = '\0';
	
	if (tuple_str[i] != ',') // Missing comma
	{
		if (is_point)
			return (point(0, 0, 0));
		else
			return (vector(0, 0, 0));
	}
	
	i++; // Skip comma
	j = 0;
	
	// Parse third number (z)
	while (tuple_str[i] && tuple_str[i] != '\0')
	{
		z_str[j] = tuple_str[i];
		i++;
		j++;
	}
	z_str[j] = '\0';
	
	x = parse_float(x_str);
	y = parse_float(y_str);
	z = parse_float(z_str);

	if (is_point)
		return (point(x, y, z));
	else
		return (vector(x, y, z));
}

float parse_float(char *str)
{
	float result = 0.0;
	float decimal_part = 0.0;
	int i = 0;
	int sign = 1;
	int decimal_places = 0;
	int in_decimal = 0;

	// Handle negative numbers
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	// Parse the number
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
			{
				result = result * 10 + (str[i] - '0');
			}
		}
		else if (str[i] == '.' && !in_decimal)
		{
			in_decimal = 1;
		}
		else
		{
			break; // Invalid character, stop parsing
		}
		i++;
	}

	// Add decimal part
	while (decimal_places > 0)
	{
		decimal_part /= 10.0;
		decimal_places--;
	}

	result += decimal_part;
	return (result * sign);
}
