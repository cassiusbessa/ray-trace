#include "../../includes/miniRT.h"

int equal_rgb(t_rgb *c1, t_rgb *c2)
{
    return (c1->r == c2->r && c1->g == c2->g && c1->b == c2->b);
}