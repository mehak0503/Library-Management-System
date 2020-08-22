all:
	rm -f lms.db
	g++ main.cpp Menu.cpp db.cpp -lsqlite3
	./a.out < testcases/1sup_membership.txt > output.txt 
	./a.out < testcases/2add_book.txt >> output.txt 
	./a.out < testcases/5sell_book.txt >> output.txt 
	./a.out < testcases/6borrow_book.txt >> output.txt 
	./a.out < testcases/8req_return.txt >> output.txt 
	if [ "`grep -o -i wrong output.txt|wc -l`" != "`echo 0`" ]; then \
                echo "Test cases failed"; \
        else\
                echo "Test cases passed";\
        fi

