#pragma once

#include<ctime>


const int DAY_MONTH[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

struct Date {
	char day[3];
	char month[3];
	char year[5];
	char hour[3];
	char minute[3];
};

char* getDateString(Date& date) {
	char  s[50];
	//VE TIME
	sprintf_s(s, "%s%s%s%s%s%s%s%s%s", date.day, "/", date.month, "/",
		date.year, "  ", date.hour, ":", date.minute);
	return s;
}



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

	sprintf_s(date.day, "%d", newTime.tm_mday);
	sprintf_s(date.month, "%d", 1 + newTime.tm_mon);
	sprintf_s(date.year, "%d", 1900 + newTime.tm_year);
	sprintf_s(date.hour, "%d", newTime.tm_hour);
	sprintf_s(date.minute, "%d", newTime.tm_min);

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



bool checkTime(Date& d) {

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

//Tinh so ngay tu ngay 0/0/0
long long  calDateToday(Date& d) {
	int year = stoi(d.year);
	int month = stoi(d.month);
	int day = stoi(d.day);

	long long dayOfYear = 365 * (year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	long long dayOfMonth = 0;
	for (int i = 0; i < month; i++) {
		dayOfMonth += DAY_MONTH[i];
	}
	if (isLeapYear(year) && month > 2) {
		dayOfMonth++;
	}

	return  dayOfYear + dayOfMonth + day - 1;
}

//Tra ve so phut giua hai moc thoi gian
long long calSpaceTime(Date& d1, Date& d2) {
	int hour = stoi(d1.hour);
	int minute = stoi(d1.minute);

	long long  minute1 = calDateToday(d1) * 24 * 60 + hour * 60 + minute;

	hour = stoi(d2.hour);
	minute = stoi(d2.minute);

	long long minute2 = calDateToday(d2) * 24 * 60 + hour * 60 + minute;
	return minute1 - minute2;
}



// kiem tra thoi gian hien tai voi moc thgian nhap vao cach bao nhieu phut
bool checkTimeBeforeMinute(Date& d, int min) {
	Date now = getCurTime();

	if (calSpaceTime(d, now) >= min)
		return true;

	return false;
}


bool in12Hour(Date& d1, Date& d2) {

	if (abs(calSpaceTime(d1, d2)) >= 720)
		return true;
	return false;


}