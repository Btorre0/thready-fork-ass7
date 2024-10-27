main: main.c \
		patterns.c\
		patterns.h
	gcc -o main main.c patterns.c -lpthread

results: main
	(echo "Pattern 1:"; ./main 1 ${shell bc --expression="$$RANDOM % 15 + 5"}; \
	echo "Pattern 2:"; ./main 2 ${shell bc --expression="$$RANDOM % 15 + 5"}) \
		> results.txt

clean:
	rm -f main results.txt