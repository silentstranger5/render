# Software Rasterizer in C

This is a Software Rasterizer written in C with SDL.

## How to build

```sh
git clone https://github.com/silentstranger5/render
cd render
cmake -B build -S .
cmake --build build
```

## About

This rasterizer parses an .obj file, loads it into memory, transforms vertices into screen space, and displays faces of the loaded meshes.
For every fragment within the bounding box of the triangle, a depth value is calculated, and depth buffer is updated.
Based on properties of material, textures and light direction, a fragment color is calculated and placed onto the color buffer.
Simple lit shader is provided. This shader takes a diffuse color or a texture map (if there is one), and scales it's value with the light intensity factor.
The light intensity is calculated as a dot product between the surface normal and directional vector pointing to the light source.
