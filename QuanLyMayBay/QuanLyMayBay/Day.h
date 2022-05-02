#pragma once

#include<ctime>

struct Date {
	char day[3];
	char month[3];
	char year[5];
	char hour[3];
	char minute[3];
};


void format(Date& d) {
	char temp[5] = "0";
	if (strlen(d.day) == 1) {
		strcat_s(temp, d.day);
		sprintf_s(d.day, "%s", temp);
		strcpy_s(temp, "0");
	}
		
	if (strlen(d.month) == 1) {
		strcat_s(temp, d.month);
		sprintf_s(d.month, "%s", temp);
		strcpy_s(temp, "0");
	}
	

	
	if (strlen(d.hour) == 1) {
		strcat_s(temp, d.hour);
		sprintf_s(d.hour, "%s", temp);
		strcpy_s(temp, "0");
	}
		
	
	if (strlen(d.minute) == 1) {
		strcat_s(temp, d.minute);
		sprintf_s(d.minute, "%s", temp);
	
	}
	

}
Date getCurTime() {
	tm newTime;
	time_t now = time(0);
	localtime_s(&newTime, &now);

	Date date;

	sprintf_s(date.day,"%d", newTime.tm_mday);
	sprintf_s(date.month,"%d", 1 + newTime.tm_mon);
	sprintf_s(date.year,"%d", 1900 + newTime.tm_year);
	sprintf_s(date.hour,"%d", newTime.tm_hour);
	sprintf_s(date.minute,"%d", newTime.tm_min);
	
	format(date);
	return date;
}

bool isLeapYear(int year) {
	if (year % 400 == 0)
		return true;
	if (year % 100 != 0 && year % 4 == 0)
		return true;
	return false;
}

bool checkTime(Date &d) {
	int month = stoi(d.month);
	int day = stoi(d.day);
	int year = stoi(d.year);

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
	{
		if (day > 31)
			return false;
		return true;
	}
	case 4: case 6: case 9: case 11: {
		if (day > 30)
			return false;
		return true;
	}
	case 2: {
		if (isLeapYear(year)) {
			if (day > 29)
				return false;
			return true;
		}
		else {
			if (day > 28)
				return false;
			return true;
		}
	}
	}
	return true;
}


bool checkPassTime(Date pass) {
	Date now = getCurTime();
	if (!checkTime(pass))
		return false;
	if (now.year < pass.year)
		return false;
	if (now.year >= pass.year)
		return true;
	if (now.month < pass.month)
		return false;
	if (now.month >= pass.month)
		return true;
	if (now.day < pass.day)
		return false;
	if (now.day >= pass.day)
		return true;
	if (now.hour < pass.hour)
		return false;
	if (now.hour >= pass.hour)
		return true;
	if (now.minute < pass.minute)
		return false;
	if (now.minute >= pass.minute)
		return true;
	return true;

}
bool checkFutureTime(Date pass) {
	Date now = getCurTime();
	if (!checkTime(pass))
		return false;
	if (now.year > pass.year)
		return false;
	if (now.year <= pass.year)
		return true;
	if (now.month > pass.month)
		return false;
	if (now.month <= pass.month)
		return true;
	if (now.day > pass.day)
		return false;
	if (now.day <= pass.day)
		return true;
	if (now.hour > pass.hour)
		return false;
	if (now.hour <= pass.hour)
		return true;
	if (now.minute > pass.minute)
		return false;
	if (now.minute <= pass.minute)
		return true;
	return true;
}

bool checkDay(char day[3]) {
	int d = stoi(day);
	return (d <= 31 && d >= 1);
}
bool checkMonth(char month[3]) {
	int d = stoi(month);
	return (d <= 12 && d >= 1);

}
bool checkYear(char year[5]) {
	int d = stoi(year);
	Date curr = getCurTime();
	int curYear = stoi(curr.year);
	return (d >= curYear && d <= curYear + 2);

}
bool checkHour(char hour[3]) {
	int d = stoi(hour);
	return (d <= 23 && d >= 0);
}

bool checkMinute(char minute[3]) {
	int d = stoi(minute);

	return (d <= 59 && d >= 0);

}

