//
// day.cpp
//
// Enter overview information here.

#include "dayDynamicArray.h"
#include <cassert>
#include <string>
#include <sstream>

const int Day::INIT_CAPACITY;

Day::Day(){ // constructor
eventList = NULL; // empty Day
eventCount = 0;
eventCapacity = 0;
theDate.day = 1;
theDate.month = 1;
theDate.year = 2014;
}

Day::Day(date aDate) { // constructor
eventList = NULL; // empty Day
eventCount = 0;
eventCapacity = 0;
theDate.day = aDate.day;
theDate.month = aDate.month;
theDate.year = aDate.year;
}

void Day::scheduleEvent() { // add default event for a full Day
scheduleEvent(0,2359,"");
}
void Day::scheduleEvent(int startTime, int endTime, string description){

if (eventList == NULL) {
eventList = new Event[INIT_CAPACITY];
eventCapacity = INIT_CAPACITY;
}
else if (eventCapacity == eventCount){
Event *tempList = new Event[eventCapacity * 2];
for (int index=0;index<eventCount;index++){
tempList[index] = eventList[index];
}
delete [] eventList;
eventList = tempList;
eventCapacity = eventCapacity * 2;
}

// create a new event
Event evt = Event(startTime,endTime,description);

// find the location where we need to insert the event
int index;
for (index=0;index<eventCount;index++) {
if (evt.amIBefore(eventList[index])) break;
}
// move the second to last item to the end, and then
// continue down the list
for (int moveIndex=eventCount;moveIndex > index; moveIndex--) {
eventList[moveIndex] = eventList[moveIndex - 1];
}
eventList[index] = evt;
eventCount++;
}

void Day::scheduleEvent(Event anEvent){
scheduleEvent(anEvent.getStartTime(),anEvent.getEndTime(),
anEvent.getDescription());
}

// attempts to schedule an Event at the earliest time available at or after 
// This may schedule the Event at the original time, or later in the Day.
// Returns true if successful, false if the Day is full and the Event could 
// not be scheduled
bool Day::scheduleEarliest(Event anEvent){

int nextAvailableTime = nextFreeBlock(anEvent);
if (nextAvailableTime == -1) {
return false; // no time during the Day!
}
else {
// calculate the difference of hours
int hourold = anEvent.getStartTime() / 100;
int hournew = nextFreeBlock(anEvent) / 100;
int hourdifference = (hournew - hourold) * 100;

// calculate the difference of minutes
int minuteold = anEvent.getStartTime() % 100;
int minutenew = nextFreeBlock(anEvent) % 100;
int minutedifference = minutenew - minuteold;

// compute the new endTime
int newEndTime = anEvent.getEndTime() + hourdifference + 
minutedifference;

// then schedule event
scheduleEvent(nextFreeBlock(anEvent), newEndTime, 
anEvent.getDescription());
return true;
}
}

void Day::cancelEvent(Event anEvent){
// find the event
int index;
for (index = 0;index < eventCount; index++){
if (eventList[index].isSameEventAs(anEvent)){
int delIndex;
for (delIndex=index;delIndex<eventCount-1;delIndex++){
eventList[delIndex] = eventList[delIndex+1];
}
eventCount--;
break; // found it, so no need to continue
}
}
}

// nextFreeBlock() returns a startTime integer for the next free block of time
// that will fit the Event.
// The function returns -1 if there was no suitable time for the event to end 
// before 2359.
int Day::nextFreeBlock(Event anEvent) {

bool conflict = false;

// first check if the list is empty, if it is just return startTime
if (eventList == NULL){
return anEvent.getStartTime();
}
// second, check if anEvent needs to be the first event
else if (anEvent.getEndTime() <= eventList[0].getStartTime()){
return anEvent.getStartTime();
}
// else, check if there is a conflict. if not, return original startTime 
else {
for (int i = 0; i < eventCount; i++){
if (anEvent.conflictsWith(eventList[i])){
conflict = true;
}
if (conflict == true) break;
}
if (conflict == false){
return anEvent.getStartTime();
}
}
// if it does conflict, call findnextfreeblock 
return findnextfreeblock(anEvent);
}

