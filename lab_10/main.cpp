#include <BMP.hpp>
#include <iostream>

int main()
{
    try
    {
        vk::images::BMP original_image(200, 100);
        original_image.Fill({ 0,255,0 });
        original_image.Save("original.bmp");
        original_image.Rotate(2*acos(-1) / 3);
        original_image.Interpolation();
        original_image.Save("rotate.bmp");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}


   