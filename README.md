## Предназначение
Проект поставляет дополнительную функциональность в систему тестирования приложений Тестер и реализован в виде внешней компоненты по технологии 1С:Предприятие 8 Native API.

## Краткое описание
В библиотеке реализованы следующие функции:
- Получение снимка экрана
- Максимизация/Минимизация окна
- Работа с регулярными выражениями
- Мониторинг файлов
- Пауза
- Получение значения переменной среды
- Перевод rdp-сессии в консоль (только для Windows)

## Совместимость
Windows / Linux. Для работы компоненты под Windows, возможно потребуется установка Microsoft Visual C++ Redistributable for Visual Studio 2015-2019.

## Сборка
Библиотека может быть собрана при помощи cmake, или любой средой с его поддержкой, файл CMakeLists.txt содержит минимально необходимый для этого набор инструкций. Под Linux потребуется установка следующих пакетов:

```
sudo apt-get install -y libx11-dev libpng-dev
```

Для компиляции библиотеки, необходимо войти в папку с проектом и выполнить следующие команды:

```
cmake -DCMAKE_BUILD_TYPE=Release
make
```

#### См. также:
- [Тестер](https://github.com/grumagargler/tester)
- [Проект Тестер в формате EDT](https://github.com/grumagargler/tester.edt)
- [Справка](http://tester.help)
