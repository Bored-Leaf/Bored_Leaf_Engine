# Index
- [[#Key Concepts]]
- [[#Introduction]]
- [[#Engine Goals]]
- [[#Project Structure]]
	- [[#Project Folder structure]]
- [[#Libraries used]]
- [[#How Engine will be used]]
- [[#Systems]]
	- [[#List of Systems]]
	- [[#File structure of each system]]
- [[#Custom Systems Integration]]
	- [[#EngineCore]]
		- [[#Event/Message Bus]]
- [[#Handling 2d and 3d aspects]]
- [[#C++ Rules]]
	- [[#Performance critical code/Areas]]
- [[#Adding features]]
- [[#What warrants a new release build to publish?]]
	- [[#Release numbering format 1.S.F]]
	- [[#!!! - Important - !!!]]
- [[#Development Lifecycle]]
- [[Distribution & External Developer Usage|Distribution & External Developer use]]
- [[#External Documentation]]
	- [[#Doxygen]]
	- [[#Engine architecture D3.js]]
		- [[#Visual aid]]
		- [[#Hovering interaction]]


# Key Concepts
|<span style="font-size:20px;">Key Words</span>| <span style="font-size:20px;">Definition</span>|
|---|---|
|**System** | A modular unit of functionality (E.g. Audio, rendering, physics).|
|**Feature Set** | A set of related features added to the same system in the same release build |
|**EngineCore** | Mediator between systems; controls initialisation, update, shutdown.|
|**Interface (`I*`)** | A pure virtual contract that any custom implementation must inherit and fulfil.|
|**GameTest** | Internal test application that uses the engine and demonstrates functionality.|
|**Performance Critical Code** | Code that is written with readability not in mind. Used for performance sensitive areas.|
|**Game Project**| An external application that will use the engine.|

# Introduction
This is a project making a 2D/3D Game engine in C++, using third party libraries. The game engine will be made along side a 2D game but want the game engine to be used by other developers, without forcing them to make the same genre of game I'm also making, by one of the features of the engine to help with this is systems of the engine being able to be swapped with custom made systems that suits a particular games needs without having to make the whole engine from the ground up. This project will also be the highlight project for my software engineering career, as it is a substantial project that requires a lot of moving parts and involves sophisticated topics and ideas. 

# Engine Goals
The engine must satisfy the following criteria's:
- Performance
	- Out of the box performance. 
- Modularity
	- Allow developers to swap systems for custom implementations that fit their needs, without breaking other systems.
- Robustness
	- Error handling and fault tolerance to minimise crashes and if they happen, provides helpful debugging information. 
	- Consistency and stability so engine behaves consistently across multiple runs, platforms and inputs. Systems interact in predictable and well defined ways.
	- Graceful degradation so engine keeps running in a degraded state when something fails via disabling features or fallback behaviours.
	- Development safety to avoid undefined behaviour via strict contracts. Strong debugging tools and information and test coverage to test systems don't break with new features/changes.

These three core design goals will result in an engine that has solid performance right out of the box without sacrificing safety or customizability for developers to tailor the engine to their needs.

# Project Structure
CMake, each system is a separate project.
There will be two build folders for a MonolithicDLL and a ModularDLL as a sibling folder to **GameEngine**
## Project Folder structure
```
/GameEngine/
├── Engine/
│   ├── EngineCore/
│   ├── InputSystem/
│   ├── WindowSystem/
│   ├── RendererSystem/
│   └── ...
├── GameTest/
├── ThirdParty/
├── Docs/
└── ../ModularDLL/
└── ../MonolithicDLL/
```

# Libraries/Resources used
- SDL3
	- For creating windows and input handling
- Vulkan
	- For rendering
- FMOD Engine/Studio
	- For robust and flexible audio capabilities
- Math
- UI
	- Custom UI Library
- Profiling/Performance monitoring
	- [Tracy Profiler](https://github.com/wolfpld/tracy)
		- Cross-platform Real-time profiler
		- Shows ***where*** bottlenecks are
	- Custom Library using PAPI
		- Display stuff like cache misses, cpu metrics, memory metrics, etc
		- Uses dear Imgui/implot for UI
		- General information not tailored specifically for this project but still well suitable
		- Shows ***why*** bottlenecks are occuring
- Documentation
	- Doxygen

# How Engine will be used
Dynamic Libraries will be compiled for other projects to link against, one dll file for each system. 
GameTest will be a project in the game engine package that serves as a demonstration of how to use the engine and it's systems.

# Systems
When adding a system, BEFORE writing any code, either refer to the /Systems directory about information collected about it  (like what to consider, what other systems need from it, other important information), or if none there then create one.

## List of Systems
Update as more is added/changed

*Link to their individual docs pages in /System directory*

| <span style="font-size:25px;">System</span> | <span style="font-size:25px;">Responsibility</span> | <span style="font-size:25px;">Used by</span> | <span style="font-size:25px;">Depends On</span>
|---|---|---|---|
| **EngineCore** | Mediator between all systems |  | Every System |
|**WindowSystem**| Creates and handles windows | EngineCore |  |
|**InputSystem**| Handles input events | EngineCore | WindowSystem |
|**Renderer**| Handles rendering tasks | EngineCore |  |
|**JobScheduler**| Splits jobs/tasks between threads | Every System | OS |
|**MemoryManager**| Supports JobScheduler and managing memory | Every System | OS |
|**GameDemo**| A gamedemo testing all the system |  | EngineCore |

## File structure of each system
Primary source file and header WILL be named after the system project name for clarity, organisation and consistency.
Primary source file MUST inherit **I*SystemName*.h** to enforce each system contract, this will be the only required interface to inherit for each system. This allows developers to structure their custom implementation of systems however they would like. 

## System Logging
Each system will use a unified logging interface, i.e. ```ILog*``` so debug info can be logged centrally

# Custom Systems Integration
Use pure virtual interfaces that the system MUST USE to be able to work with the engine, as some systems may require data from others and developers making their own system might not provide that data. This way, using static asserts and std::is_base_of like:
``` CPP
static_assert(std::is_base_of<IAudioSystem, T>::value,
	"Audio system MUST inherit from IAudioSystem");
```
Conveys to developers what they did wrong and to check IAudioSystem.h, and maybe eventually the documentation,  for what they have to implement in their custom system. 
This will be called in the GameDemo or GameProject using the dlls before initialising the Engine, e.g.:
``` CPP
int main () {
	EngineCore engine;

	// Register custom implementations
	// RegisterAudioSystem is an overridable function
	// static assert and std::is_base_of goes in here
	engine.RegisterAudioSystem(std::make_unique<FMODAudioSystem>());
	// Any other custom implementations...

	// initialise() uses default fallbacks if no custom implementations
	// are registered, to use the default systems.
	// E.G., if (!audioSystem) {...}, if (!rendererSystem) {...}
	engine.initialise();

	while (engine.IsRunning()) {
		engine.Update();
	}

	engine.shutDown();
	return 0;
}
```

## EngineCore
EngineCore CANNOT be replaced, as it is a core system that EVERY other system relies on and so must behave a certain way.
How to enforce EngineCore not able to be swapped and any other system being able to be swapped for custom implementation:
- EngineCore:
	- Provide only a **concrete class** - no interface class to implement so nobody can swap it, no IEngineCore.h.
- Other Systems:
	- Define **pure virtual interface classes** (e.g. IAudioSystem.h) that custom implementations must inherit and implement.
- Use **compile-time checks** (Like static assert and std::is_base_of seen above) to enforce that custom systems derive from that interface.
This design choice will increase the robustness, stability and contribute to more predictable behaviour.

### Event/Message Bus
(Rewrite when implementing adding it on the github board to do)
A central communication channel owned by EngineCore that allows systems and game code to communicate without direct dependencies on each other.

**How it works:**
- Systems and game code **subscribe** to event types they care about at startup
- When something happens, the relevant code **publishes** an event describing what happened
- The bus delivers that event to all subscribers
- The publisher never knows or cares who is listening

**Lives inside EngineCore** — not a separate system/DLL. It is core infrastructure EngineCore needs to fulfil its mediator role.

**When to use it:**

- Low/medium frequency events where multiple systems need to react to the same thing
- Examples: `EnemyDiedEvent`, `RoomClearedEvent`, `PlayerDamagedEvent`, `ItemPickedUpEvent`

**When NOT to use it:**

- High frequency per-frame per-entity work — use direct API calls or the component system instead
- Examples: bullet raycasts, particle updates, input polling

**Implementation approach:**

- Start simple — subscribers list per event type, publish iterates and calls them
- Only optimise if Tracy identifies it as a bottleneck, which is unlikely given correct usage
- Potential optimisations if ever needed: object pooling for event allocation, batch processing events at a defined point in the frame, JobScheduler for parallel subscriber dispatch

# Handling 2d and 3d aspects
EngineCore will be dimension-agnoistic that handles fundamental tasks that are the same for all game.
Each system, where appropriate, will take advantage of the modular design of the engine and have two versions of their concrete implementations. E.g. Both the IRenderer and IPhysics interfaces will have a 2D concrete implementation and 3D concrete implementation.
The end developers will choose which dimension to use that suits there project with EngineCore's register() functions.

# C++ Rules
***Follow good C++ guidelines and practices where applicable***

- SOLID - Help with maintenance, Extensibility, **Robustness**, and **Modularity**
- C++ Core Guidelines - Help write modern, safe, and **efficient** C++ code

Ultimately tradeoffs may have to be made for performance critical areas or due to complexity 

## Performance critical code/Areas
When writing performance critical code it can be less readable otherwise. If performance critical code is needed write a comment that states the following:
- [PERF - CRITICAL] to identify performance critical code
- Why need performance critical code
- An equivalent, more readable, piece of code to help understand what it does.

# Adding features
*** Only add engine feature when needed for game ***
- Keeps overengineering to a minimum
- Helps prioritise
- Keeps engine focused

# What warrants a new release build to publish?
If a new system has been added or a **set** of features have been added to a system and they are **robust** and **Performant**.

## Release numbering format: 1.S.F
- ```1``` - Major version release: Will always be ```1``` unless the engine undergoes a full rework/rewrite or a ***major*** architectural change has to be made. 
- ```'S'``` - New system release: Number ```'S'``` goes up by one for each **new *system*** implemented and integrated into the engine for official use.
- ```'F'``` - New feature set release: Number ```'M'``` goes up by one for each **new *feature set*** released.

## !!! - Important - !!!
!!! Feature set  ```F``` will not be tied to system ```S```.This avoids going 'backwards' in engine versions when releasing new features sets for older systems !!!


# Development Lifecycle
Will make Final Game with this engine.
When I want a new system or a new feature within an existing system for Final Game, these steps should be followed:
1. Create the new system or new feature within existing system
2. Test and verify the performance and integrity of the new system or feature in GameDemo present in the GameEngine
3. 
	a. If not satisfied then refine feature/system and repeat step 2
	b. Once satisfied with the robustness and performance continue to step 4
4. Build a release version of the dlls, test for optimisation-specific bugs, and automate copying into the Final Game project.
	- Ensures Final Game uses most recent stable release of the engine
	- Copy into same folder as the .exe
5. Use the new release dlls in Final Game Project

# External Documentation

## Doxygen
Will use Doxygen for automated code documentation

## Engine architecture D3.js
[[D3.js|D3.js]] will be used to visually represent the engine Architecture

### Visual aid
Group systems into their own bubble each containing the pages of that system, that way it gives a better insight of what parts of what systems are connected. BUT BUT BUT, still show that the EngineCore is the mediator of all connections between systems to show the architect of the system. Can say something like *All inter-system communication is routed through EngineCore to enforce modular boundaries and prevent tight coupling* or *Systems never directly depend on each other. All data communication and coordination is routed through EngineCore for decoupling and easier testing/replacement* at the top of the graph map or just somewhere and make it very noticeable.

### Hovering interaction
Have a hovering interaction that:

1. Highlights the path from a node -> EngineCore
2. Highlights paths going from EngineCore -> any other node that uses that data
3. Clicking on that connection will toggle it on and off so they can follow where the connections go
4. Makes the flow of indirect independencies (via EngineCore) immediately visible

This lets developers understand the whole data/control flow at a glance, without guessing or exploring blindly.

## On each api page
Have a view/window that shows the class the api is on and all its immediate connections.
