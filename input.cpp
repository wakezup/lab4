#include <cctype>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "input.h"
#include "Time.h"


bool IsInteger(const std::string& str) {
  if (str.empty()) {
    return false;
  }

  const std::size_t start =
      (str[0] == '-' || str[0] == '+') ? 1 : 0;
  if (start == str.size()) {
    return false;
  }

  for (std::size_t i = start; i < str.size(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
      return false;
    }
  }
  return true;
}

bool IsReal(const std::string& str) {
  if (str.empty()) {
    return false;
  }

  const std::size_t start =
      (str[0] == '-' || str[0] == '+') ? 1 : 0;
  if (start == str.size()) {
    return false;
  }

  bool decimal_point_found = false;
  for (std::size_t i = start; i < str.size(); ++i) {
    if (str[i] == '.') {
      if (decimal_point_found) {
        return false;
      }
      decimal_point_found = true;
    } else if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
      return false;
    }
  }
  return true;
}

bool IsEnglishCapsWord(const std::string& str) {
  if (str.empty()) {
    return false;
  }

  for (char ch : str) {
    if (ch < 'A' || ch > 'Z') {
      return false;
    }
  }
  return true;
}

int IntegerInput(const std::string& prompt) {
  std::string input;

  std::cout << "[ВВОД] " << prompt;
  while (true) {
    std::cin >> input;

    if (!IsInteger(input)) {
      std::cerr << "[ОШИБКА] Введенное значение не является целым числом."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
      std::cout << "[ВВОД] " << prompt;
      continue;
    }

    try {
      std::size_t parsed_length = 0;
      const long long value = std::stoll(input, &parsed_length);
      if (parsed_length != input.size() ||
          value < std::numeric_limits<int>::min() ||
          value > std::numeric_limits<int>::max()) {
        throw std::out_of_range("integer input");
      }
      return static_cast<int>(value);
    } catch (const std::out_of_range&) {
      std::cerr << "[ОШИБКА] Число выходит за диапазон int." << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
      std::cout << "[ВВОД] " << prompt;
    }
  }
}

int TaskInput(const std::string& prompt, int task_count) {
  while (true) {
    const int task = IntegerInput(prompt);
    if (task < 0 || task > task_count) {
      std::cerr << "[ОШИБКА] Такой задачи не существует." << std::endl;
      continue;
    }
    return task;
  }
}

double RealInput(const std::string& prompt) {
  std::string input;

  std::cout << "[ВВОД] " << prompt;
  while (true) {
    std::cin >> input;
    if (!IsReal(input)) {
      std::cerr << "[ОШИБКА] Введенное значение не является "
                   "действительным числом."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
      std::cout << "[ВВОД] " << prompt;
      continue;
    }
    return std::stod(input);
  }
}

std::string EnglishCapsWordInput(const std::string& prompt) {
  std::string input;

  std::cout << "[ВВОД] " << prompt;
  while (true) {
    std::cin >> input;
    if (!IsEnglishCapsWord(input)) {
      std::cerr << "[ОШИБКА] Введенное значение не является "
                   "английским словом с заглавными буквами."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
      std::cout << "[ВВОД] " << prompt;
      continue;
    }
    return input;
  }
}

Time TimeInput(const std::string& prompt) {
  std::cout << "[ИНФО] " << prompt << std::endl;

  int hours = 0;
  while (true) {
    hours = IntegerInput("Часы (0-23): ");
    if (hours >= 0 && hours < 24) {
      break;
    }
    std::cerr << "[ОШИБКА] Часы должны быть в диапазоне от 0 до 23."
              << std::endl;
  }

  int minutes = 0;
  while (true) {
    minutes = IntegerInput("Минуты (0-59): ");
    if (minutes >= 0 && minutes < 60) {
      break;
    }
    std::cerr << "[ОШИБКА] Минуты должны быть в диапазоне от 0 до 59."
              << std::endl;
  }

  return Time(hours, minutes);
}

unsigned int MinutesInput(const std::string& prompt) {
  while (true) {
    std::cout << "[ВВОД] " << prompt;

    std::string input;
    std::cin >> input;
    if (!IsInteger(input) || input[0] == '-') {
      std::cerr << "[ОШИБКА] Количество минут должно быть "
                   "неотрицательным целым числом."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
      continue;
    }

    try {
      std::size_t parsed_length = 0;
      const unsigned long long value =
          std::stoull(input, &parsed_length);
      if (parsed_length != input.size() ||
          value > std::numeric_limits<unsigned int>::max()) {
        throw std::out_of_range("unsigned minute input");
      }
      return static_cast<unsigned int>(value);
    } catch (const std::out_of_range&) {
      std::cerr << "[ОШИБКА] Количество минут выходит за диапазон "
                   "unsigned int."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(1'000'000, '\n');
    }
  }
}
