#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

typedef enum {
    AUTO_IN,
    AUTO_OUT
} note_act_t;

typedef enum {
    AUTO_PARKED,
    AUTO_OUTSIDE
} car_stat_t;

typedef struct notes_s notes_t;
typedef struct car_s car_t;
typedef struct carOwner_s * carOwner_t;
typedef struct group_s * group_t;
typedef struct owners_s * owners_t;
typedef struct parking_s parking_t;

notes_t * notes_new();
parking_t * parking_new();
void parking_addNote(parking_t * self, note_act_t stat);
void parking_getNotes(parking_t * self);

#endif // PARKING_H_INCLUDED
