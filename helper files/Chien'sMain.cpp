/* to use this,
	 - write a form that calls this program with 'action=' in the <form> tag
	 - call getPostData()
	 - use getField(string) to access form information

*/
#include <iostream>
#include "htmlform.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>

void printProgram(string);   /// print the program in HTML
void toLower(string &s);
vector<string> getWords(string Str);
void doIt(string s);
void printDuplicates(vector<string> words);

using namespace std;

/*
struct priorityQueue
{
	string data;
	int countWords;
};
class comparator
{
public:
	bool operator()(const priorityQueue & a, const priorityQueue & b)
	{
		return a.num < b.num;
	}
};
*/


struct priorityQueue
{
	string data;
	int num;
};
class comparator
{
public:
	bool operator()(const priorityQueue & a, const priorityQueue & b)
	{
		return a.num < b.num;
	}
};

int main()
{

	map<string, int> freq;
	/// complete the http header
	cout << "Content-type: text/html\n\n";

	/// build a form object
	HTMLform steps;
	steps.getPostData();

	/// Show the debugging
	cout << "Queue Parser Lab startup" << endl;
	steps.debug();



	/// the entire programs
	string program = steps.getField("program");

	printProgram(program);

	//The next line is for you to complete
	//parseProgram(program);

	return 0;
}

void printProgram(string program)
{
	string Str = program + "\n";
	string words;
	int count = 0;
	vector<string> SS;
	while (!Str.empty())
	{
		SS.push_back(Str.substr(0, Str.find(" ")));
		if (Str.find(" ") > Str.size())
		{
			break;
		}
		else
		{
			Str.erase(0, Str.find(" ") + 1);
		}
	}
	printDuplicates(SS);
}


void printDuplicates(vector<string> words)
{
	int arrNums = words.size();
	priorityQueue arr[arrNums];
	priority_queue<priorityQueue, vector<priorityQueue>, comparator> pq;
	vector<int>nums;
	vector<string>datas;
	int count = 1;
	sort(words.begin(), words.end());
	for (int i = 1; i < words.size(); i++) {
		if (words[i - 1] == words[i]) {
			count++;
			arr[i].num = count;
			arr[i].data = words[i];
			pq.push(arr[i]);
		}
		else {
			count = 1;
			arr[i].num = count;
			arr[i].data = words[i];
			pq.push(arr[i]);
		}
	}

	while (!pq.empty()) {
		nums.push_back(pq.top().num);
		datas.push_back(pq.top().data);
		pq.pop();
	}

	int ID = 0;
	cout << "<table border ='1'>";
	cout << "<th colspan='2'>" << "TOP 20 MOST USED WORDS" << "</th>" << endl;
	for (int i = 0; i < 20; i++) {
		if (nums[i] == 2) {
			cout << "<tr>";
			cout << "<td>" << nums[i] << "</td>" << "<td>" << datas[i] << "</td>" << endl;
			cout << "</tr>";
		}
		else {
			sort(nums.begin(), nums.end());
			sort(datas.begin(), datas.end());
			cout << "<tr>";
			cout << "<td>" << nums[i] << "</td>" << "<td>" << datas[i] << "</td>";
			cout << "<tr>";
		}
	}
	cout << "</table>";
}


void toLower(string &s)
{
	for (int i = 0; i < s.size(); i++)
		if (isupper(s[i]))
			s[i] = tolower(s[i]);
		else if (!isalpha(s[i]) && !isspace(s[i]))
			s.erase(i--, 1);
}