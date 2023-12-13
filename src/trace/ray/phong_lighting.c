#include "trace.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0); // 광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
	lights = scene->light;
	/* while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, get_light_point(scene, lights->element));
		lights = lights->next;
	} */
	light_color = vplus(light_color, scene->ambient);
	// 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}
