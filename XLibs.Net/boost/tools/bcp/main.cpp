/*
 *
 * Copyright (c) 2003 Dr John Maddock
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * This file implements the cpp_main entry point
 */


#include <iostream>
#include <cstring>
#include <boost/filesystem/path.hpp>
#include "bcp.hpp"

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{
   using ::strcmp;
   using ::strncmp;
}
#endif

void show_usage()
{
   std::cout <<
      "Usage:\n"
      "   bcp --list [options] module-list\n"
      "   bcp --report [options] module-list html-file\n"
      "   bcp [options] module-list output-path\n"
      "\n"
      "Options:\n"
      "   --boost=path   sets the location of the boost tree to path\n"
      "   --scan         treat the module list as a list of (possibly non-boost)\n" 
      "                  files to scan for boost dependencies\n"
      "   --cvs          only copy files under cvs version control\n"
      "   --unix-lines   make sure that all copied files use Unix style line endings\n"
      "\n"
      "module-list:      a list of boost files or library names to copy\n"
      "html-file:        the name of a html file to which the report will be written\n"
      "output-path:      the path to which files will be copied\n";
}

bool filesystem_name_check( const std::string & name )
{
   return true;
}

int cpp_main(int argc, char* argv[])
{
   //
   // Before anything else replace Boost.filesystem's file
   // name checker with one that does nothing (we only deal
   // with files that already exist, if they're not portable
   // names it's too late for us to do anything about it).
   //
   boost::filesystem::path::default_name_check(filesystem_name_check);
   //
   // without arguments just show help:
   //
   if(argc < 2)
   {
      show_usage();
      return 0;
   }
   //
   // create the application object:
   //
   pbcp_application papp(bcp_application::create());
   //
   // work through args, and tell the application
   // object what ir needs to do:
   //
   bool list_mode = false;
   for(int i = 1; i < argc; ++i)
   {
      if(0 == std::strcmp("-h", argv[i])
         || 0 == std::strcmp("--help", argv[i]))
      {
         show_usage();
         return 0;
      }
      else if(0 == std::strcmp("--list", argv[i]))
      {
         list_mode = true;
         papp->enable_list_mode();
      }
      else if(0 == std::strcmp("--report", argv[i]))
      {
         papp->enable_licence_mode();
      }
      else if(0 == std::strcmp("--cvs", argv[i]))
      {
         papp->enable_cvs_mode();
      }
      else if(0 == std::strcmp("--scan", argv[i]))
      {
         papp->enable_scan_mode();
      }
      else if(0 == std::strcmp("--unix-lines", argv[i]))
      {
         papp->enable_unix_lines();
      }
      else if(0 == std::strncmp("--boost=", argv[i], 8))
      {
         papp->set_boost_path(argv[i] + 8);
      }
      else if(argv[i][0] == '-')
      {
         show_usage();
         return 1;
      }
      else
      {
         if(!list_mode && (i == argc - 1))
            papp->set_destination(argv[i]);
         else
            papp->add_module(argv[i]);
      }
   }
   //
   // run the application object:
   //
   return papp->run();
}



