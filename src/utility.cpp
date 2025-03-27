#include "utility.hpp"

void StringSwitch::Case(const char* str, std::function<void()>& action) {
  actions[str] = action;
}

void StringSwitch::Execute() {
  for (auto it = actions.begin();  it != actions.end(); ++it) {
    if (it->first == target) {
      it->second();
      return;
    }
  }
  
  actionDefault();
}
