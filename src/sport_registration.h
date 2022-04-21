#ifndef sport_registration
#define sport_registration

typedef struct Registration {
  int registrationCode;
  int *eventCode;
  int *athleteCode;
} Registration_t;

struct RegistrationNode {
  Registration_t registration;
  struct RegistrationNode *nextRegistration;
};

void printSingleRegistration(void);
void printAllRegistrations(void);
void registrationNew(void);
void registrationUpdate(void);
void registrationRemove(void);

#endif