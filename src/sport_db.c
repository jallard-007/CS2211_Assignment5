#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "sport_db.h"

struct EventNode *eventList = NULL;
struct AthleteNode *athleteList = NULL;
struct RegistrationNode *registrationList = NULL;

int main(void) {
  char choice;
  printf("Enter 'h' for help");
  for (;;) {
    printf("\nEnter op code: ");
    scanf("%c", &choice);
    clear();
    switch (choice) {
      case 'q':
        return 0;

      case 'h':
        printf(
          "'q' to quit, 'e' for events, 'a' for athletes or 'r' for registration.\n\n"
          "Within events, athletes, and registration:\n'i' to insert new entry, 'u' to update entry, 's' to search and print, 'p' to print all, 'e' to delete\n"
          "Note: atleast one event and one athlete must be input before a registration entry can be made.\n"
        );
        break;

      case 'e': {
        printf("\tEnter op code for events: ");
        scanf("%c", &choice);
        clear();
        switch (choice) {
          case 'i':
            eventNew();
            break;

          case 's':
            printSingleEvent();
            break;

          case 'p':
            printAllEvents();
            break;

          case 'u':
            eventUpdate();
            break;

          case 'e':
            eventRemove();
            break;

          case 'q':
            break;

          default:
            printf("\t\tInvalid event op code\n");
            break;
        }
        break;
      }

      case 'a': {
        printf("\tEnter op code for athletes: ");
        scanf("%c", &choice);
        clear();
        switch (choice) {
          case 'i':
            athleteNew();
            break;

          case 's':
            printSingleAthlete();
            break;

          case 'p':
            printAllAthletes();
            break;

          case 'u':
            athleteUpdate();
            break;

          case 'e':
            athleteRemove();
            break;

          case 'q':
            break;

          default:
            printf("\t\tInvalid athlete op code\n");
            break;
        }
        break;
      }

      case 'r': {
        printf("\tEnter op code for registration: ");
        scanf("%c", &choice);
        clear();
        switch (choice) {
          case 'i':
            registrationNew();
            break;

          case 's':
            printSingleRegistration();
            break;

          case 'p':
            printAllRegistrations();
            break;

          case 'u':
            registrationUpdate();
            break;

          case 'e':
            registrationRemove();
            break;

          case 'q':
            break;

          default:
            printf("\t\tInvalid registration op code\n");
            break;
        }
        break;
      }

      default: {
        printf("Invalid op code\n");
        break;
      }
    }
  }
}

void clear(void) {
  while (getchar() != '\n');
}

struct EventNode *getEventNode(int const eventCode) {
  struct EventNode *currEvent = eventList;
  while (currEvent) {
    if (currEvent->event.eventCode == eventCode) {
      return currEvent;
    }
    currEvent = currEvent->nextEvent;
  }
  return NULL;
}

bool removeEventNode(int const eventCode) {
  struct EventNode *currEvent = eventList;
  if (!currEvent) {
    return false;
  }
  if (currEvent->event.eventCode == eventCode) {
    eventList = currEvent->nextEvent;
    free(currEvent);
    return true;
  }

  while (currEvent->nextEvent) {
    if (currEvent->nextEvent->event.eventCode == eventCode) {
      struct EventNode *temp = currEvent->nextEvent;
      currEvent->nextEvent = temp->nextEvent;
      free(temp);
      return true;
    }
    currEvent = currEvent->nextEvent;
  }
  return false;
}

struct AthleteNode *getAthleteNode(int const athleteCode) {
  struct AthleteNode *currAthlete = athleteList;
  while (currAthlete) {
    if (currAthlete->athlete.athleteCode == athleteCode) {
      return currAthlete;
    }
    currAthlete = currAthlete->nextAthlete;
  }
  return NULL;
}

bool removeAthleteNode(int const athleteCode) {
  struct AthleteNode *currAthlete = athleteList;
  if (!currAthlete) {
    return false;
  }
  if (currAthlete->athlete.athleteCode == athleteCode) {
    athleteList = currAthlete->nextAthlete;
    free(currAthlete);
    return true;
  }

  while (currAthlete->nextAthlete) {
    if (currAthlete->nextAthlete->athlete.athleteCode == athleteCode) {
      struct AthleteNode *temp = currAthlete->nextAthlete;
      currAthlete->nextAthlete = temp->nextAthlete;
      free(temp);
      return true;
    }
    currAthlete = currAthlete->nextAthlete;
  }
  return false;
}

struct RegistrationNode *getRegistrationNode(int const registrationCode) {
  struct RegistrationNode *currRegistration = registrationList;
  while (currRegistration) {
    if (currRegistration->registration.registrationCode == registrationCode) {
      return currRegistration;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  return NULL;
}

bool removeRegistrationNode(int const registrationCode) {
  struct RegistrationNode *currRegistration = registrationList;
  if (!currRegistration) {
    return false;
  }
  if (currRegistration->registration.registrationCode == registrationCode) {
    registrationList = registrationList->nextRegistration;
    free(currRegistration);
    return true;
  }

  while (currRegistration->nextRegistration) {
    if (currRegistration->nextRegistration->registration.registrationCode == registrationCode) {
      struct RegistrationNode *temp = currRegistration->nextRegistration;
      currRegistration->nextRegistration = temp->nextRegistration;
      free(temp);
      return true;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  return false;
}

int *checkForRegistrationOfAthlete(int const athleteCode) {
  struct RegistrationNode *currRegistration = registrationList;
  int *array = malloc(sizeof (int));
  int length = 1;
  while (currRegistration) {
    if (*currRegistration->registration.athleteCode == athleteCode) {
      array = realloc(array, sizeof (int)*(++length));
      array[length - 1] = currRegistration->registration.registrationCode;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  array[0] = length; // storing length in first index
  return array;
}

int *checkForRegistrationOfEvent(int const eventCode) {
  struct RegistrationNode *currRegistration = registrationList;
  int *array = malloc(sizeof (int));
  int length = 1;
  while (currRegistration) {
    if (*currRegistration->registration.eventCode == eventCode) {
      array = realloc(array, sizeof (int)*(++length));
      array[length - 1] = currRegistration->registration.registrationCode;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  array[0] = length; // storing length in first index
  return array;
}
