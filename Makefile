CC      = cc

c_bin : main.o maincpp.o decimal_to_roman.o roman_to_decimal.o number_converter.h
			$(CC) -o c_bin main.o
cpp_bin : main.o maincpp.o decimal_to_roman.o roman_to_decimal.o number_converter.h
			$(CC) -o cpp_bin maincpp.o
decimal_to_roman.o : decimal_to_roman.c
			$(CC) -c decimal_to_roman.c
roman_to_decimal.o : roman_to_decimal.c
			$(CC) -c roman_to_decimal.c
main.o : main.c
			$(CC) -c main.c
maincpp.o : maincpp.cpp
			$(CC) -c maincpp.cpp			
clean : 
			rm -rf c_bin cpp_bin main.o decimal_to_roman.o roman_to_decimal.o maincpp.o

