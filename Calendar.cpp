//
//  Calendar.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Calendar.hpp"
namespace ECE141 {


Calendar::Calendar(int aMonth, int aYear) : mon(aMonth), year(aYear), meeting_amount(0), task_amount(0) {
        days_in_cal = DateTime::get_daysinMonth(mon,year);
        dow_by_date = std::vector<DOW>(days_in_cal);
        init_DOWTable();
}

/*
 Destruct the object. Be careful about making sure to delete every
 newly created objected.
 */
Calendar::~Calendar() {
    for (auto it = items.begin(); it != items.end(); ++it) {
        for (auto it_vect = it->second.begin(); it_vect != it->second.end(); ++it_vect) {
            delete *it_vect;
        }
        //delete *it;
    }
    
}

Calendar::Calendar(const Calendar& aCal) : meeting_amount(0), task_amount(0){
    mon = aCal.mon;
    year = aCal.year;
    //task_amount = aCal.task_amount;
    //meeting_amount = aCal.meeting_amount;
    days_in_cal = aCal.days_in_cal;
    dow_by_date = aCal.dow_by_date;
    init_DOWTable();
    /*
    Deep copy the items mapvector
    */
    for (auto it = aCal.items.begin(); it != aCal.items.end(); ++it) {
        for (auto it_vect = it->second.begin(); it_vect != it->second.end(); ++it_vect) {
            if ((*it_vect)->getType() == TYPE_task) {
                Task* aTask = new Task(static_cast<Task *>(*it_vect));
                //increment_tasks();
                addItem(aTask);
            }
            else if ((*it_vect)->getType() == TYPE_meeting) {
                Meeting* aMeeting = new Meeting(static_cast<Meeting *>(*it_vect));
                //increment_meetings();
                addItem(aMeeting);
                
            }
            else {
                //this shouldn't happen
            }
        }
    }
    
}

Calendar& Calendar::operator= (const Calendar& aCal) {
    mon = aCal.mon;
    year = aCal.year;
    
    task_amount = aCal.task_amount;
    meeting_amount = aCal.meeting_amount;
    days_in_cal = aCal.days_in_cal;
    dow_by_date = aCal.dow_by_date;
    init_DOWTable();
    
    /*
     Deep copy the items mapvector
     */
    for (auto it = aCal.items.begin(); it != aCal.items.end(); ++it) {
        for (auto it_vect = it->second.begin(); it_vect != it->second.end(); ++it_vect) {
            if ((*it_vect)->getType() == TYPE_task) {
                //DateTime cur_date = DateTime(*it_vect);
                //Task * temp_task = static_cast<Task *>(*it_vect);
                Task* aTask = new Task(static_cast<Task *>(*it_vect));
                //increment_tasks();
                addItem(aTask);
            }
            else if ((*it_vect)->getType() == TYPE_meeting) {
                //DateTime cur_date = DateTime(*it_vect);
                //Meeting * temp_meeting = static_cast<Meeting *>(*it_vect);
                Meeting* aMeeting = new Meeting(static_cast<Meeting *>(*it_vect));
                //increment_meetings();
                addItem(aMeeting);
                
            }
            else {
                //this shouldn't happen
            }
        }
    }
    
    return *this;
}

/*
init the tables for fast lookup
*/
Calendar& Calendar::init_DOWTable() {
    str_to_DOW["Saturday"]= DOW::saturday;
    str_to_DOW["Sunday"]=DOW::sunday;
    str_to_DOW["Monday"]=DOW::monday;
    str_to_DOW["Tuesday"]= DOW::tuesday;
    str_to_DOW["Wednesday"]= DOW::wednesday;
    str_to_DOW["Thursday"]= DOW::thursday;
    str_to_DOW["Friday"]= DOW::friday;
    
    for (int i = 0; i < days_in_cal; i++) {
        dow_by_date[i] = getDayOfWeek(mon,i+1,year);
    }
    
    return *this;
}

/*
 Function that add tasks/meetings to the calendar.
 */
Calendar& Calendar::addItem(DateTime *anItem) {
    int item_day = anItem->getDay();
    int item_month = anItem->getMonth();
    int item_year = anItem->getYear();
    int item_hour = anItem->getHour();
    int item_min = anItem->getMinutes();
    int item_type = anItem->getType();
    
    
    /* Add the datetime event to our tables*/
    items[item_day].push_back(anItem);
    
    items_by_dow[getDayOfWeek(item_month, item_day, item_year)].push_back(anItem);
    
    update_timeUnav(item_day, item_hour, item_min);
    
    if(item_type == TYPE_task) increment_tasks();
    else if (item_type == TYPE_meeting) increment_meetings();
    else {}
    return *this;
}

/*
 Function that updates which times are unavailable to be scheduled
 tasks/meetings at. this is for fast lookup
 */
Calendar & Calendar::update_timeUnav(int item_day, int item_hour, int item_min) {
    //becareful with maps as they will create object when indexing
    times_unav[item_day][item_hour] = 1;
    //if min is not 0, then the hour after is also unavailable
    if (item_min != 0) {
        //if next hour hits max_hour (24), then wrap around to
        //next day and make time 0 unav.
        if ((item_hour+1 > MAX_HOUR) && (item_day+1 <= days_in_cal)) {
            times_unav[item_day+1][0] = 1;
        }
        //else justmake next hour unav
        else {
            times_unav[item_day][item_hour+1] = 1;
        }
            
    }
            
    return *this;
            
}

            
            
