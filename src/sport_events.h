#ifndef sport_events
#define sport_events

typedef struct Event {
  int eventCode;
  int eventCompCount;
  char eventName[50];
  char eventGender;
} Event_t;

struct EventNode {
  Event_t event;
  struct EventNode *nextEvent;
};

void printSingleEvent(void);
void printAllEvents(void);
void eventNew(void);
void eventUpdate(void);
void eventRemove(void);

#endif