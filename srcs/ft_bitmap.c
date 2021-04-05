/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:43 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/05 12:04:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		ft_bmpheader(t_bmpheader *header, t_vars *vars)
{
	double	size;

	size = vars->scene->r_x * vars->scene->r_y * 3;
	header->signaturebytes[0] = 'B';
	header->signaturebytes[1] = 'M';
	header->sizeofbitmapfile = SIZE_HEADER + size;
	header->reservedbytes = 0;
	header->pixeldataoffset = SIZE_HEADER;
}

static void		ft_bmpinfoheader(t_bmpinfoheader *infoheader, t_vars *vars)
{
	infoheader->sizeofthisheader = SIZE_INFO_HEADER;
	infoheader->width = vars->scene->r_x;
	infoheader->height = vars->scene->r_y;
	infoheader->numberofcolorplanes = 1;
	infoheader->colordepth = 24;
	infoheader->compressionmethod = 0;
	infoheader->rawbitmapdatasize = 0;
	infoheader->horizontalresolution = 3780;
	infoheader->verticalresolution = 3780;
	infoheader->colortableentries = 0;
	infoheader->importantcolors = 0;
}

static void		ft_write_header(int fd, t_vars *vars)
{
	t_bmpheader		header_one;
	t_bmpinfoheader	header_two;

	ft_bmpheader(&header_one, vars);
	ft_bmpinfoheader(&header_two, vars);
	write(fd, &(header_one.signaturebytes), 2);
	write(fd, &(header_one.sizeofbitmapfile), 4);
	write(fd, &(header_one.reservedbytes), 4);
	write(fd, &(header_one.pixeldataoffset), 4);
	write(fd, &(header_two.sizeofthisheader), 4);
	write(fd, &(header_two.width), 4);
	write(fd, &(header_two.height), 4);
	write(fd, &(header_two.numberofcolorplanes), 2);
	write(fd, &(header_two.colordepth), 2);
	write(fd, &(header_two.compressionmethod), 4);
	write(fd, &(header_two.rawbitmapdatasize), 4);
	write(fd, &(header_two.horizontalresolution), 4);
	write(fd, &(header_two.verticalresolution), 4);
	write(fd, &(header_two.colortableentries), 4);
	write(fd, &(header_two.importantcolors), 4);
}

static void		write_bmpdata(t_vars *vars, int fd)
{
	int		x;
	int		y;
	int		*pixel;
	int		i;

	y = vars->scene->r_y - 1;
	while (y > -1)
	{
		x = 0;
		while (x < vars->scene->r_y)
		{
			i = (x + vars->scene->r_y * y) * PIXEL_LEN;
			pixel = (int *)(vars->img.addr + i);
			if (write(fd, pixel, RGB_LEN) < 0)
				exit(EXIT_FAILURE);
			x++;
		}
		y--;
	}
}

void			ft_export_bmp(char *filename, t_vars *vars)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	ft_write_header(fd, vars);
	write_bmpdata(vars, fd);
	close(fd);
}
