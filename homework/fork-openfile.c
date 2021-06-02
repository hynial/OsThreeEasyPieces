#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
    int m_scope;

    int o = open("./fo.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int sz;

    printf("fd = %d/n", o);
    if(o == -1){
        printf("fail number:%d", o);
        perror("Program");
        exit(o);
    }

    FILE * fp;
    fp = fopen("./fork-openfile.output", "w");

    int rc = fork();

    int start_m = 0;

    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }else if(rc == 0){
        fprintf(fp, "sub scope change from:%d, to:%d \n", m_scope, 50);
        m_scope = 50;

        sz = write(o, "sub hello geeks\n", strlen("sub hello geeks\n"));

        printf("hello\n");
        start_m = 1;
    }else{
        // wait(NULL);
        fprintf(fp,"main scope change from:%d, to:%d \n", m_scope, 100);
        m_scope = 100;

        sz = write(o, "main hello geeks\n", strlen("main hello geeks\n"));

        while(1){
            if(start_m == 1){
                printf("goodbye"); // 
                break;
            }
        }
    }
    
    fprintf(fp, "last scope:%d \n", m_scope);
    fclose(fp);

    close(o);
    return 0;
}