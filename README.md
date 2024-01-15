# Primal Engine

## Description
Primal Engine is a videogame engine for 3rd grade subject 'Game Engines' of the videogame design and development grade at UPC CITM.

Our Github Link: https://github.com/Maksym203/PrimalEngine

## Team
Iván Bermúdez Sagra: [IvanBSupc](https://github.com/IvanBSupc)

Maksym Polupan: [Maksym203](https://github.com/Maksym203)
=======
## Engine Description

### Controls

#### Camera
- While Right clicking:
	- WASD: move forward, left, backward and right
	- QE: move up and down
	- Look around
- F: look at target
- Hold Alt:
	- Mouse Hold Left to orbit the game object selected.
- Mouse wheel to zoom in and zoom out.
- Holding SHIFT duplicates movement speed.

### Features

#### Audio System
-  Implement two backgrounds music tracks blend between each other in a loop
-  Static and moving gameobject (automatic or with keys) with spatial audio source

#### Inspector
The user should can use the inspector to modify a GameObject:
- Hierarchy: delete, reparent, create empty and create children
- Transform: translate, rotate and scale Game Objects.
- Mesh: select or drop any imported mesh
- Texture: select or drop any imported texture
- Camera is a component with settings that can be modified.

#### Game Objects
- Drag and drop game objects and textures in the Hierarchy.
- Create game objects with Game Objects Menu
- Delete game objects by pressing Delete at Inspector
- Delete selected game object at Hierarchy by pressing Delete.
- Move Game Objects in Hierarchy by drag and drop them.
- Can be picked from the world using the mouse

#### Frustrum Culling
All meshes use a bounding volume (AABB) and can be discarded using Frustum Culling. User can visualize this in the editor (debug raycast and boxes).

## Engine Description

## Features
* Model creation, delete, import + Drag & Drop
* Inspector (Game object hierarchy, transform with guizmos, mesh, texture, camera)
* Unity-like camera controls
* Editor tools
* Game viewport
* Serialization (Configuration & Scene json files)
* Play/Pause/Stop
* Camera (Component, mouse picking & frustum culling)

## How to use the engine
### Basic camera movement
* Hold Left Shift: Movement speed up.
* Left/Right Arrow: Move left/right.
* Up/Down Arrow: Zoom in/out.
* F: Focus camera around the geometry.

### Flythrough mode
While Right Clicking:
* Free look around.
* A/D: Move left/right.
* W/S: Zoom in/out.
* Q/E: Move up/down.

### Orbit camera
* Left Alt + Left Clicking

### Mouse wheel functions
* Pan movement (Free move in x & y) while clicking the mouse wheel button.
* Zoom in/out with the mouse wheel
=======
#### Additional Comments
We have managed to carry out all the assignments, except Custom file format and Resource Management.
