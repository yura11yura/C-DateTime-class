#include <iostream>
#include <ctime>
#include <string>
#include "DateTime.h"

using namespace std;

DateTime::DateTime() {
    date.day = 1;
    date.month = 1;
    date.year = 1940;
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;
}

DateTime::DateTime(int day, int month, int year, int hours, int minutes, int seconds) : DateTime() {
    if (is_correct_time(hours, minutes, seconds) && is_correct_date(day, month, year)) {
        date.day = day;
        date.month = month;
        date.year = year;
        time.hours = hours;
        time.minutes = minutes;
        time.seconds = seconds;
    }
}

DateTime::DateTime(DateTime &DT){
    SetDate(DT.date);
    SetTime(DT.time);
}

DateTime::DateTime(DateTime &&DT) noexcept {
    SetDate(DT.date);
    SetTime(DT.time);
    DT.date = {};
    DT.time = {};
}

Date DateTime::GetDate() const {
    return date;
}

Time DateTime::GetTime() const {
    return time;
}

void DateTime::print() const { // NOLINT
    if (date.day < 10) {
        cout << "0" << date.day << ".";
    } else
        cout << date.day << ".";
    if (date.month < 10) {
        cout << "0" << date.month << ".";
    } else
        cout << date.month << ".";
    cout << date.year << endl;
    if (time.hours < 10) {
        cout << "0" << time.hours << ":";
    } else
        cout << time.hours << ":";
    if (time.minutes < 10) {
        cout << "0" << time.minutes << ":";
    } else
        cout << time.minutes << ":";
    if (time.seconds < 10) {
        cout << "0" << time.seconds << "\n";
    } else
        cout << time.seconds << "\n";
}

bool DateTime::is_correct_time(int hours, int minutes, int seconds) { // NOLINT
    if (hours < 0 || hours > 23)
        return false;
    if (minutes < 0 || minutes > 59)
        return false;
    if (seconds < 0 || seconds > 59)
        return false;
    return true;
}

bool DateTime::is_correct_date(int day, int month, int year) { // NOLINT
    if (day >= 0 && day <= 31) {
        if (month == 2 && day > 28)
            return false;
        else if (month % 2 == 0 && day == 31) {
            return false;
        }
    } else
        return false;
    if (month < 1 || month > 12)
        return false;
    if (year < 0)
        return false;
    return true;
}

void DateTime::CurrentDateTime() {
    time_t ct = std::time(nullptr);
    tm current = *localtime(&ct);
    date.day = current.tm_mday;
    date.month = current.tm_mon + 1;
    date.year = current.tm_year + 1900;
    time.hours = current.tm_hour;
    time.minutes = current.tm_min;
    time.seconds = current.tm_sec;
}

DateTime DateTime::StringToDateTime(string dt, string format) { // NOLINT
    DateTime DT;
    int point = 0;
    for (int i = 0; i < format.length(); i++) {
        string ss;
        ss = format.at(i);
        if (ss == "D") {
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    if (i != format.length()) {
                        if (format.at(i + 1) == 'D') {
                            DT.date.day = stoi(dt.substr(j, 2));
                            i += 1;
                            point += 2;
                            break;
                        } else {
                            DT.date.day = stoi('0' + dt.substr(j));
                            break;
                        }
                    } else  {
                        DT.date.day = stoi('0' + dt.substr(j));
                        break;
                    }
                }
                point += 1;
            }
        }
        if (ss == "M") {
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    if (i != format.length()) {
                        if (format.at(i + 1) == 'M') {
                            DT.date.month = stoi(dt.substr(j, 2));
                            i += 1;
                            point += 2;
                            break;
                        } else {
                            DT.date.month = stoi('0' + dt.substr(j));
                            break;
                        }
                    } else {
                        DT.date.month = stoi('0' + dt.substr(j));
                        break;
                    }
                }
                point++;
            }
        }
        if (ss == "Y") {
            int temp = 1;
            for (int k = i + 1; k < format.length(); k++) {
                if (format.at(k) == 'Y')
                    temp += 1;
                else
                    break;
            }
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    DT.date.year = stoi(dt.substr(j, temp));
                    point += temp;
                    i += temp - 1;
                    break;
                }
                point++;
            }
        }
        if (ss == "h") {
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    if (i != format.length()) {
                        if (format.at(i + 1) == 'h') {
                            DT.time.hours = stoi(dt.substr(j, 2));
                            i += 1;
                            point += 2;
                            break;
                        } else {
                            DT.time.hours = stoi('0' + dt.substr(j));
                            break;
                        }
                    } else  {
                        DT.time.hours = stoi('0' + dt.substr(j));
                        break;
                    }
                }
                point += 1;
            }
        }
        if (ss == "m") {
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    if (i != format.length()) {
                        if (format.at(i + 1) == 'm') {
                            DT.time.minutes = stoi(dt.substr(j, 2));
                            i += 1;
                            point += 2;
                            break;
                        } else {
                            DT.time.minutes = stoi('0' + dt.substr(j));
                            break;
                        }
                    } else  {
                        DT.time.minutes = stoi('0' + dt.substr(j));
                        break;
                    }
                }
                point++;
            }
        }
        if (ss == "s") {
            for (int j = point; j != dt.length(); j++) {
                if (dt.at(j) >= '0' && dt.at(j) <= '9') {
                    if (i != format.length()) {
                        if (format.at(i + 1) == 's') {
                            DT.time.seconds = stoi(dt.substr(j, 2));
                            i += 1;
                            point += 2;
                            break;
                        } else {
                            DT.time.seconds = stoi('0' + dt.substr(j));
                            break;
                        }
                    } else  {
                        DT.time.seconds = stoi('0' + dt.substr(j));
                        break;
                    }
                }
                point++;
            }
        }
    }
    return DT;
}

