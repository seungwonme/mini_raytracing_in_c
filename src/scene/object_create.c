 #include "scene.h"

t_object	*object(t_type type, void *element)
{
	t_object *new;

	if (!(new = malloc(sizeof(t_object))))
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sp;

	if (!(sp = malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}
