# Schmoo Game

Schmoo Game - это интерактивная игра-симулятор стрельбы, где игрок пытается попасть в движущуюся цель (Schmoo) путем расчета угла возвышения и направления выстрела. Проект демонстрирует различные подходы к реализации пользовательского интерфейса: консольный, веб-интерфейс и автоматическое тестирование.

## Содержание
- [Возможности](#возможности)
- [Быстрый старт](#быстрый-старт)
- [Как играть](#как-играть)
- [Сборка проекта](#сборка-проекта)
- [Тестирование](#тестирование)
- [Разработка](#разработка)
- [Лицензия](#лицензия)

## Возможности

- Мультиплатформенная поддержка:
  - Windows
  - Linux
  - NetBSD
  - Web (через WebAssembly)
- Несколько режимов игры:
  - Консольный интерфейс
  - Веб-интерфейс с визуализацией
  - Режим тестирования
- Игровые механики:
  - Расчет траектории полета
  - Случайное размещение цели
  - Подсчет очков и попыток

## Быстрый старт

1. Клонируйте репозиторий:
```bash
git clone https://github.com/your-username/SchmooGame.git
```

2. Создайте директорию для сборки:
```bash
cd SchmooGame
mkdir build && cd build
```

3. Соберите проект:
```bash
cmake ..
make
```

4. Запустите игру:
```bash
./schmoo_console
```

Подробные инструкции по сборке для разных платформ находятся в [BUILDING.md](docs/BUILDING.md)

## Как играть

### Консольная версия

1. Запустите игру
2. Введите угол возвышения (1-90 градусов)
3. Введите угол направления (0-360 градусов)
4. Следуйте подсказкам о результатах выстрела
5. Повторяйте, пока не попадете в цель

### Веб-версия

Используйте клавиши управления:
- Стрелка вверх - Увеличить угол возвышения
- Стрелка вниз - Уменьшить угол возвышения
- Стрелка влево - Уменьшить угол направления
- Стрелка вправо - Увеличить угол направления
- Пробел - Выстрел

## Сборка проекта

См. подробные инструкции в [BUILDING.md](docs/BUILDING.md)

## Тестирование

Для запуска тестов:
```bash
cmake -DBUILD_TESTS=ON ..
make
./schmoo_test
```

## Разработка

Проект использует:
- C++17
- CMake для сборки
- SDL2 для веб-версии
- Emscripten для компиляции в WebAssembly

## Лицензия

Проект распространяется под лицензией MIT. Подробности в файле [LICENSE](LICENSE)
