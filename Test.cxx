#include <iostream>
#include <thread>
#include <unistd.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "TimerFunctions.h"
#include "Session.h"


using namespace std;
void sleepcp(int milliseconds) // Cross-platform sleep function
{
  clock_t time_end;
  time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
  
  while (clock() < time_end) {
  
  }

}

template <typename T>
void func(T data) {
  std::cout << "Func is there" << std::endl;
}


// int main() {
   
//   std::shared_ptr<IBasicStream<BinaryStream>> mystream(new BinaryStream("ABC"));
//   std::cout << "mystream is valid: " << mystream->IsValid() <<std::endl;
//   std::shared_ptr<ISessionDataBaseFectory< Session >> sess(new Session());
//   auto sessinfo(sess->BuildSessionInfo());
//   sessinfo.SetState(State::Invalid);
//   sessinfo.SetReminderTitle("This is uwful");
//   std::string as ="Anb";

//   sess->SetSessionInfo(as,sessinfo);
//   sess->SaveAllSession(*mystream);
//   bool status = sess->LoadSession(*mystream);
//   //TODO Flushing Issue needs to resolve
//   std::cout << "mystream is valid: " << mystream->IsValid() << std::endl;
//   auto sesinfo = sess->GetSessionInfo(as);
  
//   if(sesinfo.GetReminderTitle() == sessinfo.GetReminderTitle()) {
//     std::cout <<" Both sessions are equal as expected " << std::endl;
//   }
//   else {
//     std::cout <<" TODO Flushing Issue needs to resolve " << std::endl;
//   }
//   std::cin >> as;
//   // unsigned b  = a;
//   // std::cout<<"B  = " << b << " A = " << a << std::endl;
//   func(1);  
  

//   // long double  c = 5.1;
//   // double a = 5.1;
//   // float  b = 5.1;
//   // if(a != c) {
//   //   std::cout << "a != b" << std::endl;
    
//   // }


//   // else {
//   //   std::cout << "a == b" << std::endl;
//   // }
  
//   // std::cout << "size = " << sizeof(a) << " size = " << sizeof(c) << std::endl; 
//   // Timer tim;
//   // tim.Start();
//   // //char  a;
//   // sleepcp(2000);
//   // //this_thread::sleep_for (std::chrono::seconds(1));
//   // tim.Pause();
//   // //sleepcp(2000);
//   // tim.Start();
//   // //sleepcp(2000);
//   // cout <<  tim.SessionTime().count() << " == " <<" 2 " <<endl;
//   // tim.Start();
//   // sleepcp(2000);
//   // tim.Pause();
//   // //tim.Start();

//   // sleepcp(2000);
//   // tim.Pause();


   
//   // cout <<  tim.SessionTime().count() << " == "<<" 4 "<< endl;
//   // while(true);


//     // auto t = std::time(nullptr);
//     // auto tm = *std::localtime(&t);
//     // std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << std::endl;
//     return 0;

// }

class B {
  public: 
  B() {

  }
  ~B() {
    std::cout <<"Dis"
  } 
  void Procedure() {
    std::cout<<"Precedure is not overrided\n";
  }
};

class D : public B<D> {
  public:
  D():B() {

  }
  void Procedure() {
    std::cout<<"Precedure is overrided\n";
  }

};

int main()
{
   B* ptr = new D();
   ptr->Procedure();
  // std::fstream file ;
  // file.open("T",std::fstream::out | std::fstream::in );
  // auto value = file.is_open();
  // if(!value) {
  //   file.open("T",std::fstream::out);
  //   file.close()
  // }

  // std::string str = "Mohit is cool";
  // file << str;
  
  
  std::shared_ptr<IBasicStream<BinaryStream>> mystream(new BinaryStream("ABC"));
  std::cout << "mystream is valid: " << mystream->IsValid() << std::endl;
  std::shared_ptr<ISessionDataBaseFactory<Session>> sess(new Session());
  auto sessinfo(sess->BuildSessionInfo());
  sessinfo.SetState(State::Invalid);
  sessinfo.SetReminderTitle("This is awful");
  std::string as = "Anb";

  sess->SetSessionInfo(as, sessinfo);
  sess->SaveAllSession(*mystream);
  
  bool status = sess->LoadSession(*mystream);
  sess->Clear();
  //TODO Flushing Issue needs to resolve
  std::cout << "mystream is valid: " << status << std::endl;
  auto sesinfo = sess->GetSessionInfo(as);

  if (sesinfo.GetReminderTitle() == sessinfo.GetReminderTitle())
  {
    std::cout << "Both sessions are equal as expected " << std::endl;
  }
  else
  {
    std::cout << "TODO Flushing Issue needs to resolve " << std::endl;
  }
  int a;
  std::cin >> a;
  return 0;
  
}