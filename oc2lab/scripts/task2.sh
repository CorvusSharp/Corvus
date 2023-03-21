#!/bin/bash

# Задаем имя файла, для которого ищем жесткие ссылки
file_name="task1.sh"

# Ищем все жесткие ссылки на файл и фильтруем только те, которые находятся в пользовательском пространстве
find / -type f -inum $(ls -i $file_name | awk '{print $1}') 2>/dev/null | grep -v "/proc/" | grep -v "/sys/"
