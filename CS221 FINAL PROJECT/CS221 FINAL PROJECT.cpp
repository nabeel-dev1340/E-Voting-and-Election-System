//Hassan Raza 2018146
//Syed Nabeel 2018460
// Samin Asif 2018413
// Haider Ali Shah 2018529
// Election Comission Login user_name: admin , password: admin
// Please don't give spaces while giving input
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <map>
#include <iterator>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
using namespace std;
class Election_Comission_Login
{
public:
	struct Constituency {
		string name;
		Constituency* next;
	};
	struct Political_Party
	{
		string name;
		string symbol;
		string user_name;
		int pass;
		Political_Party* next;
	};
	struct candidate_data {
		string name;
		long long cinic = 0;
		string consituency;
		string symbol;
		string political_party;
		candidate_data* next;
	};
	struct voter_data {
		string name;
		long long cinic = 0;
		int pass;
		string consituency;
		voter_data* next;
	};

	bool delete_symbol(string s);
	bool delete_from_file(fstream& myfile, fstream& temp);
	void Election_Comission_Main_Menu();
	void voter_menu();
	void Candidate_menu();
	void constituency_menu();
	bool Login_check();
};
class Constituencies : public Election_Comission_Login {
public:
	Constituency* head = new Constituency;
	Constituency* tail;
	Constituencies()
	{
		head = NULL;
		tail = head;
	}
	void add();
	void update();
	void remove_();
	void display();
};
class Political_Parties : public Election_Comission_Login
{
public:
	Political_Party* head = new Political_Party;
	Political_Party* tail;
	Political_Parties()
	{
		head->next = NULL;
		tail = head;
	}
	void add_political_party();
	bool check_political_party(string s);
	int generate_pass(string s);
	void create_symbol(Political_Party* newnode);
};
class candidates : public Election_Comission_Login
{
public:
	candidate_data* head = new candidate_data;
	candidate_data* tail;
	candidates()
	{
		head->next = NULL;
		tail = head;
	}
	void add_candidate();
	string assign_symbol(candidate_data* newnode);
	void create_symbol(candidate_data* newnode);
	void delete_candidates();
	void display_candidates();
};
class voters : public Election_Comission_Login {
public:
	voter_data* head = new voter_data;
	voter_data* tail;
	voters()
	{
		head->next = NULL;
		tail = head;
	}
	void add_voter();
	void delete_voter();
	void update_voter_data();
	void update_cinic(fstream& temp, string line);
	void update_name(fstream& temp, string line);
	void update_consituency(fstream& temp, string line);
	void update_password(fstream& temp, string line);
	int update_menu();
	void display_voters();
};
void loading()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLoading..";
	Sleep(2000);
	cout << "..";
	Sleep(200);
	cout << "...." << endl;
	Sleep(100);
	system("CLS");
}
bool Election_Comission_Login::delete_symbol(string s)
{
	bool flag = 0;
	fstream myfile;
	myfile.open("Symbols.txt");
	fstream temp;
	temp.open("temp.txt", ios_base::app);
	string line;
	while (getline(myfile, line))
	{
		if (s == line)
		{
			flag = true;
		}
		else
		{
			temp << line << endl;
		}
	}
	myfile.close();
	temp.close();
	remove("Symbols.txt");
	rename("temp.txt", "Symbols.txt");
	return flag;
}
bool Election_Comission_Login::delete_from_file(fstream& myfile, fstream& temp)
{
	bool flag = 0;
	string s;
	cout << "Enter CINIC To Delete Data: ";
	cin >> s;
	string line;
	while (!myfile.eof())
	{
		getline(myfile, line);
		int i;
		for (i = 0; i < 13; i++)
		{
			if (line[i] != s[i])
			{
				break;
			}
		}
		if (i == 13)
		{
			flag = true;
		}
		else
		{
			temp << line << endl;
		}
	}
	return flag;
}
void Constituencies::add()
{
	Constituency* newnode = new Constituency;
	newnode->next = NULL;
	newnode->next = nullptr;
	cout << "Enter Name of Constituency " << endl;
	cin >> newnode->name;
	tail = newnode;
	fstream myfile;
	myfile.open("Constituency.txt");
	string line;
	bool flag = true;
	while (!myfile.eof())
	{
		getline(myfile, line);
		if (line == newnode->name)
		{
			cout << "Consituency Already Registered\n";
			flag = false;
		}
	}
	myfile.close();
	if (flag == true)
	{
		fstream file;
		file.open("Constituency.txt", ios::app);
		file << newnode->name << endl;
		cout << "Constituency Added\n";
		file.close();
	}
}
void Constituencies::display()
{
	ifstream myfile;
	string line;
	myfile.open("Constituency.txt");
	while (getline(myfile, line))
	{
		cout << line << endl;
	}
	myfile.close();
}
void Constituencies::remove_()
{
	string constituencyName;
	cout << "Enter Constituency Name :";
	cin >> constituencyName;
	ifstream myfile;
	myfile.open("Constituency.txt");
	ofstream temp;
	temp.open("temp.txt", std::ios_base::app);
	string line;
	bool flag = true;
	while (getline(myfile, line))
	{
		if (line == constituencyName)
		{
			flag = false;
			cout << "Constituency Deleted\n";
		}
		else
		{
			temp << line << endl;
		}
	}
	if (flag)
		cout << "Constituency Not Found\n" << endl;
	myfile.close();
	temp.close();
	remove("Constituency.txt");
	rename("temp.txt", "Constituency.txt");
}
void Constituencies::update()
{
	string constituencyName, changeName;
	cout << "Enter Constituency Name :";
	cin >> constituencyName;
	ifstream myfile;
	ofstream temp;
	myfile.open("Constituency.txt");
	temp.open("temp.txt", std::ios_base::app);
	string line;
	bool flag = true;
	while (getline(myfile, line))
	{
		if (line == constituencyName)
		{
			flag = false;
			cout << "Enter New Name :";
			cin >> changeName;
			line = changeName;
			temp << line << endl;
			cout << "Constituency Updated\n";
		}
		else
		{
			temp << line << endl;
		}
	}
	if (flag)
	{
		cout << "Constituency Not Found\n" << endl;
	}
	myfile.close();
	temp.close();
	remove("Constituency.txt");
	rename("temp.txt", "Constituency.txt");

}
void Political_Parties::create_symbol(Political_Party* newnode)
{
	cout << "Choose Political Party Symbol from following: " << endl;
	fstream myfile;
	string line;
	myfile.open("Symbols.txt");
	while (getline(myfile, line))
	{
		cout << line << endl;
	}
	cin >> newnode->symbol;
	myfile.close();
	bool flag = delete_symbol(newnode->symbol);
	if (flag == false)
	{
		cout << "INVALID SYMBOL" << endl;
		create_symbol(newnode);
	}
	return;
}
int Political_Parties::generate_pass(string s)
{
	int b = 1;
	int pass = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		int a = int(s[i]);
		pass = (a * b) + pass;
		b = b * 10;
	}
	return pass;
}
bool Political_Parties::check_political_party(string s)
{
	fstream myfile;
	myfile.open("PoliticalParties.txt");
	string line;
	string line1;
	bool flag = 1;
	while (getline(myfile, line))
	{
		unsigned int i;
		for (i = 0; line[i] != ' ' && i < line.length(); i++)
		{
			line1 = line1 + line[i];
		}
		if (line1 == s)
		{
			flag = 0;
			break;
		}
		line1.clear();
	}
	return flag;
}
void Political_Parties::add_political_party()
{
	Political_Party* newnode = new Political_Party;
	newnode->next = NULL;
	newnode->next = nullptr;
	cout << "Enter Name Of Political Party " << endl;
	cin >> newnode->name;
	if (!check_political_party(newnode->name))
	{
		cout << "***SOME POLITICAL PARTY PARTY HAS BEEN ALREADY REGISTERED WITH THIS NAME***" << endl;
		return;
	}
	create_symbol(newnode);
	newnode->pass = generate_pass(newnode->symbol);
	newnode->user_name = newnode->symbol;
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLogin is being created.";
	Sleep(2000);
	cout << "..";
	Sleep(2000);
	cout << "...." << endl;
	system("CLS");
	cout << "Use Symbol as username" << endl << endl;
	cout << "Your Password is " << newnode->pass << endl;
	tail->next = newnode;
	tail = newnode;
	fstream myfile;
	myfile.open("PoliticalParties.txt", ios_base::app);
	myfile << endl;
	myfile << newnode->name << "       " << newnode->symbol << "       " << newnode->user_name << "       " << newnode->pass;
}
long long enter_cinic()
{
	int flag = 0;
	long long cinic = 0;
	while (flag != 1)
	{
		long long num = 0, count = 0;
		cout << "Enter CINIC of voter (CINIC NO must be 13 digits long)" << endl;
		cin >> cinic;
		num = cinic;
		while (num)
		{
			num = num / 10;
			count++;
		}
		if (count == 13)
		{
			flag = 1;
		}
		else
		{
			cout << "******Invalid CINIC NUMBER******" << endl;
		}
	}
	return cinic;
}
string candidates::assign_symbol(candidate_data* newnode)
{
	cout << "Enter Political Party Name: " << endl;
	cin.ignore();
	cin >> newnode->political_party;
	string s = newnode->political_party;
	bool flag = 0;
	fstream myfile;
	myfile.open("PoliticalParties.txt");
	string line;
	string symbol;
	while (getline(myfile, line))
	{
		int i = 0;
		while (line[i] != ' ')
		{
			if (line[i] == s[i])
			{
				flag = 1;
				i++;
				continue;
			}
			else
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (flag == 0)
	{
		cout << "*****Your Political Party Is Not Registered*****" << endl;
		assign_symbol(newnode);
	}
	else
	{
		unsigned int i;
		int count = 0;
		for (i = 0; i < line.length(); i++)
		{
			if (count == 7)
			{
				break;
			}
			else if (line[i] == ' ')
			{
				count++;
				continue;
			}
			count = 0;
		}
		for (; i < line.length(); i++)
		{
			if (line[i] == ' ')
			{
				break;
			}
			symbol = symbol + line[i];
		}
	}
	return symbol;
}
void candidates::create_symbol(candidate_data* newnode)
{
	cout << "Choose Political Party Symbol from following: " << endl;
	fstream myfile;
	string line;
	myfile.open("Symbols.txt");
	while (getline(myfile, line))
	{
		cout << line << endl;
	}
	cin >> newnode->symbol;
	myfile.close();
	bool flag = delete_symbol(newnode->symbol);
	if (flag == false)
	{
		cout << "INVALID SYMBOL" << endl;
		create_symbol(newnode);
	}
	return;
}
void candidates::display_candidates()
{
	fstream myfile;
	myfile.open("Candidate.txt");
	string line;
	while (getline(myfile, line))
	{
		cout << line << endl;
	}
}
string enter_consituency()
{
	bool flag = 0;
	string s;
	do {
		fstream myfile;
		myfile.open("Constituency.txt");
		string line;
		cout << "Enter Consituency: " << endl;
		cin >> s;
		while (getline(myfile, line))
		{
			if (s == line)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			cout << "*****THIS CONSTITUENCY IS NOT REGISTERED*****" << endl;
		}
	} while (flag != 1);
	return s;
}
void candidates::add_candidate()
{
	int choice;
	cout << "1.Register Political Party Candidate" << endl;
	cout << "2.Register Independent Candidate" << endl;
	cin >> choice;
	candidate_data* newnode = new candidate_data;
	newnode->next = NULL;
	newnode->next = nullptr;
	cout << "Enter name of Candidate " << endl;
	cin >> newnode->name;
	newnode->cinic = enter_cinic();
	tail->next = newnode;
	newnode->consituency = enter_consituency();
	if (choice == 1)
	{
		newnode->symbol = assign_symbol(newnode);
		fstream myfile;
		myfile.open("CandidateRequest.txt", ios_base::app);
		myfile << newnode->cinic << "       " << newnode->name << "       " << newnode->political_party << "       " << newnode->symbol;
		myfile << "       " << newnode->consituency << endl;
		cout << "****************REQUEST SENT TO YOUR POLITICAL PARTY******************" << endl;
	}
	else if (choice == 2)
	{
		newnode->political_party = "Independent Candidate";
		create_symbol(newnode);
		fstream myfile;
		myfile.open("Candidate.txt", ios_base::app);
		myfile << endl;
		myfile << newnode->cinic << "       " << newnode->name << "       " << newnode->political_party << "       " << newnode->symbol;
		myfile << "       " << newnode->consituency;
		cout << "****************INDEPENDENT CANDIDATE REGISTERED******************" << endl;
	}
	tail = newnode;
}
void candidates::delete_candidates()
{
	fstream myfile;
	myfile.open("Candidate.txt");
	fstream temp;
	temp.open("temp.txt", ios_base::app);
	string line;
	bool flag = delete_from_file(myfile, temp);
	if (flag == 0)
		cout << "***NOT FOUND***" << endl;
	myfile.close();
	temp.close();
	remove("Candidate.txt");
	rename("temp.txt", "Candidate.txt");
}
int generate_pass(long long num)
{
	int count = 0, pass = 0;
	while (count != 4)
	{
		int digit = num % 10;
		pass = (pass * 10) + digit;
		num = num / 10;
		count++;
	}
	return pass;
}
bool check_cinic(string cinic)
{
	fstream myfile;
	myfile.open("Voter.txt");
	string line;
	bool flag = 0;
	while (getline(myfile, line))
	{
		int i;
		for (i = 0; i < 13; i++)
		{
			if (line[i] != cinic[i])
			{
				flag = 1;
				break;
			}
		}
		if (i == 13)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
void voters::add_voter()
{
	voter_data* newnode = new voter_data;
	newnode->next = NULL;
	newnode->next = nullptr;
	cout << "Enter name of voter " << endl;
	cin >> newnode->name;
	newnode->consituency = enter_consituency();
	newnode->cinic = enter_cinic();
	ostringstream str1;
	str1 << newnode->cinic;
	string cinic = str1.str();
	if (check_cinic(cinic) == false)
	{
		cout << "VOTER IS ALREADY REGISTERED";
		return;
	}
	newnode->pass = generate_pass(newnode->cinic);
	cout << endl << "Your password is: " << newnode->pass << endl << endl;
	tail->next = newnode;
	tail = newnode;
	fstream myfile;
	myfile.open("Voter.txt", ios_base::app);
	myfile << newnode->cinic << "       " << newnode->name << "       " << newnode->consituency << "       " << newnode->pass << endl;
}
void voters::delete_voter()
{
	fstream myfile;
	myfile.open("Voter.txt");
	fstream temp;
	temp.open("temp.txt", ios_base::app);
	string line;
	bool flag = delete_from_file(myfile, temp);
	if (flag == 0)
		cout << "***NOT FOUND***" << endl;
	myfile.close();
	temp.close();
	remove("Voter.txt");
	rename("temp.txt", "Voter.txt");
}
void voters::update_cinic(fstream& temp, string line)
{
	long long cinic;
	cinic = enter_cinic();
	ostringstream str1;
	str1 << cinic;
	string cinic1 = str1.str();
	if (check_cinic(cinic1) == false)
	{
		cout << "VOTER IS ALREADY REGISTERED";
		temp << line;
		return;
	}
	temp << cinic;
	for (unsigned int i = 13; i < line.length(); i++)
	{
		temp << line[i];
	}
}
void voters::update_name(fstream& temp, string line)
{
	string name;
	int count = 0;
	unsigned int i;
	cout << "Enter name: " << endl;
	cin >> name;
	for (i = 0; i < 13; i++)
	{
		temp << line[i];
	}
	temp << "       ";
	temp << name;
	for (i = 19; i < line.length(); i++)
	{
		if (count == 7)
		{
			break;
		}
		if (line[i] == ' ')
		{
			count++;
			continue;
		}
		count = 0;
	}
	temp << "       ";
	for (; i < line.length(); i++)
	{
		temp << line[i];
	}
}
void voters::update_consituency(fstream& temp, string line)
{
	string s;
	unsigned int i = 0;
	int count = 0;
	s = enter_consituency();
	for (i = 0; i < 20; i++)
	{
		temp << line[i];
	}
	for (i = 19; i < line.length(); i++)
	{
		if (count == 7)
		{
			break;
		}
		else if (line[i] == ' ')
		{
			count++;
			continue;
		}
		else
		{
			temp << line[i];
		}
		count = 0;
	}
	temp << "       ";
	temp << s;
	for (i = i + 6; i < line.length(); i++)
	{
		if (count == 7)
		{
			break;
		}
		else if (line[i] == ' ')
		{
			count++;
			continue;
		}
		count = 0;
	}
	for (; i < line.length(); i++)
	{
		temp << line[i];
	}
}
void voters::update_password(fstream& temp, string line)
{
	int pass;
	cout << "Enter Password: " << endl;
	cin >> pass;
	for (unsigned int i = 0; i < line.length() - 4; i++)
	{
		temp << line[i];
	}
	temp << pass;
}
int voters::update_menu()
{
	int choice;
	cout << "1. Update CINIC" << endl;
	cout << "2. Update Name " << endl;
	cout << "3.Update constituency" << endl;
	cout << "4. Update Password" << endl;
	cin >> choice;
	return choice;
}
void voters::update_voter_data()
{
	string cinic;
	int flag = 0;
	cout << "Enter CINIC of voter to update his data: " << endl;
	cin >> cinic;
	fstream myfile;
	myfile.open("Voter.txt");
	string line;
	fstream temp;
	temp.open("temp.txt", ios_base::app);
	int i;
	while (getline(myfile, line))
	{
		for (i = 0; i < 13; i++)
		{
			if (line[i] != cinic[i])
			{
				break;
			}
		}
		if (i == 13)
		{
			flag = 1;
			break;
		}
		else
		{
			temp << line << endl;
		}
	}
	if (flag != 1)
	{
		cout << "*** NOT FOUND***" << endl;
		remove("temp.txt");
	}
	else
	{
		int choice = update_menu();
		switch (choice)
		{
		case 1:
		{
			update_cinic(temp, line);
			break;
		}
		case 2:
		{
			update_name(temp, line);
			break;
		}
		case 3:
		{
			update_consituency(temp, line);
			break;
		}
		case 4:
		{	update_password(temp, line);
		break;
		}
		default:
			cout << "***INVALID ENTRY***";
			break;
		}
		temp << endl;
		while (getline(myfile, line))
		{
			temp << line << endl;
		}
		myfile.close();
		remove("Voter.txt");
		temp.close();
		rename("temp.txt", "Voter.txt");
	}
}
void voters::display_voters()
{
	fstream myfile;
	myfile.open("Voter.txt");
	string line;
	while (getline(myfile, line))
	{
		cout << line << endl;
	}
}
void Election_Comission_Login::constituency_menu()
{
	int choice = 0;
	do {
		Constituencies c;
		cout << "\t\t\t\t***ELECTION COMISSION LOGIN***\n" << endl;
		cout << "\n\n\n\t\t\t\t1.Add New Constituency\n" << endl;
		cout << "\t\t\t\t2.Delete Constituency \n" << endl;
		cout << "\t\t\t\t3.Update Constituency \n" << endl;
		cout << "\t\t\t\t4.Display all Constituencies \n" << endl;
		cout << "\t\t\t\t5.BACK \n" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			c.add();
			break;
		}
		case 2:
		{
			c.remove_();
			break;
		}
		case 3:
		{
			c.update();
			break;
		}
		case 4:
			c.display();
			break;
		case 5:
			loading();
			break;
		}
	} while (choice != 5);
}
void Election_Comission_Login::Candidate_menu()
{
	int choice = 0;
	do {
		candidates C;
		cout << "\n\n\n\t\t\t\t1. Add Candidate\n" << endl;
		cout << "\t\t\t\t2. Delete Candidate\n" << endl;
		cout << "\t\t\t\t3. Display all Candidates\n" << endl;
		cout << "\t\t\t\t4. Back\n" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			C.add_candidate();
			break;
		}
		case 2:
		{
			C.delete_candidates();
			break;
		}
		case 3:
		{
			C.display_candidates();
			break;
		}
		case 4:
			loading();
			break;
		}
	} while (choice != 4);
}
void Election_Comission_Login::voter_menu()
{

	int choice = 0;
	do {
		voters V;
		cout << "\n\n\n\t\t\t\t1.Add Voter Data\n" << endl;
		cout << "\t\t\t\t2.Delete Voter Data\n" << endl;
		cout << "\t\t\t\t3.Update Voter Data\n" << endl;
		cout << "\t\t\t\t4.Display Voter Data\n" << endl;
		cout << "\t\t\t\t5.Back" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			V.add_voter();
			break;
		case 2:
			V.delete_voter();
			break;
		case 3:
			V.update_voter_data();
			break;
		case 4:
			V.display_voters();
			break;
		case 5:
			loading();
			break;
		}
	} while (choice != 5);
}
map <string, int> creating_map()
{
	fstream myfile;
	myfile.open("ResultPartyWise.txt");
	string line;
	string p;
	string score;
	int scores;
	map <string, int> party;
	while (getline(myfile, line))
	{
		unsigned int i;
		for (i = 0; line[i] != ' ' && i < line.length(); i++)
		{
			p = p + line[i];
		}
		for (i = i + 7; i < line.length(); i++)
		{
			score = score + line[i];
		}
		stringstream s(score);
		s >> scores;
		party.insert(pair<string, int>(p, scores));
		p.clear();
		score.clear();
	}
	myfile.close();
	return party;
}
void political_wise_result()
{
	map<string, int> party;
	party = creating_map();
	fstream myfile;
	myfile.open("Results.txt");
	fstream temp;
	temp.open("temp.txt", ios::app);
	fstream file;
	file.open("ResultPartyWise.txt");
	string line;
	string p;
	string score;
	while (getline(myfile, line))
	{
		unsigned int i;
		for (i = 0; line[i] != ' ' && i < line.length(); i++)
		{
			score = score + line[i];
		}
		i = i + 7;
		while (line[i] != ' ')
		{
			i++;
		}
		for (i = i + 7; line[i] != ' ' && i < line.length(); i++)
		{
			p = p + line[i];
		}
		stringstream s(score);
		int scores = 0;
		s >> scores;
		auto itr = party.find(p);
		if (itr != party.end())
		{
			itr->second = 0;
			itr->second = scores + itr->second;
		}
		else
			party.insert(pair<string, int>(p, scores));
		score.clear();
		p.clear();
	}
	map<string, int>::iterator itr;
	for (itr = party.begin(); itr != party.end(); ++itr) {
		temp << itr->first << "       " << itr->second << endl;
	}
	myfile.close();
	temp.close();
	file.close();
	remove("ResultPartyWise.txt");
	rename("temp.txt", "ResultPartyWise.txt");
}
void show_results()
{
	fstream myfile;
	fstream file;
	string line;
	myfile.open("Results.txt");
	file.open("ResultPartyWise.txt");
	if (myfile.peek() == std::ifstream::traits_type::eof()) // Checking if file is empty
	{
		cout << "ELECTIONS HAVE NOT TAKEN PLACE TILL NOW" << endl;
	}
	else
	{
		while (getline(myfile, line))
		{

			cout << line << endl << endl;
		}
		//cout << "\n\n\n\n\n\n";
		while (!file.eof())
		{
			getline(file, line);
			cout << "\t\t\t\t\t\t\t\t\t" << line << endl << endl;
		}
	}
	myfile.close();
}
void show_results_constituency()
{
	string s;
	cout << "Enter Consituency: ";
	cin >> s;
	fstream myfile;
	myfile.open("Results.txt");
	string line;
	string p;
	bool flag = 0;
	if (myfile.peek() == std::ifstream::traits_type::eof()) // Checking if file is empty
	{
		cout << "ELECTIONS HAVE NOT TAKEN PLACE TILL NOW" << endl;
		return;
	}
	while (getline(myfile, line))
	{
		unsigned int i = 0;
		for (i = line.length() - 1; i >= 0 && line[i] != ' '; i--)
		{
		}
		for (i = i + 1; i < line.length(); i++)
		{
			p = p + line[i];
		}
		if (s == p)
		{
			cout << line << endl;
			flag = 1;
		}
		p.clear();
	}
	if (flag == 0)
		cout << "***INVALID ENTRY****" << endl;
	myfile.close();
}
void show_results_menu()
{
	int choice = 0;
	do {
		cout << "\n\n\n\t\t\t\t1.Show All Over Results\n" << endl;
		cout << "\t\t\t\t2.Show Results of Specific Consituency\n" << endl;
		cout << "\t\t\t\t3.Back\n" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			show_results();
			break;
		}
		case 2:
		{
			show_results_constituency();
			break;
		}
		case 3:
		{
			loading();
			break;
		}
		}
	} while (choice != 3);
}
void Election_Comission_Login::Election_Comission_Main_Menu()
{
	int choice = 0;
	do {
		Political_Parties P;
		cout << "\t\t\t\t***ELECTION COMISSION LOGIN***\n" << endl;
		cout << "\n\n\n\t\t\t\t1. UPDATE/DISPLAY CONSTITUENCY DATA-BASE\n" << endl;
		cout << "\t\t\t\t2. REGISTER A NEW POLITICAL PARTY\n" << endl;
		cout << "\t\t\t\t3. ADD NEW CANDIDATES FOR ELECTION\n" << endl;
		cout << "\t\t\t\t4. ADD/DELETE/UPDATE NEW VOTERS\n" << endl;
		cout << "\t\t\t\t5. SHOW RESULTS\n" << endl;
		cout << "\t\t\t\t6. BACK" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			constituency_menu();
			break;
		}
		case 2:
		{
			P.add_political_party();
			break;
		}
		case 3:
		{
			Candidate_menu();
			break;
		}
		case 4:
		{
			voter_menu();
			break;
		}
		case 5:
		{
			show_results_menu();
			break;
		}
		case 6:
			loading();
		}
	} while (choice != 6);
}
bool Election_Comission_Login::Login_check()
{
	string user_name;
	string password;
	bool flag = 1;
	cout << "\n\n\t\t\t\t\t**********ELECTION COMISSION LOGIN***********" << endl;
	cout << "\n\n\n\n\n\n\t\t\t\t\tEnter User Name: ";
	cin >> user_name;
	cout << "\n\n \t\t\t\t\tEnter Password: ";
	cin >> password;
	if (user_name != "admin" || password != "admin")
	{
		cout << "\n\n\n\t\t**************INVALID PASSWORD OR USER_NAME*******************" << endl;
		flag = 0;
	}
	return flag;
}
class Political_Party_Login
{
public:
	string name;
	string user_name;
	string password;
	bool show_party_requests();
	void accept_party_requests();
	bool login_check();
	void Political_Party_Login_Menu();
};
bool Political_Party_Login::login_check()
{
	cout << "\n\n\t\t\t\t\t**********POLITICAL-PARTY LOGIN***********" << endl;
	cout << "\n\n\n\n\n\n\t\t\t\t\tEnter User Name: ";
	cin >> user_name;
	cout << "\n\n \t\t\t\t\tEnter Password: ";
	cin >> password;
	fstream myfile;
	myfile.open("PoliticalParties.txt");
	string line;
	string s;
	string p;
	bool flag = 0;
	while (getline(myfile, line))
	{
		unsigned int i = 0;
		for (; i < line.length() && line[i] != ' '; i++)
		{
			name = name + line[i];
		}
		for (i = i + 7; i < line.length(), line[i] != ' '; i++)
		{
			s = s + line[i];
		}
		if (s == user_name)
		{
			flag = 1;
			for (i = line.length() - 1; line[i] != ' ' && i >= 0; i--) {}
			for (i = i + 1; i < line.length(); i++)
			{
				p = p + line[i];
			}
			if (p != password)
			{
				flag = 0;
			}
			break;
		}
		else
		{
			flag = 0;
			name.clear();
		}
		s.clear();
		p.clear();
	}
	if (flag == 0)
	{
		cout << "***INVALID USERNAME OR PASSWORD***" << endl;
	}
	return flag;
}
bool Political_Party_Login::show_party_requests()
{
	fstream myfile;
	myfile.open("CandidateRequest.txt");
	string line;
	string s;
	string p;
	bool flag = 0;
	while (getline(myfile, line))
	{
		unsigned int i;
		for (i = 20; i < line.length() && line[i] != ' '; i++)
		{
			//cout << line[i];
		}
		for (i = i + 7; i < line.length() && line[i] != ' '; i++)
		{
			p = p + line[i];
		}
		if (p == name)
		{
			flag = 1;
			cout << line << endl;
		}
		p.clear();
	}
	return flag;
}
void Political_Party_Login::accept_party_requests()
{
	bool flag3 = show_party_requests();
	if (flag3 == false)
	{
		cout << "\n\n************YOU HAVE NO REQUESTS**************" << endl << endl << endl;
		system("PAUSE");
		return;
	}
	fstream myfile;
	myfile.open("CandidateRequest.txt");
	fstream temp;
	temp.open("temp.txt", ios_base::app);
	string line;
	bool flag = false;
	string s;
	string candidate;
	cout << "Enter CINIC Of Candidate: ";
	cin >> s;
	while (getline(myfile, line))
	{
		int i;
		for (i = 0; i < 13; i++)
		{
			if (line[i] != s[i])
			{
				break;
			}
		}
		if (i == 13)
		{
			flag = true;
			candidate = line;
			break;
		}
		else
		{
			temp << line << endl;
		}
	}
	if (flag == false && myfile.eof())
		cout << "****INVALID ENTRY****" << endl;
	else
	{
		int a;
		cout << "1.Accept" << endl;
		cout << "2. Reject" << endl;
		cin >> a;
		if (a == 1)
		{
			fstream myfile;
			myfile.open("Candidate.txt", ios::app);
			myfile << endl;
			myfile << candidate;
		}
	}
	while (getline(myfile, line))
	{
		temp << line << endl;
	}
	myfile.close();
	temp.close();
	remove("CandidateRequest.txt");
	rename("temp.txt", "CandidateRequest.txt");
}
void Political_Party_Login::Political_Party_Login_Menu()
{
	int choice = 0;
	do {
		cout << "\t\t\t\t***POLITICAL PARTY LOGIN***\n" << endl;
		cout << "\n\n\n\t\t\t\t1. ACCEPT/REJECT CANDIDATE TICKET REQUEST\n" << endl;
		cout << "\t\t\t\t2.SHOW RESULTS\n" << endl;
		cout << "\t\t\t\t3. BACK" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			accept_party_requests();
			break;
		case 2:
			show_results_menu();
			break;
		case 3:
			loading();
			name.clear();
			user_name.clear();
			password.clear();
			break;
		}
	} while (choice != 3);
}
class Voter_Login
{
public:
	string cinic;
	string pass;
	string consituency;
	string name;
	bool cast_flag;
	void voter_login_menu();
	bool Login_check();
	bool show_candidates();
	void CastVote();
	void result_update(char a, string s);
	bool check_IN_results();
	void show_all_candidates();
	void show_candidates_symbol(string* array, int k);
};
bool  Voter_Login::Login_check()
{

	cout << "\n\n\t\t\t\t\t**********VOTERS LOGIN***********" << endl;
	cout << "\n\n\n\n\n\n\t\t\t\t\tEnter CINIC: ";
	cin >> cinic;
	cout << "\n\n \t\t\t\t\tEnter Password: ";
	cin >> pass;
	fstream myfile;
	myfile.open("Voter.txt");
	string line;
	bool flag = 0;
	while (getline(myfile, line))
	{
		int i;
		for (i = 0; i < 13; i++)
		{
			if (line[i] != cinic[i])
			{
				break;
			}
		}
		if (i == 13)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "***INVALID CINIC***" << endl;
	}
	else if (pass.length() > 4)
	{
		cout << "****INVALID PASSWORD****" << endl;
		flag = 0;
	}
	else
	{
		for (unsigned int i = line.length() - 4, j = 0; i < line.length(); i++, j++)
		{
			if (line[i] != pass[j])
			{
				cout << "****INVALID PASSWORD****" << endl;
				flag = 0;
				break;
			}
		}
	}
	if (flag == 1)
	{
		int count = 0;
		unsigned int i;
		for (i = 19; i < line.length(); i++)
		{
			if (count == 7)
			{
				break;
			}
			else if (line[i] == ' ')
			{
				count++;
				continue;
			}
			else
			{
				name = name + line[i];
			}
			count = 0;
		}
		for (; i < line.length() - 11; i++)
		{
			consituency = consituency + line[i];
		}
	}
	return flag;
}
bool Voter_Login::check_IN_results()
{
	fstream myfile;
	fstream temp;
	myfile.open("Results.txt");
	if (myfile.peek() == std::ifstream::traits_type::eof()) // Checking if file is empty
	{
		return 0;
	}
	string line;
	string s;
	bool flag = false;
	while (getline(myfile, line))
	{
		unsigned int i;
		for (i = line.length() - 1; i >= 0; i--)
		{
			if (line[i] == ' ')
				break;
		}
		i = i + 1;
		for (; i < line.length(); i++)
		{
			s = s + line[i];
		}
		if (s == consituency)
		{
			flag = true;
			break;
		}
		s.clear();
	}
	return flag;
}
bool  Voter_Login::show_candidates()
{
	fstream myfile;
	fstream temp;
	bool flag_ = false;
	myfile.open("Candidate.txt");
	temp.open("Results.txt", ios_base::app);
	string line;
	bool flag = 0;
	unsigned int i, j;
	bool flag1 = check_IN_results();
	while (!myfile.eof())
	{
		getline(myfile, line);
		string s;
		flag = 1;
		for (i = line.length() - 1; ; i--)
		{
			if (line[i] == ' ')
			{
				break;
			}
		}
		j = i;
		int k = 0;
		for (i = i + 1; i < line.length(); i++, k++)
		{
			if (line[i] != consituency[k])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			flag_ = 1;
			for (unsigned int i = 20; i < line.length(); i++)
			{
				cout << line[i];
			}
			cout << endl;
			if (flag1 == false)
			{
				temp << "0       ";
				for (unsigned int i = 20; i < line.length(); i++)
				{
					temp << line[i];
				}
				temp << endl;
			}
		}
	}
	myfile.close();
	temp.close();
	return flag_;
}
void Voter_Login::result_update(char a, string s)
{
	fstream myfile;
	myfile.open("Results.txt");
	fstream temp;
	temp.open("temp.txt", ios::app);
	string line;
	while (getline(myfile, line))
	{
		if (line == s)
		{
			temp << a;
			unsigned int i;
			for (i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					break;
				}
			}
			for (; i < line.length(); i++)
			{
				temp << line[i];
			}
			temp << endl;
		}
		else
		{
			temp << line << endl;
		}
	}
	myfile.close();
	remove("Results.txt");
	temp.close();
	rename("temp.txt", "Results.txt");
}
void Voter_Login::CastVote()
{
	string s;
	if (cast_flag == 1)
	{
		cout << "\n\n\t\t****YOU HAVE ALREADY CASTED VOTE********";
		cout << "\n\n\t\t****THANK YOU*****\n\n\n";
		return;
	}
	if (show_candidates() == 0)
	{
		cout << endl << endl << "***NO CANDIDATES IN YOUR CONSTITUENCY***" << endl << endl;
		return;
	}
	cout << "Enter Symbol: ";
	cin >> s;
	fstream myfile;
	myfile.open("Results.txt");
	string line;
	unsigned int i;
	bool flag = 1;
	while (getline(myfile, line))
	{
		bool flag1 = 1;
		for (i = line.length() - 1; i >= 0; i--)
		{
			if (line[i] == ' ')
			{
				break;
			}
		}
		for (unsigned int j = i + 1, k = 0; j < line.length(); j++, k++)
		{
			if (line[j] != consituency[k])
			{
				flag1 = 0;
				break;
			}
		}
		if (flag1 == 1)
		{
			i = i - 7;
			for (; i >= 0; i--)
			{
				if (line[i] == ' ')
				{
					break;
				}
			}
			i = i + 1;
			flag = 1;
			for (int j = 0; line[i] != ' '; i++, j++)
			{

				if (line[i] != s[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				char a = line[0];
				a = a + 1;
				myfile.close();
				result_update(a, line);
				cout << "\n\n\n\n\t\t\tThank you   " << name << "    for casting vote\n\n\n";
				cast_flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		cout << "********INVALID ENTRY******" << endl;
	}
	myfile.close();
	political_wise_result();
}
void merge(string* array, int mid, int low, int high)
{

	int i, j, k;
	int n1 = mid - low + 1;
	int n2 = high - mid;

	/* create temp arrays */
	string* L = new string[n1];
	string* R = new string[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = array[low + i];
	for (j = 0; j < n2; j++)
		R[j] = array[mid + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = low; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		array[k] = L[i];
		i++;
		k++;
	}

	/*Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		array[k] = R[j];
		j++;
		k++;
	}
}
void merge_sort(string* array, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		merge_sort(array, low, mid);
		merge_sort(array, mid + 1, high);
		merge(array, mid, low, high);
	}
	else
		return;
}
void Voter_Login::show_candidates_symbol(string* array, int k)
{
	for (int j = 0; j < k; j++)
	{
		fstream myfile;
		myfile.open("Candidate.txt");
		string line;
		string symbol;
		while (getline(myfile, line))
		{
			unsigned int i;
			for (i = line.length() - 1; i >= 0 && line[i] != ' '; i--)
			{
			}
			for (i = i - 7; i < line.length() && line[i] != ' '; i--)
			{
				//cout << line[i]<< endl;
			}
			for (i = i + 1; i < line.length() && line[i] != ' '; i++)
			{
				symbol = symbol + line[i];
			}
			if (array[j] == symbol)
			{
				cout << line << endl;
				symbol.clear();
				break;
			}
			symbol.clear();
		}
	}
}
void Voter_Login::show_all_candidates()
{
	fstream myfile;
	myfile.open("Candidate.txt");
	string line;
	int N = 100;
	string* array = new string[N];
	string symbol;
	int k = 0;
	while (!myfile.eof())
	{
		getline(myfile, line);
		unsigned int i;
		for (i = line.length() - 1; i >= 0 && line[i] != ' '; i--)
		{
		}
		for (i = i - 7; i < line.length() && line[i] != ' '; i--)
		{
			//cout << line[i]<< endl;
		}
		for (i = i + 1; i < line.length() && line[i] != ' '; i++)
		{
			symbol = symbol + line[i];
		}
		array[k] = symbol;
		symbol.clear();
		k++;
		N++;
	}
	myfile.close();
	int choice;
	cout << "1. Show all Candidates In Sorted Order Of Symbol" << endl;
	cout << "2. Show all Candidates In Random Order Of Symbol" << endl;
	cin >> choice;
	if (choice == 1)
	{
		merge_sort(array, 0, k - 1);
		show_candidates_symbol(array, k);
		delete[] array;
	}
	else if (choice == 2)
	{
		myfile.open("Candidate.txt");
		while (!myfile.eof())
		{
			getline(myfile, line);
			cout << line << endl;
		}
	}
	else
		cout << "****INVALID ENTRY******" << endl;
}
void Voter_Login::voter_login_menu()
{
	int choice = 0;
	do {
		cout << "\t\t\t\t***VOTER LOGIN***\n" << endl;
		cout << "\n\n\n\t\t\t\t1. SHOW ALL CANDIDATES\n" << endl;
		cout << "\t\t\t\t2.CAST VOTE\n" << endl;
		cout << "\t\t\t\t3. BACK" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			show_all_candidates();
			break;
		}
		case 2:
		{
			CastVote();
			break;
		}
		case 3:
		{
			loading();
			system("CLS");
			break;
		}
		}
	} while (choice != 3);
}
int main()
{
	int choice = 0;
	do {
		Political_Party_Login P;
		Election_Comission_Login E;
		Voter_Login V;
		cout << "\t\t\t\t********WELCOME TO ELECTION MANAGEMENT SYSTEM*********\n" << endl;
		cout << "\n\n\n\t\t\t\t1.ELECTION COMISSION LOGIN\n" << endl;
		cout << "\t\t\t\t2.POLITICAL PARTY LOGIN\n" << endl;
		cout << "\t\t\t\t3.VOTER LOGIN\n" << endl;
		cout << "\t\t\t\t4.EXIT\n" << endl;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			bool flag = E.Login_check();
			if (flag == true)
			{
				system("CLS");
				E.Election_Comission_Main_Menu();
			}
			break;
		}
		case 2:
		{
			bool flag = P.login_check();
			if (flag == true)
			{
				system("CLS");
				P.Political_Party_Login_Menu();
			}
			break;
		}
		case 3:
		{
			bool flag = V.Login_check();
			if (flag == true)
			{
				system("CLS");
				V.voter_login_menu();
			}
			break;
		}
		case 4:
			loading();
			system("CLS");
			break;

		}
		system("PAUSE");
		system("CLS");
	} while (choice != 4);
}