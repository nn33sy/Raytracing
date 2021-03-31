// Header contains meta data (addition information about the data ex width and height of an image)
// Usually the size is of 54 bytes here it will be of 54 bits

//First HEADER tells that this binary file is a bitmap file (14 bytes)
//'B' 'M' (2bytes)
//size of bitmap file in bytes = sum of size of meta data (14 + 40) + nb of pixel
// Size of offset here it is 54 bites



//Second header contains addition meta data


//Body contains actual data. Information about each pixel in the image
//Each pixel consist of 3 color RGB where each is of 1 byte

# define RGB_LEN 3
# define PIXEL_LEN 4
#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include "image.h"
# define SIZE_FILE_HEADER 14
# define SIZE_INFO_HEADER 40
# define SIZE_HEADER 54

typedef struct s_BmpHeader
{
    char signaturebytes[2];
    unsigned int sizeOfBitmapFile;
    unsigned int reservedBytes;
    unsigned int pixelDataOffset;
}   t_BmpHeader;

typedef  struct s_bmpInfoHeader{
    unsigned int sizeOfThisHeader;
    unsigned int width;
    unsigned int height;
    unsigned short numberOfColorPlanes;
    unsigned short colorDepth;
    unsigned int compressionMethod;
    unsigned int rawBitmapDataSize;
    unsigned int horizontalResolution;
    unsigned int verticalResolution;
    unsigned int colorTableEntries;
    unsigned int importantColors;
}t_bmpInfoHeader;

static void ft_bmpHeader(t_BmpHeader *header, t_vars *vars)
{
    double  size;

    size = vars->scene->r_x * vars->scene->r_y * 3;
    header->signaturebytes[0] = 'B';
    header->signaturebytes[1] = 'M';
    header->sizeOfBitmapFile = SIZE_HEADER + size;
    header->reservedBytes = 0;
    header->pixelDataOffset = SIZE_HEADER;

}

static void ft_bmpInfoHeader(t_bmpInfoHeader *infoHeader, t_vars *vars)
{
    infoHeader->sizeOfThisHeader = SIZE_INFO_HEADER;
    infoHeader->width = vars->scene->r_x;
    infoHeader->height = vars->scene->r_y;
    infoHeader->numberOfColorPlanes = 1;
    infoHeader->colorDepth = 24;
    infoHeader->compressionMethod = 0;
    infoHeader->rawBitmapDataSize = 0;
    infoHeader->horizontalResolution = 3780;
    infoHeader->verticalResolution = 3780;
    infoHeader->colorTableEntries = 0;
    infoHeader->importantColors = 0;
}

static void ft_write_header(int fd, t_vars *vars)
{
    t_BmpHeader     header_one;
    t_bmpInfoHeader header_two;

    ft_bmpHeader(&header_one, vars);
    ft_bmpInfoHeader(&header_two, vars);
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
     write(fd, &(header_two.rawBitmapDataSize),4);
   write(fd, &(header_two.horizontalResolution), 4);
   write(fd, &(header_two.verticalResolution), 4);
   write(fd, &(header_two.colorTableEntries), 4);
   write(fd, &(header_two.importantColors), 4);

}

static void	write_bmpdata(t_vars *vars, int fd)
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



void	ft_export_bmp(char *filename, t_vars *vars)
{
	int				fd;

   fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    ft_write_header(fd, vars);
	write_bmpdata(vars, fd);
	close(fd);
}
