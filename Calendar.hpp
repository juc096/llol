//
//  Calendar.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Calendar_hpp
#define Calendar_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Task.hpp"
#include "Meeting.hpp"
#include <array>
#include <map>
#include <unordered_map>
#include <algorithm>

namespace ECE141 {

    enum class DOW {sunday, monday, tuesday,wednesday, thursday, friday, saturday};
    
  class Calendar {
  public:
      Calendar(int aMonth=1, int aYear=2020);
      Calendar(const Calendar& aCal);
      Calendar& operator= (const Calendar& aCal);
      ~Calendar();
        
    bool load(std::istream &anInputStream);
      
      DateTime  firstAvailableHour(const Calendar &anOther, int startHour=0, int stopHour=0, const char *dow=nullptr) const;
      
      Calendar& init_DOWTable();
      
      void increment_tasks();
      void increment_meetings();
      Calendar& addItem(DateTime *anItem);
      Calendar& update_timeUnav(int item_day, int item_hour, int item_min);
      int findhour_ifAvailable_DAY(const Calendar &anOther,int startHour, int stopHour, int cur_day) const;
      
      
      int countTasks() const; //how many added items are tasks?
      int countMeetings() const; //how many added items are meetings?
      int countItemsForDate(const DateTime &aDateTime) const; //counts amount of items for a given date

      DOW getDOWFromString(const char *dow)const; //getter for lookup table given a DOW-string
      DOW getDayOfWeek(int aMonth, int aDay, int aYear)const; //returns the DOW given a date
      std::unordered_map<int, int> get_unav_DAY(int aDay) const; //returns the "array" of unavailable hours

      bool inRange(int aValue, int aMin, int aMax)const;
      const Calendar& show(std::ostream &anOutput) const; //show a text-based version of full-month calendar (see below)
      const Calendar& showSummary(std::ostream &anOutput) const; //show a text-based version of items (see below)
      
      
      friend std::ostream & operator << (std::ostream &anOutput, const Calendar &aCalendar);
      
      
      

    
  protected:
      
      
      static const int TYPE_dt = 0;
      static const int TYPE_task = 1;
      static const int TYPE_meeting = 2;
      static const int MAX_HOUR = 23;
      static const int TIME_NOT_FOUND = -1;
      
      int mon, year;
      int task_amount, meeting_amount;
      int days_in_cal;
      
      //a pointer to a DOW array
      //NOTE: this member variable is indexed from 0
      //Maybe write helper for retrieving elements
      //DOW * dow_by_date;
      std::vector<DOW> dow_by_date;
      //std::vector<std::vector<int> > times_unav;
      
      /*
       times_unav is a map object that maps each day to another
       map, where each inner map maps the hours in a day to
       
       inner map is essentially an "array" of ints 0-23 denoting which times are are unavailable
       int values that denote if this hour is available or not. (1 if unavailable, 0 if available)
       */
      std::unordered_map<int,std::unordered_map<int,int> > times_unav;
      
      /*
       items is a map object that maps each day to a vector of datetimes, i.e., the tasks/meetings of a given day
       */
      std::map<int,std::vector<DateTime*> > items;
      
      /*
       items_by_down is similar to items, but instead maps
       DOW (Day Of Week) objects to datetimes, as to organize
       the tasks/meetings given a specific Day Of Week.
    
       */
      std::map<DOW, std::vector<DateTime*> > items_by_dow;
      
      /*
       str_to_DOW is a lookup table of strings to DOW objects.
       e.g. given "Wednesday", it will return DOW::wednesday
       */
      std::unordered_map<const char*, DOW> str_to_DOW;
      
  };

}

#endif /* Calendar_hpp */
