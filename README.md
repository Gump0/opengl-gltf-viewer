# opengl-gltf-viewer

A lightweight glTF 3D model viewer built with C++17 and OpenGL.

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square)
![OpenGL](https://img.shields.io/badge/OpenGL-3-green?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-orange?style=flat-square)

---

## Features

- Load and render `.gltf` and `.glb` models
- Real-time camera controls (orbit, pan, zoom)
- ImGui-powered UI panel for scene inspection
- Supports meshes, materials, and textures from the glTF spec

---

## Built With

| Library | Purpose |
|---|---|
| [OpenGL](https://www.opengl.org/) | Graphics API |
| [GLFW](https://www.glfw.org/) | Window & input handling |
| [ImGui](https://github.com/ocornut/imgui) | Immediate-mode UI |

> Requires a compiler with **C++17** support.

---

## Getting Started

> ** ENSURE THAT COMPILED PROGRAM HAS ACCESS TO `/models` DIRECTORY **

```bash
# Clone the repo
git clone https://github.com/your-username/opengl-gltf-viewer.git
cd opengl-gltf-viewer

# Build (example with CMake)
mkdir build && cd build
cmake ..
make
```
<br>
    
```bash
# Or run my bash script that compiles and runs the project for you.
# (for Linux)
sudo chmod +x build.sh      # trust me bro
./build.sh
```

Then drop any `.gltf` file (including it's dependencies) into the `/models` directory.
* Examples are included in the `/models` directory. *

---

## Demo

> *Screenshots or GIFs of your demo models here.*

---

## Credits

3D models used for demonstration are credited to their respective artists:

- **Gistold** — [https://sketchfab.com/3d-models/microphone-gxl-066-bafhcteks-5172dbe9281a45f48cee8c15bdfa1831](#)
- **Naman Deep** — [https://sketchfab.com/3d-models/mazda-rx7--wheel-ac11fffbbb504d118d988f5f2dc438f9](#)

---

## License

This project is licensed under the [MIT License](LICENSE).
