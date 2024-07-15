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

        inclass_coordinates = new Matrix_2x1_d * [inclass_height];
        for (int i = 0; i < inclass_height; i++)
            inclass_coordinates[i] = new Matrix_2x1_d[inclass_width];
                
        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_pixels[i][j] = { 0,0,0 };

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
            {
                inclass_coordinates[i][j].set(0, 0, j);
                inclass_coordinates[i][j].set(1, 0, i);
            }


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

        for (int i = 0; i < inclass_height; i++)
            delete[] inclass_coordinates[i];
        delete[] inclass_coordinates;


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

    void BMP::Rotate(double angle)
    {   
        Matrix_2x1_d T({ {
            {(double)(inclass_width / 2)},
            {(double)(inclass_height / 2)}
        } });

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_coordinates[i][j] = inclass_coordinates[i][j] - T;

        Matrix_2x2_d R({ {
            {cos(angle), sin(angle)},
            {-sin(angle), cos(angle)}
        } });

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
            {
                inclass_coordinates[i][j] = R * inclass_coordinates[i][j];
            }
      
        int maxX = INT_MIN;
        int minX = INT_MAX;
        int maxY = INT_MIN;
        int minY = INT_MAX;

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
            {
                if (maxX < inclass_coordinates[i][j].get(0, 0))
                    maxX = inclass_coordinates[i][j].get(0, 0);
                if (minX > inclass_coordinates[i][j].get(0, 0))
                    minX = inclass_coordinates[i][j].get(0, 0);
                if (maxY < inclass_coordinates[i][j].get(1, 0))
                    maxY = inclass_coordinates[i][j].get(1, 0);
                if (minY > inclass_coordinates[i][j].get(1, 0))
                    minY = inclass_coordinates[i][j].get(1, 0);
            }
  
        maxX++;
        minX--;
        maxY++;
        minY--;

        int width = maxX - minX;
        int height = maxY - minY;

             
        Matrix_2x1_d shift({ {
            {(double)(width / 2)},
            {(double)(height / 2)}
        } });

        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
                inclass_coordinates[i][j] = inclass_coordinates[i][j] + shift;

        Pixel** new_pixels = new Pixel * [height];
        for (int i = 0; i < height; i++)
            new_pixels[i] = new Pixel[width];

        Matrix_2x1_d** new_coordinates = new Matrix_2x1_d * [height];
        for (int i = 0; i < height; i++)
            new_coordinates[i] = new Matrix_2x1_d[width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                new_pixels[i][j] = { 0,0,0 };

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                new_coordinates[i][j].set(0, 0, j);
                new_coordinates[i][j].set(0, 0, i);
            }
 
        for (int i = 0; i < inclass_height; i++)
            for (int j = 0; j < inclass_width; j++)
            {
                int x = (int)(inclass_coordinates[i][j].get(0, 0));
                int y = (int)(inclass_coordinates[i][j].get(1, 0));
                new_pixels[y][x] = inclass_pixels[i][j];
            }
   
        for (int i = 0; i < inclass_height; i++)
            delete[] inclass_pixels[i];
        delete[] inclass_pixels;

        for (int i = 0; i < inclass_height; i++)
            delete[] inclass_coordinates[i];
        delete[] inclass_coordinates;

        inclass_pixels = new_pixels;
        inclass_coordinates = new_coordinates;

        inclass_width = width;
        inclass_height = height;

    }


    void BMP::Interpolation()
    {
       int score = 0;

       for (int i = 1; i < inclass_height-1; i++)
           for (int j = 1; j < inclass_width-1; j++)
           {
               if ((inclass_pixels[i][j].b == 0) &&  (inclass_pixels[i][j].g == 0)  && (inclass_pixels[i][j].r == 0))
               {
                   score = 0;
                   if ((inclass_pixels[i - 1][j].b + inclass_pixels[i - 1][j].g + inclass_pixels[i - 1][j].r) != 0)
                       score += 1;

                   if ((inclass_pixels[i + 1][j].b + inclass_pixels[i + 1][j].g + inclass_pixels[i + 1][j].r) != 0)
                       score += 1;

                   if ((inclass_pixels[i][j-1].b + inclass_pixels[i][j-1].g + inclass_pixels[i][j-1].r) != 0)
                       score += 1;
                       
                   if ((inclass_pixels[i][j + 1].b + inclass_pixels[i][j + 1].g + inclass_pixels[i][j + 1].r) != 0)
                       score += 1;
                       

                   else
                       continue;
                   
                   inclass_pixels[i][j].r = (inclass_pixels[i + 1][j].r + inclass_pixels[i][j + 1].r + inclass_pixels[i - 1][j].r + inclass_pixels[i][j - 1].r) / score;
                   inclass_pixels[i][j].b = (inclass_pixels[i + 1][j].b + inclass_pixels[i][j + 1].b + inclass_pixels[i - 1][j].b + inclass_pixels[i][j - 1].b) / score;
                   inclass_pixels[i][j].g = (inclass_pixels[i + 1][j].g + inclass_pixels[i][j + 1].g + inclass_pixels[i - 1][j].g + inclass_pixels[i][j - 1].g) / score;     
                   
               }
           }
    }
}