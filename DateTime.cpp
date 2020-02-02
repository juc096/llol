//
//  Date.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "DateTime.hpp"

namespace ECE141 {

    DateTime::DateTime(int aDay, int aMon, int aYear, int anHour, int aMins, int aType) {
        day = aDay;
        mon = aMon;
        year = aYear;
        hour = anHour;
        mins = aMins;
        type = aType;
    }
    DateTime::DateTime(const DateTime &aDateTime) {
        day = aDateTime.day;
        mon = aDateTime.mon;
        year = aDateTime.year;
        hour = aDateTime.hour;
        mins = aDateTime.mins;
        type = aDateTime.type;
    }
    DateTime::DateTime(const DateTime* aDateTime) {
        day = aDateTime->day;
        mon = aDateTime->mon;
        year = aDateTime->year;
        hour = aDateTime->hour;
        mins = aDateTime->mins;
        type = aDateTime->type;
    }
    DateTime& DateTime::operator=(const DateTime &aDateTime) {
        day = aDateTime.day;
        mon = aDateTime.mon;
        year = aDateTime.year;
        hour = aDateTime.hour;
        mins = aDateTime.mins;
        type = aDateTime.type;
        return *this;
    }


    bool      DateTime::operator==(const DateTime &aCopy) {
        
        return (    (day == aCopy.getDay()) &&
                    (mon == aCopy.getMonth()) &&
                    (year == aCopy.getYear()) &&
                    (hour == aCopy.getHour()) &&
                    (mins == aCopy.getMinutes()) &&
                    (type == aCopy.getType()));
    }

    bool      DateTime::isValid() {
        
        
        
        bool valid_mon = (0 < mon) && (mon <= 12);
        bool valid_year = (0 <= year) && (year <= 2050);
        bool valid_hour = (0 <= hour) && (hour <= 23);
        bool valid_mins = (0 <= mins) && (mins <= 59);
        bool valid_day= (0 < day) && (day <= (get_daysinMonth(mon, year)));
        
        //return check if the datetime is valid
        
        return (    valid_mon &&
                    valid_day &&
                    valid_year &&
                    valid_hour &&
                    valid_mins );
    }


    int       DateTime::getMonth() const {
        return mon;
    }
    int       DateTime::getDay() const {
        return day;
    }
    int       DateTime::getYear() const {
        return year;
    }
    int       DateTime::getHour() const {
        return hour;
    }
    int       DateTime::getMinutes() const {
        return mins;
    }
    int       DateTime::getType() const {
        return type;
    }


    DateTime& DateTime::setMonth(int aValue) {
        mon = aValue;
        return *this;
    }
    DateTime& DateTime::SetDay(int aValue) {
        day = aValue;
        return *this;
    }
    DateTime& DateTime::setYear(int aValue) {
        year = aValue;
        return *this;
    }
    DateTime& DateTime::setHour(int aValue) {
        hour = aValue;
        return *this;
    }
    DateTime& DateTime::setMinutes(int aValue) {
        mins = aValue;
        return *this;
    }


}
