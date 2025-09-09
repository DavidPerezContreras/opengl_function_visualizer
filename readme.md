# 📐  C Hello World

A C hello world that causes a buffer overflow to test the runtime checks

---

### 🔧 Debugging with VS Code

The `launch.json` file assumes your executable is named `hello_world.exe`.  
If you change the project name in `CMakeLists.txt`, make sure to update the `"program"` path in `launch.json`:

```cmake
project(example_project)
```

```json
"program": "${workspaceFolder}/build/Debug/example_project.exe"
```