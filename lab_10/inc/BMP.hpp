#pragma once
#include <string>
#include <fstream>
#include <mathlib/matrix.hpp>

using vk::math::Matrix_2x1_d;
using vk::math::Matrix_2x2_d;

namespace vk::images
{
	#pragma pack(1)
	struct Pixel
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
	};
	#pragma pack()

	class BMP
	{
	public:
		
        BMP();

        BMP(int width, int height);
            
        BMP(const BMP& bmp);

        BMP& operator=(const BMP& bmp);

        ~BMP(); 

        void Fill(Pixel pixel);

        void Brightness();

        void Open(const std::string& filename);

        void Save(const std::string& filename);

        void Rotate(double angle);

        void Interpolation();

	private:
		int inclass_width, inclass_height;
		Pixel** inclass_pixels = nullptr;
        Matrix_2x1_d** inclass_coordinates = nullptr;

	private:
        #pragma pack(1) 
        struct BMPHEADER
        {
            unsigned short    Type;
            unsigned int      Size;
            unsigned short    Reserved1;
            unsigned short    Reserved2;
            unsigned int      OffBits;
        };
        #pragma pack()

        #pragma pack(1)
        struct BMPINFO
        {
            unsigned int    Size;
            int             Width;
            int             Height;
            unsigned short  Planes;
            unsigned short  BitCount;
            unsigned int    Compression;
            unsigned int    SizeImage;
            int             XPelsPerMeter;
            int             YPelsPerMeter;
            unsigned int    ClrUsed;
            unsigned int    ClrImportant;
        };
        #pragma pack()

	};

}