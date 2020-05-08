# FP_SISOP20_T11
# List Command :
## cmp , base64 , pwd

## pwd
Mendapatkan Working Directory
Source : [pwd.c](/pwd.c)

```
static int getCwd(char* resPath);
```
Fungsi utama untuk mendapatkan pwd
```
static char* upDir(int inode, char* ancestor, char* resPath);
```
Digunakan untuk naik ke parent directory
```
static int dirLookUp(int fd, int inode, char* p);
```
Mencari Nama dari Current Directory

## base64
Source : [base64.c](/base64.c)
```
char* base64Encoder(char input_str[], int len_str)
```
Main Encoding Function, Sisanya tinggal membuka file lalu membaca isinya kemudian di passing di base64Encoder

## cmp
Source : [cmp.c](/cmp.c)
```
if((fd1=open(argv[1],O_RDONLY)) < 0){
  printf(1,"Error membuka file %s\n",argv[1]);
  exit();
}
```
Membuka kedua file, lalu melakukan comparison per karakter diikuti dengan index (row dan col)
```
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
```
