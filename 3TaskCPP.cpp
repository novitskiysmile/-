// 3TaskCPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <string>
using namespace std;
int f(int x, bool upperYear) // проврека на кол-во дней в месяце
{
	if (x == 2 && upperYear)
	{
		return 29;
	}
	int f = floor(x / 8);
	return 28 + (x + f) % 2 + 2 % x + 2 * floor(1 / x);
}
int codeOfMonth(int m)
{
	int codeMonth = 0;
	//1 — январь, октябрь;
	//2 — май;
	//3 — август;
	//4 — февраль, март, ноябрь;
	//5 — июнь;
	//6 — декабрь, сентябрь;
	//0 — апрель, июль.
	if (m == 1 || m == 10)
		codeMonth = 1;
	if (m == 5)
		codeMonth = 2;
	if (m == 8)
		codeMonth = 3;
	if (m == 2 || m == 3 || m == 11)
		codeMonth == 4;
	if (m == 6)
		codeMonth = 5;
	if (m == 12 || m == 9)
		codeMonth = 6;
	if (m == 4 || m == 7)
		codeMonth = 0;

	return codeMonth;
}
int codeOfYear(int year)
{
	string year_Str = to_string(year);
	int twice = stoi(year_Str.substr(year_Str.size() - 2, year_Str.size()));
	//код года = (6 + последние две цифры года + последние две цифры года / 4) % 7;
	int twdel = floor(twice / 4);
	int code = (6 + twice + twdel) % 7;
	return code;
}
bool u(int year)
{
	if (year % 4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
class Date
{

public:
	Date();
	Date(int yr, int mn, int dt)
	{
		this->year = yr;
		this->mounth = mn;
		this->date = dt;
	}
	~Date();
	int getYear() { return year; }
	int getMounth() { return  mounth; }
	int getDate() { return date; }
	void print()
	{
		string monthStr;
		string DayStr;

		if (mounth < 10)
		{
			monthStr = "0";
			monthStr += std::to_string(mounth);
		}
		else
		{
			monthStr = std::to_string(mounth);
		}
		if (date < 10)
		{
			DayStr = "0";
			DayStr += std::to_string(date);
		}
		else
		{
			DayStr = std::to_string(date);
		}
		printf("%d.%s.%s\n", year, monthStr.c_str(), DayStr.c_str());
	}
	void printMounth()
	{
		string monthStr;

		switch (mounth)
		{
		case 1:
			monthStr = "January";
			break;
		case 2:
			monthStr = "February";
			break;
		case 3:
			monthStr = "April";
			break;
		case 4:
			monthStr = "March";
			break;
		case 5:
			monthStr = "May";
			break;
		case 6:
			monthStr = "Jun";
			break;
		case 7:
			monthStr = "Julay";
			break;
		case 8:
			monthStr = "August";
			break;
		case 9:
			monthStr = "Septembre";
			break;
		case 10:
			monthStr = "Octobre";
			break;
		case 11:
			monthStr = "Novembre";
			break;
		case 12:
			monthStr = "Decembre";
			break;
		default:
			break;
		}

		printf("%d %s %d\n", date, monthStr.c_str(), year);

	}
	void previousDate()
	{

		int nYear = year - 1;
		int nDay, nMonth = 0;
		if (mounth - 1 > 0)
		{
			nMonth = mounth - 1;//2
		}
		else
		{
			nMonth = mounth - 1;
			nMonth += 12;
			nYear--;
		}
		if (date - 1 > 0)
		{
			nDay = date - 1;//30/30
		}
		else
		{
			if (mounth - 1 > 0)
			{
				nMonth = mounth - 1;//2
			}
			else
			{
				nMonth = mounth - 1;
				nMonth += 12;
				nYear--;
			}
			nDay = date - 1;
			nDay += f(nMonth, u(nYear));

		}
		Date result(nYear, nMonth, nDay);
		result.print();

	}
	void nextDate()
	{
		int nYear = year + 1;
		int nDay, nMonth = 0;
		if (mounth + 1 <= 12)
		{
			nMonth = mounth + 1;//2
		}
		else
		{
			nMonth = mounth + 1;
			nMonth -= 12;
			nYear++;
		}
		if (date + 1 <= f(nMonth, u(nYear)))
		{
			nDay = date + 1;//30/30
		}
		else
		{
			if (mounth + 1 <= 12)
			{
				nMonth = mounth + 1;//2
			}
			else
			{
				nMonth = mounth + 1;
				nMonth -= 12;
				nYear++;
			}
			nDay = date + 1;
			nDay -= f(nMonth, u(nYear));

		}
		Date result(nYear, nMonth, nDay);
		result.print();
	}
	void week_day()
	{

		string daysofWeek[]{ "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday" };
		int result = (this->date + codeOfMonth(this->mounth) + codeOfYear(this->year)) % 7;

		cout << daysofWeek[result] << endl;
	}
	Date compare(Date d2)
	{
		Date d1(this->year, this->mounth, this->date);

		int cnt_daysFirst = 0;
		int cnt_daysSecond = 0;

		for (int i = 1; i <= this->mounth; i++)
		{
			cnt_daysFirst += f(i, u(this->year));
		}
		for (int i = 1; i <= d2.mounth; i++)
		{
			cnt_daysSecond += f(i, u(d2.year));
		}
		if (this->year == d2.year)
		{
			if (cnt_daysFirst < cnt_daysSecond)
			{
				return d1;
			}
			else
			{
				return d2;
			}
		}
		if (this->year < d2.year)
		{
			return d1;
		}
		else
		{
			return d2;
		}

	}
	void add_day(int d)
	{
		
		int nYear = year;
		int nDay = date; 
		int nMonth = mounth;
		
		if (date + d <= f(nMonth, u(nYear)))
		{
			nDay = date + d;//30/30
		}
		else
		{
			if (mounth + 1 <= 12)
			{
				nMonth = mounth + 1;//2
			}
			else
			{
				nMonth = mounth + 1;
				nMonth -= 12;
				nYear++;
			}
			nDay = date + d;
			nDay -= f(nMonth, u(nYear));

		}
		Date result(nYear, nMonth, nDay);
		result.print();
	}
	void days(Date d2)
	{
		int diffYear = 0;
		int cnt_vys = 0;
		if (this->year != d2.year)
		{
			if (this->year < d2.year)
			{
				for (int i = this->year; i < d2.year; i++)
				{
					if (u(i))
						cnt_vys++;
				}
				diffYear = (d2.year - this->year - cnt_vys) * 364 + (cnt_vys * 365);

			}
		}
		Date d1(this->year, this->mounth, this->date);

		int cnt_daysFirst = 0;
		int cnt_daysSecond = 0;

		for (int i = 1; i <= this->mounth; i++)
		{
			cnt_daysFirst += f(i, u(this->year));
		}
		for (int i = 1; i <= d2.mounth; i++)
		{
			cnt_daysSecond += f(i, u(d2.year));
		}
		int diff = abs(cnt_daysFirst - cnt_daysSecond);
		cout << "Diffrenece: " << diff + diffYear;
	}

private:
	int year;
	int mounth;
	int date;
};

Date::Date()
{
}

Date::~Date()
{
}


Date getDate()
{

	Date d1;
	int year, month, dat = 0;

	cout << "Year: " << endl;
	cin >> year;
	if (year <= 0)
	{
		cout << "Enter correct year" << endl;
		return d1;
	}

	cout << "Month: " << endl;
	cin >> month;
	if (month <= 0 || month > 12)
	{
		cout << "Enter correct month" << endl;
		return d1;
	}
	cout << "Data day: " << endl;
	cin >> dat;
	if (dat <= 0 || dat > 31 || dat > f(month, u(year)) )
	{
		cout << "Error write date!" << endl;
		return d1;
	}
	Date d2(year, month, dat);
	return d2;
}


class Time
{
public:
	Time();
	Time(int d, int hr, int min, int sec)
	{
		this->day = d;
		this->hour = hr;
		this->minute = min;
		this->second = sec;

	}

	~Time();
	void print()
	{
		string dayStr;
		string hourStr;
		string minStr;
		string secStr;
	
			dayStr += to_string(day);
		
		if (minute < 10)
		{
			minStr = "0";
			minStr += to_string(minute);
		}
		else
		{
			minStr += to_string(minute);
		}
		if (second < 10)
		{
			secStr = "0";
			secStr += to_string(second);
		}
		else
		{
			secStr += to_string(second);
		}
		if (hour < 10)
		{
			hourStr = "0";
			hourStr += to_string(hour);
		}
		else
		{
			hourStr += to_string(hour);
		}
		printf("%s.%s.%s.%s\n", dayStr.c_str(), hourStr.c_str(), minStr.c_str(), secStr.c_str());
	}
	Time getFromDate(Date d)
	{

		Time t(d.getDate(),10,10,10);
		return t;
	}
	Time compare(Time t)
	{
		Time t1(this->day, this->hour, this->minute, this->second);
		int count_secFirst = 0;
		int count_secSecond = 0;

		count_secFirst += (this->day * 24) * 3600;
		count_secFirst += this->hour * 3600;
		count_secFirst += this->minute* 60;
		count_secFirst += this->second;

		count_secSecond += (t.day * 24) * 3600;
		count_secSecond += t.hour * 3600;
		count_secSecond += t.minute * 60;
		count_secSecond += t.second;

		if (count_secFirst > count_secSecond)
		{
			return t;
		}
		else
		{
			return t1;
		}
	}
	void substuctTime(Time t)
	{
		int nDay = this->day - t.day;
		int nHour, nMinute, nSecund = 0;
		if (this->hour - t.hour > 0)
		{
			nHour = this->hour - t.hour;
		}
		else
		{
			nHour = this->hour - t.hour;
			nHour += 24;
			nDay--;
		}

		if (this->minute - t.minute > 0)
		{
			nMinute = this->minute - t.minute;
		}
		else
		{
			nMinute = this->minute - t.minute;
			nMinute += 59;
			if (nHour - 1 > 0)
			{
				nHour = nHour - 1;
			}
			else
			{
				nHour = nHour - 1;
				nHour += 24;
				nDay--;
			}

		}
		if (this->second - t.second > 0)
		{
			nSecund = this->second - t.second;
		}
		else
		{
			nSecund = this->second - t.second;
			nSecund += 59;
			if (nMinute - 1 > 0)
			{
				nMinute = nMinute - 1;
			}
			else
			{
				nMinute = nMinute - 1;
				nMinute += 59;
				if (nHour - 1 > 0)
				{
					nHour = nHour - 1;
				}
				else
				{
					nHour = nHour - 1;
					nHour += 24;
					nDay--;
				}

			}
		}
		Time res(nDay, nHour, nMinute, nSecund);
		res.print();
	}
	void addTime(Time t)
	{
		int nDay = this->day + t.day;
		int nHour,nMinute, nSecund = 0;
		if (this->hour + t.hour < 24)
		{
			nHour = this->hour + t.hour;
		}
		else
		{
			nHour = this->hour + t.hour;
			nHour -= 24;
			nDay++;
		}

		if (this->minute + t.minute <= 59)
		{
			nMinute = this->minute + t.minute;
		}
		else
		{
			nMinute = this->minute + t.minute;
			nMinute -= 59;
			if (nHour + 1< 24)
			{
				nHour = nHour + 1;
			}
			else
			{
				nHour = nHour + 1;
				nHour -= 24;
				nDay++;
			}

		}
		if (this->second+ t.second<= 59)
		{
			nSecund = this->second + t.second;
		}
		else
		{
			nSecund = this->second + t.second;
			nSecund -= 59;
			if (nMinute + 1 <= 59)
			{
				nMinute = nMinute + 1;
			}
			else
			{
				nMinute = nMinute + 1;
				nMinute -= 59;
				if (nHour + 1 < 24)
				{
					nHour = nHour + 1;
				}
				else
				{
					nHour = nHour + 1;
					nHour -= 24;
					nDay++;
				}

			}
		}
		Time res(nDay, nHour, nMinute, nSecund);
		res.print();
	}
	void addTimetoData(Date d)
	{
		
		d.add_day(this->day);
	}
private:
	int day;
	int hour;
	int minute;
	int second;
};

Time::Time()
{
}

Time::~Time()
{
}
Time getTime()
{
	Time t1;
	int day = 0;
	cout << "Enter day:" << endl;
	cin >> day;
	if (day < 0)
	{
		cout << "Error" << endl;
		return t1;
	}
	int hour = 0;
	cout << "Hour: " << endl;
	cin >> hour;
	if (hour < 0 || hour > 24)
	{
		cout << "Error" << endl;
		return t1;
	}
	int min = 0;
	cout << "Minutes:" << endl;
	cin >> min;
	if (min > 59 || min < 0)
	{
		cout << "Error" << endl;
		return t1;
	}

	int sec = 0;
	cout << "Secunds:" << endl;
	cin >> sec;
	if (sec < 0 || sec > 59)
	{
		cout << "Error" << endl;
		return t1;
	}

	Time t_cure(day, hour, min, sec);
	return t_cure;
}


int main()
{
	Date d1;
	d1 = getDate();

	d1.print();
	d1.printMounth();
	cout << "Next:" << endl;
	d1.nextDate();
	cout << "Prev:" << endl;
	d1.previousDate();
	cout << "Fill d2" << endl;
	Date d2;
	d2 = getDate();
	cout << "Compare: " << endl;
	d1.compare(d2).print();

	d1.week_day();
	d1.add_day(11);
	d1.days(d2);

	Time t1;
	t1 = getTime();
	t1.print();
	
	cout << "Enter t2" << endl;
	Time t2;
	t2 = getTime();
	t1.compare(t2).print();
	cout << "Add t1 to t2" << endl;
	t1.addTime(t2);
	cout << "Substruct t1 to t2" << endl;
	t1.substuctTime(t2);
	cout << "Add time to date" << endl;
	t1.addTimetoData(d1);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
