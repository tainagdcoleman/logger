#include "logger.h"

using namespace std;

int main()
{
  Logger logger = Logger::getLogger();
  logger.log("Detector","test msg", Levels::INFO);
}
