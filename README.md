## Introduction

В данном проекте реализованна на языке программирования Си программа для просмотра 3D моделей в каркасном виде (3D Viewer). Сами модели необходимо загружать из файлов формата .obj. Имеется отрисовка на Qt6, OpenGL с возможностью вращения, масштабирования и перемещения.

[run.webm](https://user-images.githubusercontent.com/56389088/222218202-2df6991d-07c4-4fb2-af2b-67bd05a48ee3.webm)

### Для запуска требуется:

- make
- cmake
- gcc
- qt6-base-dev
- build-essential 
- libgl1-mesa-dev

```
sudo apt install -y git
sudo apt install -y cmake
sudo apt install -y gcc
sudo apt install -y qt6-base-dev
sudo apt install -y build-essential libgl1-mesa-dev
```

### Build:
```
cd src && make install
