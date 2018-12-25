# RG_Seminar - DExplorer

RG seminar - Presentation and how to use.

This project is a part of a seminar in the computer graphics class in my college (UL FRI).

The project is being made in a group with another student (see colaborators) with whom I built together this project.

It is written in the C++ language with the OpenGL library. For easier to write code we used
GLAD (https://github.com/dav1dde/glad-web) for accessing the OpenGL functionalities. 
Window creation and event listening was handled by the GLFW library ( https://www.glfw.org/ ).

------------------------------------------------------------------------------------------------------------------------------

**The engine:**

The engine  ( Named DEngine ) was written for the purpuse of this project. The engine itself is very basic and only includes the
very basic functionality of an engine. It uses OpenGL 3.3 the virst version of modern OpenGL. Every class and its methods are
wrapped in the namespace DEngine.

The first object that must be initialised and have its method call is the Ignition object. From the object you call the start() 
method which initialises glfw, and OpenGL (through GLAD). it also creates a window pointer and stores it within itself. 
To access the pointer further in the program, you should call the method Ignition::getWindow().

A class for shader compilation is also included into the engine. As of right now the engine only supports the compilation and
linking of the vertex and fragment shader. Future updates may include further shaders. The shader compilation is done with the
method ShadersComp::compileShaders(std::string, std::string). The method requiers the paths to the vertex and fragment shaders
respectively. To link the two you simply call ShaderComp::linkShaders() method

Basic input handling is managed with the InputManager class. Every keypress sensed with a callback created by GLFW is inserted into
an unordered map with key values being the key IDs and values being type bool. The class is able to recognise if the key is being
pressed or held down. It can also manage the cursor movement, it's position and it's previous position. This comes in handy with
camera control that needs to have an "FPS" style of movement.

For error handling the ErrorMsg::message function was made. Though this function will not exit the program safely. It will simply 
print an error to your console and wait for user input. The method is here for debugging purpuses only and not made for proper 
error handling that GLFW or GLAD can produce. 

DProps are the global variables of DEngine. Here are stored the basic variables determening things, that are used in many other
places. Such as window widht and height, mouse senistivity, camera fov, begin,end and delta time (used for balancing the speed
of moving objects per render cycle)

Vertex binding to the GPU memory is handled by the Binder class. Binder accepts an std::vector<float> of vertecies. Each vertex,
is made of 5 floats. first three are the position of the vertex, the last two are the texture coordinates the bound object might
use. These objects are stored into an unordered map, that uses a string describing the object as a key (passed in the ::setBinder
method ) and can be accessed with Binder::getBinder(std::string) method. The class can also store the bindings of textures. 
As before the binds are stored in an unordered map, but this time the value of the map is another class in the engine called
Texture loader.

Texture loader, as the name suggests, loads the inputed pictures and binds them to the GPU. For image loading the stb_image header 
library is used ( https://github.com/nothings/stb ). The engine is capable of succesfully loading .jpg and .png images. Any other
images will not be bound since it relies on these two file endings to successfuly bind them.

The Camera class stores a projection and view matrix for further drawing. Its update method also makes sure that the position
of the camera is always relevant to its position.

-------------------------------------------------------------------------------------------------------------------------------

