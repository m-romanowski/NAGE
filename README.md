# NAGE (Not Advanced Game Engine)
OpenGL game engine with Qt based world editor.

## Features
- Base __OpenGL__ rendering pipeline
- Low level X11 window management
- LOD systems: [CDLOD](https://github.com/fstrugar/CDLOD/blob/master/cdlod_paper_latest.pdf), [Geometry climapping](https://hhoppe.com/geomclipmap.pdf)
- Atmosphere scattering: [Nishita](http://nishitalab.org/user/nis/cdrom/sig93_nis.pdf) and proprietary solution
- __QNAGE__ editor as an engine UI integration example and resources management solution

For more details and benchmarks, see `docs` directory.

## Project components
* __NAGE__: engine (C++) static library - `src/engine` module
* __QNAGE__: world editor based on QT (C++) - `src/editor` module

## Requirements
To build this project you must have Unix like platform (Windows and IOS window system support 
in preparation).

Other requirements:
- cmake _>= 3.1.0_
- libstdc++ _>= 9.1, c++17 support is required_
- Qt _> 5.0_
- OpenGL _> 3.0_
- X11

Other libraries (e.g. stb, glad) are provided with this project.

## Build

You can build project using cmake
```
cmake .
make -j <available processors>
```

or using provided shell script
```
ROOT_DIR/scripts/build.sh
```

## Examples and demos

You can run 5 sample demos:

* __DEMO_1__ : Geoclipmapping terrain
* __DEMO_2__ : CDLOD terrain
* __DEMO_3__ : Day-night skydome
* __DEMO_4__ : Atmosphere scattering
* __DEMO_5__ : Geoclipmapping terrain, CDLOD water and atmosphere scatering

There are provided some keyboard and mouse mappings for demos:

* __Single click of `Left Ctrl and then Mouse movement`__ - mouse cursor capture and camera movement
* __Single click of `Left Ctrl and then O or P`__ - change of time of day for 'Day-night skydome' (__DEMO_3__)
* __Single click of `Left Ctrl and then K or L`__ - change of time of day for 'Atmosphere scattering' (__DEMO_4__)

To build project with chosen demo you need pass additional paramater `-DDEMO=<DEMO>` to `cmake` command or using provided build script `ROOT_DIR/scripts/build.sh <DEMO>`, where `<DEMO>` is one of demo name from the above list.

Go to `ROOT_DIR/src/game` directory if you need more informations about demos implementation.

## Built with
* [GLX and Xlib](https://www.khronos.org/opengl/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib)
* [OpenGL](https://www.khronos.org/opengl/)
* [glad](https://github.com/Dav1dde/glad)
* [stb](https://github.com/nothings/stb)
* [Qt](https://www.qt.io)
* [cmake](https://cmake.org)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
