# SDL2FrameWork

A simple framework to simplyfy making basic games/ apps for begginers 

Required Libs SDL2 SDL2_Image and SDL2_imager
Required CPP version at least 17

# Provides:

- UI creation
- Text rendering
- Texture Manager
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