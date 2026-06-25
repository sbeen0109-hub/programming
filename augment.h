#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int Ran()
{
    return rand() % 16;
}

int upg2(int damage)
{
    printf("압도적인 힘이 발동되어 강공의 공격력이 1.5배 증가합니다.\n");
    return damage * 3 / 2;
}

void upg3(int *damage_mult) //0 //1
{   
    
    srand(time(NULL));
    if ((Ran() % 4) == 0)
    {   
        printf("하드 카운터가 발동되어 공격력이 절반이 됩니다.\n");
        *damage_mult *= 2;
    }
}

int upg4(int damage, int hp, int is16on)
{
    printf("버서커의 효과로 체력에 비례하여 공격력이 증가합니다.\n");
    if (is16on)
    {
        if (hp <= 100)
            return damage + 5;
        else if (hp <= 110)
            return damage + 4;
        else if (hp <= 120)
            return damage + 3;
        else if (hp <= 130)
            return damage + 2;
        else if (hp <= 140)
            return damage + 1;
        else
            return damage;
    }
    else
    {
        if (hp <= 50)
            return damage + 5;
        else if (hp <= 60)
            return damage + 4;
        else if (hp <= 70)
            return damage + 3;
        else if (hp <= 80)
            return damage + 2;
        else if (hp <= 90)
            return damage + 1;
        else
            return damage;
    }
}

int upg6()
{
    srand(time(NULL));
    return ((Ran() % 8) == 0);
}

int upg7(int hp, int count)
{
    printf("쾌감이 발동되어 맞은 횟수마다 체력이 2씩 회복됩니다.\n");
    return hp + (2 * count);
}

void upg8(int *hp, int *cnt)
{
    if (*hp <= 0 && *cnt == 1)
    {
        printf("정신력이 발동되어 체력을 1 남기고 살아남습니다.\n");
        *cnt = 0;
        *hp = 1;
    }  
}

int upg9()
{
    srand(time(NULL));
    if ((Ran() % 1) == 0){
        printf("신속이 발동됩니다!\n");
        return 1;
    }
    return 0;
}

int upg11(int turns, int damage)
{
    if (turns <= 8){
        printf("원 펀 치의 효과로 8턴동안 공격력이 0이 됩니다.\n");
        return 0;
    }
    else{
        printf("원 펀 치의 효과로 8턴이 지나 공격력이 10배가 됩니다.\n");
        return damage * 10;
    }
}

int upg12(int hp)
{
    printf("재생력의 효과로 체력이 1씩 회복됩니다.\n");
    return hp + 1;
}

void upg13(int *damage, int *hp)
{
    *damage *= 2;
    *hp -= 5;
    printf("강공의 공격력이 2배가 되는 대신, 자신이 강공을 성공시킬 때마다 데미지를 5 입습니다!\n");
}

void upg15(int *damage, int *count)
{
    *damage = 2;
    *count *= 3;
    printf("속공의  기본공격력이 2가 되는 대신 속공의 공격 횟수가 3배가 되었습니다!\n");
}

int upg16(int hp)
{
    printf("최대 체력이 상승했습니다\n");
    return hp + 50;
}

void upg17(int *cnt, int *damage)
{
    if (*cnt == 0){
        *cnt += 1;
        *damage = 0;
        printf("첫번째 공격을 뎀프시롤로 회피했습니다\n\n");
    }
}

void upg21(int turns, int *p1, int *p2)
{   
    if (turns <= 5)
    {
        srand(time(NULL));
        *p1 = (Ran() % 3) + 1;
        *p2 = (Ran() % 3) + 1;
        printf("시작 후 5턴 동안 플레이어들이 서로 미쳐서 공격합니다!\n");
    }
}

void upg22()
{
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!\n");
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!\n");
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!");
    printf("정말미워!!! 정말미워!!! 정말미워!!!\n");
}

int upg29()
{
    srand(time(NULL));
    if ((Ran() % 4) == 0)
        return 1;
    return 0;
}