/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:28:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/27 22:12:09 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#define TRUE 1
#define FALSE 0

# include "../includes/miniRT.h"

void	test_success(const char *message);
void	test_failure(const char *message);

int		test_check(int condition, const char *message);
int		test_check_double(double a, double b, const char *msg);
int		test_tuple_as_point(void);
int		test_tuple_as_vector(void);
int		test_add_tuples(void);
int		test_sub_points(void);
int		test_sub_vector_from_point(void);
int		test_sub_vectors(void);
int		test_sub_vector_from_zero_vector(void);
int		test_multiply_tuple_by_scalar(void);
int		test_multiply_tuple_by_fraction(void);
int		all_vector_magnitude_tests(void);
int		all_vector_normalize_tests(void);
int		all_vector_dot_product_tests(void);
int		all_vector_cross_product_tests(void);

int		vector_tests(void);
int		tuple_tests(void);

int		all_rgb_tests(void);
int		all_rgb_common_tests(void);

int		canvas_tests(void);

int		all_matrix_tests(void);
int		all_multiply_matrix_by_matrix_tests(void);
int     test_multiply_matrix_by_tuple(void);
int     identity_matrix_tests(void);
int     rotate_matrix_tests(void);
int     test_submatrix(void);
int     test_minor_matrix(void);
int     test_cofactor_matrix(void);
int     test_determinant_matrix(void);
int     invertible_matrix_tests(void);


int     run_test_translation_point(void);
int     run_test_translation_vector(void);
int     all_transformation_tests(void);
int     run_test_scaling(void);
int     run_test_rotation(void);
int     run_test_shearing(void);
int     run_test_chained_transformations(void);
int     run_test_ray(void);
int     run_test_sphere(void);
int     run_test_hit(void);
int     run_ray_tests(void);
int     run_sphere_transform_tests(void);
int     run_normal_tests(void);
int     run_reflect_tests(void);
int     run_light_tests(void);
int     run_material_tests(void);
int     run_lighting_tests(void);
int     run_world_tests(void);
int     run_computation_tests(void);
int     run_test_hit_shade(void);
int     run_test_color_at(void);
int     run_test_view_transform(void);
int     run_camera_tests(void);
int     run_render_tests(void);


#endif
