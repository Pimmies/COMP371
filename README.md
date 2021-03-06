# COMP371-A1

## Contributors
Camil Bouzidi - 40099611 <br />
Charles Abou Haidar - 40024373<br />
Claudia Guerreiro - 26951929<br />
Julie Pierrisnard 40077165<br />
Ningyuan Sun 40124859<br />

## Controls:
Right click + move cursor along x-axis = pan<br />
Middle click + move cursor along y-axis = tilt<br />
Left click + move cursor along y-axis = zoom<br />
Direction arrows = "fly" around<br />

P = Render models as points<br />
L = Render models as lines<br />
T = Render models as filled triangles<br />

Keys 1-5 = select a model<br />
W = move selected model up<br />
A = move selected model left<br />
S = move selected model down<br />
D = move selected model right<br />
U = scale selected model up<br />
J = scale selected model down<br />
Q = rotate selected model left<br />
E = rotate selected model right<br />

B = rotate world +x axis (anticlockwise)<br />
M = rotate world -x axis (anticlockwise)<br />
N = rotate world down around y-axis<br />
H = rotate world up around y-axis<br />
SPACE KEY = reset world rotation<br />

Escape key = exit the application<br />


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
./a1
```

### Windows

Click on the **a1.exe** from the File Explorer.

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

