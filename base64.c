#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#define SIZE 1000

char* base64Encoder(char input_str[], int len_str)
{
    //Set Karakter yang dipakai pada encoding base64
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Buffer yang hold result string
    char *res_str = (char *) malloc(SIZE * sizeof(char));

    int index, totalBit,pad,val,count,temp;
    int i, j, k = 0;

    //Loop untuk ngambil tiap tiga karakter terus hasilnya dimasukkin ke Hasil
    for (i = 0; i < len_str; i += 3)
        {
            val = 0, count = 0, totalBit = 0;
            for (j = i; j < len_str && j <= i + 2; j++)
            {
                // Val diubah menjadi binary
                val = val << 8;
                // Binary dari input_str
                val = val | input_str[j];
                //Menghitung apakah kelipatan 3
                count++;
            }
            // Setiap karakter 8 bit, jdi dikali 8
            totalBit = count * 8;
            // Di Mod 3 soalnya buat kasih '=' klo masih sisa
            pad = totalBit % 3;
            // Diambil 6 block bit dan dicari nilainya
            while (totalBit != 0)
            {
                // Ambil value tiap 6 block
                if (totalBit >= 6)
                {
                    temp = totalBit - 6;
                    // binary of 63 is (111111) f
                    index = (val >> temp) & 63;
                    totalBit -= 6;
                }
                else
                {
                    temp = 6 - totalBit;
                    // Kalau bitnya sisa kurang dari 6, di append 0
                    index = (val << temp) & 63;
                    totalBit = 0; // Dah habis
                }
                res_str[k++] = char_set[index];
            }
    }
    for (i = 1; i <= pad; i++)
    {
        res_str[k++] = '='; // Buat kalau nggak kelipatan 3 dikasih '='
    }
    res_str[k] = '\0';
    return res_str;
}


// Driver code
int main(int argc,char* argv[])
{
    if(argc < 1){
      printf(1,"Need more Argument");
    }
    int fd1;
    if((fd1=open(argv[1],O_RDONLY)) < 0){
      printf(1,"Error membuka file %s\n",argv[1]);
      exit();
    }
    char buff[1000];
    read(fd1,buff,1000);
    printf(1,"%s",buff);
    int i = 0;
    while(buff[i] != '\0'){
      i++;
    }
    // printf(1,"%d",i);
    printf(1,"%s\n",base64Encoder(buff,i-1));
    // char input_str[] = "MENON";
    // int len_str;

    exit();
}
