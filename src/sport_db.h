#ifndef sport_db
#define sport_db
#include "sport_events.h"
#include "sport_athletes.h"
#include "sport_registration.h"

extern struct EventNode *eventList;
struct EventNode *getEventNode(int);
bool removeEventNode(int);

extern struct AthleteNode *athleteList;
struct AthleteNode *getAthleteNode(int);
bool removeAthleteNode(int);

extern struct RegistrationNode *registrationList;
struct RegistrationNode *getRegistrationNode(int);
bool removeRegistrationNode(int);

void clear(void);

int *checkForRegistrationOfAthlete(int);
int *checkForRegistrationOfEvent(int);

#endif