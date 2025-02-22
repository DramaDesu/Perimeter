/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <string>
#include <map>
#include <regex>

// purpose:
// takes the contents of a file in the form of a string
// and searches for all the C++ class definitions, storing
// their locations in a map of strings/int's

typedef std::map<std::string, int, std::less<std::string> > map_type;

regex expression("^(template[[:space:]]*<[^;:{]+>[[:space:]]*)?(class|struct)[[:space:]]*(\\<\\w+\\>([[:blank:]]*\\([^)]*\\))?[[:space:]]*)*(\\<\\w*\\>)[[:space:]]*(<[^;:{]+>[[:space:]]*)?(\\{|:[^;\\{()]*\\{)");

class IndexClassesPred
{
   map_type& m;
   std::string::const_iterator base;
public:
   IndexClassesPred(map_type& a, std::string::const_iterator b) : m(a), base(b) {}
   bool operator()(const reg_match<std::string::const_iterator, regex::alloc_type>& what)
   {
      // what[0] contains the whole string
      // what[5] contains the class name.
      // what[6] contains the template specialisation if any.
      // add class name and position to map:
      m[std::string(what[5].first, what[5].second) + std::string(what[6].first, what[6].second)] = 
               what[5].first - base;
      return true;
   }
};

void IndexClasses(map_type& m, const std::string& file)
{
   std::string::const_iterator start, end;
   start = file.begin();
   end = file.end();
   reg_grep(IndexClassesPred(m, start), start, end, expression, match_default);
}


#include <fileiter.h>
#include <iostream>

using namespace std;

int main(int argc, const char** argv)
{
   for(int i = 1; i < argc; ++i)
   {
      cout << "Processing file " << argv[i] << endl;
      map_type m;
      mapfile f(argv[i]);
      std::string text(f.begin(), f.end());
      IndexClasses(m, text);
      cout << m.size() << " matches found" << endl;
      map_type::iterator c, d;
      c = m.begin();
      d = m.end();
      while(c != d)
      {
         cout << "class \"" << (*c).first << "\" found at index: " << (*c).second << endl;
         ++c;
      }
   }
   return 0;
}





