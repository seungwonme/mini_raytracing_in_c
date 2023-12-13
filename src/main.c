#include <stdio.h>
#include "print.h"
#include "scene.h"
#include "structures.h"
#include "trace.h"
#include "utils.h"

int main(void)
{
	int         i;
	int         j;
	double      u;
	double      v;

	t_color3    pixel_color;
	t_canvas    canv;
	t_camera    cam;
	t_ray       ray;
	t_object	*world;

	// Scene setting
	canv = canvas(400, 300);
	cam = camera(&canv, point3(0, 0, 0));

	world = object(SP, sphere(point3(-2, 0, -5), 2)); // world 에 구1 추가
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2))); // world 에 구2 추가
	oadd(&world, object(SP, sphere(point3(0, -1000, 0), 990))); // world 에 구3 추가

	// 랜더링
	// P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;

		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray, world);
			// write_color(pixel_color);
			++i;
		}
		--j;
	}
}
