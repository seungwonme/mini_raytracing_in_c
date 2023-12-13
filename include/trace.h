#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

// trace/hit/hit.c
t_bool		hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);

// trace/hit/normal.c
void	set_face_normal(t_ray *r, t_hit_record *rec);

// trace/ray/phong_lighting.c
t_color3	phong_lighting(t_scene *scene);
t_color3	get_light_point(t_scene *scene, t_light *light);
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_bool		is_shadow(t_object *objs, t_ray right_ray, double light_len);

// trace/ray.c
t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);

#endif
