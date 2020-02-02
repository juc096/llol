//
//  Task.cpp
//  Assignment2
//
//  Created by rick gessner on 1/15/20.
//  Copyright © 2020 rick gessner. All rights reserved.
//

#include "Task.hpp"

namespace ECE141 {

    /*
     ctor for task. must init type here
     */
    Task::Task(const DateTime &aDT, const std::string &aTitle, const std::string &aPerson) : DateTime(aDT) {
        type = 1;
        DT = aDT;
        title = aTitle;
        person = aPerson;
    }

    Task::Task(const Task& aTask) : DateTime(aTask) {

        DT = aTask.DT;
        title = aTask.title;
        person = aTask.person;
    }
    /*
     copy ctor given a pointer. mostly used when dealing with deep copying a vector of DateTime*
     */
    Task::Task(const Task * aTask) : DateTime(aTask) {

        DT = aTask->DT;
        title = aTask->title;
        person = aTask->person;
    }

    Task& Task::operator= (const Task& aTask) {
        DateTime::operator=(aTask);
        DT = aTask.DT;
        title = aTask.title;
        person = aTask.person;
        
        return *this;
    }

    Task&         Task::setDate(const DateTime &aDate) {
        DT = aDate;
        return *this;
    }
    Task&         Task::setTitle(const std::string &aTitle) {
        title = aTitle;
        return *this;
    }
    Task&         Task::setPerson(const std::string &aPerson) {
        person = aPerson;
        return *this;
    }

    DateTime&     Task::getDate() {
        return DT;
    }
    std::string&  Task::getTitle() {
        return title;
    }
    std::string&  Task::getPerson() {
        return person;
    }
}
