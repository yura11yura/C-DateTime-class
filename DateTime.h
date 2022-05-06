#ifndef DATE_TIME_DATETIME_H
#define DATE_TIME_DATETIME_H

#include <string>

struct Date {
    int day;
    int month;
    int year;
};
struct Time {
    int hours;
    int minutes;
    int seconds;
};

class DateTime {
private:
    Date date;
    Time time;
public:
    DateTime();
    DateTime(int day, int month, int year, int hours, int minutes, int seconds);
    DateTime(DateTime &DT);
    DateTime(DateTime &&DT) noexcept;
    Date GetDate() const;
    inline void SetDate(Date change);
    Time GetTime() const;
    inline void SetTime(Time change);
    void print() const;
    static bool is_correct_date(int day, int month, int year);
    static bool is_correct_time(int hours, int minutes, int seconds);
    void CurrentDateTime();
    static DateTime StringToDateTime(std::string dt, std::string format);
    Date struct_date() const;
    Time struct_time() const;
    std::string DateTimeToString(std::string format);
    void AddHours(int value);
    void AddMins(int value);
    void AddSecs(int value);
    void AddDays(int value);
    void AddMonths(int value);
    void AddYears(int value);
    int DaysTo(DateTime DT) const;
    int SecsTo(DateTime DT) const;
    bool CompareDates(DateTime DT) const;
    bool CompareTimes(DateTime DT) const;
};

inline void DateTime::SetTime(Time change) {
    if (DateTime::is_correct_time(change.hours, change.minutes, change.seconds)) {
        time.hours = change.hours;
        time.minutes = change.minutes;
        time.seconds = change.seconds;
    }
}

inline void DateTime::SetDate(Date change) {
    if (DateTime::is_correct_date(change.day, change.month, change.year)) {
        date.day = change.day;
        date.month = change.month;
        date.year = change.year;
    }
}

#endif //DATE_TIME_DATETIME_H