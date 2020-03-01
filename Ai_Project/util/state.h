#pragma once


class state
{
public:
  virtual ~state() = default;

public:
  state* ptr_ToNextState = nullptr;
  state* ptr_ToPrevState = nullptr;

  virtual void
  onEnter() = 0;

  virtual void 
  onLeave() = 0;


private:

};

