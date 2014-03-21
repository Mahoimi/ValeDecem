ValeDecem
=========

A real-time demo about "An Adventure in Time and Space : Farewell to the Tenth Doctor" in C++/OpenGL created by Thomas Demenat, Aurélie Beauprez and Cécilia Lejeune.

Needed Dependencies
-------------------

This project is made using the following librairies : SFML, AntTweakBar, GLM and GLEW.

While they are directly included in this repository, SFML depends on a few other libraries, so before starting to compile you must have their development files installed :
- pthread
- opengl
- xlib
- xrandr
- freetype
- glew
- jpeg
- sndfile
- openal


Compiling
---------

To compile this project, you must have CMake with a version >= 2.6 and use the following commands in your terminal :
<pre><code>cd {ValeDecem folder}
mkdir build
cd build 
cmake ..
make
cd bin
./ValeDecem</code></pre>

Commands
--------

Our project is a demo, so you can just sit and watch the sequences while enjoying its music.
However, you can also display our Debug mode by pressing the D key.
While in Debug mode, you can :
- interact with the AntTweakBar GUI (Change the objects parameters...)
- select a sequence to play (sequence 0 = pause)
- deplace the camera with the directionnal arrow keys
- rotate the camera with the right mouse button
