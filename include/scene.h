#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_camera	camera(t_canvas *canvas, t_point3 origin);
t_canvas	canvas(int  width, int height);
t_sphere	sphere(t_point3 center, double radius);


#endif
