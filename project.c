#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "augment.h"

void maingame();
void manual();
void augment(int ply);

int p1upg[16] = {0,};
int p2upg[16] = {0,};
char attack[3][200] = {"속공", "강공", "카운터"};

char augmentExplain[16][2][500] = {
    {{"압도적인 힘"}, {"강공의 공격력이 1.5배가 됩니다."}},
    {{"하드 카운터"}, {"25% 확률로 카운터를 맞은 상대의 다음턴 공격력이 절반이 됩니다."}},
    {{"버서커"}, {"받은 피해에 비례해서 데미지가 올라갑니다.  (최대 15, 체력이 10 줄었을 때마다 공격력 1 증가)"}},
    {{"패왕색 패기"}, {"12.5% 확률로 상대가 이번 턴에 행동하지 않습니다. 이후 상대는 10 데미지를 입습니다."}},
    {{"쾌감"}, {"상대에게 공격당할 때마다 체력을 2 회복합니다."}},
    {{"정신력"}, {"KO당할 피해를 받았을 때, 체력이 1 남습니다."}},
    {{"신속"}, {"자신이 피해를 받을 때, 12.5% 확률로 회피합니다."}},
    {{"원 펀 치"}, {"시작 후 20턴까지 공격력이 0이 됩니다. 대신, 20턴 이후 강공의 데미지가 10배 늘어납니다."}},
    {{"재생력"}, {"매 턴마다 체력이 1씩 회복됩니다."}},
    {{"하이리스크"}, {"강공의 공격력이 2배가 되는 대신, 자신이 강공을 성공시킬 때마다 데미지를 5 입습니다."}},
    {{"오라오라!"}, {"속공의  기본공격력이 2가 되는 대신 속공의 공격 횟수가 3배가 됩니다."}},
    {{"체급 상승"}, {"최대 체력이 상승합니다. (50)"}},
    {{"뎀프시롤"}, {"첫 번째 공격을 회피합니다."}},
    {{"광란의 밤"}, {"시작 후 5턴동안, 양쪽 플레이어 모두 미쳐서 자신 마음대로 공격합니다."}},
    {{"정말 미워!!!"}, {"당신은 상대가 정말 밉습니다. 공격당할 때마다, ""정말 미워!!!""라고 외칩니다."}},
    {{"사나이의 결투"}, {"무승부가 났을 때, 25% 확률로 최후의 1대1 승부를 해 이긴 사람이 그 라운드에서 승리합니다."}}
};

int main(int argc, char const *argv[])
{
    while (1)
    {

        printf("============================\n");
        printf("        LET's FIGHT!\n");
        printf(" 김도윤 VS 양하준 시뮬레이터\n\n");
        printf("1. 게임 시작\n");
        printf("2. 게임 설명\n");
        printf("3. 게임 종료\n");
        printf("============================\n\n");
        printf("원하는 조작을 입력해주세요 => ");

        int order;
        scanf("%d", &order);
        getchar();
        if (order == 1)
            maingame();
        else if (order == 2)
            manual();
        else if (order == 3)
            break;
        else
        {
            printf("잘못된 입력입니다. 메인 메뉴로 돌아갑니다.\n");
            Sleep(2000);
        }
    }

    system("cls");
    printf("플레이 해주셔서 감사합니다.\n");
    return 0;
}

void manual()
{
    system("cls");
    printf("========================================================================\n");
    printf(" 이 게임은 2명의 플레이어가 격투기를 펼치는 게임입니다.\n");
    printf(" 기본적으로, 플레이어에게는 세가지 기술이 주어집니다.\n");
    printf(" 강공보다 빠르게 공격하는 속공, \n");
    printf(" 카운터를 부수는 강공, \n");
    printf(" 속공을 막고 받아치는 카운터. \n");
    printf(" 속공은 강공을 이기고, 강공은 카운터를 이기고, 카운터는 속공을 이깁니다.\n");
    printf(" 마치 가위바위보 같은 거죠.\n");
    printf(" 속공은 1, 강공은 2, 카운터는 3을 입력하면 사용할 수 있습니다.\n");
    printf(" 상대의 심리를 읽고 이 3가지 기술을 사용해 승리하세요!\n");
    printf("========================================================================\n\n");
    printf(" 종료하려면 아무 글자나 입력해주세요. => ");
    getchar();
    system("cls");

    return;
}

