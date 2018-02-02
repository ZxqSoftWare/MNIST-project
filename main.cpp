#include <iostream>
#include <cstdlib>
#include "utils.h"

int ReverseInt(int i)   
{  
    unsigned char ch1, ch2, ch3, ch4;  
    ch1 = i & 255;  
    ch2 = (i >> 8) & 255;  
    ch3 = (i >> 16) & 255;  
    ch4 = (i >> 24) & 255;  
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;  
}  

int main(int argc, char *argv[])
{
	char* filename="C:/workspace/train-images-idx3-ubyte";
	char* filename_label="C:/workspace/train-labels-idx1-ubyte";
	char* file_out_dir="C:/workspace/img_train/";
	
	FILE* file;
	FILE* file_label;
	FILE* file_out;
	BYTE** pixel;
	int magic_num, img_num, img_height, img_width, magic_num_label;
	BYTE t_label;
	BITMAPINFOHEADER bitmapInfo={
		0
	};
	BITMAPFILEHEADER bitmapHead;
	RGBQuad bitmap_sqrd[256];
	
	file=fopen(filename, "rb");
	if(file==0) return 0;
	file_label=fopen(filename_label,"rb");
	if(file_label==0) return 0;
	std::cout<<"Open Train-images Successfully"<<std::endl;
	fread(&magic_num,4,1,file);
	fread(&magic_num_label,4,1,file_label);
	magic_num=ReverseInt(magic_num);
	magic_num_label=ReverseInt(magic_num_label);
	std::cout<<"The magic number of image "<<magic_num
		<<" and label "<<magic_num_label<<std::endl;
	fread(&img_num,4,1,file);
	img_num=ReverseInt(img_num);
	std::cout<<"It contains "<<img_num<<" images."<<std::endl;
	fread(&img_width,4,1,file);
	img_width=ReverseInt(img_width);
	std::cout<<"Each image's width "<<img_width<<", ";
	fread(&img_height,4,1,file);
	img_height=ReverseInt(img_height);
	std::cout<<"height "<<img_height<<"."<<std::endl;
	fseek(file_label,8,SEEK_SET);
	
	bitmapHead.bfType=0x4d42;
	bitmapHead.bfReserved1=0;
	bitmapHead.bfReserved2=0;
	bitmapHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQuad)*256+img_width*img_height;
	bitmapHead.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQuad)*256;
	
	bitmapInfo.biSize=sizeof(BITMAPINFOHEADER);
	bitmapInfo.biHeight=-img_height;
	bitmapInfo.biWidth=img_width;
	bitmapInfo.biPlanes=1;
	bitmapInfo.biBitCount=8;
	bitmapInfo.biSizeImage=img_width*img_height;
	bitmapInfo.biCompression=0;
	bitmapInfo.biXPelsPerMeter=0;
	bitmapInfo.biYPelsPerMeter=0;
	bitmapInfo.biClrUsed=0;
	bitmapInfo.biClrImportant=0;
	
	std::cout<<"okay1";
	
	pixel=new BYTE *[img_width]; 
	for(int i=0;i<img_width;i++) 
		pixel[i]=new BYTE[img_height];
	for(int i=0;i<256;i++){
		bitmap_sqrd[i].rgbRed=(BYTE)i;
		bitmap_sqrd[i].rgbGreen=(BYTE)i;
		bitmap_sqrd[i].rgbBlue=(BYTE)i;
		bitmap_sqrd[i].rgbReserved=0x00;
	}
	
	std::cout<<"okay2";
	
	for(int i=0;i<img_num;i++){
		char file_out_name[50], file_index[10];
		fread(&t_label,1,1,file_label);
		strcpy(file_out_name,file_out_dir);
		sprintf(file_index,"index_%d-%d",i,t_label);
		std::cout<<"current index:"<<i<<" label is"<<file_index<<std::endl;
		strcat(file_out_name,file_index);
		strcat(file_out_name,".bmp");
		file_out=fopen(file_out_name,"wb"); 
		if(file_out==0) return 0;
		fwrite(&bitmapHead,sizeof(BITMAPFILEHEADER),1,file_out);
		fwrite(&bitmapInfo,sizeof(BITMAPINFOHEADER),1,file_out);
		fwrite(&bitmap_sqrd,sizeof(RGBQuad)*256,1,file_out);
		for(int j=0;j<img_width;j++){
			fread(pixel[j],1,img_height,file);
			fwrite(pixel[j],img_height,1,file_out);
		}
		fclose(file_out);
	}
	
	fclose(file_label);
	fclose(file);
	
	std::cout<<"done!"<<std::endl;
	
	return 0;
}
