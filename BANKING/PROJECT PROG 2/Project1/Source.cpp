using namespace std;
#include <iostream>
#include<cmath>
#include <iomanip>
#include<cstring>
#include <cstring>
#include <regex> 
#include<cstdlib>
#include<ctime>
#include<fstream>
#include <sstream> 
#include "md5.h"
#include <algorithm>
#include <cctype>
struct date
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
};
struct appointment
{
	int num;
	date d;
	string dis;
};
struct client
{
	int  ID;
	string firstname;
	string lastname;
	string password;
	string email;
	string phonenum;
	appointment* a;
};
void copyf(fstream& fout, client user) {
	fout.open("client.txt", ios::out | ios::app);
	fout << user.ID << "\t"
		<< user.firstname << "\t"
		<< user.lastname << "\t"
		<< user.password << "\t"
		<< user.email << "\t"
		<< user.phonenum << "\t"
		<< "\n";
	fout.close();


}
bool is_valid(string email) {
	string email2;
	bool atFlag = false;
	bool comFlag = false;

	int size = email.length();
	for (int c = 0; c < email.length(); c++) {
		if (email[c] == '@') {
			atFlag = true;


			email2 = email.substr(size - (c + 2), size - 2);
			for (int i = 0; i < email2.length(); i++)
			{
				if (email2[i] == '.') {
					comFlag = true;
				}
			}



		}

	}
	if (atFlag && comFlag) {

		return true;

	}
	return false;
}
bool is_valid2(string email) {
	bool t = false;
	ifstream clintr("client.txt");
	client junk;
	while (clintr)
	{
		clintr >> junk.ID >> junk.firstname >> junk.lastname >> junk.password >> junk.email >> junk.phonenum;
		if (email == junk.email) {

			return false;
		}
	}
	return true;
}
void strongPass(string& str) {
	int lowcase = 0, upcase = 0, d = 0, s = 0;
	
	cout << "plz enter your password ";
	getline(cin, str);
	while (str.length() < 8)
	{
		cout << " your pass is short please inter a 8 digits at least ";
		getline(cin, str);
	}
	while (lowcase == 0 || upcase == 0 || d == 0 || s == 0) {

		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
				lowcase++;
			if (isupper(str[i]))
				upcase++;
			if (isdigit(str[i]))
				d++;
			if (!isalpha(str[i]) && !isdigit(str[i]))
				s++;
		}
		if (lowcase + upcase + d + s < 8 || (lowcase == 0 || upcase == 0 || d == 0 || s == 0))
		{
			cout << "week password pls enter a password ontaining numbers, letters, and special characters and at least 8 char" << endl;
			getline(cin, str);
		}
		if (lowcase && upcase && d && s && str.length() >= 8)
		{
			break;
		}
	}
}
bool checkPhone(string& pass) {
	if (pass.length() != 8) {
		cout << "the number most be  8 nubers plz enter the number correctly";

		return 0;
	}
	if ((pass[0] == '0' && pass[1] == '3') || (pass[0] == '7 ' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '0') || (pass[0] == '7' && pass[1] == '6') || (pass[0] == '8' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '8') || (pass[0] == '7 ' && pass[1] == '9')) {

		return 1;

	}
	else {
		cout << "plz the nuer most be star with (03,70,71,76,81)";


		return 0;
	}


}
void hash(client& password) {
	password.password = md5(password.password);
}
void IDgen(client& str1) {
	client junk;
	str1.ID = 1;
	junk.ID = 0;
	ifstream clintr("client.txt");
	while (clintr)
	{

		clintr >> junk.ID >> junk.firstname >> junk.lastname >> junk.password >> junk.email >> junk.phonenum;
	}
	str1.ID = junk.ID + 1;

	clintr.close();
}
void signIn(client& user) {
	IDgen(user);
	
	bool t = false;
	ifstream clintr("client.txt");
	client junk;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "pls enter your first name " << endl;
	getline(cin, user.firstname);
	cout << "pls enter your last name" << endl;
	getline(cin, user.lastname);
	
	
		strongPass(user.password);

	user.password = md5(user.password);

	cout << "plz enter your email" << endl;
	getline(cin, user.email);
	while ((is_valid(user.email) == 0) || (is_valid2(user.email) == 0)) {
		while ((is_valid(user.email) == 0))
		{
			cout << "your email is incorect plz enternt correctly" << endl;
			getline(cin, user.email);
		}
		while ((is_valid2(user.email) == 0)) {
			cout << "your email is already exist enter onother onr plz ";
			getline(cin, user.email);
		}
	}

	cout << "plz enter your number ";
	getline(cin, user.phonenum);
	while (checkPhone(user.phonenum) == 0) {
		getline(cin, user.phonenum);
	}

	fstream fout;
	copyf(fout, user);


}
bool login(client& user) {
	client junk;
	cout << "enter your email and your password plss" << endl;
	cin.ignore(INT_MAX, '\n');

	getline(cin, user.email);
	getline(cin, user.password);
	user.password = md5(user.password);

	ifstream clintr("client.txt");
	while (clintr)
	{
		clintr >> junk.ID >> junk.firstname >> junk.lastname >> junk.password >> junk.email >> junk.phonenum;

		if ((user.email == junk.email) && (user.password == junk.password)) {
			cout << "log in sussesfull" << endl;
			user.ID = junk.ID;
			user.firstname = junk.firstname;
			user.lastname = junk.lastname;
			user.phonenum = junk.phonenum;
			return true;
		}


	}clintr.close();
	return false;
}
bool administrator(client user) {


	string alyoussf = "alyoussf";
	string AlYoussf = "AlYoussf";

	if ((user.lastname == AlYoussf || (user.lastname == alyoussf))) {

		return true;


	}
	else return false;

}
void clienT(client user) {
	cout << endl << "hello Mr." << user.lastname << endl << "You login as client";


}
void AddAPP(appointment& first) 
{
	fstream rooms("Appointment.txt", ios::in | ios::out | ios::app);
	cout << "pleace enter the number of the appointment";
	cin >> first.num;
	cout << "pleace enter the day day/monthe /year";
	cin >> first.d.day >> first.d.month >> first.d.year >> first.d.hour >> first.d.minute >> first.d.second;
	rooms << first.num << "\t" << first.d.day << "-" << first.d.month << "-" << first.d.year << "\t" << first.d.hour << ":" << first.d.minute << ":" << first.d.second << "\n";
	rooms.close();
}
int dayofweek(int date, int month, int year)
{
	static int t[] = { 0, 3, 2, 5, 0, 3,
					   5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	return (year + year / 4 - year / 100 +
		year / 400 + t[month - 1] + date) % 7;
}
bool checkWeekday(int day) {

	if (day == 0 || day == 6) {  

		return false;
	
	}
	else {
		return true;
	}
}
void delete_row(int id) {

	ifstream in("Appointment.txt");
	ofstream out("appointments_new.txt");


	if (!in || !out) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}

	std::string line;
	while (getline(in, line)) {

		std::stringstream ss(line);


		appointment app;
		ss >> app.num >> app.d.day >> app.d.month >> app.d.year >> app.d.hour >> app.d.minute >> app.d.second;


		if (app.num != id) {

			out << app.num << "\t" << app.d.day << " " << app.d.month << " " << app.d.year << "\t" << app.d.hour << " " << app.d.minute << " " << app.d.second << endl;
		}
	}

	in.close();
	out.close();

	std::remove("Appointment.txt");
	std::rename("appointments_new.txt", "Appointment.txt");
}
void saveappointment(client& user,int &m) 
{
	
	user.firstname = "zahi";
	user.lastname = "chami";
	int i = 0;
	string a;
	client junk;
	date d;
	ifstream in("clientappointment.txt");
	if (!in ) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	while (in)
	{
		getline(in, junk.firstname, '\t');
		getline(in, junk.lastname, '\t');
		in >> d.day >> d.month >> d.year >> d.hour >> d.minute >> d.second;
		
		
		getline(in,a, '\n');
		
		if ((junk.firstname == user.firstname) && (junk.lastname == user.lastname))
		{
			i++;
		}
	}
	in.close();
	user.a = new appointment[i + 1];
	m = i;
	i = 0;
	ifstream iin("clientappointment.txt");
	while (iin)
	{
		getline(iin, junk.firstname, '\t');
		getline(iin, junk.lastname, '\t');
		iin >> d.day >> d.month >> d.year >> d.hour >> d.minute >> d.second;


		getline(iin, a, '\n');

		if ((junk.firstname == user.firstname) && (junk.lastname == user.lastname))
		{
			user.a[i].d = d;
			user.a[i].dis = a;
			
			i++;
		}
	}
	iin.close();


}
void appointmentt(appointment &t,client&user,int m ) 
{
	string junk;
	appointment t2[10];
	int day = 0;
	while (day ==0)
	{


		cout << endl << "pleace enter thre day (day /month /years)" << endl;
		cin >> t.d.day >> t.d.month >> t.d.year;
		cout << "You Have Entered: " << t.d.day << "/" << t.d.month << "/" << t.d.year << endl;
		day = dayofweek(t.d.day, t.d.month, t.d.year);
		checkWeekday(day);
		if (day == 0)
		{
			cout << "this a week ind day pleace enter onather day";
		}
	}
	cout << endl << " all available appointment on " << t.d.day << "/" << t.d.month << "/" << t.d.year << endl;
	
    ifstream fout("Appointment.txt",ios::out| ios::out | ios::app);
	int i = 0;
	while (fout)
	{
		

		fout >> t2[i].num >> t2[i].d.day >> t2[i].d.month >> t2[i].d.year >> t2[i].d.hour >> t2[i].d.minute >> t2[i].d.second;
		
		if ((t2[i].d.day == t.d.day) && (t2[i].d.month == t.d.month) && (t2[i].d.year == t2[i].d.year))
		{
			cout<<"id"<<"   " << t2[i].num << "\t" << t2[i].d.day << "-" << t2[i].d.month << "-" << t2[i].d.year << "\t" << t2[i].d.hour << "-" << t2[i].d.minute << "-" << t2[i].d.second << endl;
		}
		i++;
    }
	cout << endl << "pleace enter the id of the appointment you wanet ";
	cin >> i;
	fout.close();
	delete_row(i);
	user.a[m].d = t2[i - 1].d;
	user.a[m].dis = "";
	cout <<endl<<user.a[m].d.day << endl;
	fstream out("clientappointment.txt", ios::out | ios::app);
	
		out << user.firstname << "\t" << user.lastname << "\t" << user.a[m].d.day << " " << user.a[m].d.month << " " << user.a[m].d.year << "\t" << user.a[m].d.hour << " " << user.a[m].d.minute << " " << user.a[m].d.second << "\t" << user.a[m].dis<<endl;
	
		out.close();
}
void camcelappointmentt(client& user,int m)
{
	client user2;
	user2.a = new appointment[m - 1];
	int j;
	for (int i = 0; i < m; i++)
	{
		cout << endl << endl<<i<<"\t"  << user.firstname << "\t" << user.lastname << "\t" << user.a[i].d.day << " " << user.a[i].d.month << " " << user.a[i].d.year << "\t " << user.a[i].d.hour << " " << user.a[i].d.minute << " " << user.a[i].d.second;
	}cout <<endl<< endl;
	cout << "plece enter the id of thr appointment u wont to cancelet ";
	cin >> j;
	ifstream in("clientappointment.txt");
	ofstream out("clientappointment_new.txt");


	if (!in || !out) {
		cerr << "Error: Unable to open the input or output file" << std::endl;
		return;
	}
	int d = 0;
	std::string line, about;
	while (getline(in, line)) {

		std::stringstream ss(line);


		client app;
		date app2;
		getline(ss, app.firstname, '\t');

		getline(ss, app.lastname, '\t');
		ss >> app2.day >> app2.month >> app2.year >> app2.hour >> app2.minute >> app2.second;
		getline(ss, about, '\n');

		if ((app2.day == user.a[j].d.day) && (app2.month == user.a[j].d.month) && (app2.year == user.a[j].d.year) && (app2.hour == user.a[j].d.hour) && (app2.minute == user.a[j].d.minute) && (app2.second == user.a[j].d.second))
		{

			
			continue;
		}
		else
		{
			
			//cout<<endl << app2.day <<'\t' << app2.month <<"\t" << app2.year <<"\t" << app2.hour <<'\t' << app2.minute <<'\t' << app2.second;
			out << app.firstname << '\t' << app.lastname << "\t" << app2.day << " " << app2.month << " " << app2.year << "\t" << app2.hour << " " << app2.minute << " " << app2.second <<"\t"<<about << endl;
		}
	}

	in.close();
	out.close();

	std::remove("clientappointment.txt");
	std::rename("clientappointment_new.txt", "clientappointment.txt");
	
	for (int   i = 0; i < m; i++)
	{
		if (i == j) 
		{
			for (int t = i; t < m-1; t++)
			{
				user.a[t] = user.a[t + 1];

			}
	    }

	}
	for (int i = 0; i < m - 1; i++)
	{
		user2.a[i] = user.a[i];
		

	}  user.a = new appointment[m-1 ];
	for (int i = 0; i < m-1 ; i++)
	{
		user.a[i] = user2.a[i];
		//cout << endl << endl << i << "\t" << user.firstname << "\t" << user.lastname << "\t" << user2.a[i].d.day << " " << user2.a[i].d.month << " " << user2.a[i].d.year << "\t " << user2.a[i].d.hour << " " << user2.a[i].d.minute << " " << user2.a[i].d.second;

	}
	

}
void acceptregect()
{


	fstream file("clientappointment.txt", std::ios::in | std::ios::out);
	ofstream file2("new.txt");

	if (!file.is_open()) {
		cerr << "Failed to open client_appointment.txt" << std::endl;

	}

	int day, month, year, hour, minute, second;
	string first_name, last_name,  status,temp;
	while (file) {
		file >> first_name >> last_name >> day >> month >> year >> hour >> minute>>second;
	

		getline(file, status, '\n');	
	
	if ((status != "\tAccepted") && (status != "\tRejected"))
    {   

		
			string action;
			cout << "Accept or reject the appointment for " << first_name << " " << last_name << " on " << day << "/" << month << "/" << year << " at " << hour << ":" << minute << ":" << second << "? (A/R): ";
			cin >> action;
			if (action == "A") {
				status = "Accepted";
			}
			else if (action == "R") {
				status = "Rejected";
			}

    }
		
		file2 << first_name << "\t" << last_name << "\t" << day << " " << month << " " << year << "\t" << hour << " " << minute << " " << second << " " << status<<endl;
	}	
	file.close();
	file2.close();
		std::remove("clientappointment.txt");
	std::rename("new.txt", "clientappointment.txt");
	
}
void Removeap() 
{
	fstream file("clientappointment.txt", std::ios::in | std::ios::out);
	

	if (!file.is_open()) {
		cerr << "Failed to open client_appointment.txt" << std::endl;

	}

	int id=0,index, day, month, year, hour, minute, second;
	string first_name, last_name, status, temp;
	while (file) {
		file >> first_name >> last_name >> day >> month >> year >> hour >> minute >> second;


		getline(file, status, '\n');

		
		


			string action;
			cout << "all th eappointmet  "<<id <<'\t' << first_name << " " << last_name << " on " << day << "/" << month << "/" << year << " at " << hour << ":" << minute << ":" << second << ":"<<status<<" : " << endl;
			


			id++;

		//file2 << first_name << "\t" << last_name << "\t" << day << " " << month << " " << year << "\t" << hour << " " << minute << " " << second << " " << status << endl;
	}
	file.close();
	ofstream file2("new.txt");
	fstream file3("clientappointment.txt", std::ios::in | std::ios::out);
	cout << endl << "enter the number of the appointment you wat to delete" << endl;
	cin >> index;
	int id2 = id;
	id = 0;
	while (file3)
	{
		file3 >> first_name >> last_name >> day >> month >> year >> hour >> minute >> second;


		getline(file3, status, '\n');
		
		if (id != index)
		{
			
			
			



			file2 << first_name << "\t" << last_name << "\t" << day << " " << month << " " << year << "\t" << hour << " " << minute << " " << second  << status << endl;
			cout << "all th eappointmet  " << id << '\t' << first_name << " " << last_name << " on " << day << "/" << month << "/" << year << " at " << hour << ":" << minute << ":" << second << ":" << status << " : " << endl;
		}
		
		
		id++;

		




	}
	
	
	file2.close();
	file3.close();
	remove("clientappointment.txt");
	rename("new.txt", "clientappointment.txt");


}
bool compareDates(const date& a, const date& b) {

	if (a.year != b.year) {
		return a.year < b.year;
	}

	if (a.month != b.month) {
		return a.month < b.month;
	}


	if (a.day != b.day) {
		return a.day < b.day;
	}

	if (a.hour != b.hour) {
		return a.hour < b.hour;
	}

	if (a.minute != b.minute) {
		return a.minute < b.minute;
	}


	return a.second < b.second;
}
void sort_appointments(appointment arr[], int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (arr[j].d.year > arr[j + 1].d.year) {
				
					appointment temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
				else if (arr[j].d.year == arr[j + 1].d.year) {
				
					if (arr[j].d.month > arr[j + 1].d.month) {
					
						appointment temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
					else if (arr[j].d.month == arr[j + 1].d.month) {
				
						if (arr[j].d.day > arr[j + 1].d.day) {
						
							appointment temp = arr[j];
							arr[j] = arr[j + 1];
							arr[j + 1] = temp;
						}
					}
				}
			}
		}
}


