#include <BMP.hpp>

namespace vk::images
{
    BMP::BMP()
    {
        inclass_width = 0;
        inclass_height = 0;
    }

    BMP::BMP(int width, int height)
    {
        inclass_width = width;
        inclass_height = height;

        inclass_pixels = new Pixel * [inclass_height];
        for (int i = 0; i < inclass_height; i++)
            inclass_pixels[i] = new Pixel[inclass_width];

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_pixels[i][j] = { 0,0,0 };
    }

    BMP::BMP(const BMP & bmp)
    {

        if (inclass_pixels != nullptr)
        {
            for (int i = 0; i < inclass_height; i++)
                delete[] inclass_pixels[i];
            delete[] inclass_pixels;
        }

        inclass_width = bmp.inclass_width;
        inclass_height = bmp.inclass_height;

        inclass_pixels = new Pixel * [inclass_height];
        for (int i = 0; i < inclass_height; i++)
            inclass_pixels[i] = new Pixel[inclass_width];

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_pixels[i][j] = bmp.inclass_pixels[i][j];
    }

    BMP& BMP::operator=(const BMP& bmp)
    {
        if (inclass_pixels != nullptr)
        {
            for (int i = 0; i < inclass_height; i++)
                delete[] inclass_pixels[i];
            delete[] inclass_pixels;
        }

        inclass_width = bmp.inclass_width;
        inclass_height = bmp.inclass_height;

        inclass_pixels = new Pixel * [inclass_height];
        for (int i = 0; i < inclass_height; i++)
            inclass_pixels[i] = new Pixel[inclass_width];

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_pixels[i][j] = bmp.inclass_pixels[i][j];

        return *this;
    }

    BMP::~BMP()
    {
        for (int i = 0; i < inclass_height; i++)
            delete[] inclass_pixels[i];
        delete[] inclass_pixels;
    }

    void BMP::Fill(Pixel pixel)
    {
        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_pixels[i][j] = pixel;
    }

    void BMP::Brightness()
    {
        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
            {
                if (inclass_pixels[i][j].b - 50 < 0)
                    inclass_pixels[i][j].b -= 50;
                if (inclass_pixels[i][j].g + 50 < 256)
                    inclass_pixels[i][j].g += 50;
                if (inclass_pixels[i][j].r + 50 < 256)
                    inclass_pixels[i][j].r += 50;
            }
    }

    void BMP::Open(const std::string& filename)
    {

        std::ifstream in(filename, std::ios::binary); 

        BMPHEADER bmpHeader;
        in.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHEADER));

        BMPINFO bmpInfo;
        in.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPINFO));

        if (inclass_pixels != nullptr)
        {
            for (int i = 0; i < inclass_height; i++)
                delete[] inclass_pixels[i];
            delete[] inclass_pixels;
        }

        inclass_width = bmpInfo.Width;
        inclass_height = bmpInfo.Height;

        inclass_pixels = new Pixel * [inclass_height];
        for (int i = 0; i < inclass_height; i++)
            inclass_pixels[i] = new Pixel[inclass_width];

        for (int i = 0; i < bmpInfo.Height; i++)
        {
            for (int j = 0; j < bmpInfo.Width; j++)
                in.read(reinterpret_cast<char*>(&inclass_pixels[i][j]), sizeof(Pixel));

            if ((3 * bmpInfo.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * bmpInfo.Width) % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
        }
    }

    void BMP::Save(const std::string& filename)
    {
        if (inclass_width == 0 || inclass_height == 0)
            throw std::exception("Zero height or width");

        std::ofstream out(filename, std::ios::binary);

        BMPHEADER bmpHeader_new;
        bmpHeader_new.Type = 0x4D42; 
        bmpHeader_new.Size = 14 + 40 + (3 * inclass_width * inclass_height);
        if (inclass_width % 4 != 0)
            bmpHeader_new.Size += (4 - (3 * inclass_width) % 4) * inclass_height;
        bmpHeader_new.OffBits = 54;
        bmpHeader_new.Reserved1 = 0;
        bmpHeader_new.Reserved2 = 0;

        out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

        BMPINFO bmpInfo_new;
        bmpInfo_new.BitCount = 24;
        bmpInfo_new.ClrImportant = 0;
        bmpInfo_new.ClrUsed = 0;
        bmpInfo_new.Compression = 0;
        bmpInfo_new.Height = inclass_height;
        bmpInfo_new.Planes = 1;
        bmpInfo_new.Size = 40;
        bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
        bmpInfo_new.Width = inclass_width;
        bmpInfo_new.XPelsPerMeter = 0;
        bmpInfo_new.YPelsPerMeter = 0;

        out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));

        for (int i = 0; i < bmpInfo_new.Height; i++)
        {
            for (int j = 0; j < bmpInfo_new.Width; j++)
                out.write(reinterpret_cast<char*>(&inclass_pixels[i][j]), sizeof(Pixel));

            if ((3 * bmpInfo_new.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * bmpInfo_new.Width) % 4; j++)
                {
                    char c = 0;
                    out.write(&c, 1);
                }
        }
    }
}