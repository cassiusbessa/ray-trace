#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"

// Validates and parses RGB values, ensuring they are in range 0-255
int validate_and_parse_rgb(char *rgb_str, t_rgb *out_rgb)
{
	char r_str[32], g_str[32], b_str[32];
	float r, g, b;
	int i = 0, j = 0;
	
	if (!rgb_str || !out_rgb)
		return (0);
	
	// Parse first number (r)
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		if (j >= 31) // Prevent buffer overflow
			return (0);
		r_str[j] = rgb_str[i];
		i++;
		j++;
	}
	r_str[j] = '\0';
	
	if (rgb_str[i] != ',') // Missing comma
		return (0);
	
	i++; // Skip comma
	j = 0;
	
	// Parse second number (g)
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		if (j >= 31) // Prevent buffer overflow
			return (0);
		g_str[j] = rgb_str[i];
		i++;
		j++;
	}
	g_str[j] = '\0';
	
	if (rgb_str[i] != ',') // Missing comma
		return (0);
	
	i++; // Skip comma
	j = 0;
	
	// Parse third number (b)
	while (rgb_str[i] && rgb_str[i] != '\0')
	{
		if (j >= 31) // Prevent buffer overflow
			return (0);
		b_str[j] = rgb_str[i];
		i++;
		j++;
	}
	b_str[j] = '\0';
	
	// Check if there are extra characters after the third number
	if (rgb_str[i] != '\0')
		return (0);
	
	r = parse_float(r_str);
	g = parse_float(g_str);
	b = parse_float(b_str);

	// Validate RGB values are in range 0-255
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);

	*out_rgb = new_rgb(r / 255.0, g / 255.0, b / 255.0);
	return (1);
}

// Legacy function for compatibility - will print error and return black on failure
t_rgb parse_rgb(char *rgb_str)
{
	t_rgb result;
	
	if (!validate_and_parse_rgb(rgb_str, &result))
	{
		printf("Error: Invalid RGB values '%s'. RGB values must be between 0-255.\n", rgb_str);
		return (new_rgb(0, 0, 0)); // Return black color on error
	}
	
	return (result);
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

// Count number of tokens in array
int count_tokens(char **tokens)
{
	int count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

// Validate exact number of parameters for element type
int validate_parameter_count(char **tokens, char *element_type, int expected_count)
{
	int actual_count;
	
	if (!tokens)
	{
		printf("Error: %s missing all parameters\n", element_type);
		return (0);
	}
	
	actual_count = count_tokens(tokens);
	
	if (actual_count < expected_count)
	{
		printf("Error: %s missing parameters. Expected %d, got %d\n", 
			element_type, expected_count, actual_count);
		return (0);
	}
	else if (actual_count > expected_count)
	{
		printf("Error: %s has too many parameters. Expected %d, got %d\n", 
			element_type, expected_count, actual_count);
		return (0);
	}
	
	return (1);
}
