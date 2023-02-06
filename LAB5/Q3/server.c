#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(){
    int serid,sessid;
    int n=20;
    int num[20];
    struct sockaddr_in server_address,client_address;
    int server_addlen,client_addlen;
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_address.sin_port=5081;
    server_addlen=sizeof(server_address);
    client_addlen=sizeof(client_addlen);
    serid=socket(AF_INET,SOCK_STREAM,0);
    bind(serid,(struct sockaddr*)&server_address,server_addlen);
    listen(serid,10);
    while(1){
        printf("Server is ready to accept ......\n");
        sessid=accept(serid,(struct sockaddr *)&client_address,&client_addlen);
        for(int i=0;i<n;i++){
            read(sessid,&num[i],sizeof(int));    
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(num[j]<num[i]){
                    int temp = num[i];
                    num[i] = num[j];
                    num[j] = temp;
                }
            }
        }
        printf("Sorted array:\n");
        for(int i=0;i<n;i++){
            printf("%d ",num[i]);
        }
        int cnt=0;
        for(int i=0;i<n;i++){
            cnt++;
            int j=i+1;
            while(j<n && num[i]==num[j]){
                j++;
            }
            i=j-1;
        }
        printf("\nSize: %d",cnt);
        int arr[cnt];
        int k=0;
        for(int i=0;i<n;i++){
            arr[k++]=num[i];
            int j=i+1;
            while(j<n && num[i]==num[j]){
                i++;
            }
        }
        printf("\nk: %d",k);
        for(int i=0;i<cnt;i++){
            write(sessid,&arr[i],sizeof(int));
        }
        //read(sessid,&,1);
        //write(sessid,&c,1);
        close(sessid);
    }
    return(0);
}