void IsStat(int player) {
    int AugmentListSet[16]={0,};
    int j=0;
    if(player==1) {
        for(int i=0;i<16;i++) {
            if(p1upg[i]) {
                AugmentListSet[j]=i;
                j++;
            }
        }
    }
    else {
        for(int i=0;i<16;i++) {
            if(p2upg[i]) {
                AugmentListSet[j]=i;
                j++;
            }
        }
    }
    printf("Player %d 획득한 카드:\n", player);
    for(int i=0;i<16;i++) {
        if(AugmentListSet[i]) {
            printf("%s: %s\n", augmentExplain[AugmentListSet[i]][0], augmentExplain[AugmentListSet[i]][1]);
        }
    }
}

char P1Input()
{
    char p1turn;
    printf("Player 1 입력  1: 속공 / 2: 강공 / 3: 카운터\n");
    printf("부정행위 방지를 위해 입력은 보이지 않게 처리됩니다.\n");
    while (1)
    {
        p1turn = _getch();
        if (p1turn == '\n' || p1turn == '1' || p1turn == '2' || p1turn == '3' || p1turn ==27)
            break;
        if(p1turn==9) {
            IsStat(1);
            continue;
        }
        if(p1turn==48) {
            IsStat(2);
            continue;
        }
        printf("다른 거 입력하세요\n");
    }
    return p1turn - 48;
}

char P2Input()
{
    char p2turn;
    printf("Player 2 입력  4: 속공 / 5: 강공 / 6: 카운터\n");
    printf("부정행위 방지를 위해 입력은 보이지 않게 처리됩니다.\n");
    while (1)
    {
        p2turn = _getch();
        if (p2turn == '\n' || p2turn == '4' || p2turn == '5' || p2turn == '6' || p2turn ==27)
            break;
        if(p2turn==48) {
            IsStat(2);
            continue;
        }
        if(p2turn==9) {
            IsStat(1);
            continue;
        }
        printf("다른 거 입력하세요\n");
    }
    return p2turn - 51;
}

