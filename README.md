# SDL2FrameWork

A simple framework to simplyfy making basic games/ apps for begginers 

Required Libs SDL2 SDL2_Image and SDL2_imager
Required CPP version at least 17

# Provides:

- UI creation
- Text rendering
- Texture Manager
- Sound Manager
- Scene System
- Collision Detection
- Basic Objects
- Objects to simplyfy 2d grid managment
- PreBuild basic game class and game loop
- Distances Calculation for 2d grid 

# Used Libs
- Niels Lohmann Json library
https://github.com/nlohmann/json


#Changes

1.01
- Interaction box can now be turned on or off
- Interaction box calculation speed optimalization
- Option to choose text rendering type (standard,center or from right)
 - Standard text is rendered from the left side of the button (very fast)
 - Center text is rendered at the center of the button (slowest)
 - Right text is rendered from the right part of the button (fast)
 - Center Predefined text is rendered from the center with a precalcualated dimensions only works correctly with static text (medium)
 
 1.011
 - Small fix for rendering text from right
 
 1.02
 - Warning when name collision is created in ui element addition
 - New Interaction box function that return status and immidetly sets it to true to prevent manual reset
 - A lot of comments for functions
 
 1.03
 - New function to scan font and create json file from scratch
 - Texture manager now no longer can load textures with the same name
 - UI automaticaly loads its required textures
 
 1.04
 - Basic Scene Manager Tests
 - Easier Game Loop
 - Shared Data for Scene Manager
 
 1.05
 - Scene Manager has been finisched and tested
 - UI element can be hidden
 - UI elements can be hooverable
 
 1.06
 - Special pointer type for storing counting and clearing references
 - Redesigned Grid position calculation
 - Better camera position calculation
 - Remove camera from main object
 - Camera Scalling functions
 - Camera borders
 - Silent checks for map pos (without writing to console)
 
 1.07
 - Texture manager can now load all directory and sub
directories with a single function
 - Texture manager now supports all files extensions
 supported by IMG Load from sdl_image 
 - Fixed a bug that did not allow transparent buttons to be hoverable
 - Reference Pointer fixes
 - Buttons now can make sounds
 - Addon function that calculates equal rectangles distibution across screen 
 
 1.08
 - Reading csv files
 - RefPtr improvements
 - Dynamic Scene Management
 - Beter single reference removal in RefPtr
 
 1.09
 - Shared ptr removed from framework it was just an bad and dangerous class
 - IsData function for scene manager to check if shared data with this key even exist
 - Shorter Naming Convertion
 - Better UI element border creation
 
 1.10
 - More readiblility fixes
 - Sound Manager can adjust sound volume
 - New List type ui element ClickBoxList
 - List Improvements
 - Quick Shortcuts functions for vector removal
 - Camera Improvements
 - Better UI names
 - Texture Manager function to split texture
 
 1.11
 - Added basic animator class
 - Better Camera Functions Name
 - 3 more animation types
 - Another 2 more animation types
 - You can now duplicate animation frames
 - Animations are now dynamicly allocated
 - Load Multiple Textures no longer crashes when path is incorrect
 - Load Multiple Sounds no longer crashes when path is incorrect
 
 
 1.12
 - Switched basic texture load function to DeepLoad
 - UI no longer loads its textures and it is now capable of using any texture manager
 - File Explorer Prototype
 - Better file explorer