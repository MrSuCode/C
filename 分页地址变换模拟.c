#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define Long 4096
int fno[10] = {32102, 443217, 6723, 8985, 11238, 29065, 234205, 45812, 240561, 300451}; // 页表

//函数中不带有其他函数的函数要放在前面

int GongShi(int addr_logic) //公式法
{
    int p = addr_logic / Long; //页号
    int d = addr_logic % Long; //页内偏移量
    int addr_physi = fno[p] * 4096 + d; //计算物理地址
    return addr_physi; //返回物理地址
}

int  BinaryToDecimal(char* str, int bit) //二进制转十进制，传入字符数组名
{
    int i, pho = 0;
    for (i = 0; str[i] != '\0'; i++)
        pho += (str[i] - '0')*pow((double)2, (double)(bit - 2 - i));
    return pho;
}

void DecimalToBinary(int x, char* str, int bit) //传入十进制数、字符数组名以及字符数组长度
{
    int i, j = bit - 1;
    for (i = 0; i < j; i++)
       str[i] = '0';
    while (x != 0){ //转二进制
        if (x % 2 == 1) str[--j] = '1';
        else str[--j] = '0';
        x /= 2;
    }
    str[bit- 1] = '\0';
}

void YingPin(char* addr_string) //硬拼法，传入字符数组名
{
    int i, p;
    char High_bit[21]; // 高20位二进制代码
    for (i = 0; i < 20; i++) //初始化页号
        High_bit[i] = addr_string[i];
    High_bit[20] = '\0';
    p = BinaryToDecimal(High_bit, 21); //二进制页号转换为十进制页号
    DecimalToBinary(fno[p], High_bit, 21); //由页号查数组后得到块号，转为二进制
    for (i = 0; i < 20; i++)
        addr_string[i] = High_bit[i];
}

void HexadecimalToBinary(char* addr_hex, char* addr_string) //十六进制转为二进制，传入十六进制字符数组名以及二进制字符数组名
{
    int i, j, p = 0;
    char temp[5];
    char change[16][5] = {"0000", "0001", "0010", "0011",
                            "0100", "0101", "0110", "0111",
                            "1000", "1001", "1010", "1011",
                            "1100", "1101", "1110", "1111"};
    for (i = 0; addr_hex[i] != '\0'; i++){
        if ((addr_hex[i] <= '9')&&(addr_hex[i] >= '0')) strcpy(temp, change[addr_hex[i] - '0']);
        //addr_hex[i]是字符，转为数组下标时需要减去0的ASCII值
        else if ((addr_hex[i] == 'a')||(addr_hex[i] == 'A')) strcpy(temp, change[10]);
        else if ((addr_hex[i] == 'b')||(addr_hex[i] == 'B')) strcpy(temp, change[11]);
        else if ((addr_hex[i] == 'c')||(addr_hex[i] == 'C')) strcpy(temp, change[12]);
        else if ((addr_hex[i] == 'd')||(addr_hex[i] == 'D')) strcpy(temp, change[13]);
        else if ((addr_hex[i] == 'e')||(addr_hex[i] == 'E')) strcpy(temp, change[14]);
        else if ((addr_hex[i] == 'f')||(addr_hex[i] == 'F')) strcpy(temp, change[15]);
        for (j = 0; temp[j] != '\0'; j++){
            addr_string[p++] = temp[j];
        }
        addr_string[32] = '\0';
    }
}

int main()
{
    char i, o;
    char addr_string[33]; //虚拟地址位数为32
    char addr_hex[9]; //8位十六进制逻辑地址，因为还要存放空字符'\0'，所以数组长度为9
    int addr_logic, addr_physi_GS, addr_physi_YP, temp;
    // 十进制逻辑地址, 使用公式法后物理地址， 使用硬拼法后的物理地址，中间转换地址

    printf("The address you want to enter is ___?\n");
    printf("Decimal--D    Hexadecimal--H\n");
    scanf(" %c", &i);
    printf("The address you want to output is ___?\n");
    printf("Decimal--D    Hexadecimal--H\n");
    scanf(" %c", &o);
    printf("Note:The high five bits of Hexadecimal must be less than \"00000a000\"!\n");
    //00000a000对应的十进制数40960刚好是9的页号加上4096的偏移量
    printf("Please input a legal logic address: ");
    //十六进制地址的高五位（对应二进制的高二十位）要小于40960，否则查找不到对应的页号

    if (i == 'D'){ //用户确认输入十进制地址
        scanf("%d", &addr_logic);
        //使用公式法
        addr_physi_GS = GongShi(addr_logic);
        //使用硬拼法
        DecimalToBinary(addr_logic, addr_string, 33);
        YingPin(addr_string);
        addr_physi_YP = BinaryToDecimal(addr_string, 33);
        if (o == 'D'){
            printf("The physical address you get after GS:%d\n", addr_physi_GS);
            printf("The physical address you get after YP:%d", addr_physi_YP);
        }
        else {
            printf("The physical address you get after GS:%x\n", addr_physi_GS);
            printf("The physical address you get after YP:%x", addr_physi_YP);
        }
    }
    else if (i == 'H'){ //用户确认输入十六进制地址
        scanf("%s", addr_hex);
        HexadecimalToBinary(addr_hex, addr_string);
        //使用公式法
        addr_logic = BinaryToDecimal(addr_string, 33); //十六进制转换为十进制后得到的逻辑地址
        addr_physi_GS = GongShi(addr_logic);
        //使用硬拼法
        YingPin(addr_string);
        addr_physi_YP = BinaryToDecimal(addr_string, 33);
        if (o == 'D'){
            printf("The physical address you get after GS:%d\n", addr_physi_GS);
            printf("The physical address you get after YP:%d", addr_physi_YP);
        }
        else {
            printf("The physical address you get after GS:%x\n", addr_physi_GS);
            printf("The physical address you get after YP:%x", addr_physi_YP);
        }
    }
    return 0;
}
