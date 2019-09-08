
#ifndef TIMER_FUNCTION_H

#define TIMER_FUNCTION_H

#include<ctime>   //TODO :  Remove the date and time in future 
#include<chrono>
#include<vector>
#include<sstream>
#include"Utils.hpp"


class Timer {
  using cppTimer  =  std::chrono::steady_clock;
  cppTimer::time_point mtNow;
  cppTimer::duration mdDuration;
  bool mbIsPause;
  //appUtils::OneToOne<string,int>  smap;

public:
  
  Timer() noexcept: mbIsPause(true), mdDuration{}{
    
    // smap.add("Jan",1);
    // smap.add("Fab",2);
    // smap.add("Mar",3);
    // smap.add("Apr",4);
    // smap.add("May",5);
    // smap.add("Jun",6);
    // smap.add("Jul",7);
    // smap.add("Aug",8);
    // smap.add("Sep",9);
    // smap.add("Oct",10);
    // smap.add("Nov",11);
    // smap.add("Dec",12);
  }

  // No Need of inline function 
  // by default every function is in lile

  /*
  inline is not when....

  1) If a function contains a loop. (for, while, do-while)
  2) If a function contains static variables.
  3) If a function is recursive.
  4) If a function return type is other than void, and the return statement doesn’t exist in function body.
  5) If a function contains switch or goto statement.
  
  */
  
  
  
  enum date{
    weekday,
    monthname,
    day,
    time,
    year,
    dateEnd
  };

  // enum time {
  //   hrs,
  //   mins,
  //   sec,
  //   timeEnd
  // };

  void Reset() noexcept {
    if(!mbIsPause) {
      mtNow    = {};
      mbIsPause = true;
      mdDuration = {};
    }
  }

  void Pause() noexcept {
    if(!mbIsPause) {
      mbIsPause = true;
      mdDuration += (cppTimer::now() - mtNow);
      mtNow = {};
    }
  }
  
  void Start() noexcept {
    
    if(mbIsPause) {         
      mtNow = cppTimer::now();
      mbIsPause = false;
    }
  
  }
  

  std::vector<int64_t> GetHHMMSS(const cppTimer::duration & duration) {
    
    std::vector<int64_t> timings;
    
    auto hours   = std::chrono::duration_cast<std::chrono::hours>(duration);
    timings.push_back(hours.count());

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
    timings.push_back(minutes.count());

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);
    timings.push_back(seconds.count());
    
    return timings;
  
  } 
  
  
  cppTimer::duration SessionTime() {
    
    auto now   =  cppTimer::now();
    if(!mbIsPause) {
      mdDuration += (now -mtNow);
    }
   
    return mdDuration;
  }
  
  //TODO Get Time Struct from here
  std::string CurrentDate() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    std::time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d-%m-%Y?%H:%M:%S",timeinfo);
    std::string str(buffer);
    auto time = appUtils::split(str,'?');
    return time[0];
  } 


};

#endif /*ENDING TIMER_FUNCTION_H */