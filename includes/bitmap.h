#ifndef BITMAP_H
# define BITMAP_H
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

typedef struct s_bmpheader
{
    char signaturebytes[2];
    unsigned int sizeOfBitmapFile;
    unsigned int reservedBytes;
    unsigned int pixelDataOffset;
}   t_bmpheader;

typedef  struct s_bmpinfoheader{
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
}t_bmpinfoheader;
#endif