#include "trace.h"

// ray 생성자(정규화된 방향벡터를 갖는 ray)
t_ray		ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

// primary_ray(가장 처음 카메라에서 출발한 광선) 생성자
t_ray		ray_primary(t_camera *cam, double u, double v)
{
	t_ray   ray;

	ray.orig = cam->orig;
	// left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3	ray_color(t_ray *ray, t_object *world)
{
	double			t;
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	// 광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면)
	if (hit(world, ray, &rec))
	{
		return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
	}
	else
	{
		//ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
		t = 0.5 * (ray->dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
	}
}
