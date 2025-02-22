/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE:        recursion_test.cpp
  *   VERSION:     see <boost/version.hpp>
  *   DESCRIPTION: Test for indefinite recursion and/or stack overrun.
  */

#include <string>
#include <boost/regex.hpp>
#include <boost/test/test_tools.hpp>

int test_main( int , char* [] )
{
   std::string bad_text(1024, ' ');
   std::string good_text(200, ' ');
   good_text.append("xyz");

   boost::smatch what;

   boost::regex e1("(.+)+xyz");

   BOOST_CHECK(boost::regex_search(good_text, what, e1));
   BOOST_CHECK_THROW(boost::regex_search(bad_text, what, e1), std::runtime_error);
   BOOST_CHECK(boost::regex_search(good_text, what, e1));

   BOOST_CHECK(boost::regex_match(good_text, what, e1));
   BOOST_CHECK_THROW(boost::regex_match(bad_text, what, e1), std::runtime_error);
   BOOST_CHECK(boost::regex_match(good_text, what, e1));

   boost::regex e2("abc|[[:space:]]+(xyz)?[[:space:]]+xyz");

   BOOST_CHECK(boost::regex_search(good_text, what, e2));
   BOOST_CHECK_THROW(boost::regex_search(bad_text, what, e2), std::runtime_error);
   BOOST_CHECK(boost::regex_search(good_text, what, e2));

   return 0;
}

