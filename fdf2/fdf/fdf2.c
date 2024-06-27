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
}	t_data;

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
	while (y <= e_y)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f < 0)
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
	while (e_y <= y)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
		if (f < 0)
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
	//printf ("value f :%f\n",f);
	//printf("s_x : %d s_y : %d e_x : %d e_y : %d \n",s_x,s_y,e_x,e_y);
	while (x <= e_x)
	{
		my_mlx_pixel_put(img,x,y*-1,0xffffff);
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
	f = (2 * (e_y - s_y)) - (e_x - s_x);
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
			f = f + (2 * (e_y - s_y) - (e_x - s_x));
			x++;
			y--;
		}
	}
}
void line_maker (t_data *img, int s_x, int s_y, int e_x, int e_y)
{
	double angle;
	if (e_x-s_x == 0)
		angle = ((double)e_y-(double)s_y)/1;
	else	
		angle = ((double)e_y-(double)s_y)/((double)e_x-(double)s_x);
	printf("angle : %f\n",angle);
	printf("s_x : %d s_y : %d e_x : %d e_y : %d \n",s_x,s_y,e_x,e_y);
	printf("cs_x : %f ss_y : %f ce_x : %fse_y : %f \n",cos(s_x),sin(s_y),cos(e_x),sin(e_y));
	if (angle >= 1)
		up_over_line_maker(img,s_x,s_y,e_x,e_y);
	if (angle >= 0 && angle < 1)
		up_under_line_maker(img,s_x,s_y,e_x,e_y);
	if (angle <= -1)
		down_over_line_maker(img,s_x,s_y,e_x,e_y);
	if (angle > -1 && angle < 0)
		down_under_line_maker(img,s_x,s_y*-1,e_x,e_y*-1);
}
void pole_maker (t_data *img, int s_x, int s_y, int e_y)
{
	int x;
	int y;

	x = s_x;
	y = s_y;
	
	while (y >= e_y)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
		y--;
	}
}
void map_maker (int fd, t_data *img)
{
	char *get_line;
	char **sp_line;
	int x ;
	int y ;
	int s_y;
	int e_y;
	int line;
	int row;
	line = 0;
	row = 0;
	y=100;
	while (1)
	{
	x=100;
	get_line = get_next_line(fd);
	if (!get_line)
		break;
	sp_line = ft_split(get_line,' ');

	row = 0;
	while (*sp_line)
	{
		if(*(sp_line + 1))
		{
			s_y = ft_atoi(*sp_line);
			e_y = ft_atoi(*(sp_line + 1));
			printf("\nline :%d row : %d \n",line,row);
			line_maker(img,x,(y - s_y),x + 30,(y - e_y));
		}
		//if (y != 100)
		//	line_maker(img,x,y,x-30,y-30);
		x+=30;
		sp_line++;
		row++;
	}
	line++;
	y+=30;
	}
}
int main ()
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int i;
	mlx=mlx_init();
	mlx_win = mlx_new_window(mlx,1920,1080,"hello world");
	img.img= mlx_new_image(mlx,1920,1080);

	img.addr = mlx_get_data_addr(img.img,&img.bits_per_pixel, &img.line_length,&img.endian);
	i = open("test_maps/42.fdf", O_RDONLY);
	map_maker(i,&img);
	mlx_put_image_to_window(mlx, mlx_win , img.img, 0, 0);
	mlx_loop(mlx);

}
