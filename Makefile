forky: forky.c \
		patterns.c\
		patterns.h
	gcc -o forky forky.c patterns.c -lpthread

results: forky
	(echo "Pattern 1:"; ./forky 1 ${shell bc --expression="$$RANDOM % 15 + 5"}; \
	echo "Pattern 2:"; ./forky 2 ${shell bc --expression="$$RANDOM % 15 + 5"}) \
		> results.txt

clean:
	rm -f forky results.txt