# Core-Framework
A game framework with 2D and 3D capabilities 

## Features
- Simple OOP opengl wrapper
- Load, edit and save images
- Create a texture from a image
- display a texture with a sprite
- Transformations
- 2D and 3D Views
- Simple Window
- Compatible with ImGui

## Planned Features
- 2D and 3D shapes like cube, circle, sphere, triangle, etc
- make imgui be optional
- event handling system
- cross platform

## Build
this project uses meson as build system, to build do the following:
        cd ./build
        meson compile
Meson will download all required libraries and compile, then run the example with:
        ./src/example/Example
if everything went well, you will see a white place with an approaching image rotating
