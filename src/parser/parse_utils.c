#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"
#include <string.h>

// Split a line by spaces, ignoring spaces within commas
char **split_by_spaces(char *line, int *count)
{
	char **tokens = malloc(sizeof(char *) * 10); // Max 10 tokens
	int i = 0;
	int token_count = 0;
	int start = 0;
	int len = strlen(line);

	// Skip leading spaces
	while (i < len && line[i] == ' ')
		i++;
	start = i;

	while (i <= len)
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			if (i > start)
			{
				int token_len = i - start;
				tokens[token_count] = malloc(token_len + 1);
				strncpy(tokens[token_count], line + start, token_len);
				tokens[token_count][token_len] = '\0';
				token_count++;
			}
			// Skip consecutive spaces
			while (i < len && line[i] == ' ')
				i++;
			start = i;
		}
		else
		{
			i++;
		}
	}
	*count = token_count;
	return tokens;
}

void free_tokens(char **tokens, int count)
{
	for (int i = 0; i < count; i++)
		free(tokens[i]);
	free(tokens);
}

t_rgb parse_rgb(char *rgb_str)
{
	char *token;
	char *str_copy = strdup(rgb_str);
	float r, g, b;

	token = strtok(str_copy, ",");
	r = parse_float(token);

	token = strtok(NULL, ",");
	g = parse_float(token);

	token = strtok(NULL, ",");
	b = parse_float(token);

	free(str_copy);
	return (new_rgb(r, g, b));
}

t_tuple parse_tuple(char *tuple_str, int is_point)
{
	char *token;
	char *str_copy = strdup(tuple_str);
	float x, y, z;

	token = strtok(str_copy, ",");
	x = parse_float(token);

	token = strtok(NULL, ",");
	y = parse_float(token);

	token = strtok(NULL, ",");
	z = parse_float(token);

	free(str_copy);
	if (is_point)
		return (point(x, y, z));
	else
		return (vector(x, y, z));
}

float parse_float(char *str)
{
	return (atof(str));
}