void maingame()
{
    memset(p1upg, 0, sizeof(p1upg));
    memset(p2upg, 0, sizeof(p2upg));
    int p1win = 0, p2win = 0;
    while (1)
    {
        printf("새로운 라운드\n");
        printf("%d : %d\n", p1win, p2win);
        srand(time(NULL));
        int turns = 0;
        int p1_hp = 100;
        int p2_hp = 100;
        int P1MaxHp, P2MaxHp;
        int p1_hitted = 0, p2_hitted = 0;
        int p1_damage_mult = 1, p2_damage_mult = 1;
        int damage;

        // 16번
        if (p1upg[11])
            p1_hp = upg16(p1_hp);
        if (p2upg[11])
            p2_hp = upg16(p2_hp);

        int p1_zap = 10, p2_zap = 10, p1_punch = 10, p2_punch = 10, p1_counter = 10, p2_counter = 10, p1_zapcount = 1, p2_zapcount = 1;
        int p1_upg8cnt = 1, p2_upg8cnt = 1;

        // 15번
        if (p1upg[10])
            upg15(&p1_zap, &p1_zapcount);
        if (p2upg[10])
            upg15(&p2_zap, &p2_zapcount);

        // 2번
        if (p1upg[0])
            p1_punch = upg2(p1_punch);
        if (p2upg[0])
            p2_punch = upg2(p2_punch);

        while (1)
        {
            printf("====================================================\n");
            turns += 1;
            int p1, p2;
            p1 = P1Input();
            if (p1 == -21)
            {
                printf("나가기\n");
                return;
            }
            p2 = P2Input();
            if (p2 == -21)
            {
                printf("나가기\n");
                return;
            }
            // 6번
            if (upg6() && p1upg[3])
            {
                printf("패왕색 패기로 이번턴에 p2가 행동하지 않습니다.\n");
                p2_hp-=damage;
                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p1_hp, P1MaxHp);
                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p2_hp, P2MaxHp);

                if (p1_hp <= 0){
                    printf("P1 승!\n");
                    break;
                }
                else if (p2_hp <= 0){
                    printf("P2 승!\n");
                    break;
                }
                continue;
            }

            if (upg6() && p2upg[3])
            {
                printf("패왕색 패기로 이번턴에 p1이 행동하지 않습니다.\n");
                p1_hp-=damage;
                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p1_hp, P1MaxHp);
                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p2_hp, P2MaxHp);

                if (p1_hp <= 0){
                    printf("P1 승!\n");
                    break;
                }
                else if (p2_hp <= 0){
                    printf("P2 승!\n");
                    break;
                }
                continue;
            }


            // 12번
            if(p1upg[8]) p1_hp = upg12(p1_hp);
            if(p2upg[8]) p2_hp = upg12(p2_hp);

            // 21번
            if (p1upg[13] || p2upg[13])
                upg21(turns, &p1, &p2);


            if ((p1 - p2 + 3) % 3 == 2) //p1 승일 때
            {
                // 22번
                if(p2upg[14]) upg22();
                if (p1 == 1)
                { // p1:속공 p2:강공
                    damage = p1_zap * p1_zapcount;
                    damage /= p1_damage_mult;
                    p1_damage_mult /= p1_damage_mult;
                    // 4번
                    if (p1upg[2])
                        damage = upg4(damage, p1_hp, p1upg[11]);

                    // 11번
                    if (p1upg[7]) damage = upg11(turns, damage);

                    // 17번
                    if (p2upg[12])
                        upg17(&p2_hitted, &damage);               

                    // 9번
                    if(p2upg[6]) {
                        if(upg9()) {
                            damage = 0;
                        }
                    }


                    p2_hp -= damage;

                    // 7번
                    if (p2upg[4])
                        p2_hp = upg7(p2_hp, p1_zapcount);
                }
                else if (p1 == 2)
                {
                    damage = p1_punch;
                    damage /= p1_damage_mult;
                    p1_damage_mult /= p1_damage_mult;

                    // 11번
                    if (p1upg[7]) damage = upg11(turns, damage);

                    // 4번
                    if (p1upg[2])
                        damage = upg4(damage, p1_hp, p1upg[11]);


                    // 17번
                    if (p2upg[12])
                        upg17(&p2_hitted, &damage);

                    // 9번
                    if(p2upg[6]) {
                        if(upg9()) {
                        damage=0;
                        }
                    }

                    // 13번
                    if(p1upg[9]) {
                        upg13(&damage, &p1_hp);
                    }

                    p2_hp -= damage;

                    // 7번
                    if (p2upg[4])
                        p2_hp = upg7(p2_hp, 1);
                }
                else if (p1 == 3)
                {
                    damage = p1_counter;
                    damage /= p1_damage_mult;
                    p1_damage_mult /= p1_damage_mult;

                    // 4번
                    if (p1upg[2])
                        damage = upg4(damage, p1_hp, p1upg[11]);
                    
                    // 17번
                    if (p1upg[12])
                        upg17(&p2_hitted, &damage);

                    // 11번
                    if (p1upg[7]) damage = upg11(turns, damage);

                    // 9번
                    if(p2upg[6]) {
                        if(upg9()) {
                        damage=0;

                        }
                    }


                    p2_hp -= damage;

                    // 7번
                    if (p2upg[4])
                        p2_hp = upg7(p2_hp, 1);

                    // 3번
                    if (p1upg[1])
                        upg3(&p2_damage_mult);
                    
                }
                // 8번
                if (p1upg[5]) upg8(&p1_hp, &p1_upg8cnt);
                if (p2upg[5]) upg8(&p2_hp, &p2_upg8cnt);

                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                printf("p1 : %s, p2 : %s\n", attack[p1 - 1], attack[p2 - 1]);
                printf("p1승 / 현재 턴 : %d\n", turns);
                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p1_hp, P1MaxHp);
                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p2_hp, P2MaxHp);
                printf("Damage: %d\n", damage);

            }

            else if ((p1 - p2 + 3) % 3 == 1) { // p2 승일 때
                if(p1upg[14]) upg22();
                if (p2 == 1)
                { // p1:속공 p2:카운터
                    damage = p2_counter;
                    damage /= p2_damage_mult;
                    p2_damage_mult /= p2_damage_mult;

                    // 4번
                    if (p2upg[2])
                        damage = upg4(damage, p1_hp, p1upg[11]);

                    // 17번
                    if (p1upg[12])
                        upg17(&p1_hitted, &damage);

                    // 11번
                    if (p2upg[7]) damage = upg11(turns, damage);

                    // 9번
                    if(p1upg[6]) {
                        if(upg9()) {
                        damage=0;
                        }
                    }

                    p1_hp -= damage;

                    // 7번
                    if (p1upg[4])
                        p1_hp = upg7(p1_hp, 1);

                }
                else if (p2 == 2)
                {
                    damage = p2_zap * p2_zapcount;
                    damage /= p2_damage_mult;
                    p2_damage_mult /= p2_damage_mult;

                    // 4번
                    if (p2upg[2])
                        damage = upg4(damage, p2_hp, p2upg[11]);

                    // 17번
                    if (p1upg[12])
                        upg17(&p1_hitted, &damage);

                    // 11번
                    if (p2upg[7]) damage = upg11(turns, damage);

                    // 9번
                    if(p2upg[6]) {
                        if(upg9()) {
                        damage=0;
                        }
                    }

                    // 13번
                    if(p2upg[9]) {
                        upg13(&damage,&p2_hp);
                    }

                    p1_hp -= damage;

                    // 7번
                    if (p1upg[4])
                        p1_hp = upg7(p1_hp, p2_zapcount);
                }
                else if (p2 == 3)
                {
                    damage = p2_punch;
                    damage /= p2_damage_mult;
                    p2_damage_mult /= p2_damage_mult;

                    // 4번
                    if (p2upg[2])
                        damage = upg4(damage, p2_hp, p2upg[11]);

                    // 17번
                    if (p1upg[12])
                        upg17(&p1_hitted, &damage);

                    // 11번
                    if (p2upg[7]) damage = upg11(turns, damage);
                        
                    // 9번
                    if(p2upg[6]) {
                        if(upg9()) {
                        damage=0;
                        }
                    }
                    
                    // 3번
                    if (p2upg[1])
                        upg3(&p1_damage_mult);

                    p1_hp -= damage;

                    // 7번
                    if (p1upg[4])
                        p1_hp = upg7(p1_hp, 1);
                }
                // 8번
                if (p1upg[5]) upg8(&p1_hp, &p1_upg8cnt);
                if (p2upg[5]) upg8(&p2_hp, &p2_upg8cnt);

                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                printf("p1 : %s, p2 : %s\n", attack[p1 - 1], attack[p2 - 1]);
                printf("p2승 / 현재 턴 : %d\n", turns);
                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p1_hp, P1MaxHp);
                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                printf("] %d / %d\n", p2_hp, P2MaxHp);
                printf("Damage: %d\n", damage);
            }
            else 
            {
                // 29번
                if (p1upg[15] || p2upg[15])
                {
                    if (upg29())
                    {
                        while (1)
                        {
                            printf("최후의 결투를 시작합니다...\n");
                            printf("다른 효과는 전부 무시하고, 이 결투의 승자가 라운드를 승리합니다.\n");
                            p1 = P1Input();
                            p2 = P2Input();
                            if ((p1 - p2 + 3) % 3 == 2)
                            {
                                p2_hp = 0;
                                printf("p1 : %s, p2 : %s\n", attack[p1 - 1], attack[p2 - 1]);
                                printf("p1 승!\n");
                                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                                printf("] %d / %d\n", p1_hp, P1MaxHp);
                                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                                printf("] %d / %d\n", p2_hp, P2MaxHp);
                                break;
                            }
                            else if ((p1 - p2 + 3) % 3 == 1)
                            {
                                p1_hp = 0;
                                printf("p1 : %s, p2 : %s\n", attack[p1 - 1], attack[p2 - 1]);
                                printf("p2 승!\n");
                                P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                                P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                                printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                                printf("] %d / %d\n", p1_hp, P1MaxHp);
                                printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                                printf("] %d / %d\n", p2_hp, P2MaxHp);                            
                                break;
                            }
                            else
                            {
                                printf("무승부입니다. 사나이의 결투를 다시 진행합니다.\n");
                            }
                        }
                    }
                }
                else {
                    printf("p1 : %s, p2 : %s\n", attack[p1 - 1], attack[p2 - 1]);
                    printf("무승부! / 현재 턴 : %d\n", turns);
                    P1MaxHp=((((p1upg[11])?150:100)+((p1upg[8])?turns:0))>((p1upg[11])?150:100))?(((p1upg[11])?150:100)+((p1upg[8])?turns:0)):((p1upg[11])?150:100);
                    P2MaxHp=((((p2upg[11])?150:100)+((p2upg[8])?turns:0))>((p2upg[11])?150:100))?(((p2upg[11])?150:100)+((p2upg[8])?turns:0)):((p2upg[11])?150:100);
                    printf("P1 HP[");for(int i=0;i<p1_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P1MaxHp-p1_hp)/2;i++) printf("░");
                    printf("] %d / %d\n", p1_hp, P1MaxHp);
                    printf("P2 HP[");for(int i=0;i<p2_hp/2;i++)printf("\033[31m█\033[0m");for(int i=0;i<(P2MaxHp-p2_hp)/2;i++) printf("░");
                    printf("] %d / %d\n", p2_hp, P2MaxHp);}
            }


            if (p1_hp <= 0 || p2_hp <= 0)
            {
                printf("KO!\n");
                break;
            }

            printf("\n");

        }
        if (p1_hp <= 0)
                p2win += 1;
            else
                p1win += 1;

            if (p1win == 5){
                printf("p1 승!\n");
                break;
            }
            else if (p2win == 5){
                printf("p2 승!\n");
                break;
            }

        if (p1_hp <= 0){
            augment(1);
        }

        else if (p2_hp <= 0){
            augment(2);
        }
    }
}

