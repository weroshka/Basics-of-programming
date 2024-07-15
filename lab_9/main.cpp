#include <BMP.hpp>
#include <iostream>

int main()
{
    try
    {
        vk::images::BMP original_image(1920, 1080);
        original_image.Fill({ 255,100,50 });
        original_image.Save("original.bmp");

        original_image.Brightness();
        original_image.Save("changed_image.bmp");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}


   