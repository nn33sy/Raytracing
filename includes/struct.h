#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_bmpheader
{
	char			signaturebytes[2];
	unsigned int	sizeofbitmapfile;
	unsigned int	reservedbytes;
	unsigned int	pixeldataoffset;
}				t_bmpheader;

typedef struct	s_bmpinfoheader{
	unsigned int	sizeofthisheader;
	unsigned int	width;
	unsigned int	height;
	unsigned short	numberofcolorplanes;
	unsigned short	colordepth;
	unsigned int	compressionmethod;
	unsigned int	rawbitmapdatasize;
	unsigned int	horizontalresolution;
	unsigned int	verticalresolution;
	unsigned int	colortableentries;
	unsigned int	importantcolors;
}				t_bmpinfoheader;

typedef	struct	s_list
{
	void			*object;
	int				type;
	struct s_list	*next;
	double			magic;
}				t_list;

typedef struct	s_coord
{
	double			x;
	double			y;
	double			z;
}				t_coord;

typedef struct	s_rgb
{
	double		r;
	double		g;
	double		b;
}				t_rgb;

typedef struct	s_palette{
	t_rgb		rgb;
	double		intensity;
	int			magic;
}				t_palette;

typedef struct	s_ray
{
	t_coord		origin;
	t_coord		direction;
}				t_ray;

typedef struct	s_light
{
	t_coord			pos;
	double			i;
	t_rgb			rgb;
	struct s_light	*next;
}				t_light;

typedef struct	s_amb_light
{
	double			ratio;
	t_rgb			rgb;
}				t_amb_lig;

typedef struct	s_sphere
{
	t_coord			origin;
	double			rayon;
	t_rgb			rgb;
	int				multicolor;

}				t_sphere;

typedef struct	s_plan
{
	t_coord			center;
	t_coord			direction;
	t_rgb			rgb;
}				t_plan;

typedef struct	s_square
{
	t_coord			center;
	t_coord			direction;
	double			side_size;
	t_rgb			rgb;
}				t_square;

typedef struct	s_triangle
{
	t_coord			first;
	t_coord			second;
	t_coord			third;
	t_rgb			rgb;
}				t_triangle;

typedef struct	s_cylinder
{
	t_coord			base;
	t_coord			direction;
	double			diameter;
	double			height;
	t_rgb			rgb;

}				t_cylinder;

typedef struct	s_matrix_two
{
	double			x1;
	double			x2;
	double			y1;
	double			y2;
}				t_matrix_two;

typedef struct	s_camera
{
	t_ray			ray;
	t_coord			direction;
	t_coord			forward;
	t_coord			right;
	t_coord			up;
	double			fov;
	struct s_camera	*next;
	struct s_camera	*before;
}				t_camera;

typedef struct	s_scene
{
	t_light			**light;
	t_camera		**camera;
	t_camera		*cam_actual;
	int				r_x;
	int				r_y;
	t_amb_lig		amb_light;
	t_list			**list;
	double			ratio;
	int				nb_rebond;
	t_palette		color_f;
}				t_scene;

typedef struct	s_point {
	t_coord			normal;
	t_coord			pos;
	t_rgb			rgb;
}				t_point;

typedef struct	s_list_gnl
{
	int					fd;
	char				*chain;
	struct s_list_gnl	*next;
	struct s_list_gnl	*prec;
}				t_list_gnl;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_scene			*scene;
}				t_vars;
#endif