void mdisplayain() {
	
	ifstream file("clientappointment.txt");
	string junk;
	
	date date1;
	cout << "Enter the date for which to find appointments (DD MM YYYY): ";
	cin >> date1.day >> date1.month >> date1.year;


	string first_name, last_name;
	date appointment_date;
	while (file >> first_name >> last_name >> appointment_date.day >> appointment_date.month
		>> appointment_date.year >> appointment_date.hour >> appointment_date.minute
		>> appointment_date.second) {
		getline(file, junk, '\n');
	
		if (appointment_date.day == date1.day && appointment_date.month == date1.month
			&& appointment_date.year == date1.year) {
			cout << first_name << " " << last_name << " " << appointment_date.hour << ":"
				<< appointment_date.minute << endl;
		}
	}

	
}
int main()
{
	mdisplayain();

	appointment first;
	client user, junk, arr;
	char  num1[2];
	int var, m;
	bool ad;
	int size = 0;
	int size2 = 0;
	appointment date1;




	cout << "1- log in" << "2- sign in" << endl;

	do
	{
		cin >> num1;
	} while (num1[0] != '1' && num1[0] != '2');
	if (num1[0] == '1') {
		while ((login(user) == 0) && num1[0] == '1') {
			cout << "your password or your email is incorrect plz try again or create a new account" << endl;
			cout << "1- log in" << "2- sign in" << endl;
			cin >> num1[0];
			if (num1[0] == '2') {
				break;
			}
		}
	}
	if (num1[0] == '2') {
		signIn(user);

	}

	if (administrator(user))
	{
		do {
			cout << "hello Mr." << user.lastname << endl << "You login as clent" << endl;
			cout << endl << "Accept or Reject the apointment ";
			acceptregect();
			cout << "1-Add appointment" << endl;
			cout << "2-Delete a appointment" << endl;
			cout << "3-Display the appointment" << endl;
			cin >> var;

		} while ((var != 1) && (var != 2) && (var != 3));
		if (var == 1) {
			AddAPP(first);

		}if (var == 2)
		{
			Removeap();
		}if (var == 3)
		{
			mdisplayain();
		}
	}
	else
	{
		cout << "hello Mr." << user.lastname << endl << "You login as user" << endl;
		cin >> var;
		saveappointment(user, m);
		while ((var != 1) && (var != 2) && (var != 3));
		if (var == 1)
		{
			appointmentt(date1, user, m);
		}if (var == 2)
		{
			camcelappointmentt(user, m);
		}
	}




}

