#pragma once

class TestComWebEventHandlerRt :
  public IDispEventSimpleImpl<ID_TESTCOMSINK, 
                              TestComWebEventHandlerRt, 
                              &DIID_DITestAtl7WebEvents>
{
public:
  TestComWebEventHandlerRt(void);
  virtual ~TestComWebEventHandlerRt(void);
};
