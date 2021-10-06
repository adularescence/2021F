
#include "TestControl.h"


//network data
const string TestControl::titles[3]={"Dogs","Cats", "Ferrets"};
const string TestControl::subs[3] ={"Sub1", "Sub2", "Sub3"};
const string TestControl::creds[3] ={"0000", "1111", "2222"};
const string TestControl::hosts[3] ={"Irene", "Bob", "Alice"};

//const TestControl::string content[20];  - at end of file

void TestControl::launch(){
    //make a view, get input, launch the appropriate test
    TestView view;
    int choice = 5;

    while (choice!=0){
        view.showMenu(choice);
        switch(choice){
            case 1: podArrayTest(); break;
            case 2: playEpisodesTest(); break;
            case 3: networkTest(); break;
            case 4: downloadTest(); break;
            case 5: clientTest(); break;
        }
    }
}


void TestControl::podArrayTest(){
       
    Podcast* pod; 

    PodArray* parray = new PodArray();

    for (int j = 0; j < 3; ++j){
        parray->addPodcast(pod = new Podcast(titles[j],hosts[j]));
        cout<<"podcast added!"<<endl;
    }

    if(parray->isFull()){
        cout<<"parray is full"<<endl;
    }else{
        cout<<"parray is not full"<<endl;
    }

    Podcast* pod2;
    for (int j = 0; j < 3; ++j){
        if(parray->getPodcast(titles[j],&pod2)){
            cout<<"found podcast!"<<endl;
            pod2->print();
        }else{
            cout<<"podcast not found"<<endl;
        }
    }

    delete parray;
}

void TestControl::playEpisodesTest(){
    
    Podcast* pod; 

    pod = new Podcast(titles[1],hosts[1]);
    pod->print(); 
    for (int i = 0; i <5; ++i){
        stringstream ss;
        ss << "Clever Episode Title "<<i+1;
        string title = ss.str();
        pod->addEpisode(title, content[i]);
    }
    cout<<"Checking for corrupt data:"<<endl;
    pod->print();
    cout<<"Num episodes (5 expected): "<<pod->getNumEpisodes()<<endl;

    Episode* ep;
    int noEp = pod->getNumEpisodes()+1;
    if(!pod->getEpisode(noEp,&ep)){
        cout<<"Episode "<<noEp<<" not found! Correct!"<<endl;
    }else{
        cout<<"**Error!** Episode found in location "<<noEp<<". Let's listen to it:"<<endl;
        ep->play();
    }

    cout<<endl<<"Playing all episodes: "<<endl;
    for (int i = 0; i <5; i++){
        pod->getEpisode(i,&ep);
        ep->play();
    }

    delete pod;
    
}

void TestControl::initNetwork(Network* network){
    cout<<"Initializing network..."<<endl;
    for (int j = 0; j < 3; ++j){
        if(network->addPodcast(titles[j],hosts[j])){
            for (int i = j*5; i <(j+1)*5; ++i){
                stringstream ss;
                ss << "Episode "<<i;
                string title = ss.str();
                network->addEpisode(titles[j],title, content[i]);
            }
        }else{
            cout<<"***Error!*** Podcast not added!"<<endl;
        }
        network->addSubscriber(subs[j],creds[j]);
    }
}


void TestControl::networkTest(){

    Network* network = new Network("My Podcast Network");
    network->print();

    initNetwork(network);

    Podcast* pod;
    Episode* ep;
    cout<<"Get first 3 podcasts and play all episodes"<<endl;
    for (int i = 0; i < 3; ++i){
        if (network->getPodcast(titles[i],&pod)){
            pod->print();

            //if you are confident episodes work, comment this out
            for (int i = 0; i <5; i++){
                pod->getEpisode(i,&ep);
                ep->play();
            }

        }else{
            cout<<"***Error!*** Podcast "<<titles[i]<<" not found!"<<endl;
        }
    }
    cout<<endl<<"Checking the subscribers..."<<endl;
    for (int i = 0; i < 3; ++i){
        if(network->hasSubscriber(subs[i])){
            cout<<"Found subscriber "<<subs[i]<<endl;
        }else{
            cout<<"***Error!*** Subscriber "<<subs[i]<< " not found!"<<endl;
        }
    }

    cout<<endl<<"*********stream test************:"<<endl;
    for (int i = 0; i < 3; ++i){
        if (network->stream(subs[i],titles[i],i, &ep)){
            ep->play();
        }
    }
    cout<<"Streams should not be found:"<<endl;
    network->stream("Bad title", titles[1],3, &ep);
    network->stream(subs[1],"Bad subscriber",3, &ep);
    network->stream(subs[1],titles[1],6, &ep);

    delete network;
    
}

void TestControl::downloadTest(){
    Network* network = new Network("My Podcast Network");
    network->print();

    initNetwork(network);

    Podcast* pod;
    Episode* ep;
    cout<<"Downloading podcast "<<titles[1]<<endl;
    network->download(subs[0],titles[1], &pod);

    cout<<"Printing downloaded podcast:"<<endl;
    pod->print();

    cout<<"Playing podcast "<<titles[1]<<" Episode 2"<<endl;
    network->stream(subs[0],titles[1],1, &ep);

    ep->play();

    cout<<"Removing podcast "<<titles[1]<<" from network"<< endl;
    network->removePodcast(titles[1]);

    cout<<"attempt to stream "<<titles[1]<<" from network - should be not found"<<endl;
    if(network->stream(subs[0],titles[1],1, &ep)){
        cout<<"***Error!*** Episode not deleted? Playing episode:"<<endl;
        ep->play();
    }

    delete network;
}

void TestControl::clientTest(){
    Network* network = new Network("My Podcast Network");
    network->print();

    initNetwork(network);

    Client* client = new Client(subs[2]);

    cout<<"Downloading podcast "<<titles[1]<<" to "<<subs[2]<<endl;

    client->download(network, titles[1]);

    cout<<"Playing podcast "<<titles[1]<<" Episode 2 locally for subscriber "<<subs[0]<<endl;
    client->playLocal(titles[1],1);

    cout<<"Removing podcast "<<titles[1]<<" from network"<< endl;
    network->removePodcast(titles[1]);



    cout<<"attempt to stream "<<titles[1]<<" locally - should play"<<endl;
    client->playLocal(titles[1],1);

    delete network;
    delete client;
}

const string TestControl::content[20] = {"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. ",
  
  "Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.",
  
  "Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus.",

"Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper.",

"Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales.",

"Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta.",

"Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. ",

"Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. ",

"Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. ",

"Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. ",

"Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. ",

"Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. ",

"Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. ",

"Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. ",

"Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. ",

"Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. ",

"Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. ",

"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. ",

"Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. ",

"Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna."
};