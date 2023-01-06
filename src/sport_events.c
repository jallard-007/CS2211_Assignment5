#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "sport_events.h"
#include "sport_db.h"

bool validEventCode(int eventCode) {
  if (eventCode < 0) {
    printf("\t\tEvent code out of bounds. Try again: ");
    return false;
  }
  return true;
}

bool eventCodeAvailable(int eventCode) {
  if (!validEventCode(eventCode)) {
    return false;
  }
  struct EventNode *currEvent = eventList;
  while (currEvent != NULL) {
    if (currEvent->event.eventCode == eventCode) {
      printf("\t\tEvent code already exists. Try again: ");
      return false;
    }
    currEvent = currEvent->nextEvent;
  }
  return true;
}

bool validEventCodeChange(const int oldEventCode, const int newEventCode) {
  if (oldEventCode != newEventCode && !eventCodeAvailable(newEventCode)) {
    return false;
  }
  return true;
}

void updateEventCode(Event_t *const event) {
  int newEventCode;
  printf("\t\tEnter event code: ");
  do {
    scanf("%d", &newEventCode);
    clear();
  } while (!validEventCodeChange(event->eventCode, newEventCode));
  event->eventCode = newEventCode;
}

void updateEventName(Event_t *const event) {
  char currChar;
  printf("\t\tEnter event name: ");
  for (int i = 0; i < 49; ++i) {
    scanf("%c", &currChar);
    if (currChar != '\n') {
      event->eventName[i] = currChar;
    } else {
      event->eventName[i] = '\0';
      return;
    }
  }
  clear();
  event->eventName[49] = '\0';
}

bool validCompCountChange(const int competitorCount) {
  if (competitorCount < 10 || competitorCount > 99) {
    printf("\t\tError. Invalid competitor count. Try again: ");
    return false;
  }
  return true;
}

void updateCompCount(Event_t *const event) {
  int competitorCount;
  printf("\t\tEnter competitor count: ");
  do {
    scanf("%d", &competitorCount);
    clear();
  } while (!validCompCountChange(competitorCount));
  event->eventCompCount = competitorCount;
}

bool validEventGenderChange(const char gender) {
  if (gender != 'M' && gender != 'W' && gender != 'X') {
    printf("\t\tInvalid gender: Not one of 'M', 'W', or 'X'. Try again: ");
    return false;
  }
  return true;
}

void updateEventGender(Event_t *const event) {
  char gender;
  printf("\t\tEnter gender: ");
  do {
    scanf("%c", &gender);
    clear();
  } while (!validEventGenderChange(gender));
  event->eventGender = gender;
}

static void printTableHeader(void) {
  printf(
    "Event Code      Event Name                                        Competitors    Gender\n"
  );
}

void printEvent(Event_t event) {
  printf(
    "   %-13d%-55s%-12d%c\n",
    event.eventCode,
    event.eventName,
    event.eventCompCount,
    event.eventGender
  );
}

void printSingleEvent(void) {
  if (!eventList) {
    printf("\t\tThere are no events to display");
    return;
  }
  struct EventNode *currEvent = eventList;
  int eventCode;
  printf("\t\tEnter an event code (-1 to cancel): ");
  for (;;) {
    scanf("%d", &eventCode);
    clear();
    if (eventCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    currEvent = getEventNode(eventCode);
    if (currEvent) {
      break;
    }
    printf("\t\tEvent code does not exists. Try again: ");
  }
  printTableHeader();
  printEvent(currEvent->event);
}

void printAllEvents() {
  if (!eventList) {
    printf("\t\tThere are no events to display");
    return;
  }
  struct EventNode *currEvent = eventList;
  printTableHeader();
  while (currEvent) {
    printEvent(currEvent->event);
    currEvent = currEvent->nextEvent;
  }
}

int newEventCodeInput(void) {
  int eventCode = -2;
  printf("\t\tEnter a new event code (-1 to cancel): ");
  do {
    scanf("%d", &eventCode);
    clear();
    if (eventCode == -1) {
      return -1;
    }
  } while (!eventCodeAvailable(eventCode));
  return eventCode;
}

void eventNew(void) {
  int eventCode = newEventCodeInput();
  if (eventCode == -1) {
    printf("\t\tCancelled\n");
    return;
  }
  struct EventNode *eventNode = malloc(sizeof (struct EventNode));
  if (!eventNode) {
    printf("\t\tUnable to allocate memory\n");
    exit(1);
  }
  if (eventList == NULL) {
    eventList = eventNode;
  } else {
    struct EventNode *currEvent = eventList;
    while (currEvent->nextEvent != NULL) {
      currEvent = currEvent->nextEvent;
    }
    currEvent->nextEvent = eventNode;
  }
  eventNode->event.eventCode = eventCode;
  updateEventName(&eventNode->event);
  updateEventGender(&eventNode->event);
  updateCompCount(&eventNode->event);
  eventNode->nextEvent = NULL;
}

void eventUpdate(void) {
  if (eventList == NULL) {
    printf("\t\tThere are no events to update\n");
    return;
  }
  printf("\t\tEnter event code to update (-1 to cancel): ");
  int eventCode = -2;
  struct EventNode *eventNode = NULL;
  for (;;) {
    scanf("%d", &eventCode);
    clear();
    if (eventCode == -1) {
      printf("\t\tCancelled\n");
      return;
    }
    eventNode = getEventNode(eventCode);
    if (eventNode) {
      updateEventCode(&eventNode->event);
      updateEventName(&eventNode->event);
      updateEventGender(&eventNode->event);
      updateCompCount(&eventNode->event);
      return;
    }
    printf("\t\tEvent code does not exist. Try again: ");
  }
}

void eventRemove(void) {
  if (eventList == NULL) {
    printf("\t\tThere are no events to remove\n");
    return;
  }
  int eventCode = -2;
  printf("\t\tEnter event code to remove (-1 to cancel): ");
  for (;;) {
    scanf("%d", &eventCode);
    clear();
    if (eventCode == -1) {
      return;
    }
    int *regCodesToRemove = checkForRegistrationOfEvent(eventCode);
    if (regCodesToRemove[0] > 1) {
      printf(
        "\t\tThis event is currently registered\n\t\tWould you like to continue and remove the registration(s) as well? (Y/N): "
      );
      char choice;
      scanf("%c", &choice);
      clear();
      if (choice == 'Y' || choice == 'y') {
        for (int i = 1; i < regCodesToRemove[0]; ++i) {
          removeRegistrationNode(regCodesToRemove[i]);
        }
        removeEventNode(eventCode);
      }
      free(regCodesToRemove);
      return;
    }
    free(regCodesToRemove);
    if (removeEventNode(eventCode)) {
      return;
    }
    printf("\t\tEvent node does not exist. Try again: ");
  }
}