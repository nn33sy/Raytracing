/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <how-choongines@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:43 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/03 19:21:18 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		ft_bmpheader(t_bmpheader *header, t_vars *vars)
{
	double	size;

	size = vars->scene->r_x * vars->scene->r_y * 3;
	header->signaturebytes[0] = 'B';
	header->signaturebytes[1] = 'M';
	header->sizeOfBitmapFile = SIZE_HEADER + size;
	header->reservedBytes = 0;
	header->pixelDataOffset = SIZE_HEADER;
}

static void		ft_bmpinfoheader(t_bmpinfoheader *infoheader, t_vars *vars)
{
	infoheader->sizeOfThisHeader = SIZE_INFO_HEADER;
	infoheader->width = vars->scene->r_x;
	infoheader->height = vars->scene->r_y;
	infoheader->numberOfColorPlanes = 1;
	infoheader->colorDepth = 24;
	infoheader->compressionMethod = 0;
	infoheader->rawBitmapDataSize = 0;
	infoheader->horizontalResolution = 3780;
	infoheader->verticalResolution = 3780;
	infoheader->colorTableEntries = 0;
	infoheader->importantColors = 0;
}

static void		ft_write_header(int fd, t_vars *vars)
{
	t_bmpheader		header_one;
	t_bmpinfoheader	header_two;

	ft_bmpheader(&header_one, vars);
	ft_bmpinfoheader(&header_two, vars);
	write(fd, &(header_one.signaturebytes), 2);
	write(fd, &(header_one.sizeOfBitmapFile), 4);
	write(fd, &(header_one.reservedBytes), 4);
	write(fd, &(header_one.pixelDataOffset), 4);
	write(fd, &(header_two.sizeOfThisHeader), 4);
	write(fd, &(header_two.width), 4);
	write(fd, &(header_two.height), 4);
	write(fd, &(header_two.numberOfColorPlanes), 2);
	write(fd, &(header_two.colorDepth), 2);
	write(fd, &(header_two.compressionMethod), 4);
	write(fd, &(header_two.rawBitmapDataSize), 4);
	write(fd, &(header_two.horizontalResolution), 4);
	write(fd, &(header_two.verticalResolution), 4);
	write(fd, &(header_two.colorTableEntries), 4);
	write(fd, &(header_two.importantColors), 4);
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
