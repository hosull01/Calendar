#
# Makefile for Calendar Ordered Lists, Assignment 3
#
CXX = clang++
FLAGS = -Wall -Wextra -Wconversion -g 

calendar: dayDynamicArray.cpp dayDynamicArray.h event.cpp event.h main.cpp Calendar.cpp Calendar.h
${CXX} ${FLAGS} -o calendar dayDynamicArray.cpp event.cpp main.cpp Calendar.cpp

clean:
rm -f calendar

make provide:
provide comp15 hw3 main.cpp dayDynamicArray.cpp dayDynamicArray.h \
event.cpp event.h main.cpp \
Calendar.cpp Calendar.h \
readme.txt Makefile
