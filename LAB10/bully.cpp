#include <iostream>
#include <vector>
#include <algorithm>
//#define n 11 
using namespace std;

int n=10, leader;
int prio[10];
int status[10];
int ini;

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

return 0;
}
