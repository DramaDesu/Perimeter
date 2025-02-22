//-----------------------------------------------------------------------------
// boost-libs variant/test/test5.cpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman, Itay Maman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/test/minimal.hpp"
#include "boost/variant.hpp"

#include "jobs.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>


void run()
{
   using std::string;
   using boost::variant;
   using boost::apply_visitor;

   typedef variant<int, float, unsigned short, unsigned char> t_var1;
   typedef variant<int, t_var1, unsigned short, unsigned char> t_var2;
   typedef variant<string, int, t_var2> t_var3;

   t_var1 v1;
   t_var2 v2;
   t_var2 v2_second;
   t_var3 v3;

   const char c0 = 'x';
   v1 = c0;

   //v2 and v3 are holding (aka: containing) a variant
   v2 = v1;
   v3 = v2;

   verify(v1, spec<int>());
   verify(v2, spec<t_var1>());
   verify(v3, spec<t_var2>());


   //
   // assignment from const char (Converted to int)
   //
   v2 = c0;
   v3 = c0;

   verify(v2, spec<int>());
   verify(v3, spec<int>());


   BOOST_TEST(apply_visitor(sum_int(), v2) == c0);
   BOOST_TEST(apply_visitor(sum_int(), v3) == c0);

   sum_int adder;
   apply_visitor(adder, v2);
   apply_visitor(adder, v3);

   BOOST_TEST(adder.result() == 2*c0);

   //
   // A variant holding a variant
   //
   typedef variant<unsigned char, float> t_var4;
   typedef variant<string, t_var4> t_var5;

   t_var4 v4;
   t_var5 v5;

   v5 = 22.5f;
   verify(v5, spec<t_var4>(), "[V] [V] 22.5");
}



int test_main(int , char* [])
{
   run();
   return 0;
}

