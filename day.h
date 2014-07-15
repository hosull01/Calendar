//
// day.h
//
// Enter overview information here.


#ifndef __CalendarOrderedLists__day__
#define __CalendarOrderedLists__day__

#include <iostream>
#include "event.h"

struct date{
int day;
int month;
int year;
};

class Day {
public:
static const int INIT_CAPACITY = 5;

Day(); // constructor
Day(date aDate); // constructor
Day(const Day &rightHandSide); // copy constructor
Day &operator=(const Day &rightHandSide); // operator= overload

void scheduleEvent(); // default event for full day
void scheduleEvent(int startTime, int endTime, string description);
void scheduleEvent(Event anEvent);

// scheduleEarliest() will schedule an event into the earliest available time slot
// either at or after the requested slot.
// The function returns true if the event was scheduled during the Day,
// false otherwise
bool scheduleEarliest(Event anEvent);

// cancels and removes an event from a Day
void cancelEvent(Event anEvent);

// pretty-prints the Day
void printDay();

// exports the Day into a CSV, in the following format:
// 
string exportDay();
date getDate() { return theDate; }
bool isBefore(Day anotherDay);
int nextFreeBlock(Event anEvent);
~Day(); // destructor

private:
Event *eventList;
int eventCount;
int eventCapacity;
date theDate;

// private methods

int duration(int time1,int time2);
int addTimes(int time1,int time2);
int findnextfreeblock(Event anEvent);
};

#endif /* defined(__CalendarOrderedLists__day__) */
© 2014 Microsoft Terms Privacy & cookies Developers English (United States)
       