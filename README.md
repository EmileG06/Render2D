# Render2D
*A modern OpenGL 2D renderer written in C++ (2023)*

Render2D is an object-oriented 2D rendering framework built with **C++ (2023 standard)** and **OpenGL 4.6 Core Profile**, designed to be modular, extensible, and easy to experiment with.  
The project is split into a reusable rendering library and a sandbox application that demonstrates its usage.

---

## Key Goals

- Modern **C++ OOP design**
- Clean **OpenGL abstraction layer**
- Separation of **engine code** and **application code**
- Easy project generation using **Premake5**
- Educational and extensible architecture

---

## Projects

### **Render2D** (Static Library)

The core rendering engine that provides:

- Rendering API
- Scene & layer management
- Event handling
- Camera systems
- OpenGL abstractions

This library is intended to be reused by multiple applications.

---

### **Sandbox** (Console Application)

An example application that uses the **Render2D** library.

- Demonstrates engine usage
- Contains app-specific logic
- Renders a **rotating blue cube**
- Uses an **orthographic camera**

---

## Features

### Layer System
- Stack-based layer architecture
- Enables modular scene logic

### Event System
- Keyboard, mouse, and window events
- Event dispatching with propagation control

### OpenGL Abstraction
Encapsulated OpenGL objects for cleaner and safer usage:

- Shaders
- Vertex Arrays (VAO)
- Vertex Buffers (VBO)
- Element Buffers (EBO)
- Textures

### Camera System
- **Orthographic Camera** (used in Sandbox)
- **Perspective Camera**
- Camera movement, rotation, and zoom support

---

## Sandbox Controls

| Input | Action |
|------|-------|
| **W / A / S / D** | Move camera |
| **Q / E** | Rotate camera left / right |
| **Mouse Scroll** | Zoom in / out |

---

## Build Instructions

### Requirements
- **VS2022**
- **Premake5**

---

## Generate Project Files

From the root directory:

```bash
premake5 vs2022
```

(Replace vs2022 with your preferred build system)
Then open the generated solution and build.

---

## Design Philosophy

- Object-oriented architecture
- Clear responsibility separation
- Minimal engine-to-application coupling
- Readable and maintainable code
- Easy to extend with new renderers, layers, or systems

---

## Notes

- This project is intended for learning, experimentation, and as a foundation for more advanced rendering systems.
- While named Render2D, the architecture allows for easy expansion into 3D rendering.

---

## License

This project is provided as-is for educational purposes.
Feel free to modify, extend, and experiment.
