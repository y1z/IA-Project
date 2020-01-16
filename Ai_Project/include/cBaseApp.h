#pragma once
class cBaseApp
{
public:
  cBaseApp() = default;
  virtual ~cBaseApp() = default;

  virtual bool init() = 0;

  virtual int run() = 0;
  
};

