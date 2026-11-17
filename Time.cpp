#include <iomanip>
#include <ostream>

#include "Time.h"


namespace {

constexpr int kMinutesPerHour = 60;
constexpr int kHoursPerDay = 24;
constexpr int kMinutesPerDay = kHoursPerDay * kMinutesPerHour;

int NormalizeMinutes(int total_minutes) {
  return (total_minutes % kMinutesPerDay + kMinutesPerDay) %
         kMinutesPerDay;
}

}  // namespace

Time::Time() : hours(0), minutes(0) {}

Time::Time(int hours, int minutes) {
  const int normalized_hours = hours % kHoursPerDay;
  const int normalized_minute_offset = minutes % kMinutesPerDay;
  const int normalized = NormalizeMinutes(
      normalized_hours * kMinutesPerHour + normalized_minute_offset);
  this->hours = static_cast<short int>(normalized / kMinutesPerHour);
  this->minutes = static_cast<short int>(normalized % kMinutesPerHour);
}

Time::Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

Time Time::operator-(unsigned int minutes) const {
  const int current_minutes =
      this->hours * kMinutesPerHour + this->minutes;
  const int minutes_to_subtract =
      static_cast<int>(minutes % kMinutesPerDay);
  const int result =
      NormalizeMinutes(current_minutes - minutes_to_subtract);

  return Time(result / kMinutesPerHour, result % kMinutesPerHour);
}

Time& Time::operator-() {
  hours = 0;
  minutes = 0;
  return *this;
}

Time& Time::operator--() {
  minutes = 0;
  return *this;
}

Time::operator short int() const { return hours; }

Time::operator bool() const { return hours != 0 || minutes != 0; }

bool Time::operator==(const Time& other) const {
  return hours == other.hours && minutes == other.minutes;
}

bool Time::operator!=(const Time& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& output, const Time& time) {
  const char previous_fill = output.fill('0');
  output << std::setw(2) << time.hours << ':' << std::setw(2) << time.minutes;
  output.fill(previous_fill);
  return output;
}

short int Time::GetHours() const { return hours; }

short int Time::GetMinutes() const { return minutes; }
