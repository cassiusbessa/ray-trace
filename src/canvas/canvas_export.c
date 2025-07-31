/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 16:15:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


static int clamp(float v)
{
    if (v < 0.0f) return 0;
    if (v > 1.0f) return 255;
    return (int)(v * 255 + 0.5f);
}

void canvas_to_ppm(t_canvas *canvas, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
        return;

    fprintf(fp, "P3\n%d %d\n255\n", canvas->width, canvas->height);

    for (int y = 0; y < canvas->height; y++)
    {
        for (int x = 0; x < canvas->width; x++)
        {
            t_rgb col = canvas->pixels[y * canvas->width + x];
            fprintf(fp, "%d %d %d ", clamp(col.r), clamp(col.g), clamp(col.b));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}