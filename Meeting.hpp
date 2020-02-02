//
//  Meeting.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Meeting_hpp
#define Meeting_hpp

#include <stdio.h>
#include <string>
#include "DateTime.hpp"

namespace ECE141 {

  class Meeting : public DateTime {
  public:
      Meeting(const DateTime &aDT, const std::string &aTitle,
            const std::string &aPerson1, const std::string &aPerson2);
      Meeting(const Meeting& aMeeting);
      Meeting(const Meeting* aMeeting);
      Meeting& operator= (const Meeting& aMeeting);

      ~Meeting() {};
    
      Meeting&     setDate(const DateTime &aDate);
      Meeting&     setTitle(const std::string &aTitle);
      Meeting&     setPerson(const std::string &aName, int aPersonNumber); //a little different than the Task class?
      
      DateTime&    getDate();
      std::string& getTitle();
      std::string& getPerson(int aPersonNumber);
      
      

  protected:
    //add data members here...
      DateTime DT;
      std::string title, person1, person2;
  };

}

#endif /* Meeting_hpp */
