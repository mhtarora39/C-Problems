#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

// todo Add support for boost

namespace appUtils {
  
  template<typename T1, typename T2>
  
  // 
  class OneToOne {
    public:
      OneToOne() noexcept {   
      }
      
      //One to one mapping 
      void add(const T1& key1,const T2& key2) {
        mfirst[key1] = key2;
        mSecond[key2] = key1;
      }

      T2 getValuefromFirst(const T1& key) {
        if(mfirst.find(key) != mfirst.end()){
          return mfirst[key]; 
        }
        return nullptr;
      }

      T1 getValuefromSecond(const T2& key) {
        if(mSecond.find(key) !=  mSecond.end()) {
          return mSecond[key]; 
        }
        return nullptr;
      }

      void remove(T1 key1,T2 key2) {
       
        if(mfirst.find(key1) != mfirst.end()){
          
          if(mfirst[key1] != key2) {
            return;
          }

          mSecond.erase(mfirst[key1]);
          mfirst.erase(key1); 
        }  
      }

      
      clear() {
        mSecond.clear();
        mfirst.clear();
      }

    private:
      std::map<T1,T2> mfirst;
      std::map<T2,T1> mSecond;


  };

  std::vector<std::string> split(std::string str, char del) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream sstr(str);
    while(std::getline(sstr,token,del)) {
      tokens.push_back(token);
    }
    return tokens;
  }
}