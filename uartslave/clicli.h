#ifndef CLICLI_H
#define CLICLI_H
//#include "hvacontrol.h"

 class clicli {
  private:
  //hvacontrol &myhvacontrol;
  int number;
  
  public:
   //clicli(hvacontrol &myhvacontrol);
   clicli;
   void begin(int bdrate);   //must be called from  void setup()
   void run();   //must be called from  void loop()

 };
#endif 