#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
//#define n 11 
using namespace std;

int n=10, leader;
int prio[10];
int status[10];
int ini;
struct timeval offset[10]; // Clock offsets for each node
double drift[10];          // Clock drift rates for each node
double time[10];
void elec(int ini){

leader=ini;
for(int i=0; i<n;i++){

    if(prio[ini]<prio[i]){
        cout<<"\nelection msg sent from "<<ini<<" to "<<i<<"\n";
        
        if(status[i]==1) {
            cout<<"\nOK msg sent back from "<<i;
            //elec(i);
        }
    
    }

}


for(int i=0; i<n;i++){

    if(prio[ini]<prio[i]){
        //cout<<"\nelection msg sent from "<<ini<<" to "<<i<<"\n";
        
        if(status[i]==1) {
            //cout<<"\nOK msg sent back from "<<i;
            elec(i);
        }
    
    }

}

 


}


int main(){


cout<<"assuming number of process is 10. \n enter the priorities for each process: \n";
for(int i=0; i<n;i++){
cin>>prio[i];

}

cout<<"enter status(0/1) for each process: \n";
for(int i=0; i<n;i++){
cin>>status[i];
}

cout<<"process which initiates election: "; cin>>ini;
cout<<"\n";
leader=ini;
elec(ini);

cout<<"\nfinally, leader is "<<leader;
// Synchronize clocks at regular intervals
while(1){
    // Calculate average clock offset and drift rate across all nodes
    for(int i=0;i<10;i++){
        offset[i].tv_sec = rand() % 60;                                 // Initialize to a random offset between 0 and 59 seconds
        offset[i].tv_usec = rand() % 1000000;                           // Initialize to a random offset between 0 and 999,999 microseconds
        drift[i] = (rand() % 100) / 1000.0;                             // Initialize to a random drift rate between 0 and 0.1 seconds per second
        time[i] = i + offset[i].tv_sec + offset[i].tv_usec / 1000000.0; // Initialize current time based on offset
        if(status[i]==0) time[i]=-1;
    }
    double total=0; int count = 0;
    for(int i=0;i<10;i++){
        if(time[i]==-1) continue;

        total+=time[i];count++;
    }
    double avg=total/count; 
    cout<<"\n average time is "<<avg;
    
    for(int i=0;i<10;i++){
        if(time[i]!=-1){
            time[i]=avg;
        }
    }
  for(int i=0;i<10;i++){
        
            cout<<"\n time of process "<<i<<" is "<<time[i];
        
    }
    sleep(5);
}


}