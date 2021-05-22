#ifndef MINIRT_H
# define MINIRT_H

# include	"get_next_line.h"
# include	"../minilibx-linux/mlx.h"
# include <math.h>
# include <float.h>
# include <stdint.h>
# include <errno.h>

# define KEYCODE_ESC		0xff1b
# define KEYCODE_LEFT		0xff51
# define KEYCODE_RIGHT		0xff53
# define HOOK_NUM			33
# define ERROR	-1
# define EPSILON 0.000001

typedef struct s_vec
{
	double			x;
	double			y;
	double			z;
}				t_vec;

typedef enum e_objecttype
{
	SP,
	PL,
	CY,
	SQ,
	TR,
}				t_objecttype;

typedef struct s_cy
{
	t_vec			pos;
	t_vec			normal;
	double			radius;
	double			height;
}				t_cy;

typedef struct s_tr
{
	t_vec			Sirius;
	t_vec			Procyon;
	t_vec			Betelgeuse;
}				t_tr;

typedef struct s_sq
{
	t_vec			normal;
	t_vec			center;
	double			side_size;
}				t_sq;

typedef struct s_pl
{
	t_vec			normal;
	t_vec			pos;
}				t_pl;

typedef struct s_sp
{
	t_vec			center;
	double			rad;
}				t_sp;

typedef union u_data
{
	t_sp			sp;
	t_pl			pl;
	t_cy			cy;
	t_sq			sq;
	t_tr			tr;
}				t_data;

typedef struct s_rgb
{
	double			r;
	double			g;
	double			b;
}				t_rgb;

typedef struct s_mtrl
{
	t_rgb			amb;
	t_rgb			dif;
	t_rgb			spe;
	double			shininess;
}				t_mtrl;

typedef struct s_object
{
	t_objecttype	type;
	t_data			data;
	t_mtrl			mtrl;
}				t_object;

typedef struct s_ray
{
	t_vec			start;
	t_vec			dir;
}				t_ray;

typedef struct s_itrsec
{
	int				has_itrsec;
	double			dist;
	t_vec			pos;
	t_vec			normal;
}				t_itrsec;

typedef struct s_light
{
	t_vec			pos;
	t_rgb			illum;
}				t_light;

