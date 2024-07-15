cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME game)				 # имя проекта		 
project("${PROJECT_NAME}")

SET(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")

set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("inc/")


add_library("${PROJECT_NAME}" SHARED GameForm.cpp GameForm.h GameMap.cpp GameMap.h Gamer.h Gamer.cpp StartForm.cpp StartForm.h)
