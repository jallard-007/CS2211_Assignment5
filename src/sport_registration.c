#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "sport_registration.h"
#include "sport_db.h"

bool validRegistrationCode(int registrationCode) {
  if (registrationCode < 0) {
    printf("\t\tRegistration code out of bounds. Try again: ");
    return false;
  }
  return true;
}

bool registrationCodeAvailable(int registrationCode) {
  if (!validRegistrationCode(registrationCode)) {
    return false;
  }
  struct RegistrationNode *currRegistration = registrationList;
  while (currRegistration != NULL) {
    if (currRegistration->registration.registrationCode == registrationCode) {
      printf("\t\tRegistration code already exists. Try again: ");
      return false;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  return true;
}

bool registrationCodeExists(int registrationCode) {
  if (!validRegistrationCode(registrationCode)) {
    return false;
  }
  struct RegistrationNode *currRegistration = registrationList;
  while (currRegistration != NULL) {
    if (currRegistration->registration.registrationCode == registrationCode) {
      return true;
    }
    currRegistration = currRegistration->nextRegistration;
  }
  printf("\t\tRegistration code does not exist. Try again: ");
  return false;
}

bool validRegistrationCodeChange(const int oldRegistrationCode, const int newRegistrationCode) {
  if (oldRegistrationCode != newRegistrationCode && !registrationCodeAvailable(newRegistrationCode)) {
    return false;
  }
  return true;
}

void updateRegistrationCode(Registration_t *const registration) {
  int newRegistrationCode;
  printf("\t\tEnter registration code: ");
  do {
    scanf("%d", &newRegistrationCode);
    clear();
  } while (!validRegistrationCodeChange(registration->registrationCode, newRegistrationCode));
  registration->registrationCode = newRegistrationCode;
}

void updateRegistrationAthleteCode(Registration_t *const registration) {
  int athleteCode = -1;
  struct AthleteNode *athleteNode = NULL;
  printf("\t\tEnter athlete code: ");
  for (;;) {
    scanf("%d", &athleteCode);
    clear();
    athleteNode = getAthleteNode(athleteCode);
    if (athleteNode) {
      break;
    }
    printf("\t\tAthlete code does not exist. Try again: ");
  }
  registration->athleteCode = &athleteNode->athelete.athleteCode;
}

void updateRegistrationEventCode(Registration_t *const registration) {
  int eventCode = -1;
  struct EventNode *eventNode;
  printf("\t\tEnter event code: ");
  for (;;) {
    scanf("%d", &eventCode);
    clear();
    eventNode = getEventNode(eventCode);
    if (eventNode) {
      break;
    }
    printf("\t\tEvent code does not exist. Try again: ");
  }
  registration->eventCode = &eventNode->event.eventCode;
}

static void printTableHeader(void) {
  printf("Registration Code      Event Code     Athlete Code\n");
}

void printRegistration(Registration_t registration) {
  printf(
    "         %-16d%-16d%d\n",
    registration.registrationCode,
    *registration.eventCode,
    *registration.athleteCode
  );
}

void printSingleRegistration(void) {
  if (registrationList == NULL) {
    printf("\t\tThere are no registrations to display\n");
    return;
  }
  struct RegistrationNode *currRegistration = registrationList;
  int registrationCode;
  printf("\t\tEnter a registration code (-1 to cancel): ");
  for (;;) {
    scanf("%d", &registrationCode);
    clear();
    if (registrationCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    currRegistration = getRegistrationNode(registrationCode);
    if (currRegistration) {
      break;
    }
    printf("Registration code does not exist. Try again: ");
  }
  printTableHeader();
  printRegistration(currRegistration->registration);
}

void printAllRegistrations() {
  if (!registrationList) {
    printf("\t\tThere are no registration to display\n");
    return;
  }
  struct RegistrationNode *currRegistration = registrationList;
  printTableHeader();
  while (currRegistration) {
    printRegistration(currRegistration->registration);
    currRegistration = currRegistration->nextRegistration;
  }
}

int newRegistrationCodeInput() {
  int registrationCode = -2;
  printf("\t\tEnter a new registration code (-1 to cancel): ");
  do {
    scanf("%d", &registrationCode);
    clear();
    if (registrationCode == -1) {
      return registrationCode;
    }
  } while (!registrationCodeAvailable(registrationCode));
  return registrationCode;
}

void registrationNew(void) {
  if (!athleteList || !eventList) {
    printf("\t\tAt least one event and one athlete in the database is required for registration\n");
    return;
  }
  int registrationCode = newRegistrationCodeInput();
  if (registrationCode == -1) {
    printf("\t\tCancelled\n");
    return;
  }
  struct RegistrationNode *registrationNode = malloc(sizeof (struct AthleteNode));
  if (!registrationNode) {
    printf("\t\tUnable to allocate memeory\n");
  }
  if (registrationList == NULL) {
    registrationList = registrationNode;
  } else {
    struct RegistrationNode *currRegistration = registrationList;
    while (currRegistration->nextRegistration != NULL) {
      currRegistration = currRegistration->nextRegistration;
    }
    currRegistration->nextRegistration = registrationNode;
  }
  registrationNode->registration.registrationCode = registrationCode;
  updateRegistrationEventCode(&registrationNode->registration);
  updateRegistrationAthleteCode(&registrationNode->registration);
  registrationNode->nextRegistration = NULL;
}

void registrationUpdate(void) {
  if (!registrationList) {
    printf("\t\tThere are no registrations to update\n");
    return;
  }
  printf("\t\tEnter registration code to update (-1 to cancel): ");
  int registrationCode;
  struct RegistrationNode *registrationNode = NULL;
  for (;;) {
    scanf("%d", &registrationCode);
    clear();
    if (registrationCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    registrationNode = getRegistrationNode(registrationCode);
    if (registrationNode) {
      updateRegistrationCode(&registrationNode->registration);
      updateRegistrationEventCode(&registrationNode->registration);
      updateRegistrationAthleteCode(&registrationNode->registration);
      return;
    }
    printf("\t\tRegistration code does not exist. Try again: ");
  }
}

void registrationRemove(void) {
  if (registrationList == NULL) {
    printf("\t\tThere are no registrations to remove\n");
    return;
  }
  int registrationCode = -2;
  printf("\t\tEnter registration code to remove (-1 to cancel): ");
  for (;;) {
    scanf("%d", &registrationCode);
    clear();
    if (registrationCode == -1) {
      return;
    }
    if (removeRegistrationNode(registrationCode)) {
      return;
    }
    printf("\t\tRegistration code does not exist. Try again: ");
  }
}