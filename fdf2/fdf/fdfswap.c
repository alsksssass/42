#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
typedef struct s_data{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int **point;
	int y;
	int x;
}	t_data;

int x_point(int x,int y,int s)
{
	return ((x * cos(M_PI/s)) - (y * sin(M_PI/s)) + 0.5);
}

int y_point(int x,int y,int s)
{
	return ((x * sin(M_PI/s)) + (y * cos(M_PI/s)) + 0.5);
}
void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /8 ));
	*(unsigned int*)dst = color;
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}
void up_over_line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double f;
	int x;
	int y;
	double angle;

	angle = e_y-s_y/e_x-s_x;
	x = s_x;
	y = s_y;
	f = (2 * (e_x - s_x)) - (e_y - s_y);
	printf("uo\n");
	while (y <= e_y)
	{
		printf("%d %d %f\n", x,y,f);
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f < 0)
		{
			f = f + (2 * (e_x - s_x));
			y++;
		}
		else
		{
			f = f + (2 * (e_x - s_x) - (e_y - s_y));
			x++;
			y++;
		}
	}
}
void down_over_line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double f;
	int x;
	int y;
	double angle;

	angle = e_y-s_y/e_x-s_x;
	x = s_x;
	y = s_y;
	f = (2 * (e_x - s_x)) - (e_y - s_y);
	printf("do\n");
	while (e_y <= y)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f > 0)
		{
			f = f + (2 * (e_x - s_x));
			y--;
		}
		else
		{
			f = f + (2 * (e_x - s_x) - (e_y - s_y));
			x++;
			y--;
		}
	}
}
void down_under_line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double f;
	int x;
	int y;

	x = s_x;
	y = s_y;
	f = (2 * (e_y - s_y)) - (e_x - s_x);
	printf("du\n");
	while (x <= e_x)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f < 0)
		{
			f = f + (2 * (e_y - s_y));
			x++;
		}
		else
		{
			f = f + ((2 * (e_y - s_y) ) - (e_x - s_x));
			x++;
			y--;
		}
	}
}

void up_under_line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double f;
	int x;
	int y;
	x = s_x;
	y = s_y;
	f = (2 * (e_x - s_x)) - (e_y - s_y);
	printf("uu\n");
	while (y <= e_y)
	{
		printf("%d %d %d %d\n",x,y,e_x,e_y);
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f < 0)
		{
			f = f + (2 * (e_x - s_x));
			y++;
		}
		else
		{
			f = f + (2 * (e_x - s_x) - (e_y - s_y));
			x++;
			y++;
		}
	}
}
void line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double angle;
	int gap;

	gap = 400;
	if (e_x-s_x == 0)
		angle = ((double)e_y-(double)s_y)/1;
	else	
		angle = ((double)e_y-(double)s_y)/((double)e_x-(double)s_x);

	if (angle >= 1)
		up_over_line_maker(img,s_x+gap,s_y,e_x+gap,e_y);
	if (angle >= 0 && angle < 1)
		up_under_line_maker(img,s_x+gap,s_y,e_x+gap,e_y);
	if (angle <= -1)
		down_over_line_maker(img,s_x+gap,s_y,e_x+gap,e_y);
	if (angle > -1 && angle < 0)
		down_under_line_maker(img,s_x+gap,((s_y)*-1),e_x+gap,((e_y)*-1));
}
void make_pole (t_data *img, int x, int y)
{
	int s_y;
	int e_y;
	int i;

	i = 0;
	s_y = img->point[y][x];
	e_y = img->point[y][x];
	y = y * 30;
	if (x == 0)
		x = 30;
	else
		x = x * 30;
	line_maker(img,x_point(x,y-30,4), y_point(x,y - 30,4),x_point(x,y,4), y_point(x,y,4));
}
void make_h (t_data *img, int x, int y)
{
	y = y * 30;
	if (x == 0)
		x = 30;
	else
		x = x * 30;
	line_maker(img,x_point(x -30 ,y,6), y_point(x-30,y,6),x_point(x,y,6), y_point(x,y,6));
}
void map_maker (int fd, t_data *img)
{
	int x;
	int y;
	int ffd;

	ffd = fd;
	y= img->y;

	while (y > 0)
	{
		x = img->x;
		while (x > 0)
		{
			printf("maker x y=%d %d \n", x, y);	
			//if (y>1)
			//	make_pole(img,x,y);
			if (x>1)
				make_h(img,x,y);
			x--;
		}
		y--;
	}
}

void check_map (t_data *img, char *map)
{
	char *maps;
	int x;
	int y;
	int i;
	int count;
	char *get_line;
	char **sp_line;
	y = 0;
	x = 0;	
	maps = map;
	i = open("test_maps/42.fdf", O_RDONLY);
	while (1)
	{
	count=0;
	get_line = get_next_line(i);
	if (!get_line)
		break;
	sp_line = ft_split(get_line,' ');
	while (*sp_line)
	{
		count++;
		sp_line++;
	}
	if (x == 0)
		x = count;
	y++;
	}
	img->y = y - 1;
	img->x = x - 1;
	img->point = (int **)malloc(sizeof(int *) * (y));
	ft_bzero(img->point,sizeof(int *)*(y));
	while (y > 0)
	{
		--y;
		img->point[y] = (int *)malloc(sizeof(int)*(x));
		ft_bzero(img->point[y],sizeof(int)*(x));
	}
	close(i);
}
void load_map (t_data *img, char *map)
{
	int x;
	int y;
	int i;
	char *get_line;
	char **sp_line;
	y = 0;
	
	check_map (img,map);
	i = open("test_maps/42.fdf", O_RDONLY);
	while (1)
	{
	x=0;
	get_line = get_next_line(i);
	if (!get_line)
		break;
	sp_line = ft_split(get_line,' ');
	while (*sp_line)
	{
		img->point[y][x] = ft_atoi(*sp_line);
		x++;
		sp_line++;
	}
	y++;
	}
	close(i);
}
int main ()
{
	void *mlx;
	void *mlx_win;
	int i;
	int j;

	i = 0;
	j = 0;
	t_data img;
	ft_bzero(&img,sizeof(t_data));
	mlx=mlx_init();
	mlx_win = mlx_new_window(mlx,1000,1000,"hello world");
	img.img= mlx_new_image(mlx,1000,1000);

	img.addr = mlx_get_data_addr(img.img,&img.bits_per_pixel, &img.line_length,&img.endian);
	load_map(&img,"42.fdf");
	map_maker(i,&img);
	printf("cos = %f\n",cos(0.523598));
	mlx_put_image_to_window(mlx, mlx_win , img.img, 0, 0);
	mlx_loop(mlx);

}
