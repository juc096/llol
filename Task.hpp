//
//  Task.hpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#ifndef Task_hpp
#define Task_hpp

#include <stdio.h>
#include "DateTime.hpp"
#include <string>

namespace ECE141 {

  class Task : public DateTime {
  public:
      Task(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson);
      Task(const Task& aTask);
      Task(const Task* aTask);
      Task& operator= (const Task& aTask);
      ~Task(){};
    
      Task&         setDate(const DateTime &aDate);
      Task&         setTitle(const std::string &aTitle);
      Task&         setPerson(const std::string &aPerson);
      
      DateTime&     getDate();
      std::string&  getTitle();
      std::string&  getPerson();
      
  protected:
      DateTime DT;
      std::string title, person;

  };

}

#endif /* Task_hpp */
