# Personal
## Classes
### Access content heirarchy
In classes have the public contents above the private or protected contents as it is a game engine and developers would like to see the public API which would be in the public contents of a class. The contents in the private space can be considered an implementation details, which is not strictly needed when viewing an API.

### Grouping within access spaces
In member access spaces, group contents as well with ```// -- * -- //```, such as:
``` CPP
class AudioSystem {
public:
	// -- Lifecycle -- //
	void initialise();
	void shutdown();

	// -- Playback -- //
	void playSound();
	void stopSound();
	void stopAll();
};
```

# SOLID

## S - Single Responsibility Principle (SRP)
A class should have one, and only one, reason to change. A class should only have one job or responsibility.

## O - Open/Closed Principle (OCP)
Software entities should be open for extension, but closed for extension. This mean you should be able to add new functionality without altering existing code.

## L - Liskov Substitution Principle (LSP)
Subtypes must be substitutable for their base type without altering correctness of the program. In essence, derived classes should be usable in place of their base classes without causing issues. 

## I - Interface Segregation Principle (ISP)
Clients should not be forced to depend on methods they do not use. Instead of large interface, create smaller, more specific interfaces that cater to the needs of different clients.
Can inherit from multiple virtual interfaces to achieve this, BUT do not inherit from multiple classes.

## D - Dependency Inversion Principle (DIP)
High-level modules should not depend on low-level modules. Both should depend on abstractions. This means relying on interfaces or abstract classes rather than concrete implementations.
To clarify:
- Use interfaces (or abstract base classes) to define *what* something does - the contract
- High-level code depends on those interfaces, not on specific concrete classes
- Concrete classes implement those interfaces and provide the actual details
- Your application then uses those classes that inherit those interfaces
- This way, your high-level code is decoupled from low-level implementation details

# C++ Core Guidelines

More relevant C++ Core Guidelines

## Performance
- Use RAII
	Manage resources via objects with constructors/deconstructors to avoid leaks
- Prefer ```std::vector``` over raw arrays
	Safe, cache friendly, and performant dynamic arrays
- Avoid unnecessary copying
	Use references and move semantics where appropriate
- Minimise dynamic allocations
	Pool allocations or use stack allocations for frequently created objects.
- Pass small objects by value, big ones by const reference.

## Modularity & Design
- Prefer interfaces for polymorphism
	Use pure virtual classes to decouple systems
- Use ```= delete``` to disable unwanted functions (e.g. copying when not allowed)
- Use ```final``` for classes or method you don't want overridden to help compiler optimisations
- Use ```constexpr``` for compile-time constants and functions
	Helps optimisations and clarity
- Use ```enum class``` over plain ```enum```
	Scoped and type safe

## Robustness and Safety
- Avoid raw pointers for ownership
	Use smart pointers or references for clarity
- Prefer ```nullptr``` over ```NULL``` or ```0```
- Use ```auto``` judiciously
	Use it to avoid verbosity but keep code readable
- Check for errors early (asserts, exceptions if appropriate)
	Defensive programming saves debugging time
- Initialise variable on declaration
	Prevents undefined behaviour.

## Style and Readability
- Consistent naming conventions
	camelCase for variable, PascalCase for types
- Avoid using magic numbers (including unlabelled Booleans)
	To maintain readability for other developers as they will know what those numbers are for or what the Booleans are enabling/disabling.
- Limit function length and complexity
	Smaller functions are easier to test and maintain
- Use ranged-based loops when possible
