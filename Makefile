# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-L /usr/include/mariadb/mysql -lmariadbclient
VERSION = --std=c++17

all: mychat

mychat: Chat.o console.o
	$(CC) -g3 Chat.o console.o -o mychat $(VERSION) $(CFLAGS) 

Chat.o: Chat.cpp
	$(CC) -c Chat.cpp

console.o: console.cpp
	$(CC) -c console.cpp



clean:
	rm -rf *.o mychat
