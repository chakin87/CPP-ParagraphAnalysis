/* 


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
#include <iterator>

using namespace std;

void printForm(string &s);
void tr(string word, int number);
void tr(string s);
void tr(int s);
void toLower(string &s);
string getWord(string &s);
void doIt(string s);
void add100(string &s);
void add1000(string &s);
void add10000(string &s);
int strWordCount(std::string& strString);
void clearStr(std::string& strString);
void dontPush(std::string& strString);



template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
  return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
		 flip_pair<A,B>);
  return dst;
}



int main()
{
  // 
  map<string, int> freq;
  int totalWords;

  /// complete the http header
  cout << "Content-type: text/html\n\n";
  srand(time(0));

  /// build a form object
  HTMLform serverForm;
  serverForm.getPostData(); /// reads the form and inits the object

  /// the output ('name' is in the html form that started this)
  cout << "<html><head><title>";
  cout << "Frequency histogram ";
  cout << "Vers 1";
  cout << "</title></head><body>";
  cout << "<table width='100%'>"; //fullpage

  cout << "<tr><td align='center' colspan='2' >";
  cout << "<h1>Frequency Histogram</h1><hr>"; 
  cout << "</td></tr>";


  string paragraph = serverForm.getField("paragraph");
  string selection = serverForm.getField("selection");


  if (selection == "Add 100 Words") 
    add100(paragraph);
  if (selection == "Add 1000 Words")
	  add1000(paragraph);
  if (selection == "Add 10000 Words")
	  add10000(paragraph);
  if (selection == "Clear Text")
	  clearStr(paragraph);
  if (selection == "DO NOT PUSH!")
	  dontPush(paragraph);

  totalWords = strWordCount(paragraph);

  cout << "<tr><td align='center'>"; //fullpage
  printForm(paragraph);
  cout << "</td>"; //fullpage
 
  cout << "<td align='center' width='30%'>"; //fullpage
  
  /// what we have
  cout << "<table bgcolor='CornflowerBlue' border='3' >";
  cout << "<tr><th>TOP 20</th></tr>";
  cout << "<tr><th>Total Words</th>";
  cout << /*</td>*/"<td align='center'>";
  cout << totalWords;
  cout << "</td></tr>";

  doIt(paragraph);
  cout << "</table>";

  cout << "</td></tr>"; //fullpage
  cout << "</table>";//fullpage
  cout << "</body></html>";//fullpage
  return 0;
}
string getWord(string &s)
{
  int space;
  string retVal;
  space = s.find(" ");
  while (space == 0) {
    s.erase(0, 1);
    space = s.find(" "); 
  }
  if (space != string::npos) {
    retVal = s.substr(0, space);
    s = s.substr(space+1);
  }
  else {
    retVal = s;
    s.clear();
  }
  return retVal;
}

void doIt(string s)
{
	//std::cout << "in doIt(string s) <br />";
  string word;
  map<string, int> freq;
  map<string, int>::iterator it;
  toLower(s);
  while (s.size() > 0) {
    word = getWord(s);
    it = freq.find(word);
    if (it==freq.end())
      freq[word] = 0;
    freq[word]++;
  }
  std::multimap<int, string> dst = flip_map(freq);
  std::multimap<int, string>::reverse_iterator flip_it;
  int count = 0;
  for (flip_it=dst.rbegin(); flip_it!=dst.rend(); ++flip_it)
    {
      tr(flip_it->second, flip_it->first);
      count ++;
      if (count == 20) break;
    }
}

void printForm(string &s)
{
	//std::cout << "in printForm(string& s) <br />";
  cout << "<form method='POST'><table cellpadding='5'>";
  cout << "<tr>";
  cout << "<td align='center'>"; 
  cout << "<p>";
  cout << "Enter paragraph below. ";
  cout << "</p>";
  cout << "</td>";
  cout << "</tr>";

  cout << "<tr>";

  cout << "<td align='center'>";
  cout << "<textarea rows='25' cols='50' name='paragraph'>";
  cout << s;
  cout << "</textarea>";
  cout << "</td>";

  cout << "</tr>";
  cout << "<tr>";
  cout << "<td align='center'>";
  cout << "<input type='submit' name='selection' value='Process Text'/>";
  cout << "<input type='submit' name='selection' value='Add 100 Words'/>";
  cout << "</td>";
  cout << "</tr>";
  cout << "<tr>";
  cout << "<td align='center'>";
  cout << "<input type='submit' name='selection' value='Clear Text'/>";
  cout << "<input type='submit' name='selection' value='Add 1000 Words'/>";
  cout << "</td>";
  cout << "</tr>";
  cout << "<tr>";
  cout << "<td align='center'>";
  cout << "<input type='submit' name='selection' value='DO NOT PUSH!'/>";
  cout << "<input type='submit' name='selection' value='Add 10000 Words'/>";
  cout << "</td>";
  cout << "</tr>";
  cout << "</table></form>";
}

