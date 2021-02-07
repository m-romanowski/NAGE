# NAGE (Not Advanced Game Engine)
OpenGL game engine with Qt based world editor.

## Project components
* __NAGE__: engine (C++) static library
* __QNAGE__: world editor based on QT (C++)

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

## Built with
* [GLX and Xlib](https://www.khronos.org/opengl/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib)
* [OpenGL](https://www.khronos.org/opengl/)
* [glad](https://github.com/Dav1dde/glad)
* [stb](https://github.com/nothings/stb)
* [Qt](https://www.qt.io)
* [cmake](https://cmake.org)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
