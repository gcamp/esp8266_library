
#ifndef Switch_H
#define Switch_H

class Switch {
  public:
  virtual void setup();

  virtual const char* getName() = 0;
  virtual void set(bool value) = 0;
};

#endif
