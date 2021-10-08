#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>

#include "Network.h"
#include "TestView.h"
#include "Client.h"
#include "Podcast.h"
#include "PodArray.h"

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

    static string titles[3];
    static string hosts[3];
    static string subs[3];
    static string creds[3];
    static string content[20];


    
};

#endif
