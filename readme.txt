Harry O'Sullivan
Comp 15 
HW3 
readme.txt

Purpose of the Program --------------------------------------------------------

This program includes the ability to import from and export to a format that 
can be read by Google Calendar, muiples days for a calendar, multiple months, 
handling calendar conflicts, and finding the next free block of time in a day. 

List of files -----------------------------------------------------------------

main.cpp: this file is the testing file. Functons from Calendar.h are called to
use this program. Through main, one can schedule events however as 
they please. 

Calendar.h: This is the header file for Calendar.cpp. It includes the functions
within dayDynamicArray.h and event.h. This header file creates an
array of Days (class). 

dayDynamicArray.h: This is header file for dayDynamicArray.cpp. It includes the
functions within the event.h header file. This creates an 
array of Events (class). Functions like nextFreeBlock deter-
mine if/what the next free block of time is. 

Event.h: This is the header file for Event.cpp. This file creates an instance 
of an event to fit within the overall event array (eventList in 
dayDynamicArray). 

How to Compile ----------------------------------------------------------------

Use the included Makefile to compile the program. 

Outline of Data Structure -----------------------------------------------------

The calendar is a dynamic array of Days and each day is a dynamic array of 
Events. Because the arrays were dynamic, I was able to expand them as the data
was flowing in. The overall performace is efficient. 

Outline of Algorithm ----------------------------------------------------------

In this particular program, once the correct index for a specific day is found
in the Calendar dynamic array, all of the other days are moved over by one. The
same is done for an Event. 

Nextfreeblock: First, the program checks whether the original time conflicts
with an already-scheduled event. If not, if searches for where it needs to 
insert the event, and returns the corrected starttime to the schedule function.



- - - - 