/*
 *
 * Copyright (c) 2003 Dr John Maddock
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include "bcp.hpp"
#include <string>
#include <cstring>
#include <list>
#include <set>
#include <map>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

class fileview;

//
//path operations:
//
int compare_paths(const fs::path& a, const fs::path& b);
inline bool equal_paths(const fs::path& a, const fs::path& b)
{ return compare_paths(a, b) == 0; }

struct path_less
{
   bool operator()(const fs::path& a, const fs::path& b)const
   { return compare_paths(a, b) < 0; }
};

struct licence_data
{
   std::set<fs::path, path_less> files;
   std::set<std::string>         authors;
};

class bcp_implementation
   : public bcp_application
{
public:
   bcp_implementation();
   ~bcp_implementation();
private:
   //
   // the following are the overridden virtuals from the base class:
   //
   void enable_list_mode();
   void enable_cvs_mode();
   void enable_unix_lines();
   void enable_scan_mode();
   void enable_licence_mode();
   void set_boost_path(const char* p);
   void set_destination(const char* p);
   void add_module(const char* p);

   virtual int run();
private:
   // internal helper functions:
   void scan_cvs_path(const fs::path& p);
   void add_path(const fs::path& p);
   void add_directory(const fs::path& p);
   void add_file(const fs::path& p);
   void copy_path(const fs::path& p);
   void add_file_dependencies(const fs::path& p, bool scanfile);
   bool is_source_file(const fs::path& p);
   bool is_html_file(const fs::path& p);
   bool is_binary_file(const fs::path& p);
   void add_dependent_lib(const std::string& libname, const fs::path& p);
   void create_path(const fs::path& p);
   // licence code:
   void scan_licence(const fs::path& p, const fileview& v);
   void output_licence_info();

   std::list<std::string> m_module_list; // the modules to process
   bool m_list_mode;                     // list files only
   bool m_licence_mode;                  // generate licence information for files listed
   bool m_cvs_mode;                      // check cvs for files
   bool m_unix_lines;                    // fix line endings
   bool m_scan_mode;                     // scan non-boost files.
   fs::path m_boost_path;                // the path to the boost root
   fs::path m_dest_path;                 // the path to copy to
   std::map<fs::path, bool, path_less> m_cvs_paths;    // valid files under cvs control
   std::set<fs::path, path_less> m_copy_paths;         // list of files to copy
   std::map<int, licence_data>   m_licence_data;       // licences in use
   std::set<fs::path, path_less> m_unknown_licences;   // files with no known licence
   std::set<fs::path, path_less> m_unknown_authors;    // files with no known copyright/author
   std::map<std::string, std::set<fs::path, path_less> > m_author_data;  // all the authors
   std::map<fs::path, fs::path, path_less>               m_dependencies; // dependency information
};
