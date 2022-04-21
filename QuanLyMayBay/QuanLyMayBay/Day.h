#pragma once
#include<ctime>

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;
};

bool isLeapYear(int year) {
	if (year % 400 == 0)
		return true;
	if (year % 100 != 0 && year % 4 == 0)
		return true;
	return false;
}

bool checkDay(Date &d) {
	switch (d.month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
	{
		if (d.day > 31)
			return false;
		return true;
	}
	case 4: case 6: case 9: case 11: {
		if (d.day > 30)
			return false;
		return true;
	}
	case 2: {
		if (isLeapYear(d.year)) {
			if (d.day > 29)
				return false;
			return true;
		}
		else {
			if (d.day > 28)
				return false;
			return true;
		}
	}
	}
}

Date getCurTime() {
	tm newTime;
	time_t now = time(0);
	localtime_s(&newTime,&now);

	Date date;

	date.day = newTime.tm_mday;
	date.month = 1 + newTime.tm_mon;
	date.year = 1900 + newTime.tm_year;
	date.hour = newTime.tm_hour;
	date.minute = newTime.tm_min;

	return date;
}