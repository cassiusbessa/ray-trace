/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thick.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:34:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/09 01:30:52 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

typedef struct s_env
{
   t_tuple *wind;
    t_tuple *gravity;
} t_env;

typedef struct s_projectile
{
    t_tuple *position;
    t_tuple *velocity;
} t_projectile;

t_env *create_env(t_tuple *wind, t_tuple *gravity)
{
    t_env *env;

    env = malloc(sizeof(t_env));
    env->wind = wind;
    env->gravity = gravity;
    return (env);
}

t_projectile *create_projectile(t_tuple *position, t_tuple *velocity)
{
    t_projectile *projectile;

    projectile = malloc(sizeof(t_projectile));
    projectile->position = position;
    projectile->velocity = normalize_vector(velocity);
    return (projectile);
}

t_projectile *tick(t_env *env, t_projectile *projectile)
{
    t_tuple *new_position;
    t_tuple *new_velocity;
    printf("Original Position: x: %f, y: %f, z: %f\n", projectile->position->x, projectile->position->y, projectile->position->z);
    printf("Original Velocity: x: %f, y: %f, z: %f\n", projectile->velocity->x, projectile->velocity->y, projectile->velocity->z);
    new_position = add_tuples(projectile->position, projectile->velocity);
    new_velocity = add_tuples(add_tuples(projectile->velocity, env->gravity), env->wind);
    return (create_projectile(new_position, new_velocity));
}

int main(void)
{
    t_tuple *position;
    t_tuple *velocity;
    t_tuple *gravity;
    t_tuple *wind;
    t_projectile *projectile;
    t_env *env;

    position = new_tuple(0, 1, 0, TRUE);
    velocity = new_tuple(1, 1, 0, FALSE);
    gravity = new_tuple(0, -0.1, 0, FALSE);
    wind = new_tuple(-0.01, 0, 0, FALSE);
    projectile = create_projectile(position, velocity);
    free(velocity);
    env = create_env(wind, gravity);
    while (projectile->position->y > 0)
    {
        projectile = tick(env, projectile);
        printf("Position: x: %f, y: %f, z: %f\n", projectile->position->x, projectile->position->y, projectile->position->z);
    }

    return (0);
}


