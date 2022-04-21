#ifndef sport_athletes
#define sport_athletes

typedef struct Athlete {
  int athleteCode;
  int athleteAge;
  char athleteName[50];
  char athleteGender;
} Athlete_t;

struct AthleteNode {
  Athlete_t athelete;
  struct AthleteNode *nextAthlete;
};

void printSingleAthlete(void);
void printAllAthletes(void);
void athleteNew(void);
void athleteUpdate(void);
void athleteRemove(void);

#endif