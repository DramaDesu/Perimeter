@echo off
echo Begin test processing...
bjam --dump-tests %* >bjam.log 2>&1
echo Begin log processing...
process_jam_log <bjam.log
start bjam.log
echo Begin compiler status processing...
compiler_status %BOOST_ROOT% test_status.html test_links.html
start test_status.html
