#include <iostream>

#include "input.h"
#include "Time.h"


namespace {

constexpr int MaxMenuChoice = 9;

void PrintMenu(const Time& time) {
  std::cout << "\n[ИНФО] ========== Проверка класса Time ==========\n"
            << "Текущее время: " << time << '\n'
            << "1. Ввести время (конструктор с параметрами)\n"
            << "2. Вычесть минуты (без изменения текущего времени)\n"
            << "3. Обнулить часы и минуты оператором -\n"
            << "4. Обнулить минуты оператором --\n"
            << "5. Преобразовать время в short int (часы)\n"
            << "6. Преобразовать время в bool\n"
            << "7. Сравнить с другим временем\n"
            << "8. Создать копию времени\n"
            << "9. Создать время конструктором по умолчанию\n"
            << "0. Выход\n";
}

}  // namespace

int main() {
  Time current_time;

  while (true) {
    PrintMenu(current_time);
    const int choice = TaskInput("Выберите пункт меню: ", MaxMenuChoice);

    if (choice == 0) {
      std::cout << "[ИНФО] Работа программы завершена.\n";
      return 0;
    }

    switch (choice) {
      case 1:
        current_time = TimeInput("Введите новое время");
        std::cout << "[ИНФО] Установлено время: " << current_time << '\n';
        break;

      case 2: {
        const unsigned int minutes =
            MinutesInput("Сколько минут вычесть? ");
        const Time result = current_time - minutes;
        std::cout << "[ИНФО] " << current_time << " - " << minutes
                  << " мин. = " << result << '\n';
        break;
      }

      case 3:
        -current_time;
        std::cout << "[ИНФО] После обнуления часов и минут: " << current_time << '\n';
        break;

      case 4:
        --current_time;
        std::cout << "[ИНФО] После обнуления минут: " << current_time << '\n';
        break;

      case 5: {
        const short int hours = current_time;
        std::cout << "[ИНФО] Количество часов: " << hours << '\n';
        break;
      }

      case 6: {
        const bool is_nonzero = static_cast<bool>(current_time);
        std::cout << "[ИНФО] Преобразование в bool: "
                  << (is_nonzero ? "true" : "false") << '\n';
        break;
      }

      case 7: {
        const Time other_time = TimeInput("Введите время для сравнения");
        std::cout << "[ИНФО] "
                  << "[ИНФО] Результат ==: "
                  << (current_time == other_time ? "true" : "false") << '\n'
                  << "[ИНФО] Результат !=: "
                  << (current_time != other_time ? "true" : "false") << '\n';
        break;
      }

      case 8: {
        const Time source_time = TimeInput("Введите время для копирования");
        const Time copied_time(source_time);
        current_time = copied_time;
        std::cout << "[ИНФО] Копия: " << copied_time << '\n';
        break;
      }

      case 9:
        current_time = Time();
        std::cout << "[ИНФО] Время по умолчанию: " << current_time << '\n';
        break;
    }
  }
}
