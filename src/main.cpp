#include<logger.h>

using namespace std;

int main()
{
  Logger logger = getLogger();
  logger.log("Detector","test msg", Logger::Levels::INFO);
}
