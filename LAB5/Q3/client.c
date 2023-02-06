#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(){
    int sid;
    int arr[20] = {10,10,8,8,6,5,6,12,12,0,0,0,1,1,1,6,5,1,0,10};
    int n = sizeof(arr)/sizeof(int);
    struct sockaddr_in server_address;
    int server_addlen;
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_address.sin_port=5081;
    server_addlen=sizeof(server_address);
    sid=socket(AF_INET,SOCK_STREAM,0);
    connect(sid,(struct sockaddr *)&server_address,server_addlen);
    //read(sid,&arr,10);
    printf("Given array: \n");
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    for(int i=0;i<n;i++){
        //rintf("%d ",arr[i]);
        write(sid,&arr[i],sizeof(int));
    }
    printf("\n\nArray received from server is:\n");
    int num[7];
    int k=7;
    for(int i=0;i<k;i++){
        read(sid,&num[i],sizeof(int));    
    }
    for(int i=0;i<k;i++){
        printf("%d ",num[i]);
    }            
    close(sid);
    return(0);
}
