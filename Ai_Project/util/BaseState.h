#pragma once


class BaseState
{
public:
  virtual ~BaseState() = default;

public:
  BaseState* ptr_toNextState = nullptr;
  BaseState* ptr_toPrevState = nullptr;

  virtual void
  onEnter() = 0;

  virtual void
  onExit() = 0;

  virtual void
  update() = 0;

private:

};

