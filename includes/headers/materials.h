#ifndef MATERIALS_H
# define MATERIALS_H

# include "colors.h"

typedef struct s_material
{
	t_rgb	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

// Material operations
t_material	new_material_default(void);
t_bool		equal_materials(t_material m1, t_material m2);

#endif
