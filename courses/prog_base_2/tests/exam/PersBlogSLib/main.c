#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct notes_s{
    int reqCount;
    note_act_t ** reqList;
};

struct car_s{
    car_stat_t status;
    char* name;
    int id;
};

struct carOwner_s{
    int id;
    char * name
    car_t * car;
};

struct group_s{
    int salary;
    int ownerCount
    carOwner_t * ownersList;
};

struct owners_s{
    int groupCount;
    group_t * groupList
};

struct parcking_s{
    notes_t * notesList
    owners_t * ownersList
};