typedef struct s_img
{
	int				width;
	int				height;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_img;

typedef struct s_cam
{
	t_vec			pos;
	t_vec			dir;
	double			fov;
	t_img			img;
	t_vec			x_basis;
	t_vec			y_basis;
	t_vec			d_center;
	int				n;
}				t_cam;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

typedef struct s_info
{
	void			*mlx;
	void			*win;
	int				screen_width;
	int				screen_height;
	t_dlist			*cameras;
	t_list			*objects;
	t_rgb			ambient;
	t_list			*lights;
}				t_info;

// mlx		minilibx特有のやつ
// win 		minilibxのウィンドウを指すポインタ
// cameras	カメラのリスト
// objects	物体のリスト
// ambient	環境光の強度
// lights	光源のリスト

//////amb.c
t_rgb			amb_init(double r, double g, double b);
unsigned int	rgb_to_hex(int r, int g, int b);
unsigned int	col_to_hex(t_rgb rgb);
int				ch_amb(t_info *info, char **array);

//////bmp.c

int				save_bmp(t_info *info);
int				cam2bmp(t_cam *cam, char *filepath);
void			bmp_file_header(t_img *img, int fd);
void			bmp_info_header(t_img *img, int fd);
void			bmp_img_data(t_img *img, int fd);

//////cam.c

void			cam_basis(t_cam *cam);
t_cam			*cam_setup(t_info *info, t_vec pos, t_vec dir, double fov);
t_cam			*cam_init(t_info *info, t_vec pos, t_vec dir, double fov);
int				ch_cam(t_info *info, t_cam *tmp);
int				cam_tmp(char **array, t_cam *tmp);

//////cy.c

void			cy_calc(t_itrsec *itrsec, t_cy *cy, t_ray *ray, double *t);
t_itrsec		cy_itrsec(t_ray ray, t_cy *cy);
t_object		*init_cy(t_vec pos, t_vec normal, double *f, t_mtrl mtrl);
int				ch_cy(t_info *info, char **array);

//////err.c

int				ret_err(char *str);
int				exit_err(char *str);

//////keycon.c

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	get_color_from_img(t_img img, int x, int y);
int				key_press(int key, t_info *info);

//////light.c

t_light			*init_light(t_vec pos, t_rgb illum);
int				ch_light(t_info *info, char **array);

//////main.c

int				main_loop(t_info *info);
int				info_init(t_info *info);
int				exit_window(t_info *info);
int				main(int argc, char *argv[]);

//////pl.c

t_itrsec		pl_itrsec(t_ray ray, t_pl *pl);
t_object		*init_pl(t_vec pos, t_vec normal, t_mtrl mtrl);
int				ch_pl(t_info *info, char **array);

//////ray.c

int				no_params(char **array);
int				has_shadow(t_info *info, t_light light, t_itrsec itrsec);
t_rgb			calc_ref_diff(t_object object, t_itrsec itrsec, t_light light);
t_rgb			calc_ref_spec(t_ray ray, t_object shape, \
				t_itrsec itrsec, t_light light);
void			calc_ray(t_info *info, t_ray *ray, t_object \
				*nearest, t_rgb *result);

//////raytrace.c

t_itrsec		calc_itrsec(t_ray ray, t_object object);
t_object		*get_front_obj(t_info *info, t_ray ray);
void			raytrace(t_info *info, t_cam *cam, int x, int y);
void			make_object(t_info *info);

//////read_rtfile.c

void			free_array(void **array);
void			ch_array(t_info *info, char **array, int *ret, t_cam *tmp);
int				divide_file(int fd, t_info *info);
int				ch_rtfile_name(char *str);
int				read_rtfile(t_info *info, char *str);

//////res.c

int				ch_res(t_info *info, char **array);

//////rgb.c

// rgbの値を0.0~1.0に丸める
t_rgb			rgb_normalize(t_rgb rgb);
// 各成分から構造体の値を返す
t_rgb			rgb_init(double red, double green, double blue);
// t_rgb同士の足し算
t_rgb			rgb_add(t_rgb a, t_rgb b);
// t_rgb同士の各要素同士の掛け算
t_rgb			rgb_mult(t_rgb a, t_rgb b);
t_mtrl			init_mtrl(t_rgb diffuse, t_rgb specular, double shininess);

//////rgb2.c

t_rgb			rgb_scalar(t_rgb rgb, double n);
int				rgb_to_col(int r, int g, int b);
//rgbのレンジは0-255
int				rgb_range(int r, int g, int b);
//rgbの情報を各構造体メンバへ
int				get_rgbhex_from_rgbstr(unsigned int *rgb, char *rgbstr);
int				rgb2bin(t_rgb *rgb, char *rgbstr);

//////sp.c

void			sp_calc(t_itrsec *itrsec, double t, t_sp *sp, t_ray *ray);
t_itrsec		sp_itrsec(t_ray ray, t_sp *sp);
t_object		*init_sp(t_vec center, double rad, t_mtrl mtrl);
int				ch_sp(t_info *info, char **array);

//////sq.c

int				ch_sq(t_info *info, char **array);
t_object		*init_sq(t_vec center, t_vec normal, double side_size,
					t_mtrl mtrl);
t_itrsec		sq_itrsec(t_ray ray, t_sq *sq);
int				calc_sq(t_vec point, t_sq *sq);

//////tr.c

int				calc_tr(t_vec point, t_tr *tr);
t_itrsec		tr_itrsec(t_ray ray, t_tr *tr);
t_object		*init_tr(t_vec Sirius, t_vec Procyon, t_vec Betelgeuse, \
				t_mtrl mtrl);
int				ch_tr(t_info *info, char **array);

//////vec.c

// 各成分を受け取ってベクトル構造体として返す
t_vec			vec_init(double x, double y, double z);
// ベクトルの足し算 a + b
t_vec			vec_add(t_vec a, t_vec b);
// ベクトルの引き算 a - b
t_vec			vec_sub(t_vec a, t_vec b);
// ベクトルの定数倍 a * b
t_vec			vec_scalar(t_vec a, double b);
// 
int				ch_normal_range(t_vec *n);

//////vec2.c

// ベクトルの内積 a · b
double			vec_dot(t_vec a, t_vec b);
// ベクトルの外積 a × b
t_vec			vec_cross(t_vec a, t_vec b);
// ベクトルの大きさを1にしたものを返す
double			squared_norm(t_vec v);
double			norm(t_vec v);
t_vec			normalize(t_vec v);

//////win.c

int				win_set(t_info *info);
int				int_comp(int a, int b, char c);
void			init_normy(double *a, double *b);

//////utils

int				ft_isspace(char c);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
t_list			*ft_lstadd_back_new(t_list **lst, void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

//////utils2

t_dlist			*ft_add_data4dlst(t_dlist **list, t_dlist *new);
double			ft_atof(char *s);
int				ft_ch_dir_vec(t_vec *chdir);
int				ft_digit_check(char *str);
t_dlist			*ft_new_dlist(t_dlist **list, void *data);
size_t			ft_poipoi_strlen(void **poipoistr);
int				ft_split_counter(char *str, char c);
int				ft_str2vec(t_vec *vec, char *str);
size_t			ft_strchr_counter(char *str, char c);

#endif
