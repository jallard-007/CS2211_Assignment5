#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "sport_athletes.h"
#include "sport_db.h"

bool validAlthleteCode(int athleteCode) {
  if (athleteCode < 0) {
    printf("\t\tAthlete code out of bounds. Try again: ");
    return false;
  }
  return true;
}

bool athleteCodeAvailable(int athleteCode) {
  if (!validAlthleteCode(athleteCode)) {
    return false;
  }
  struct AthleteNode *currAthlete = athleteList;
  while (currAthlete != NULL) {
    if (currAthlete->athelete.athleteCode == athleteCode) {
      printf("\t\tAthlete code already exists. Try again: ");
      return false;
    }
    currAthlete = currAthlete->nextAthlete;
  }
  return true;
}

bool validAthleteCodeChange(const int oldAthleteCode, const int newAthleteCode) {
  if (oldAthleteCode != newAthleteCode && !athleteCodeAvailable(newAthleteCode)) {
    return false;
  }
  return true;
}

void updateAthleteCode(Athlete_t *const athlete) {
  int newAthleteCode;
  printf("\t\tEnter athlete's code: ");
  do {
    scanf("%d", &newAthleteCode);
    clear();
  } while (!validAthleteCodeChange(athlete->athleteCode, newAthleteCode));
  athlete->athleteCode = newAthleteCode;
}

void updateAthleteName(Athlete_t *const athlete) {
  char currChar;
  printf("\t\tEnter athlete's name: ");
  for (int i = 0; i < 49; ++i) {
    scanf("%c", &currChar);
    if (currChar != '\n') {
      athlete->athleteName[i] = currChar;
    } else {
      athlete->athleteName[i] = '\0';
      return;
    }
  }
  clear();
  athlete->athleteName[49] = '\0';
}

bool validAgeChange(const int age) {
  if (age < 16 || age > 99) {
    printf("\t\tError. Invalid age. Try again: ");
    return false;
  }
  return true;
}

void updateAthleteAge(Athlete_t *const athlete) {
  int age;
  printf("\t\tEnter age: ");
  do {
    scanf("%d", &age);
    clear();
  } while (!validAgeChange(age));
  athlete->athleteAge = age;
}

bool validAthleteGenderChange(const char gender) {
  if (gender != 'M' && gender != 'W' && gender != 'X') {
    printf("\t\tInvalid gender: Not one of 'M', 'W', or 'X'. Try again: ");
    return false;
  }
  return true;
}

void updateAthleteGender(Athlete_t *const athlete) {
  char gender;
  printf("\t\tEnter gender: ");
  do {
    scanf("%c", &gender);
    clear();
  } while (!validAthleteGenderChange(gender));
  athlete->athleteGender = gender;
}

static void printTableHeader(void) {
  printf(
    "Athlete Code    Athlete Name                                          Age        Gender\n"
  );
}

void printAthlete(Athlete_t athlete) {
  printf(
    "   %-13d%-55s%-12d%c\n",
    athlete.athleteCode,
    athlete.athleteName,
    athlete.athleteAge,
    athlete.athleteGender
  );
}

void printSingleAthlete(void) {
  if (!athleteList) {
    printf("\t\tThere are no athletes to display\n");
    return;
  }
  struct AthleteNode *currAthlete = athleteList;
  int athleteCode;
  printf("\t\tEnter an athlete code (-1 to cancel): ");
  for (;;) {
    scanf("%d", &athleteCode);
    clear();
    if (athleteCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    currAthlete = getAthleteNode(athleteCode);
    if (currAthlete) {
      break;
    }
    printf("\t\tAthlete code does not exists. Try again: ");
  }
  printTableHeader();
  printAthlete(currAthlete->athelete);
}

void printAllAthletes(void) {
  if (!athleteList) {
    printf("\t\tThere are no athletes to display\n");
    return;
  }
  struct AthleteNode *currAthlete = athleteList;
  printTableHeader();
  while (currAthlete) {
    printAthlete(currAthlete->athelete);
    currAthlete = currAthlete->nextAthlete;
  }
}

int newAthleteCodeInput(void) {
  int athleteCode = -2;
  printf("\t\tEnter a new athlete code (-1 to cancel): ");
  do {
    scanf("%d", &athleteCode);
    clear();
    if (athleteCode == -1) {
      return -1;
    }
  } while (!athleteCodeAvailable(athleteCode));
  return athleteCode;
}

void athleteNew(void) {
  int athleteCode = newAthleteCodeInput();
  if (athleteCode == -1) {
    printf("\t\tCancelled\n");
    return;
  }
  struct AthleteNode *athleteNode = malloc(sizeof (struct AthleteNode));
  if (!athleteNode) {
    printf("\t\tUnable to allocate memeory\n");
    exit(1);
  }
  if (athleteList == NULL) {
    athleteList = athleteNode;
  } else {
    struct AthleteNode *currAthlete = athleteList;
    while (currAthlete->nextAthlete != NULL) {
      currAthlete = currAthlete->nextAthlete;
    }
    currAthlete->nextAthlete = athleteNode;
  }
  athleteNode->athelete.athleteCode = athleteCode;
  updateAthleteName(&athleteNode->athelete);
  updateAthleteGender(&athleteNode->athelete);
  updateAthleteAge(&athleteNode->athelete);
  athleteNode->nextAthlete = NULL;
}

void athleteUpdate(void) {
  if (athleteList == NULL) {
    printf("\t\tThere are no athletes to update\n");
    return;
  }
  printf("\t\tEnter athlete code to update (-1 to cancel): ");
  int athleteCode;
  struct AthleteNode *athleteNode = NULL;
  for (;;) {
    scanf("%d", &athleteCode);
    clear();
    if (athleteCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    athleteNode = getAthleteNode(athleteCode);
    if (athleteNode) {
      updateAthleteCode(&athleteNode->athelete);
      updateAthleteName(&athleteNode->athelete);
      updateAthleteGender(&athleteNode->athelete);
      updateAthleteAge(&athleteNode->athelete);
      return;
    }
    printf("\t\tAthlete code does not exist. Try again: ");
  }
}

void athleteRemove(void) {
  if (!athleteList) {
    printf("\t\tThere are no athletes to remove\n");
    return;
  }
  int athleteCode = -2;
  printf("\t\tEnter athlete code to remove (-1 to cancel): ");
  for (;;) {
    scanf("%d", &athleteCode);
    clear();
    if (athleteCode == -1) {
      return;
    }
    int *regCodesToRemove = checkForRegistrationOfAthlete(athleteCode);
    if (regCodesToRemove[0] > 1) {
      printf(
        "\t\tThis athlete is currently registered\n\t\tWould you like to continue and remove the registration(s) as well? (Y/N): "
      );
      char choice;
      scanf("%c", &choice);
      clear();
      if (choice == 'Y' || choice == 'y') {
        for (int i = 1; i < regCodesToRemove[0]; ++i) {
          removeRegistrationNode(regCodesToRemove[i]);
        }
        removeAthleteNode(athleteCode);
      }
      return;
    }
    if (removeAthleteNode(athleteCode)) {
      return;
    }
    printf("\t\tAthlete code does not exist. Try again: ");
  }
}