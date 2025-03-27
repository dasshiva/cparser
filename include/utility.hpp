#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <map>
#include <functional>
#include <string>

class StringSwitch {
public:
  StringSwitch(std::string &t, std::function<void()> def) 
          : target(t), actionDefault(def) {}

  void Case(const char* str, std::function<void()>& action);
  void Execute(); 
private:
  std::string target;
  std::map<std::string, std::function<void()>> actions;
  std::function<void()> actionDefault;
  
};

#endif