     /*
      load the input filestream data into our calendar
      */
    bool Calendar::load(std::istream &anInputStream) {
    
        std::array<std::string, 4> theParts;
      std::string theLine;
      while (std::getline(anInputStream, theLine)) {
        std::istringstream theStringStream(theLine);
        int theCount=0;
          std::string token;
          
          //std::cout<<theLine<<std::endl;
          
        while (std::getline(theStringStream,token,',')){
            theParts.at(theCount++) = token;
        }
          
          std::string title = theParts.at(0);
          std::string datetime = theParts.at(1);
          //std::string time = theParts.at(2);
          std::string person1 = theParts.at(2);
          
          
          std::array<std::string, 2> dt_parts;
          std::array<int,3> theDate;
          std::array<int,2> theTime;
          
          int i = 0;
          
          //strip the quotes around datetime string
          datetime.erase(std::remove(datetime.begin(),datetime.end(),'\"'), datetime.end());
                
         //parse string to date and time
          std::istringstream parse_datetime(datetime);
          int dt_count = 0;
          while(parse_datetime.good()) {
              parse_datetime >> dt_parts.at(dt_count++);
          }
          //dt_count should be 2
          //std::cout << dt_count <<std::endl;
          
          std::string date = dt_parts.at(0);
          std::string time = dt_parts.at(1);
          
          std::istringstream parse_date(date);
          std::istringstream parse_time(time);
          
          
          while (std::getline(parse_date,token,'-')) {
              theDate.at(i++) = std::stoi(token);
          }
          
          i = 0;
          
          while (std::getline(parse_time,token,':')) {
              theTime.at(i++) = std::stoi(token);
          }
          int cur_year = theDate.at(0);
          int cur_day = theDate.at(2);
          int cur_mon = theDate.at(1);
          
          //do not include any datetimes that are not same month
          //as this calendar
          if ((cur_mon != mon) || (cur_year != year)) continue;
          
          int cur_hour = theTime.at(0);
          int cur_mins = theTime.at(1);
          
          //data parsed finally now we determine if we make a task or meeting
          switch (theCount) {
              case 3: {
                //Task
                  DateTime cur_date = DateTime(cur_day,cur_mon,cur_year,cur_hour,cur_mins);
                  Task* aTask = new Task(cur_date,title,person1);
                  //increment_tasks();
                  addItem(aTask);
                  break;
              }
              case 4: {
                  //Meeting
                  DateTime cur_date = DateTime(cur_day,cur_mon,cur_year,cur_hour,cur_mins);
                  std::string person2 = theParts.at(3);
                  Meeting* aMeeting = new Meeting(cur_date,title,person1,person2);
                  //increment_meetings();
                  addItem(aMeeting);
                  break;
              }
              default: {
                  std::cout<<"error;string should be composed of 4-5 elements"<<std::endl;
                  return false;
              }
          }
          
      }
      return true;
  }

/*
 attempt to return the table of unavailable hours given a day if possible
 
 if not possible (throws exception) it means that the entire day is available
 as the table doesn't exist
 */
std::unordered_map<int, int> Calendar::get_unav_DAY(int aDay) const {
    std::unordered_map<int, int> temp;
    try {
        temp = times_unav.at(aDay);
    }
    catch (const std::out_of_range& e) {
        
    }
    return temp;
}

/*
 Finds the first hour available given a day
 */
            
int Calendar::findhour_ifAvailable_DAY(const Calendar &anOther, int startHour, int stopHour, int cur_day) const {
    auto times_unav_OURS = get_unav_DAY(cur_day);
    auto times_unav_OTHER = anOther.get_unav_DAY(cur_day);
    int avail_hour = TIME_NOT_FOUND;
    
    /*
     given two "arrays" of unavailable times, we can sum them
     to find a slot where both are available.
     
     since unavailable times are denoted with value 1,
     then if we add the two time slots together, their values
     can only be 0, 1, or 2, where 0 is the only case where
     both are available.
     
     The logic is similar to how you'd do it with numpy
     */
    for (int i  = startHour; i <= stopHour; i++) {
        if((times_unav_OURS[i] + times_unav_OTHER[i]) == 0) {
            avail_hour = i;
            break;
        }
    }
    return avail_hour;
}


/*
 function that finds a first available hour given a DOW or any
 
 WARNING: Function is sensitive in the case where it does not
 handle cases where if a Calendar can not find a single
 open slot. In this edge case, it will return a simple DateTime
 using the default constructor.
 
 There is nothing in the write-up that says to take care of this
 so I'm hoping that is okay.
 */
DateTime  Calendar::firstAvailableHour(const Calendar &anOther, int startHour, int stopHour, const char *dow) const {
    
    int avail_hour = TIME_NOT_FOUND;
    DateTime aSlot;
    /*
     If we need a timeslot on a given dow, search those days only.
     */
    if (dow) {
        
        DOW theDay = getDOWFromString(dow);
        
        /* NOTE: dow_by_date is indexed by 0 */
        for (int i = 0; i < days_in_cal; i++) {
            if (dow_by_date[i] == theDay) {
                /* Determine if there is an avail time slot*/
                avail_hour = findhour_ifAvailable_DAY(anOther,startHour, stopHour, i+1);
               
                /* If time slot found, break*/
                if (avail_hour != TIME_NOT_FOUND) {
                    aSlot = DateTime(i+1, mon, year, avail_hour, 0, TYPE_dt);
                    break;
                }
            }
        }
    }
    /*
     If we don't have a specific DOW, then just find any.
     */
    else {
        for (int i = 0; i < days_in_cal; i++) {
            /* Determine if there is an avail time slot*/
            avail_hour= findhour_ifAvailable_DAY(anOther,startHour, stopHour, i+1);
            
            /* If time slot found, break*/
            if (avail_hour != TIME_NOT_FOUND) {
                aSlot = DateTime(i+1, mon, year, avail_hour, 0, TYPE_dt);
                break;
            }
        }
    }
    
    return aSlot;
}
/*
 overloaded output stream
 */
  std::ostream & operator << (std::ostream &anOutput, const Calendar &aCalendar) {
      aCalendar.show(anOutput);
    return anOutput;
  }



void Calendar::increment_meetings() {
    meeting_amount++;
}
void Calendar::increment_tasks() {
    task_amount++;
}
int Calendar::countTasks() const{
    return task_amount;
}
int Calendar::countMeetings() const {
    return meeting_amount;
}

DOW Calendar::getDOWFromString(const char *dow)const {
    return str_to_DOW.at(dow);
}

DOW Calendar::getDayOfWeek(int aMonth, int aDay, int aYear)const {
    if (aMonth<3) {
      aMonth+=12;
      aYear--;
    }
        
    int k = aYear % 100;
    int j = aYear / 100;
    int theDOY = aDay + 13*(aMonth+1)/5 + k + k/4 + j/4 + 5*j;
    int theDOW = theDOY % 7;
    static DOW kDOWMap[]= {
      DOW::saturday, DOW::sunday, DOW::monday, DOW::tuesday,
      DOW::wednesday, DOW::thursday, DOW::friday};
    return kDOWMap[theDOW];
}


int Calendar::countItemsForDate(const DateTime &aDateTime) const {
    int aDay = aDateTime.getDay();
    int item_amt = 0;
    
    if ((aDateTime.getMonth() != mon) || (aDateTime.getYear() != year)) {
        return item_amt;
    }
    
    try {
        item_amt = items.at(aDay).size();
    }
    catch (const std::out_of_range& e) {
        
    }
    return item_amt;
    
}
bool Calendar::inRange(int aValue, int aMin, int aMax) const{
  return (aValue>=aMin) && (aValue<aMax);
}
const Calendar& Calendar::show(std::ostream &anOutput) const {
    std::ostringstream theHeader;
     theHeader << DateTime::getMonthName(mon) << " " << year;
     
     anOutput <<
       "|------------------------------------------------|\n";
     anOutput << "|  " << std::setw(46) << std::left
       << theHeader.str() << "|\n";
    anOutput << "|------------------------------------------------|\n";
    anOutput << "|  Su  |  Mo  |  Tu  |  We  |  Th  |  Fr  |  Sa  |\n";
    anOutput << "|------------------------------------------------|\n";
     
    int theDayNum=-(int)getDayOfWeek(mon,1,year);
    int theDaysInMonth=days_in_cal;
    
     for(int row=0;row<5;row++) {
       for(int col=0;col<7;col++) {
         anOutput << "|  " << std::setw(4);
           if(inRange(++theDayNum,1,theDaysInMonth+1)) {
               int amt_of_items = countItemsForDate(DateTime(theDayNum, mon,year));
               if (amt_of_items)
                   anOutput << amt_of_items;
               else
                   anOutput << " ";
           }
         else anOutput << " ";
       }
       anOutput <<
         "|\n|------------------------------------------------|\n";
     }
     return *this;
    
}

const Calendar& Calendar::showSummary(std::ostream &anOutput) const {
    std::ostringstream theHeader;
     theHeader << DateTime::getMonthName(mon) << " " << year;
     
     anOutput <<
       "|------------------------------------------------|\n";
     anOutput << "|  " << std::setw(46) << std::left
       << theHeader.str() << "|\n";
    anOutput << "|------------------------------------------------|\n";
    
    std::string abrev_mon = DateTime::getMonthName(mon);
    abrev_mon = abrev_mon.substr(0,3);
    
    for (auto it = items.begin(); it != items.end(); ++it) {
        for (auto it_vect = it->second.begin(); it_vect != it->second.end(); ++it_vect) {
            std::ostringstream info;
            int abrev_hour = (*it_vect)->getHour();
            char am_pm = 'a';
            if(abrev_hour/12 == 1) {
                abrev_hour = abrev_hour % 12;
                am_pm = 'p';
            }
            
            info <<abrev_mon << " " << (*it_vect)->getDay();
            info<<",  " <<abrev_hour << am_pm;
            
            
            if((*it_vect)->getType() == TYPE_task) {
                Task* aTask = static_cast<Task *>(*it_vect);
                info << "     | Task: " <<aTask->getTitle();
                anOutput << "|  " <<std::setw(46) << std::left << info.str() <<"|\n";
            }
            else if((*it_vect)->getType() == TYPE_meeting) {
                Meeting* aMeeting =static_cast<Meeting *>(*it_vect);
                info << "     | Meeting: " <<aMeeting->getTitle();
                anOutput << "|  " <<std::setw(46) << std::left << info.str() <<"|\n";
                info.str("");
                info.clear();
                info << aMeeting->getPerson(1) << ", " <<aMeeting->getPerson(2);
                anOutput << "|  " <<std::setw(46) << std::left << info.str() <<"|\n";
                
            }
            else {
                anOutput <<
                "|\n|------------------------------------------------|\n";
            }
            anOutput <<
            "|\n|------------------------------------------------|\n";
        }
        
    }
    return *this;
}


  
}
