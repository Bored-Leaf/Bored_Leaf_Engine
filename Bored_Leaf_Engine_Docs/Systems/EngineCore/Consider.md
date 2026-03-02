Having a helper class that contains the registration functions instead of inside EngineCore.cpp. Make it so only EngineCore.cpp can call these functions.
Don't have EngineCore choose the systems to register, let Game Project choose what systems to register.
- Allows Game Project/developers to choose the default system or a custom system.