EngineCore is responsible for all communication between the different systems of the Engine. This was chosen to have a more centralised control flow, reduce coupling and to increase maintainability and to help modularity. To further increase modularity and give developers more control over per-frame logic, EngineCore will not implement a game loop.

## Different phases:
Engine Core contains an update loop and will be organised into different phases for cleaner code and make it easier to understand:
- Fetching data phase
	- Fetches data from systems to feed into other systems, if only consists of reading system state any not modifying ANYTHING, then a good contender for multi-threading
- Feeding data phase 
	- Feeds the fetched data into other systems
- Update phase
	- Updates all the systems states

## Responsibilities
- Centralises control and communication flow
- Handles fetching data from systems and feeding into other systems

## Used by
- [[WindowSystem|WindowSystem]]
- [[InputSystem|InputSystem]]
- [[OpenGLRenderer|OpenGLRenderer]]

## Depends on
- IWindowSystem
- IInputSystem
- IOpenGLRenderer

## Events
### Events subscribed
### Events published

## Public APIs
