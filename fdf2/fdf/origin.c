#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

double deg_set (int deg)
{
	return(deg * M_PI / 180.0);
}
int x_point(int x,int y)
{
	return ((x * cos(deg_set(45))) - (y * sin(deg_set(57))) + 0.5);
}

point_x_y isometric(double x, double y, double angle) 
{

	double isomatrix[2][2];
	point_x_y result;
	angle = 45;
    isomatrix[0][0] = cos(deg_set(angle));
    isomatrix[0][1] = -sin(deg_set(angle));
    isomatrix[1][0] = sin(deg_set(angle));
    isomatrix[1][1] = cos(deg_set(angle));
  
	result.x = ((sqrt(2) / 2.0) * (isomatrix[0][0] * x + isomatrix[0][1] * y)+0.5);
	 result.y = ((sqrt(2) / 2.0) * (isomatrix[1][0] * x + isomatrix[1][1] * y)+0.5);

  return result;
}

int y_point(int x,int y)
{
	return ((x * sin(deg_set(45))) + (y * cos(deg_set(57))) + 0.5);
}
void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /8 ));
	*(unsigned int*)dst = color;
}

void plot_line_low(t_data *img, int x0, int y0, int x1, int y1) 
{
    int dx;
    int dy;
    int yi;
	int x;
	int y;
	int f;

	yi= 1;
    y = y0;
	x = x0;
   	dx = x1 - x0;
	dy = y1 - y0;
    f = 2 * dy - dx;
	if (dy < 0) 
	{
        yi = -1;
        dy = -dy;
    }
    while (x <= x1) 
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
        printf("low (%d, %d)\n", x, y);

        if (f > 0) 
		{
            y += yi;
            f -= 2 * dx;
        }

        f += 2 * dy;
		x++;
    }
}

void plot_line_high(t_data *img, int x0, int y0, int x1, int y1) 
{
    int dx;
    int dy;
    int xi;
	int f;
	int x;
	int y;
	
	dx = x1 -x0;
	dy = y1 -y0;
	y = y0;
	xi = 1;
    f = 2 * dx - dy;
    x = x0;
    if (dx < 0)
	{
        xi = -1;
        dx = -dx;
    }

    while(y <= y1)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
        printf("high (%d, %d)\n", x, y);
        if (f > 0) 
		{
            x += xi;
            f -= 2 * dy;
        }

        f += 2 * dx;
		y++;
    }
}

void plot_line(t_data *img, int x0, int y0, int x1, int y1) 
{
    if (abs(y1 - y0) < abs(x1 - x0)) 
	{
//		printf("x0 %d y0 %d x1 %d y1 %d\n", x0, y0, x1, y1);
        if (x0 > x1)
            plot_line_low(img, x1, y1, x0, y0);
        else
            plot_line_low(img, x0, y0, x1, y1);
    } 
	else 
	{
        if (y0 > y1)
            plot_line_high(img, x1, y1, x0, y0);
        else
            plot_line_high(img, x0, y0, x1, y1);
    }
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}
void make_pole (t_data *img, int x, int y)
{
	int s_y;
	int e_y;
	int i;
	int gap;
	int x0;
	int y0;
	int x1;
	int y1;
	point_x_y result;
	gap = 400;
	i = 0;
	s_y = img->point[y][x]*2;
	e_y = img->point[y+1][x]*2;
	y = y * 30;
	if (x == 0)
		x = 30;
	else
		x = x * 30;
	x+=gap;
	result = isometric(x,y-s_y,60);
	x0 = result.x;
	y0 = result.y;
	result = isometric(x,y+30-e_y,60);
	x1 = result.x;
	y1 = result.y;
	plot_line(img,x0,y0,x1,y1);
}
void make_h (t_data *img, int x, int y)
{
	int gap;
	int x0;
	int y0;
 	int y1;
	int x1;
	int s_y;
	int e_y;
	point_x_y result;
	s_y = img->point[y][x]*2;
	e_y = img->point[y][x+1]*2;
	gap = 400;
	y = y * 30;
	if (x == 0)
		x = 30;
	else
		x = x * 30;
	x+=gap;
	result = isometric(x,y-s_y,60);
	x0 = result.x;
	y0 = result.y;
	result = isometric(x+30,y-e_y,60);
	x1 = result.x;
	y1 = result.y;
	plot_line(img,x0,y0,x1,y1);
}
void map_maker (int fd, t_data *img)
{
	int x;
	int y;
	int ffd;
	ffd = fd;
	y= 1;
	while (y < img->y)
	{
		x = 1;
		while (x < img->x)
		{
			if (y < img->y-1)
				make_pole(img,x,y);
			if (x < img->x-1)
				make_h(img,x,y);
			x++;
		}
		y++;
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
	printf("%d\n", count);
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
