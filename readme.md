# 🧭 OpenGL Function Visualizer

This project is a real-time OpenGL-based visualizer for mathematical functions written in C++. It renders a 2D graph of any function you define, using GLFW, GLAD, and GLM for graphics and input handling.

### ✨ Features

- Visualize any single-variable function `f(x)` in real time
- Modify the function directly in code 
- Uses modern OpenGL (core profile) with shader support
- Clean separation between rendering and function logic
- Bundling script included for easy distribution

---

### 🚀 Getting Started



I already included a compiled and bundled version ready for distribution in the dist/ folder with the function f(x)=x as an example 
```PS1
.\dist\hello_world.exe
```

#### Prerequisites

- CMake
- vcpkg (for dependency management)
- Visual Studio or any C++17-compatible compiler



#### Dependencies (via vcpkg)

- `glfw3`
- `glad`
- `glm`

Make sure these are listed in your `vcpkg.json` and installed via:
```bash
vcpkg install
```

---

### 🧪 How to Run

It's a bit tricky to compile since you need the Visual Studio C++ workload, cmake, and vcpkg...
I used VSCode as an IDE.

When installing Visual Studio, make sure to select:

✔️ Desktop development with C++

This workload includes:

    MSVC compiler

    CMake integration

    Windows SDK

    Debugging tools

    Standard C++ libraries

Without this workload, Visual Studio won’t be able to compile C++ code or run CMake-based projects properly.

ADD your vcpkg folder and C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin to your PATH environment variable


Build the project in Release mode:
```bash
cmake --build build --config Release
```

---

### 🧠 Modifying the Function in Code

To change the function being visualized, edit the lambda inside `main.cpp`:
```cpp
// Define the function to visualize
Function myFunction = [](float x) { return x; // Try changing this! 
};
```

You can replace `return x;` with any valid C++ expression, such as:
```cpp
return sin(2.0f * x);
return x * x - 0.5f;
return exp(-x * x) * cos(10.0f * x);
```

Make sure to rebuild the project after making changes.

---

### 📦 Bundling

Use the included `bundle.ps1` script to build and package the app:
```powershell
.\bundle.ps1
```

This will:
- Build the project in Release mode
- Copy required DLLs
- Copy shader files
- Create a `dist/` folder with everything ready to distribute

---