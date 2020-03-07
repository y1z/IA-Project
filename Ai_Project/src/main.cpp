#include "AppSteeringBehaviors.h"

int
main()
{
  cBaseApp* ptr_app = new AppSteeringBehaviors();
  if (!ptr_app->init()) 
  {
    return -1;
  }
  int result = ptr_app->run();
  ptr_app->destroy();
  delete ptr_app;
  return  result;
}

