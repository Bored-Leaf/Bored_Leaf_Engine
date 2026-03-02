# For now
Have this as a notes section when implementing the VulkanRenderer for first time. Basically have it behave same as the existing OpenGL renderer but maybe with some improvements after retrospectives about OpenGL renderer features.
https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/00_Base_code.html

Enable Hot-reloading
- Don't have to re compile engine or game every time a shader change is made.

## When swapping to Vulkan
Don't disgarde the opengl renderer, I will keep it as a failsafe option if the vulkan renderer crashes or failed extensively:
- Have informative log errors if the Vulkan or OpenGL renderer fails
- Increases robustness of engine, engine won't crash if Vulkan renderer crashes
- The OpenGL renderer will be ALL ABOUT a safe renderer that is COMPLETELY about ROBUSTNESS and not performance.

Have developers have the option to make their own fall back renderer.