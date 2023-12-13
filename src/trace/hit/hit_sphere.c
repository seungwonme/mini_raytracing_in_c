#include "structures.h"
#include "utils.h"
#include "trace.h"

// hit_sphere 함수는 관련 정보를 hit_record 구조체에 저장하고 bool 값을 리턴.
// double	hit_sphere(t_sphere *sp, t_ray *ray)를 아래와 같이 변경
t_bool	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc; //방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double	a;
	// b를 half_b로 변경
	double	half_b;
	double	c;
	double	discriminant; //판별식
	double	sqrtd; //판별식의 제곱근
	double	root; //근

	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	// 두 실근(t) 중 tmin <= t <= tmax 인 근을 찾는다. (작은 근부터 찾는다.)
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	// tmin <= t <= tmax 인 근을 찾았다면, hit_record 구조체에 관련 정보를 저장.
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선벡터
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터의 내적을 통해 광선이 구의 앞면에 있는지 뒷면에 있는지 판별.
	return (TRUE);
}
