#ifndef _HTMLFORM_H_
#define _HTMLFORM_H_


#include <string>
#include <vector>
#include "namevaluepair.h"

using namespace std;

class HTMLform
{
 public:
   void debug();
   void getPostData();
   string getField(string);
 private:
   int hexToDec(string);
   void processPair(string);
   void urlDecode(string&);
   string m_PostData;

   vector<NameValuePair> m_Pairs;
};

#endif
