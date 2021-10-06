#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>

#include "Network.h"
#include "TestView.h"
#include "Client.h"

using namespace std;


class TestControl
{
  public:
    
    void launch();
    

  private:
    void podArrayTest();
    void playEpisodesTest();
    void networkTest();
    void downloadTest();
    void clientTest();

    //helper function
    void initNetwork(Network*);

    const static string titles[3];
    const static string hosts[3];
    const static string subs[3];
    const static string creds[3];
    const static string content[20];


    
};

#endif