void augment(int ply)
{
    int randomN,select=0, i = 0;
    srand(time(NULL));
    int ranset[3] = {
        0,
    };
    int VArray[16]={0,};

    while (ranset[2] == 0)
    {
        randomN = Ran();
        if (ply == 1)
        {
            if (p1upg[randomN] || VArray[randomN]) {
                continue;
            }
            else {
                VArray[randomN] = 1;
                ranset[i] = randomN;
                i++;
            }
                
        }
        else
        {
            if (p2upg[randomN] || VArray[randomN]) {
                continue;
            }
            else {
                VArray[randomN] = 1;
                ranset[i] = randomN;
                i++;
            }

        }
    }
    printf("1. %s: %s\n", augmentExplain[ranset[0]][0], augmentExplain[ranset[0]][1]);
    printf("2. %s: %s\n", augmentExplain[ranset[1]][0], augmentExplain[ranset[1]][1]);
    printf("3. %s: %s\n", augmentExplain[ranset[2]][0], augmentExplain[ranset[2]][1]);

    printf("player %d 선택:\n", ply);
    while (1)
    {
        scanf("%c", &select);
        if(select=='1'||select=='2'||select=='3') {
            select= select-48;
            printf("%d번 선택함:\n", select);
            printf("%s: %s\n\n", augmentExplain[ranset[select-1]][0], augmentExplain[ranset[select-1]][1]);
            break;
        }
        else if(select=='\n') continue;
        else {
            printf("1, 2, 3 중 하나를 입력하세요.\n");
        }
    }
    
    if (ply == 1)
        p1upg[ranset[select - 1]] = 1;
    else
        p2upg[ranset[select - 1]] = 1;

}