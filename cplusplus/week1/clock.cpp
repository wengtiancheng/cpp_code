#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <cmath> 
using namespace std;

struct Clock {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

unordered_map<string, int> month_map = {
    {"January", 1}, {"February", 2}, {"March", 3}, {"April", 4},
    {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8},
    {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}
};

bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) return true;
            else return false;
        } else return true;
    } else return false;
}

int daysInMonth(int year, int month) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

int daysInYear(int year) {
    return isLeapYear(year) ? 366 : 365;
}

long long totalSeconds(const Clock& clk) {
    long long days = clk.day - 1;
    for (int i = 1; i < clk.month; ++i) {
        days += daysInMonth(clk.year, i);
    }
    for (int i = 2024; i < clk.year; ++i) {
        days += daysInYear(i);
    }
    return days * 86400 + clk.hour * 3600 + clk.minute * 60 + clk.second;
}

Clock addSeconds(Clock clk, long long seconds) {
    if (seconds < 0) {
        seconds = -seconds;
        clk.second -= seconds;
        while (clk.second < 0) {
            clk.second += 60;
            clk.minute -= 1;
        }
        while (clk.minute < 0) {
            clk.minute += 60;
            clk.hour -= 1;
        }
        while (clk.hour < 0) {
            clk.hour += 24;
            clk.day -= 1;
        }
        while (clk.day <= 0) {
            clk.month -= 1;
            if (clk.month <= 0) {
                clk.month += 12;
                clk.year -= 1;
            }
            clk.day += daysInMonth(clk.year, clk.month);
        }
    } else {
        clk.second += seconds;
        while (clk.second >= 60) {
            clk.second -= 60;
            clk.minute += 1;
        }
        while (clk.minute >= 60) {
            clk.minute -= 60;
            clk.hour += 1;
        }
        while (clk.hour >= 24) {
            clk.hour -= 24;
            clk.day += 1;
        }
        while (clk.day > daysInMonth(clk.year, clk.month)) {
            clk.day -= daysInMonth(clk.year, clk.month);
            clk.month += 1;
            if (clk.month > 12) {
                clk.month -= 12;
                clk.year += 1;
            }
        }
    }
    return clk;
}

int main() {
    string month_str;
    Clock electronic_clock;
    cin >> electronic_clock.year >> month_str >> electronic_clock.day >> electronic_clock.hour >> electronic_clock.minute >> electronic_clock.second;
    electronic_clock.month = month_map[month_str];

    Clock base_clock = {2024, 9, 16, 0, 0, 0};
    Clock base_watch = {2024, 9, 1, 22, 20, 0};

    long long electronic_seconds = totalSeconds(electronic_clock);
    long long base_watch_seconds = totalSeconds(base_watch);

    long long total_seconds_diff = electronic_seconds - base_watch_seconds;
    long long real_seconds_diff = floor(total_seconds_diff * 60.0 / 59.0); 

    Clock real_time = addSeconds(base_clock, real_seconds_diff);

    cout << setfill('0') << setw(4) << real_time.year << '-'
         << setw(2) << real_time.month << '-'
         << setw(2) << real_time.day << 'T'
         << setw(2) << real_time.hour << ':'
         << setw(2) << real_time.minute << ':'
         << setw(2) << real_time.second << endl;

    return 0;
}