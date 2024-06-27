#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
//ss
double deg_set (int deg)
{
	return(deg * M_PI / 180.0);
}

double cos_apb(double a, double b)
{
	return ((cos(a) * cos(b)) - (sin(a) * sin(b)));
}
double cos_anb(double a, double b)
{
	return ((cos(a) * cos(b)) + (sin(a) * sin(b)));
}
double sin_apb(double a, double b)
{
	return ((sin(a) * cos(b)) + (cos(a) * sin(b)));
}

double sin_anb(double a, double b)
{
	return ((sin(a) * cos(b)) - (cos(a) * sin(b)));
}
t_point isometric(t_point point) 
{
	t_point result;
	int x;
	int y;
	int z;

	x = point.x;
	y = point.y;
	z = point.z;
	ft_bzero(&result, sizeof(result));
	result.x = x *cos(point.b) - z * sin(point.b);
    result.y = sin(point.a) * sin(point.b) * x + cos(point.a) * y + sin(point.a) * cos(point.b) * z;
	//result.x = ((x * cos(point.b)) + z * -sin(point.b));
	//result.y = ((((2 * y) * cos(point.a)) + x * -cos_apb(point.a,point.b) + ( x * cos_anb(point.a,point.b)) + ( z * sin_apb(point.a,point.b)) + (z * sin_anb(point.a,point.b))))/2;
	return result;
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
void plot_line_low(t_data *img, t_point result1, t_point result2) 
{
    int dx;
    int dy;
    int yi;
	int x;
	int y;
	int f;

	yi= 1;
    y = result1.y;
	x = result1.x;
   	dx = result2.x - result1.x;
	dy = result2.y - result1.y;
    f = 2 * dy - dx;
	if (dy < 0) 
	{
        yi = -1;
        dy = -dy;
    }
    while (x <= result2.x) 
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

void plot_line_high(t_data *img, t_point result1, t_point result2) 
{
    int dx;
    int dy;
    int xi;
	int f;
	int x;
	int y;
	
	dx = result2.x -result1.x;
	dy = result2.y -result1.y;
	y = result1.y;
	xi = 1;
    f = 2 * dx - dy;
    x = result1.x;
    if (dx < 0)
	{
        xi = -1;
        dx = -dx;
    }

    while(y <= result2.y)
	{
		my_mlx_pixel_put(img,x,y,0xffffff);
        printf("high (%d, %d)\n", x, y);
        printf("color %d\n", get_t(result1.color));
        if (f > 0) 
		{
            x += xi;
            f -= 2 * dy;
        }

        f += 2 * dx;
		y++;
    }
}

void plot_line(t_data *img, t_point *result1, t_point *result2) 
{
	int x0;
	int y0;
	int x1;
	int y1;

	x0 = result1->x;
	y0 = result1->y;
	x1 = result2->x;
	y1 = result2->y;

    if (fabs((double)y1 - y0) < fabs((double)x1 - x0)) 
	{
        if (x0 > x1)
            plot_line_low(img, *result2, *result1);
        else
            plot_line_low(img, *result1, *result2);
    } 
	else 
	{
        if (y0 > y1)
			plot_line_high(img, *result2, *result1);
        else
            plot_line_high(img, *result1, *result2);
    }
}

t_point view_point (t_data *img, int x, int y)
{
	t_point result;
	t_point result2;

	result.x = (img->x_c + (x * img->term)) + 0.5;
	result.y = (img->y_c + (y * img->term)) + 0.5;
	result.z = img->point[y][x] * 3;
	result.a = deg_set(img->deg_a);
	result.b = deg_set(img->deg_b);
	result.color = img->color[y][x];
	result2 = isometric(result);
	result.x = result2.x;
	result.y = result2.y;
	return (result);
}

void make_pole (t_data *img, int x, int y)
{
	t_point result1;
	t_point result2;
	
	result1 = view_point(img, x, y);
	result2 = view_point(img,x, y + 1);
	plot_line(img,&result1,&result2);
}

void make_h (t_data *img, int x, int y)
{
	t_point result1;
	t_point result2;
	
	result1 = view_point(img, x, y);
	result2 = view_point(img,x + 1, y);
	plot_line(img,&result1,&result2);
}

void map_maker (t_data *img)
{
	int x;
	int y;
	t_point set_point;

	y = 0;
	while (y < img->y)
	{
		x = 0;
		while (x < img->x)
		{
			if (y + 1 < img->y)
				make_pole(img,x,y);
			if (x + 1 < img->x)
				make_h(img,x,y);
			x++;
		}
		y++;
	}
}

int count_data(char **sp_data)
{
	int i;
	char **copy_data;
	
	i = 0;
	copy_data = sp_data;
	while(*copy_data++)
		i++;
	return i;
}
int split_saver(t_data *img, char *line, int y)
{
	char **sp_line;
	char **sp_data;
	int x;
	int i;

	x = 0;
	sp_line = ft_split(line,' ');
	while (x < img->x)
	{
		sp_data = ft_split(*sp_line,',');
		i = count_data(sp_data);
		if (i == 2)
		{
			img->point[y][x] = ft_atoi(*sp_data++);
			img->color[y][x] = ft_atoi(*sp_data);
			free(*(sp_data-1));
			free(*sp_data);
			free(sp_data-1);
		}
		else
		{
			img->point[y][x] = ft_atoi(*sp_data);
			free(*sp_data);
			free(sp_data);
		}
		free(*sp_line);
		x++;
		sp_line++;
	}
	free(sp_line-x);
	return (x);
}

int save_map_data(t_data *img, char *map)
{	
	int i;
	int y;
	char *get_line;

	y = 0;
	i = open(map, O_RDONLY);
	while (y < img->y)
	{
		get_line = get_next_line(i);
		if(!get_line)
			break;
		if(!split_saver(img, get_line, y))
			return 0;
		free(get_line);
		y++;
	}
	return 1;
}

int make_malloc(t_data *img)
{
	int **color;
	int **point;
	int i;

	i = 0;
	color = (int **)calloc(sizeof(int *), (img->y));
	if (!color)
		return 0;
	point = (int **)calloc(sizeof(int *), (img->y));
	if (!point)
		return 0;
	while (i < img->y)
	{
		color[i] = (int *)calloc(sizeof(int), (img->x));
		if(!color[i])
			return 0;
		point[i] = (int *)calloc(sizeof(int), (img->x));
		if(!point[i])
			return 0;
		i++;
	}
	img->color = color;
	img->point = point;
	return 1;
}

int split_counter(char *line)
{
	char **sp_line;
	int x;

	x = 0;
	sp_line = ft_split(line, ' ');
	while (sp_line[x])
	{
		free(sp_line[x]);
		x++;
	}
	free(sp_line);
	return (x);
}
int check_map_data(t_data *img, char *map, int fd)
{
	int x;
	int y;
	int count;
	char *get_line;
	char **sp_line;
	
	count = 0;
	y  = 0;
	while (1)
	{
		x=0;
		get_line = get_next_line(fd);
		if (!get_line)
			break;
		x = split_counter(get_line);
		if ((count != 0 && count != x) || x < 1)
			return 0;
		free(get_line);
		get_line = 0;
		count = x;
		y++;
	}
	img->x = count;
	img->y = y;
	return 1;
}

int check_name(char *map)
{
	int name_len;
	int i;
	char *fdf_point;
	char *check_point;

	name_len = ft_strlen(map);
	if (!ft_strnstr(map,".fdf",name_len))
		return 0;
	check_point = ft_strnstr(map,".fdf",name_len);
	if (ft_strlen(check_point) != 4)
		return 0;
	i = open(map, O_RDONLY);
	if (i < 0)
		return 0;
	close(i);
	return 1;
}
int load_map (t_data *img, char *map)
{
	int x;
	int y;
	int i;
	char *get_line;
	char **sp_line;
	y = 0;
	if(!check_name(map))
		return 0;
	i = open(map, O_RDONLY);
	if(!check_map_data(img,map,i))
	{
		close(i);
		return 0;
	}
	close(i);
	if(!make_malloc(img))
		return 0;
	if(!save_map_data(img,map))
		return 0;
	return 1;
}
int error_message (const char *message)
{
	write(1,message,ft_strlen(message));
	write(1,"\n",1);
	return 0;
}

int key_hook(int keycode, t_data *vars)
{
	if (keycode == 0)
		vars->deg_b-=1;
	if (keycode == 13)
		vars->deg_b+=1;
	if (keycode == 2)
		vars->deg_a+=1;
	if (keycode == 1)
		vars->deg_a-=1;
	//a = 0
	//w =13
	//d = 2
	//s = 1
	return 0;
}

void center_maker(t_data *img)
{
    t_point point;
    t_point result;
    int x;
    int y;

    point.x = img->term * img->x/2;
    point.y = img->term * img->y/2;
    point.z = 0;
    result = isometric(point);
    img->x_c = (1000 - result.x)/2;
    img->y_c = 500 - result.y;
}

int main (int argc, char **argv)
{
    if(argc != 2)
        return (error_message("map file error"));
    t_data img;
    ft_bzero(&img,sizeof(t_data));
    img.deg_a = 30;
    img.deg_b = 45;
    img.high = -2;
    if (!load_map(&img,argv[1]))
        return (error_message("map file error"));
    img.term = 30;
    center_maker(&img);
    img.mlx=mlx_init();
    img.win = mlx_new_window(img.mlx,1000,1000,"hello world");
    img.img= mlx_new_image(img.mlx,1000,1000);
    img.addr = mlx_get_data_addr(img.img,&img.bits_per_pixel, &img.line_length,&img.endian);
    map_maker(&img);
    printf("%d\n",img.x * img.term/2);
    printf("%d\n",img.y * img.term/2);
    mlx_put_image_to_window(img.mlx, img.win , img.img, 0, 0);
    mlx_key_hook(img.win, key_hook, &img);
    mlx_loop(img.mlx);

}
