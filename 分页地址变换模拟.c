#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define Long 4096
int fno[10] = {32102, 443217, 6723, 8985, 11238, 29065, 234205, 45812, 240561, 300451}; // ҳ��

//�����в��������������ĺ���Ҫ����ǰ��

int GongShi(int addr_logic) //��ʽ��
{
    int p = addr_logic / Long; //ҳ��
    int d = addr_logic % Long; //ҳ��ƫ����
    int addr_physi = fno[p] * 4096 + d; //���������ַ
    return addr_physi; //���������ַ
}

int  BinaryToDecimal(char* str, int bit) //������תʮ���ƣ������ַ�������
{
    int i, pho = 0;
    for (i = 0; str[i] != '\0'; i++)
        pho += (str[i] - '0')*pow((double)2, (double)(bit - 2 - i));
    return pho;
}

void DecimalToBinary(int x, char* str, int bit) //����ʮ���������ַ��������Լ��ַ����鳤��
{
    int i, j = bit - 1;
    for (i = 0; i < j; i++)
       str[i] = '0';
    while (x != 0){ //ת������
        if (x % 2 == 1) str[--j] = '1';
        else str[--j] = '0';
        x /= 2;
    }
    str[bit- 1] = '\0';
}

void YingPin(char* addr_string) //Ӳƴ���������ַ�������
{
    int i, p;
    char High_bit[21]; // ��20λ�����ƴ���
    for (i = 0; i < 20; i++) //��ʼ��ҳ��
        High_bit[i] = addr_string[i];
    High_bit[20] = '\0';
    p = BinaryToDecimal(High_bit, 21); //������ҳ��ת��Ϊʮ����ҳ��
    DecimalToBinary(fno[p], High_bit, 21); //��ҳ�Ų������õ���ţ�תΪ������
    for (i = 0; i < 20; i++)
        addr_string[i] = High_bit[i];
}

void HexadecimalToBinary(char* addr_hex, char* addr_string) //ʮ������תΪ�����ƣ�����ʮ�������ַ��������Լ��������ַ�������
{
    int i, j, p = 0;
    char temp[5];
    char change[16][5] = {"0000", "0001", "0010", "0011",
                            "0100", "0101", "0110", "0111",
                            "1000", "1001", "1010", "1011",
                            "1100", "1101", "1110", "1111"};
    for (i = 0; addr_hex[i] != '\0'; i++){
        if ((addr_hex[i] <= '9')&&(addr_hex[i] >= '0')) strcpy(temp, change[addr_hex[i] - '0']);
        //addr_hex[i]���ַ���תΪ�����±�ʱ��Ҫ��ȥ0��ASCIIֵ
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
    char addr_string[33]; //�����ַλ��Ϊ32
    char addr_hex[9]; //8λʮ�������߼���ַ����Ϊ��Ҫ��ſ��ַ�'\0'���������鳤��Ϊ9
    int addr_logic, addr_physi_GS, addr_physi_YP, temp;
    // ʮ�����߼���ַ, ʹ�ù�ʽ���������ַ�� ʹ��Ӳƴ����������ַ���м�ת����ַ

    printf("The address you want to enter is ___?\n");
    printf("Decimal--D    Hexadecimal--H\n");
    scanf(" %c", &i);
    printf("The address you want to output is ___?\n");
    printf("Decimal--D    Hexadecimal--H\n");
    scanf(" %c", &o);
    printf("Note:The high five bits of Hexadecimal must be less than \"00000a000\"!\n");
    //00000a000��Ӧ��ʮ������40960�պ���9��ҳ�ż���4096��ƫ����
    printf("Please input a legal logic address: ");
    //ʮ�����Ƶ�ַ�ĸ���λ����Ӧ�����Ƶĸ߶�ʮλ��ҪС��40960��������Ҳ�����Ӧ��ҳ��

    if (i == 'D'){ //�û�ȷ������ʮ���Ƶ�ַ
        scanf("%d", &addr_logic);
        //ʹ�ù�ʽ��
        addr_physi_GS = GongShi(addr_logic);
        //ʹ��Ӳƴ��
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
    else if (i == 'H'){ //�û�ȷ������ʮ�����Ƶ�ַ
        scanf("%s", addr_hex);
        HexadecimalToBinary(addr_hex, addr_string);
        //ʹ�ù�ʽ��
        addr_logic = BinaryToDecimal(addr_string, 33); //ʮ������ת��Ϊʮ���ƺ�õ����߼���ַ
        addr_physi_GS = GongShi(addr_logic);
        //ʹ��Ӳƴ��
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
