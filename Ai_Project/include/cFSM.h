#include <utility>
#include"BaseState.h"

enum states
{
  idle,
};

class cFSM
{
public:
  cFSM();
  ~cFSM() = default;


private:

  BaseState* mptr_currentState = nullptr;

  states m_state = states::idle;
};


