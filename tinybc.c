#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define oops(m,x) {perror(m);exit(x);}

int be_bc(int from[2],int to[2]);
int be_dc(int out[2],int in[2]);
int fatal (char *mess);

int main(){
    int from[2],to[2];
    int pid;
    if(pipe(from)==-1)
        oops("pipe fail",1);
    if(pipe(to)==-1)
        oops("pipe fail",1);
    pid=fork();
    if(pid==0)
        be_dc(to,from);
    else{
        be_bc(from,to);
        wait(NULL);
    }
}


int be_bc(int from[2],int to[2]){
    char message[BUFSIZ];
    int num1,num2;
    char option[BUFSIZ];
    FILE *fin,*fout;
    
    close(from[1]);
    close(to[0]);
    fin=fdopen(from[0],"r");
    fout=fdopen(to[1],"w");
    if(fin==NULL || fout==NULL)
        oops("error",1);
    while(printf("tinybc: "),(fgets(message,BUFSIZ,stdin))!=NULL){

        sscanf(message,"%d%[+-*/^]%d",&num1,option,&num2);
        if(fprintf(fout,"%d\n%d\n%c\np\n",num1,num2,*option)==EOF)
            fatal("error writing");
        fflush(fout);
        if(fgets(message,BUFSIZ,fin)==NULL)
            break;
        printf("%d %c %d = %s",num1,*option,num2,message);
    }
    fclose(fout);
    fclose(fin);
}

int be_dc(int out[2],int in[2]){
    if(dup2(out[0],0)==-1)
        oops("error",1);
    close(out[0]);
    close(out[1]);
    if(dup2(in[1],1)==-1)
        oops("error",1);
    close(in[0]);
    close(in[1]);
    execlp("dc","dc","-",NULL);
    oops("cannot run dc",5);
}

int fatal(char *mess){
    fprintf(stderr,"%s\n",mess);
    exit(1);
}