int Day::findnextfreeblock(Event anEvent){
// if it does conflict, check if it needs to go at the back, or in a gap, 
// interate, repeat
for (int i = 0; i < eventCount; i++){
if (i + 1 == eventCount){
int time_between = duration(eventList[i].getEndTime(), 2359);
if (time_between >= duration(anEvent.getStartTime(), 
anEvent.getEndTime())){
return eventList[i].getEndTime();
}
else {
return -1;
}
}
else if (anEvent.conflictsWith(eventList[i])){
if (duration(eventList[i].getEndTime(), 
eventList[i+1].getStartTime()) >= 
duration(anEvent.getStartTime(), anEvent.getEndTime())){
return eventList[i].getEndTime();
}
}
}
return -1; // return -1 if there is no time 
}

// the printDay() function prints an entire Day, beginning with the Date on 
// one line, in the
// following format:
// Date: 4/25/2014
void Day::printDay() {
cout << "Date: " << theDate.month << "/" << theDate.day << "/" << 
theDate.year << endl;
// loop through the eventList and print each event 
for (int i = 0; i < eventCount; i++){
eventList[i].printEvent();
}
}

string Day::exportDay(){
// this function exports the day into 
ostringstream day_oss;
day_oss << theDate.month << "/" << theDate.day << "/" << theDate.year;
string csvString = "";
for (int index=0;index < eventCount; index++) {
csvString+= day_oss.str() + "," + day_oss.str() + "," +
eventList[index].eventCSV() + "\n";
}
return csvString;
}

bool Day::isBefore(Day anotherDay) {
// check year
if (theDate.year < anotherDay.theDate.year) return true;
if (theDate.year > anotherDay.theDate.year) return false;

// year is the same, check month
if (theDate.month < anotherDay.theDate.month) return true;
if (theDate.month > anotherDay.theDate.month) return false;

// month is the same, check day
if (theDate.day < anotherDay.theDate.day) return true;
if (theDate.day > anotherDay.theDate.day) return false;
return false;
}

int Day::duration(int time1,int time2){
// calculate a duration between two times in the same day
// time1 <= time2
// returns a duration in 24-hour time
int durationHours,durationMinutes;

int time1Hours = time1 / 100;
int time1Minutes = time1 - (time1Hours * 100);

int time2Hours = time2 / 100;
int time2Minutes = time2 - (time2Hours * 100);

durationHours = time2Hours-time1Hours;
durationMinutes = time2Minutes-time1Minutes;

if (durationMinutes < 0) {
durationHours--;
durationMinutes+=60;
}
return durationHours * 100 + durationMinutes;
}

int Day::addTimes(int time1,int time2){
// add two 24-hour times together
int totalHours,totalMinutes;

int time1Hours = time1 / 100;
int time1Minutes = time1 - (time1Hours * 100);

int time2Hours = time2 / 100;
int time2Minutes = time2 - (time2Hours * 100);

totalHours = time2Hours+time1Hours;
totalMinutes = time2Minutes+time1Minutes;

if (totalMinutes >=60) {
totalHours++;
totalMinutes-=60;
}
return totalHours * 100 + totalMinutes;
}

Day::~Day(){
//if (eventList != NULL)
// delete [] eventList;
}

Day::Day(const Day &rightHandSide) {
// first copy the values
eventCapacity = rightHandSide.eventCapacity;
eventCount = rightHandSide.eventCount;
theDate = rightHandSide.theDate;
eventList = NULL;

if (eventCapacity==0) return;

// create a new eventList and copy all events
delete [] eventList;
eventList = new Event[eventCapacity];

for (int i=0;i<eventCount;i++) {
eventList[i] = rightHandSide.eventList[i];
}
}

Day &Day::operator=(const Day &rightHandSide){
if (this != &rightHandSide) {
// first copy the values
eventCapacity = rightHandSide.eventCapacity;
eventCount = rightHandSide.eventCount;
theDate = rightHandSide.theDate;
eventList = NULL;
if (eventCapacity == 0) return *this;
delete [] eventList;

eventList = new Event[eventCapacity];

for (int i=0;i<eventCount;i++) {
eventList[i] = rightHandSide.eventList[i];
}
}
return *this;

}
© 2014 Microsoft Terms Privacy & cookies Developers English (United States)
