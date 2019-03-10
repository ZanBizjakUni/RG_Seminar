# RG_Seminar - DExplorer

RG seminar - Presentation and how to use.

This project is a part of a seminar in the computer graphics class at my college (UL FRI).

The project is being made in a group with another student (@ziga-solar) with whom I built together this project.

It is written in the C++ language with the OpenGL library. For easier to write code we used
GLAD (https://github.com/dav1dde/glad-web) for accessing the OpenGL functionalities. 
Window creation and event listening was handled by the GLFW library ( https://www.glfw.org/ ).

--Most of the readme will be moved over to the Wiki at some point in time--

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

Collision manager is a simple method only class, that informs the user whether two objects are colliding. The manager is capable
of AABB v AABB collision, AABB v Sphere Collision, 2D version of point v AABB and shpere v sphere collision. The AABBs are
handled and calculated in the Entity (or Player) class. More about the boxes will be written about in the Entity section of the
DExplorer part.


In the future I should add physics to the engine itself. Then Physics handling on multiple Entites will be simpler. As of now, 
the physics and proper collision setbacks are managed in the Player class ( see DExplorer section ). This limits the physics to
only the player and if I would want to implement physics and gravity to other mobs, I would have to duplicate code, which is not
my intention.

------------------------------------------------------------------------------------------------------------------------------


**The Game (DExplorer)**

The game is called DExplorer ( short for Dungeon Explorer ) and in the game itself you do just that! The engine project talked
about above is built into a static c++ library, but the game itself is the executable. The main.cpp file only serves for the 
initialisation and definition of a MainGame object. After that the MainGame::start() method is called from where the whole game
begins to build up. 

*MainGame after start() method*

The MainGame object servers as the objects, that links every part of the game together. It contains the Ignition object, InputManager, and every other core component of the Engine.
  The start method call all other initialising methods responsible for: Shader initialisation, compiling and linking; callback
function initalisation for key handling; Initalisation of the environment. 

*enviromentInit()*

The typo of this function is pending to be fixed. This method has the important role of setting up the binders and loading in
the level. Since this game does not contain model loading (and neither does the engine). The vertices, that are stored in the
binder are set here. This game initialises 4 types of binders. the "square", "skeleton" "cube" and "normalCube" binders. The
square binder is a square-shaped plane with a radius of 0.5 units. The skeleton binder is a 1:0.5 plane that is used for (you
guessed it) skeletons of the game. The unique part of this binder are the UV coordinates saved in the binder. the other
binders have their textures mapped from 0.0, 0.0 to 1.0, 1.0 but in this case it is mapped from 0.0, 0.0 to 0.1, 0.2 . The
purpose is the animation that the skeletons have in the game.
  The next important thing that happens in this method is the loading/initalisation of the level. As of now, the capability of
  choosing between loading from file and loading nothing is not a thing. You have to uncomment a part of the code and comment
  ther other in order to switch between the two (implementation pending). The game reads a level from a binary file.

*gameLoop()*

The last method to be called from the start() method is the gameLoop. The name is pretty self explanatory. The method
contains a loop, that repeats itself until the glfwWindowShouldClose() flag of the window pointer is set. The loop contains
methods to draw and update entites, but the loop acts differently, depending on what state the player is in.

*Player object*

The player object is the object controlled by the user. It's a child class of the Camera class from the engine, since the game
is played in first-person mode, the attributes of the Camera class are very useful to have in the Player class itself. In the 
MainGame object and most others, we contain the pointer to the Player class, since we may change it in many places, having only
a pointer is a very helpful thing.
