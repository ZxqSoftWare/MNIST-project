#pragma pack(2)

#ifndef BYTE
typedef unsigned char  BYTE;
#endif
#ifndef WORD
typedef unsigned short WORD;
#endif
#ifndef DWORD
typedef unsigned long  DWORD;
#endif
#ifndef LONG
typedef long    LONG;
#endif

typedef struct {  
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;
  
typedef struct {  
    DWORD      biSize;
    LONG       biWidth;
    LONG       biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG       biXPelsPerMeter;
    LONG       biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant;
} BITMAPINFOHEADER;

typedef struct  
{  
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed; 
    unsigned char rgbReserved; 
} RGBQuad;
