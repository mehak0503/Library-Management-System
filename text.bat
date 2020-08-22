@ECHO OFF
START lms.exe < testcases\1sup_membership.txt >& output.txt 
START lms.exe < testcases\2add_book.txt >& output.txt 
START lms.exe < testcases\5sell_book.txt >& output.txt 
START lms.exe < testcases\6borrow_book.txt >& output.txt 
START lms.exe < testcases\8req_return.txt >& output.txt 
SET OUTPUT_LMS
@ECHO ON
for /f %%i in ('findstr /c:"wrong" output.txt | find /c ":"') do set OUTPUT_LMS=%%i
if %OUTPUT_LMS%==0 (echo "Test cases passed") else (echo "Test cases failed")


