//
//  Meeting.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Meeting.hpp"
#include <iostream>

namespace ECE141 {
  
    Meeting::Meeting(const DateTime &aDT, const std::string &aTitle,
      const std::string &aPerson1, const std::string &aPerson2) : DateTime(aDT) {
        type = 2;
        DT = aDT;
        title = aTitle;
        person1 = aPerson1;
        person2 = aPerson2;
    }
    Meeting::Meeting(const Meeting& aMeeting) : DateTime(aMeeting){

        DT = aMeeting.DT;
        title = aMeeting.title;
        person1 = aMeeting.person1;
        person2 = aMeeting.person2;
    }

    Meeting::Meeting(const Meeting* aMeeting) : DateTime(aMeeting) {

        DT = aMeeting->DT;
        title = aMeeting->title;
        person1 = aMeeting->person1;
        person2 = aMeeting->person2;
    }
    Meeting& Meeting::operator= (const Meeting& aMeeting) {
        DateTime::operator=(aMeeting);

        DT = aMeeting.DT;
        title = aMeeting.title;
        person1 = aMeeting.person1;
        person2 = aMeeting.person2;
        return *this;
    }
      
    Meeting&     Meeting::setDate(const DateTime &aDate) {
        DT = aDate;
        return *this;
    }
    Meeting&     Meeting::setTitle(const std::string &aTitle) {
        title = aTitle;
        return *this;
    }
    Meeting&     Meeting::setPerson(const std::string &aName, int aPersonNumber) {
        switch (aPersonNumber) {
            case 1:
                person1 = aName;
                break;
            case 2:
                person2 = aName;
                break;
            default:
                break;
                //std::cout << "error! invalid int for person" <<std::endl;
               //ERROR STATEMENT
        }
        return *this;
    }
        
    DateTime &    Meeting::getDate() {return DT;}
    std::string& Meeting::getTitle() {return title;}
    std::string& Meeting::getPerson(int aPersonNumber){
        switch (aPersonNumber) {
            case 1:
                return person1;
                break;
            case 2:
                return person2;
                break;
            default:
                std::cout << "error" <<std::endl;
                return person1;
        }
    }


}
