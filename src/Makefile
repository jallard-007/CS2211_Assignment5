CC=gcc
CFLAGS=-Wall -Wpedantic -Wextra -std=c99

default: sport_db.o sport_events.o sport_athletes.o sport_registration.o
	gcc sport_db.o sport_events.o sport_athletes.o sport_registration.o -o sport

clean:
	rm -f *.o sport_events sport_athletes sport_db sport_registration

# To be implemented
sport_db.o: sport_db.c sport_db.h
	gcc -c sport_db.c

sport_events.o: sport_events.c sport_events.h
	gcc -c sport_events.c

sport_athletes.o: sport_athletes.c sport_athletes.h
	gcc -c sport_athletes.c

sport_registration.o: sport_registration.c sport_registration.h
	gcc -c sport_registration.c