#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화
	hit_anything = FALSE;
	while (world != NULL)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}

// hit_obj 함수는 오브젝트 타입에 맞는 hit 함수를 호출한다.
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	return (hit_result);
}

// hit_sphere 함수는 관련 정보를 hit_record 구조체에 저장하고 bool 값을 리턴.
// double	hit_sphere(t_sphere *sp, t_ray *ray)를 아래와 같이 변경
t_bool	hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3		oc; //방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double		a;
	// b를 half_b로 변경
	double		half_b;
	double		c;
	double		discriminant; //판별식
	double		sqrtd; //판별식의 제곱근
	double		root; //근

	t_sphere	*sp;

	sp = obj->element;
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