void tr(string s)
{
  cout << "<tr><td align='center'>";
  cout << s;
  cout << "</td><td align='center'>";
  cout << "N/A";
  cout << "</td></tr>";
}

void tr(string word, int number)
{
	//std::cout << "in tr(string word, int number) <br />";
  cout << "<tr><td align='center'>";
  cout << word;
  cout << "</td><td align='center'>";
  cout << number;
  cout << "</td></tr>";
}

void tr(int s)
{
  cout << "<tr><td align='center'>";
  cout << s;
  cout << "</td><td align='center'>";
  cout << "N/A";
  cout << "</td></tr>";
}

void toLower(string &s)
{
  for (int i=0; i<s.size(); i++)
    if ( isupper(s[i]) )
      s[i]=tolower(s[i]);
    else if ( !isalpha(s[i]) && !isspace(s[i])  )
      s.erase(i--, 1);  
}

void add100(string &s)
{
	//std::cout << "in add100() <br />";
  vector<string> words;
  string inputBuffer;
  ifstream wordFile("common1000.txt");
  while ( !wordFile.eof() ) {
    getline(wordFile, inputBuffer);
    words.push_back(inputBuffer);
  }
  wordFile.close();
  for (int i=0;i<100;i++)
    s += " " + words[ rand() % words.size()  ];
 
}

void add1000(string &s)
{
	//std::cout << "in add1000() <br />";
	vector<string> words;
	string inputBuffer;
	ifstream wordFile("common1000.txt");
	while (!wordFile.eof()) {
		getline(wordFile, inputBuffer);
		words.push_back(inputBuffer);
	}
	wordFile.close();
	for (int i = 0; i < 1000; i++)
		s += " " + words[rand() % words.size()];

}

void add10000(string &s)
{
	//std::cout << "in add10000() <br />";
	vector<string> words;
	string inputBuffer;
	ifstream wordFile("common1000.txt");
	while (!wordFile.eof()) {
		getline(wordFile, inputBuffer);
		words.push_back(inputBuffer);
	}
	wordFile.close();
	for (int i = 0; i < 10000; i++)
		s += " " + words[rand() % words.size()];

}

int strWordCount(std::string& strString)
{
	int nSpaces = 0;
	unsigned int i = 0;

	if (strString == "") { return 0; }

	// Skip over spaces at the beginning of the word
	while (isspace(strString.at(i)))
		i++;

	for (; i < strString.length(); i++)
	{
		if (isspace(strString.at(i)))
		{
			nSpaces++;

			// Skip over duplicate spaces & if a NULL character is found, we're at the end of the string
			while (isspace(strString.at(i++)))
				if (strString.at(i) == '\0')
					nSpaces--;
		}
	}

	// The number of words = the number of spaces + 1
	return nSpaces + 1;
}


void clearStr(std::string& strString) {
	//std::cout << "in strClear() <br />";
	strString = "";
}

void dontPush(std::string& strString) {
	//std::cout << "in dontPush() <br />";

	std::string str = "I TOLD YOU NOT TO PUSH THE BUTTON!!!!\n\n\n";

	for (int x = 0; x < 20; ++x) {
		for (int y = 0; y < 55; ++y) {
			switch (x) {
			case 0: {str += "chris "; break; }
			case 1: {str += "chriss "; break; }
			case 2: {str += "chrisss "; break; }
			case 3: {str += "chrissss "; break; }
			case 4: {str += "chrisssss "; break; }
			case 5: {str += "schris "; break; }
			case 6: {str += "sschriss "; break; }
			case 7: {str += "ssschrisss "; break; }
			case 8: {str += "sssschrissss "; break; }
			case 9: {str += "ssschris "; break; }
			case 10: {str += "sschris "; break; }
			case 11: {str += "schris "; break; }
			case 12: {str += "zchrisz "; break; }
			case 13: {str += "chriszz "; break; }
			case 14: {str += "chriszzz "; break; }
			case 15: {str += "chriszzzz "; break; }
			case 16: {str += "chriszzzz "; break; }
			case 17: {str += "chriszzzzz "; break; }
			case 18: {str += "chriszzzzzz "; break; }
			case 19: {str += "chriszzzzzzz "; break; }
			}
		}
	}

	if (strString != "") {
		str += strString;

	}
	
	strString = str;
}