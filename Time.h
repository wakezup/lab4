#ifndef TIME_H_
#define TIME_H_

#include <ostream>


class Time {
 public:
  Time();
  Time(int hours, int minutes);
  Time(const Time& other);
  Time& operator=(const Time& other) = default;

  Time operator-(unsigned int minutes) const;
  Time& operator-();
  Time& operator--();

  operator short int() const;
  explicit operator bool() const;

  bool operator==(const Time& other) const;
  bool operator!=(const Time& other) const;

  friend std::ostream& operator<<(std::ostream& output, const Time& time);

  short int GetHours() const;
  short int GetMinutes() const;

 private:
  short int hours;
  short int minutes;
};

#endif  // TIME_H_
