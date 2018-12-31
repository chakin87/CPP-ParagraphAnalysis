#include <iostream>
#include <sstream>
#include "htmlform.h"

using namespace std;

void HTMLform::debug()
{
  cout << "<hr />";
  cout << "Version 1 from 9/23/15, written by Ken Urban in class <br/>" << endl;
  cout << "Version 2 from 2/11/16, modified by Ken Urban <br />" << endl;
  cout << "Version 3 from 2/6/18, modified by Ken Urban <br />" << endl;
  cout << "Data in:[" << m_PostData << "] <br/>";
  cout << "<br /><center>Table stored:<br />";
  cout << "<table border='1'>";
  for (int i=0;i<m_Pairs.size();i++)
  {
    cout << "<tr>";
    cout << "<td>[";
    cout << m_Pairs[i].getName(); 
    cout << "]</td>";
    cout << "<td>[";
    cout << m_Pairs[i].getValue(); 
    cout << "]</td>";
    cout << "</tr>";
  }
  cout << "</table></center>";
  cout << "<hr />";
}

void HTMLform::getPostData()
{
  /// read the data from cin (stdin) as defined in the POST method and 
  /// CGI. 
  getline(cin, m_PostData);
  /// store those lines in m_Pairs
  
  /* format:
  name1=value1&name2=value2&name3=value3...
  */

  string postData = m_PostData;
  string firstPair;
  int pos;

  while (postData.length() > 1) /// loop while there's data
  {
    //cout << "Debug: postData [" << postData << "]<br />";
    
    /// find end of the first pair
    pos = postData.find("&");  
    if (pos != string::npos)
    {
      /// found a pair, cut out
      firstPair = postData.substr(0, pos);   
      postData.erase(0, pos+1);

      /// parse the first pair
      processPair(firstPair);
    }
    else 
    {
      /// there was no &, so there's only 1 pair
      processPair(postData);
      postData.clear();
    }
  }

}

/// given a string like name=value, store it
void HTMLform::processPair(string nvpair)
{
  //cout << "Debug: nvpair [" << nvpair << "]<br />";
  NameValuePair temp;
  string first;
  string second;

  int pos = nvpair.find("=");
  first = nvpair.substr(0,pos);
  second = nvpair.substr(pos+1);  /// until the end

  ///  url decode both parts
  //cout << "Debug: first [" << first << "]<br />";
  //cout << "Debug: second [" << second << "]<br />";
  urlDecode(first);
  urlDecode(second);

  //cout << "Debug: decoded first [" << first << "]<br />";
  //cout << "Debug: decoded second [" << second << "]<br />";

  temp.setName(first);
  temp.setValue(second);
  m_Pairs.push_back(temp);
  //cout << "Debug: pairs stored = [" << m_Pairs.size() << "]<br />";
}

int HTMLform::hexToDec(string hex)
{
  std::stringstream ss;
  int decimalValue;
  ss << hex; 
  // use the hex input reader in <iostream>
  ss >> std::hex >> decimalValue;

  return decimalValue;
}

void HTMLform::urlDecode(string &queryString)
{
  /// turn plus signs into spaces and
  /// replace %xx with a single character
  int pos = 0;
  int decimal;
  while ( pos < queryString.size() )   // size() might change!
  {
    switch ( queryString[pos] )   // check each character
      {
      case '+':                   // '+' --> ' '
	queryString[pos]=' ';
	break;
      case '%':                   // '%' found
	// convert 2 characters to an int 
	decimal = hexToDec( queryString.substr(pos+1, 2) );
	// convert the int to it's ASCII char, overwrite the '%'
	queryString[pos] = static_cast<char>(decimal);
	// clean out the hex 
	queryString.erase(pos+1, 2);
	break;
      }
    pos++;
  }
}

string HTMLform::getField(string field)
{
  for (int i=0;i<m_Pairs.size();i++)
  {
    if (m_Pairs[i].getName() == field)
      { 
	return m_Pairs[i].getValue(); 
      }
  }
  return ""; /// what if it's not found?
}


