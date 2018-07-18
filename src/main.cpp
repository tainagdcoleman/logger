#include "logger.h"
#include <vector>

using namespace std;

int main()
{
  Logger logger = Logger::getLogger();
  logger.log("Detector","test msg", Levels::INFO, {"lane"});
}
