#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc,char* argv[]){

  if(argc < 2){
    printf(1,"Argumen Harus 2, file 1 dan file 2\n");
    exit();
  }
  int fd1,fd2;
  if((fd1=open(argv[1],O_RDONLY)) < 0){
    printf(1,"Error membuka file %s\n",argv[1]);
    exit();
  }

  if((fd2=open(argv[2],O_RDONLY)) < 0){
    printf(1,"Error membuka file %s\n",argv[2]);
    exit();
  }


  //Ngambil karakter 1 1
  // int tes,tes2;
  // char buff[1],buff2[1];
  // while((tes = read(fd1,buff,1)) > 0 || (tes2 = read(fd2,buff2,1)) > 0){
  //
  //   printf(1,"%s",buff);
  // }
  //

  // Full trus dibandingin
  char buff[100];//sbuff2[100];
  read(fd1,buff,99);

  char buff2[100];
  read(fd2,buff2,99);
  int i = 0;
  int col = 1;
  int row = 0;
  while(i < 99){

    if(buff[i] != buff2[i])
      break;

    col++;
    if(buff[i] == '\n'){
      row++;
      col = 1;
    }
    i++;
  }

  printf(1,"The first difference found in col %d and line %d\n",col,row);
  // for(int i = 0; i < 99;i++){
  //   printf(1,"%c",buff[i]);
  // }



  exit();
}
