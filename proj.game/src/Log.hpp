#include <string>

namespace GoumzAndStuff {
  
class Log {
 public:
  static void debug(const std::string& msg);
  static void error(const std::string& msg);
};

}  // namespace GoumzAndStuff