#include "trace.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0); // 광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, get_light_point(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	// 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

t_color3	get_light_point(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd; // diffuse 강도

	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn; // shininess value
	double		ks; // specular 강도

	double		brightness;

	light_dir = vunit(vminus(light->orig, scene->rec.p)); // 교점에서 출발하여 광원을 향하는 정규화된 벡터
	// cosθ는 θ 값이 90도일 때 0이고, θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 처리
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0); // 교점에서 출발하여 광원을 향하는 벡터와 교점에서의 법선 벡터의 내적값
	diffuse = vmult(light->light_color, kd); // 광원의 색상과 diffuse 강도를 곱해준다.

	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, ks), spec);

	brightness = light->bright_ratio * LUMEN;
	return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	// v - 2 * dot(v, n) * n
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}
