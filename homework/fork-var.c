#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
    int m_scope;

    int rc = fork();

    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }else if(rc == 0){
        printf("sub scope change from:%d, to:%d \n", m_scope, 50);
        m_scope = 50;
    }else{
        printf("main scope change from:%d, to:%d \n", m_scope, 100);
        m_scope = 100;
    }
    
    printf("last scope:%d \n", m_scope);
    return 0;
}