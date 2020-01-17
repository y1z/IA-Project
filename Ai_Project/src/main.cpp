#include "AppSteeringBehavoirs.h"

int
main()
{
  cBaseApp* ptr_app = new AppSteeringBehaviors();
  ptr_app->init();
  int result = ptr_app->run();
  ptr_app->destroy();

  return  result;
}

