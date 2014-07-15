//
// event.cpp
//
// Enter overview information here.

#include "event.h"
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

Event::Event() { // constructor
startTime = 0;
endTime = 2359;
description = "";

}

Event::Event(int startT, int endT, string desc) {
startTime = startT;
endTime = endT;
description = desc;
}

int Event::getStartTime() {
return startTime;
}

int Event::getEndTime() {
return endTime;
}

std::string Event::getDescription() {
return description;
}

void Event::setStartTime(int startT) {
startTime = startT;
}

void Event::setEndTime(int endT) {
endTime = endT;
}

void Event::setDescription(string str) {
description = str;
}

bool Event::amIBefore(Event otherEvent) {
if (startTime < otherEvent.getStartTime()) {
return true;
}
return false;
}

bool Event::isSameEventAs(Event otherEvent) {
if (startTime == otherEvent.getStartTime() &&
endTime == otherEvent.getEndTime() &&
description == otherEvent.getDescription())
return true;
return false;
}

// conflictsWith returns true if this event overlaps with another event
// during the day
// events can "touch" but not overlap. I.e., one event can end
// at the same time the next event begins and this is not an overlap
bool Event::conflictsWith(Event anEvent) {
// instead of seeing if it conflicts, this checks if they dont. 
if (startTime < anEvent.getStartTime() && 
endTime < anEvent.getStartTime()){
return false;
}
else if (startTime > anEvent.getEndTime() && 
endTime > anEvent.getEndTime()){
return false;
}
return true;

}


void Event::printEvent(){
cout << "Start Time: " << convert24HourTime(startTime) << "\n";
cout << "End Time: " << convert24HourTime(endTime) << "\n";
cout << "Description: " << description << "\n\n";
}

string Event::eventCSV() {
string EventString = convert24HourTime(startTime) + "," +
convert24HourTime(endTime) + "," +
description;
return EventString;

}

// converts int to 24 hour time (e.g., 1330 -> 1:30 PM)
string Event::convert24HourTime(int time24){
string fullTime;
string meridiem = "AM"; // initialize it to AM; change to PM if need to 
ostringstream hour_oss, minute_oss; 
int hourNum, minuteNum;
hourNum = time24 / 100;
minuteNum = time24 % 100;

// first determine whether we are in AM or PM
if (hourNum > 11 && hourNum < 24) {
hourNum = hourNum - 12;
meridiem = "PM";
}
// corner case
if (hourNum == 0) hourNum = 12;

hour_oss << hourNum;
minute_oss << minuteNum;
if (minuteNum == 0){
fullTime = hour_oss.str() + ":" + "0" + minute_oss.str() + 
" " + meridiem;
}
else if (0 < minuteNum && minuteNum <= 9){
fullTime = hour_oss.str() + ":" + "0" + minute_oss.str() + 
" " + meridiem;
}
else {
fullTime = hour_oss.str() + ":" + minute_oss.str() + " " + meridiem;
}
return fullTime;
}
© 2014 Microsoft Terms Privacy & cookies Developers English (United States)
       