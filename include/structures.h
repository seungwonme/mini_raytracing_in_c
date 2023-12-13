/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 20:10:42 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH	960
# define HEIGHT	540
# define IMG_RATIO	1.7778
# define EPSILON 1e-6	// 0.0000001
# define LUMEN 3 // 기준 광속/광량을 정의한 매크로, 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

typedef enum e_bool			t_bool;
typedef enum e_type			t_type;
typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_camera		t_camera;
typedef struct s_canvas		t_canvas;
typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_light		t_light;
typedef struct s_hit_record	t_hit_record;


enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_type
{
	SP = 0,
	LIGHT_POINT = 1,
};

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};


// P = O + d (P : 광선, O : 출발점, d : 방향벡터)
// P(t) = O + tD (t : 실수, D : 정규화된 방향벡터)

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct  s_camera
{
	t_point3	orig;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	double		focal_len; // 초점 거리
	t_point3	left_bottom; // 왼쪽 아래 코너점
};

struct  s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
};

struct s_hit_record
{
	t_point3	p; // 교점의 좌표
	t_vec3		normal; // 교점에서의 법선
	double		tmin;
	double		tmax;
	double		t; // 광선의 원점과 교점 사이의 거리
	t_bool		front_face;
	t_color3	albedo;
};

struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient; // 환경광
	t_ray			ray;
	t_hit_record	rec;
};

struct  s_sphere
{
	t_point3	center; // 구의 중심점
	double		radius; // 구의 반지름
	double		radius2; // 반지름의 제곱
};

struct s_object
{
	t_type		type;
	void		*element;
	void		*next;
	t_color3	albedo;
};

struct s_light
{
	t_point3	orig;
	t_color3	light_color;
	double		bright_ratio;
};


#endif
