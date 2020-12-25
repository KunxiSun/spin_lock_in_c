#!/bin/bash

gcc ./src/test/test1.c ./src/src/spinlock.c -o test1 -O0 -Wall -Werror -Werror=vla -g -std=gnu11 -lm -lpthread -fsanitize=address
gcc ./src/test/test2.c ./src/src/spinlock.c -o test2 -O0 -Wall -Werror -Werror=vla -g -std=gnu11 -lm -lpthread -fsanitize=address


./test1
./test2


rm test1
rm test2