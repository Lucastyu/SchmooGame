# Инструкции по сборке Schmoo Game

## Содержание
- [Требования](#требования)
- [Windows](#windows)
- [Linux](#linux)
- [NetBSD](#netbsd)
- [Web-версия](#web-версия)
- [Тесты](#тесты)

## Требования

### Основные требования
- CMake 3.10 или выше
- Компилятор с поддержкой C++17
  - Windows: Visual Studio 2017+ или MinGW-w64
  - Linux: GCC 7+ или Clang 5+
  - NetBSD: GCC 7+
- Git

### Дополнительные требования для веб-версии
- Emscripten SDK
- SDL2

## Windows

### Использование Visual Studio

1. Установите Visual Studio 2017 или новее с компонентами C++
2. Установите CMake (https://cmake.org/download/)
3. Откройте командную строку разработчика:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Использование MinGW-w64

1. Установите MinGW-w64 (https://www.mingw-w64.org/downloads/)
2. Установите CMake
3. В командной строке:
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

## Linux

### Ubuntu/Debian

1. Установите необходимые пакеты:
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git
```

2. Соберите проект:
```bash
mkdir build
cd build
cmake ..
make
```

### Fedora

1. Установите пакеты:
```bash
sudo dnf install gcc-c++ cmake git
```

2. Соберите проект как описано выше

## NetBSD

1. Установите необходимые пакеты:
```bash
pkg_add cmake
pkg_add gcc
```

2. Соберите проект:
```bash
mkdir build
cd build
cmake ..
make
```

## Web-версия

### Установка Emscripten

1. Клонируйте и установите SDK:
```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
```

2. Активируйте окружение:
- Linux/macOS:
```bash
source ./emsdk_env.sh
```
- Windows:
```cmd
emsdk_env.bat
```

### Сборка

```bash
mkdir build-web
cd build-web
emcmake cmake -DBUILD_WEB_VERSION=ON ..
make
```

## Тесты

### Сборка и запуск тестов

```bash
mkdir build-test
cd build-test
cmake -DBUILD_TESTS=ON ..
make
./schmoo_test
```

## Проверка сборки

### Консольная версия
```bash
./schmoo_console
```

### Веб-версия
Откройте `schmoo_web.html` в браузере через веб-сервер:
```bash
python -m http.server 8000
```
Затем откройте http://localhost:8000/schmoo_web.html

### Тесты
```bash
./schmoo_test
```

## Возможные проблемы

### Windows
- Если CMake не находит компилятор, убедитесь что установлены компоненты C++ в Visual Studio
- При использовании MinGW убедитесь, что он добавлен в PATH

### Linux
- При ошибках сборки проверьте версию GCC: `gcc --version`
- Убедитесь, что установлены все необходимые dev-пакеты

### Web-версия
- Проверьте, что активировано окружение Emscripten
- SDL2 должен быть доступен в системе