Date DateTime::struct_date() const { // NOLINT
    return this->date;
}

Time DateTime::struct_time() const { // NOLINT
    return this->time;
}

string DateTime::DateTimeToString(string format) { // NOLINT
    int i = 0;
    string dt;
    while (i < format.length()) {
        string ss;
        ss = format.substr(i, 1);
        if (ss == "D") {
            if (date.day > 9)
                dt += to_string(date.day);
            else
                dt += '0' + to_string(date.day);
            dt += ' ';
            if (i != format.length())
                if (format.at(i+1) == 'D')
                    i++;
        }
        if (ss == "M") {
            if (date.month > 9)
                dt += to_string(date.month);
            else
                dt += '0' + to_string(date.month);
            dt += ' ';
            if (i != format.length())
                if (format.at(i+1) == 'M')
                    i++;
        }
        if (ss == "Y") {
            dt += to_string(date.year);
            dt += ' ';
            i += to_string(date.year).length() - 2;
        }
        if (ss == "h") {
            if (time.hours > 9)
                dt += to_string(time.hours);
            else
                dt += '0' + to_string(time.hours);
            dt += ' ';
            if (i != format.length())
                if (format.at(i+1) == 'h')
                    i++;
        }
        if (ss == "m") {
            if (time.minutes > 9)
                dt += to_string(time.minutes);
            else
                dt += '0' + to_string(time.minutes);
            dt += ' ';
            if (i != format.length())
                if (format.at(i+1) == 'm')
                    i++;
        }
        if (ss == "s") {
            if (time.seconds > 9)
                dt += to_string(time.seconds);
            else
                dt += '0' + to_string(time.seconds);
            dt += ' ';
            if (i != format.length())
                if (format.at(i+1) == 's')
                    i++;
        }
        i += 1;
    }
    return dt;
}

void DateTime::AddHours(int value) {
    for (int i = 0; i < value; ++i)
        if (time.hours == 23) {
            this->AddDays(1);
            time.hours = 0;
        } else
            ++time.hours;
}

void DateTime::AddMins(int value) {
    for (int i = 0; i < value; ++i) {
        if (time.minutes == 59) {
            this->AddHours(1);
            time.minutes = 0;
        } else
            ++time.minutes;
    }
}

void DateTime::AddSecs(int value) {
    for (int i = 0; i < value; ++i)
        if (time.seconds == 59) {
            this->AddMins(1);
            time.seconds = 0;
        } else
            ++time.seconds;
}

void DateTime::AddDays(int value) {
    for (int i = 0; i < value; ++i) {
        if (date.month == 2 && date.day == 28) {
                this->AddMonths(1);
                date.day = 1;
            }
        else if (date.month % 2 != 0 && date.day == 30) {
                this->AddMonths(1);
                date.day = 1;
            }
        else if (date.month % 2 == 0 && date.day == 31) {
                this->AddMonths(1);
                date.day = 1;
            }
        else
            ++date.day;
    }
}

void DateTime::AddMonths(int value) {
    for (int i = 0; i < value; ++i)
        if (date.month == 12) {
            this->AddYears(1);
            date.month = 1;
        } else
            ++date.month;
}

void DateTime::AddYears(int value) {
    date.year += value;
}

int DateTime::SecsTo(DateTime DT) const { // NOLINT
    DateTime Temp(date.day, date.month, date.year, time.hours, time.minutes, time.seconds);
    int i = 0;
    while (!(Temp.CompareTimes(DT) && Temp.CompareDates(DT))) {
        Temp.AddSecs(1);
        i += 1;
    }
    return i;
}

int DateTime::DaysTo(DateTime DT) const { // NOLINT
    DateTime Temp(date.day, date.month, date.year, time.hours, time.minutes, time.seconds);
    int i = 0;
    while (!Temp.CompareDates(DT)) {
        Temp.AddDays(1);
        i += 1;
    }
    return i;
}

bool DateTime::CompareDates(DateTime DT) const { // NOLINT
    if (date.day == DT.date.day && date.month == DT.date.month && DT.date.year == date.year)
        return true;
    return false;
}

bool DateTime::CompareTimes(DateTime DT) const { // NOLINT
    if (time.seconds == DT.time.seconds && time.minutes == DT.time.minutes && DT.time.hours == time.hours)
        return true;
    return false;
}




