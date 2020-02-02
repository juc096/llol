//
//  Date.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef DateTime_hpp
#define DateTime_hpp

#include <stdio.h>
#include <iostream>

namespace ECE141 {


  class DateTime {
  public:
      DateTime(int aDay=0, int aMon=0, int aYear=0, int anHour=0, int aMins=0, int aType = 0);
      DateTime(const DateTime& aDateTime);
      DateTime(const DateTime* aDateTime);
      DateTime& operator=(const DateTime& aDateTime);
      ~DateTime() {};
      
    //add copy constructor...
    //add assignment operator
    //add destructor
    
    //add specified methods here...
      bool      operator==(const DateTime &aCopy); //this is the comparison operator

      bool      isValid(); //return true if all fields are within the valid range

      DateTime& setMonth(int aValue);  //range: 1-12
      DateTime& SetDay(int aValue);    //range: 1-31
      DateTime& setYear(int aValue);   //range: 0-2050
      DateTime& setHour(int aValue);   //range: 0-23 (military time)
      DateTime& setMinutes(int aValue); //range: 0-59

      int       getMonth() const;
      int       getDay() const;
      int       getYear() const;
      int       getHour() const;
      int       getMinutes() const;
      
      
      int       getType() const;
      //returns the type of datetime; whether meeting or task
      //0 : DateTime
      //1 : Task
      //2 : Meeting

    friend std::ostream& operator<<(std::ostream &aStream, DateTime &aDate) {
        aStream << aDate.getMonth() <<" "<< aDate.getDay() <<" "<< aDate.getYear();
          return aStream;
      }
    friend std::ostream& operator<<(std::ostream &aStream, DateTime *aDate) {
        aStream << aDate->getMonth()<< " " << aDate->getDay() << " " << aDate->getYear();
        return aStream;
    }
      /*
       determines if the year is a leap year. static method for use by other classes
       */
      static bool isLeapYear(int aYear){
          bool year_divisible_by_four = (aYear % 4) == 0;
          bool year_divisible_by_hundred = (aYear % 100) == 0;
          bool year_divisible_by_fourhund = (aYear % 400) == 0;
          bool isLeap = year_divisible_by_hundred ?
              year_divisible_by_fourhund : year_divisible_by_four;
          return isLeap;
      };
      /*
      determines days in a month, given a month/year. static method for use by other classes
      */
      static int get_daysinMonth(int aMonth, int aYear) {
          static const int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
          if(aMonth == 2) {
              return (days_in_month[aMonth] + isLeapYear(aYear));
          }
          return days_in_month[aMonth];
      };
      static const char* getMonthName(int aMonth) {
        static const char* kMonths[]=
        {"", "January", "February", "March", "April", "May",
         "June", "July", "August", "September",
         "October", "November", "December"};
        return kMonths[aMonth];
      };
  protected:
    //add specified data members here..
      int day, mon, year, hour, mins;
      
      int type;
      //type refers to whether DateTime is task, meeting or itself
      //0 : DateTime
      //1 : Task
      //2 : Meeting
      //type should not be directly assigned and should be inherent qualities that will be
      //init. in an object's ctor.
  };

}

#endif /* DateTime_hpp */
