# COMP371-A1

Controls:
Right click + move cursor along x-axis = pan
Middle click + move cursor along y-axis = tilt
Left click + move cursor along y-axis = zoom
Direction arrows = "fly" around

P = Render models as points
L = Render models as lines
T = Render models as filled triangles

Keys 1-5 = select a model
W = move selected model up
A = move selected model left
S = move selected model down
D = move selected model right
U = scale selected model up
J = scale selected model down
Q = rotate selected model left
E = rotate selected model right

B = rotate world +x axis (anticlockwise)
M = rotate world -x axis (anticlockwise)
N = rotate world down around y-axis
H = rotate world up around y-axis
SPACE KEY = reset world rotation

Escape key = exit the application


## Build Instructions

### Command Line

1. Download and Install CMake
2. Open a terminal
3. Run cmake:

```
cd <source_folder>
cmake -S . -B <build_folder>
cmake --build <build_folder> --target install
```

To generate an Xcode project from the command line use:

```
cd <source_folder>
cmake -S . -B <build_folder> -G Xcode
cmake --build <build_folder> --target install
```


**NOTE:** In the case of cmake the `<source_folder>` is the topmost folder with
a CMakeLists.txt file.

**NOTE:** The `<build_folder>` can be anything but is usually just named `build`.


### CMake GUI

You can use the CMake GUI to configure and generate the Visual Studio Project.

1. Download and Install CMake
2. Open the CMake GUI
3. Set the `Where is the source code:` field to the source folder
4. Set the `Where to build the binaries:` field to different location (e.g.: source_folder/build)
5. Click Configure
6. Select the project generator (this will be the project file that compiles program)
7. Click Generate

#### Windows

Once the project is created you can build the **ALL_BUILD** project followed by
building the **INSTALL** project.

#### Xcode

Once the project is created you can build the **ALL_BUILD** target followed by
the **INSTALL** target. 

#### Unix Make File

In the terminal:

```
cd <build_folder>
make install
```


## Running

Once built and installed, all the relevant files will be in the **dist** folder
at the top level of the source folder.

### Linux/macOS

In the terminal type:

```
./lab03
```

### Windows

Click on the **lab03.exe** from the File Explorer.

## References

Good place to learn OpenGL
https://www.learnopengl.com

Official OpenGL 4 Reference Documentation
https://www.khronos.org/registry/OpenGL-Refpages/gl4/

Official OpenGL Wiki
https://www.khronos.org/opengl/wiki/

Easy to Navigate OpenGL Function Documentation
http://docs.gl/

GLM Documentation
https://glm.g-truc.net/0.9.9/index.html

GLFW Documentation
https://www.glfw.org/

Good place for advanced graphics theory
https://www.scratchapixel.com/

