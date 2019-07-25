#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MAX_NAME_SZ 100

typedef struct items{
    unsigned int sides, numberDice, rollDice, fatigue, maxFat, lvl, gold, enKill, nameLen;
    float curHealth, curMana;
    int hPotions, mPotions;
    float maxHealth, maxMana, exp, expToLevel;
    float dmgTaken, hRest, mRest;
    int armor, sword, staff;
    char armorType[10], swordType[10], staffType[10], spec[10], gender[7], race[10];
    int raceLen, gendLen, specLen;
    char *name;
    char raceType[10][10], gendType[2][10], armorVar[5][15], swordVar[5][15], staffVar[5][15];
    time_t t;
    int id;
    char innName[50][10], innFam[50][10];
}ITEMS;

typedef struct enemyStats{
    unsigned int sides, numberDice, rollDice, fatigue, maxFat, lvl;
    float curHealth, curMana;
    int hPotions, mPotions;
    float maxHealth, maxMana;
    float dmgTaken, hRest, mRest;
    int armor, sword, staff;
    unsigned int str,mgck,speed;
    char armorType[15], swordType[15], staffType[15], spec[10], gender[7], race[10], enemy[17];
    char raceType[10][10], gendType[2][10], enemyType[5][17], armorVar[5][15], swordVar[5][15], staffVar[5][15];
}ENEMYstats;

typedef struct skills{
    unsigned int str,mgck,speed;
}SKILLS;

typedef struct hallOfFame{
    int id;
    char *name;
    unsigned int lvl, enKill, nameLen;
    int raceLen, gendLen, specLen;
    char race[10], gender[7], spec[10];
}HALL_OF_FAME;

float healing(struct items *healing);
float mana(struct items *mana);
float damage(struct items *dmg);
float cast(struct items *dice, struct skills *magic);
float attack(struct items *dice, struct skills *attack);
float spellDmg(struct items *dice, struct skills *magic, int flag, char castType[10]);
float attackDmg(struct items *dice, struct skills *magic, int flag, char castType[7]);
float enemyAttackDmg(struct enemyStats *dice, int flag);
float enemyMagicDmg(struct enemyStats *dice, int flag);
float enemyHeal(struct enemyStats *healing);
float enemyRestMana(struct enemyStats *healing);
int roll(struct items *dice);
int addHPotion(struct items *healing);
int addMPotion(struct items *mana);
int encounter(struct enemyStats *stats, struct items *attr, struct skills *skill);
int battle(struct enemyStats *stats, struct items *attr, struct skills *skill);
int leveling(struct items *lvl, struct skills *skill);
unsigned int rollSkill(int level);
void display(struct items *attr, struct skills *skill);
void input(struct items *attr, struct skills *skill);
void characterCustomize(struct items *cust);
void charName(struct items *cust);
void setSkill(struct skills *skill);
void restFat(struct items *fat);
void equip(struct items *eq, struct skills *sk);
void restInn(struct items *fat);
void checkInv(struct items *inv);
void setStrings(struct items *set, struct enemyStats *en);
void hallOfFame(struct items *it, struct hallOfFame *hof);
void writehallOfFame(struct items *it, struct hallOfFame *hof);
void viewhallOfFame(struct items *it, struct hallOfFame *hof);
void emptyhallOfFame();
void check(struct items *it);
void flicker();
void clear();
void line();
void continueScreen(struct items *cnt);
void contNoFat();

int main(){
    struct items items1;
    struct skills skills1;
    struct enemyStats enemy1;
    struct hallOfFame hof1;
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    setStrings(&items1, &enemy1);

    charName(&items1);
    characterCustomize(&items1);
    setSkill(&skills1);
    input(&items1, &skills1);

    int option;
    while(items1.curHealth>0){
        check(&items1);
        checkInv(&items1);
        leveling(&items1, &skills1);
        if(items1.fatigue<=0){
            clear();
            printf("\n You have lost all your fatigue and need to rest");
            items1.fatigue++;
            printf("\n Resting... \n");
            contNoFat();
        }
        if(items1.curMana<=0){
            items1.curMana=0;
        }
        leveling(&items1, &skills1);
        clear();
        line();
        printf(" \tChoose:\n");
        line();
        printf("  1. Show Attributes/Inventory.\n");
        printf("  2. Manage Equipment.\n");
        printf("  3. Buy a Health Potion for 7 gold pieces.\n");
        printf("  4. Buy a Mana Potion for 5 gold pieces.\n");
        printf("  5. Sleep in the local inn to restore your attributes.\n");
        printf("  6. Encounter Enemy.\n");
        line();
        printf("  7. Cast Spell.\n");
        printf("  8. Perform Attack. \n");
        printf("  9. Restore Health.\n");
        printf(" 10. Restore Mana.\n");
        printf(" 11. Restore Fatigue. \n");
        printf(" 12. Take Damage.\n");
        line();
        printf(" 13. Re-roll character.\n");
        printf(" 14. Enter Hall of Fame. \n");
        printf(" 15. Exit.\n");

        line();
        printf(" \tPlease choose an option: ");
        scanf("%d", &option);

        switch(option){
        case(1):
            display(&items1, &skills1);
            break;
        case(2):
            equip(&items1, &skills1);
            break;
        case(3):
            addHPotion(&items1);
            break;
        case(4):
            addMPotion(&items1);
            break;
        case(5):
            restInn(&items1);
            break;
        case(6):
            encounter(&enemy1, &items1, &skills1);
            break;
        case(7):
            cast(&items1, &skills1);
            break;
        case(8):
            attack(&items1, &skills1);
            break;
        case(9):
            healing(&items1);
            break;
        case(10):
            mana(&items1);
            break;
        case(11):
            restFat(&items1);
            break;
        case(12):
            damage(&items1);
            break;
        case(13):
            //charName(&items1);
            characterCustomize(&items1);
            setSkill(&skills1);
            input(&items1, &skills1);
            break;
        case(14):
            hallOfFame(&items1, &hof1);
            break;
        case(15):
            exit(0);
            break;
        default:
            printf(" Error.");
            option=0;
            break;
        }
    }

    if(items1.curHealth<=0){
        clear();
        line();
        printf("\n \t You have lost all your health.\n\t\tGame over.\n");
        line();
        exit(0);
    }
    //items1.curHealth = healing(&items1);
    //items1.curMana = mana(&items1);

    //printf("\n Health : %3.2f, Mana: %3.2f, Dice Roll: %d, Potions left: %d", items1.curHealth, items1.curMana, items1.rollDice, items1.hPotions);
    return 0;
}

void line(){
    printf(" \n --------------------------------------------------------------------------------------------- \n");
}

void clear(){
    system("cls");
}

void check(struct items *cust){
    if(cust->gendLen == 0){
        clear();
        int flag, opt, i;
        printf(" There has been an error. \n Please input your gender again. \n");
        line();
        flag=0;
        while(flag!=1){
            printf("\n %s, what is your gender? \n", cust->name);
            for(i=0; i < (sizeof(cust->gendType) / sizeof(cust->gendType[0])) ;i++){
            printf(" %d.%s. \n", i+1, cust->gendType[i]);
            }
            line();
            printf(" Choose:");
            scanf("%d",&opt);
            line();
            switch(opt){
            case(1):
                strcpy(cust->gender,"Male");
                cust->gendLen = strlen(cust->gender);
                //printf("%d", cust->gendLen);
                if(cust->gendLen == 0){
                    printf("There has been an error. Please input again. \n");
                    flag = 0;
                }else{
                flag=1;
                }
                break;
            case(2):
                strcpy(cust->gender,"Female");
                cust->gendLen = strlen(cust->gender);
                //printf("%d", cust->gendLen);
                if(cust->gendLen == 0){
                    printf("There has been an error. Please input again. \n");
                    flag = 0;
                }
                flag=1;
                break;
            default:
                printf("Input error.");
                break;
            }
        }
        contNoFat();
        //flag = 0;
    }
}

void setStrings(struct items *set, struct enemyStats *en){
    strcpy(set->raceType[0], "Human");
    strcpy(set->raceType[1], "Elf");
    strcpy(set->raceType[2], "Dwarf");
    strcpy(set->raceType[3], "Undead");
    strcpy(set->raceType[4], "Orc");
    strcpy(set->raceType[5], "Halfling");
    strcpy(set->raceType[6], "Treefolk");
    strcpy(set->raceType[7], "Feline");
    strcpy(set->raceType[8], "Ogre");
    strcpy(set->raceType[9], "Russian");

    strcpy(set->gendType[0], "Male");
    strcpy(set->gendType[1], "Female");

    strcpy(set->armorVar[0], "Leather");
    strcpy(set->armorVar[1], "Iron");
    strcpy(set->armorVar[3], "Steel");
    strcpy(set->armorVar[4], "Ebony");
    strcpy(set->armorVar[2], "Bone");

    strcpy(set->swordVar[0], "Wooden");
    strcpy(set->swordVar[1], "Iron");
    strcpy(set->swordVar[2], "Steel");
    strcpy(set->swordVar[4], "Hell-forged");
    strcpy(set->swordVar[3], "Ebony");

    strcpy(set->staffVar[0], "Birch");
    strcpy(set->staffVar[1], "Ash");
    strcpy(set->staffVar[2], "Maple");
    strcpy(set->staffVar[3], "Redwood");
    strcpy(set->staffVar[4], "Mahogany");

    int i = 0;
    for(i=0; i<(sizeof(set->raceType)/sizeof(set->raceType[0]));i++){
        strcpy(en->raceType[i], set->raceType[i]);
       // printf(" %d.%s. \n", i+1, en->raceType[i]);
    }
    for(i=0; i<(sizeof(set->gendType)/sizeof(set->gendType[0]));i++){
        strcpy(en->gendType[i], set->gendType[i]);
        //printf(" %d.%s. \n", i+1, en->gendType[i]);
    }
    for(i=0; i<(sizeof(set->armorVar)/sizeof(set->armorVar[0]));i++){
        strcpy(en->armorVar[i], set->armorVar[i]);
        //printf(" %d.%s. \n", i+1, en->armorVar[i]);
    }
    for(i=0; i<(sizeof(set->swordVar)/sizeof(set->swordVar[0]));i++){
        strcpy(en->swordVar[i], set->swordVar[i]);
        //printf(" %d.%s. \n", i+1, en->swordVar[i]);
    }
    for(i=0; i<(sizeof(set->staffVar)/sizeof(set->staffVar[0]));i++){
        strcpy(en->staffVar[i], set->staffVar[i]);
        //printf(" %d.%s. \n", i+1, en->staffVar[i]);
    }

    strcpy(en->enemyType[0], "Bandit");
    strcpy(en->enemyType[1], "Highwayman");
    strcpy(en->enemyType[2], "Raider");
    strcpy(en->enemyType[3], "Cunning Merchant");
    strcpy(en->enemyType[4], "Lunatic");

    strcpy(set->innName[0], "John");
    strcpy(set->innName[1], "Sebastos");
    strcpy(set->innName[2], "William");
    strcpy(set->innName[3], "Barry");
    strcpy(set->innName[4], "Marcus");
    strcpy(set->innName[5], "Marco");
    strcpy(set->innName[6], "Jack");
    strcpy(set->innName[7], "Geoffrey");
    strcpy(set->innName[8], "Eduin");
    strcpy(set->innName[9], "Firmo");
    strcpy(set->innName[10], "Oswell");
    strcpy(set->innName[11], "Finn");
    strcpy(set->innName[12], "Maxwell");
    strcpy(set->innName[13], "Gallus");
    strcpy(set->innName[14], "Orpheus");
    strcpy(set->innName[15], "Kremona");
    strcpy(set->innName[16], "Philkin");
    strcpy(set->innName[17], "Oscar");
    strcpy(set->innName[18], "Fulk");
    strcpy(set->innName[19], "Quintin");
    strcpy(set->innName[20], "Quinton");
    strcpy(set->innName[21], "Petrakis");
    strcpy(set->innName[22], "Grimbold");
    strcpy(set->innName[23], "Issac");
    strcpy(set->innName[24], "Faber");
    strcpy(set->innName[25], "Castell");
    strcpy(set->innName[26], "Ned");
    strcpy(set->innName[27], "Fellipe");
    strcpy(set->innName[28], "Boris");
    strcpy(set->innName[29], "Astell");
    strcpy(set->innName[30], "Maleos");
    strcpy(set->innName[31], "Raimond");
    strcpy(set->innName[32], "Dreux");
    strcpy(set->innName[33], "Yvet");
    strcpy(set->innName[34], "Robertus");
    strcpy(set->innName[35], "James");
    strcpy(set->innName[36], "Lars");
    strcpy(set->innName[37], "Basyle");
    strcpy(set->innName[38], "Gregorz");
    strcpy(set->innName[39], "Stu");
    strcpy(set->innName[40], "Joffridus");
    strcpy(set->innName[41], "Bastun");
    strcpy(set->innName[42], "Tristan");
    strcpy(set->innName[43], "Ywain");
    strcpy(set->innName[44], "Allen");
    strcpy(set->innName[45], "Jeff");
    strcpy(set->innName[46], "Chares");
    strcpy(set->innName[47], "Herodos");
    strcpy(set->innName[48], "Damien");
    strcpy(set->innName[49], "Vlad");

    strcpy(set->innFam[0], "Cena");
    strcpy(set->innFam[1], "Arbuckle");
    strcpy(set->innFam[2], "Buser");
    strcpy(set->innFam[3], "Cumin");
    strcpy(set->innFam[4], "Schult");
    strcpy(set->innFam[5], "Schmidt");
    strcpy(set->innFam[6], "Amiti");
    strcpy(set->innFam[7], "Tsoni");
    strcpy(set->innFam[8], "Vasseur");
    strcpy(set->innFam[9], "Russo");
    strcpy(set->innFam[10], "Kaplan");
    strcpy(set->innFam[11], "Louppe");
    strcpy(set->innFam[12], "Lutz");
    strcpy(set->innFam[13], "Klimmer");
    strcpy(set->innFam[14], "Wilson");
    strcpy(set->innFam[15], "Troshani");
    strcpy(set->innFam[16], "Caprara");
    strcpy(set->innFam[17], "Forcella");
    strcpy(set->innFam[18], "Delluc");
    strcpy(set->innFam[19], "Mendiburu");
    strcpy(set->innFam[20], "Versteeg");
    strcpy(set->innFam[21], "Pichot");
    strcpy(set->innFam[22], "Nyssen");
    strcpy(set->innFam[23], "Stille");
    strcpy(set->innFam[24], "Mochirie");
    strcpy(set->innFam[25], "Vael");
    strcpy(set->innFam[26], "Tepes");
    strcpy(set->innFam[27], "Forge");
    strcpy(set->innFam[28], "Akerfell");
    strcpy(set->innFam[29], "Block");
    strcpy(set->innFam[30], "Owens");
    strcpy(set->innFam[31], "Schafer");
    strcpy(set->innFam[32], "Van Ghoul");
    strcpy(set->innFam[33], "Copia");
    strcpy(set->innFam[34], "Emeritus");
    strcpy(set->innFam[35], "Adonis");
    strcpy(set->innFam[36], "Hair");
    strcpy(set->innFam[37], "Barlow");
    strcpy(set->innFam[38], "DiGiorgio");
    strcpy(set->innFam[39], "Ulrich");
    strcpy(set->innFam[40], "Steele");
    strcpy(set->innFam[41], "Hetfield");
    strcpy(set->innFam[42], "Trujilio");
    strcpy(set->innFam[43], "Prator");
    strcpy(set->innFam[44], "Hayes");
    strcpy(set->innFam[45], "Bateman");
    strcpy(set->innFam[46], "Santolla");
    strcpy(set->innFam[47], "Persner");
    strcpy(set->innFam[48], "Grohl");
    strcpy(set->innFam[49], "Osbourne");
}

void continueScreen(struct items *cnt){
    cnt->fatigue--;
    line();
    printf("\n You have used up 1 point in fatigue.\n Remaining points : %d out of %d \n", cnt->fatigue, cnt->maxFat);
    printf(" Press any button to continue. \n");
    line();
    getch();
}

void contNoFat(){
    line();
    printf("\n Press any button to continue. \n");
    line();
    getch();
}

void flicker(){
    system("color 70");
    clock_t goal = 200 + clock();
    while (goal > clock());
    system("color 07");
}

void checkInv(struct items *inv){
    if(inv->gold <= 0){
        inv->gold=0;
    }
    if(inv->hPotions <= 0){
        inv->hPotions = 0;
    }
    if(inv->mPotions <= 0){
        inv->mPotions = 0;
    }
}

void charName(struct items *cust){
    line();
    //free(cust->name);
    cust->name = malloc(MAX_NAME_SZ);
    if(cust->name == NULL){
        printf(" Error allocation memory. Terminating.");
        exit(1);
    }
        printf("\n \t Greeting traveler. What is your name? \n");
        printf(" Choose wisely, as it can't be changed later. \n");
        printf(" I am : ");
        fgets(cust->name, MAX_NAME_SZ, stdin);
        if((strlen(cust->name) > 0) && (cust->name[strlen(cust->name) - 1]== '\n' )){
            cust->name[strlen(cust->name) - 1] = '\0';
        }

    //printf("Length name: %d", strlen(cust->name));
    cust->id = rand() + 1;
    cust->nameLen = strlen(cust->name);
    //printf(" id %d", cust->id);
    //contNoFat();
    }

void characterCustomize(struct items *cust){

    /*int j, k, l;
    for(l=0;l<=50;l++){
        j = rand()%50;
        k = rand()%50;
        printf("%s %s. \n", cust->innName[k], cust->innFam[j]);
        flicker();
    }
    contNoFat();*/


    int opt, flag=0, flCont=0;
    int i;
    while(flCont!=1){
        clear();
        if(strstr(cust->name, "Wisely") || strstr(cust->name, "Changed later") || strstr(cust->name, "wisely") || strstr(cust->name, "changed later")){
            printf(" You cheeky little shit.");
        }
        line();
        while(flag!=1){
            printf("\n %s, what is your race? \n", cust->name);
            for(i=0; i < (sizeof(cust->raceType) / sizeof(cust->raceType[0])) ;i++){
            printf(" %d.%s. \n", i+1, cust->raceType[i]);
            }
            line();
            printf(" Choose:");
            scanf("%d",&opt);
            line();
            switch(opt){
            case(1):
                strcpy(cust->race, cust->raceType[0]);
                flag=1;
                break;
            case(2):
                strcpy(cust->race,  cust->raceType[1]);
                flag=1;
                break;
            case(3):
                strcpy(cust->race,  cust->raceType[2]);
                flag=1;
                break;
            case(4):
                strcpy(cust->race,  cust->raceType[3]);
                flag=1;
                break;
            case(5):
                strcpy(cust->race,  cust->raceType[4]);
                flag=1;
                break;
            case(6):
                strcpy(cust->race,  cust->raceType[5]);
                flag=1;
                break;
            case(7):
                strcpy(cust->race,  cust->raceType[6]);
                flag=1;
                break;
            case(8):
                strcpy(cust->race,  cust->raceType[7]);
                flag=1;
                break;
            case(9):
                strcpy(cust->race,  cust->raceType[8]);
                flag=1;
                break;
            case(10):
                strcpy(cust->race,  cust->raceType[9]);
                flag=1;
                break;
            default:
                printf("Input error.");
                flag=0;
                break;
            }
        }
        flag=0;
        while(flag!=1){
            printf("\n %s, what is your gender? \n", cust->name);
            for(i=0; i < (sizeof(cust->gendType) / sizeof(cust->gendType[0])) ;i++){
            printf(" %d.%s. \n", i+1, cust->gendType[i]);
            }
            line();
            printf(" Choose:");
            scanf("%d",&opt);
            line();
            switch(opt){
            case(1):
                strcpy(cust->gender,"Male");
                cust->gendLen = strlen(cust->gender);
                //printf("%d", cust->gendLen);
                if(cust->gendLen == 0){
                    printf("There has been an error. Please input again. \n");
                    flag = 0;
                }else{
                flag=1;
                }
                break;
            case(2):
                strcpy(cust->gender,"Female");
                cust->gendLen = strlen(cust->gender);
                //printf("%d", cust->gendLen);
                if(cust->gendLen == 0){
                    printf("There has been an error. Please input again. \n");
                    flag = 0;
                }
                flag=1;
                break;
            default:
                printf("Input error.");
                break;
            }
        }
        line();
        printf(" %s, you are a %s %s. Is that correct? \n", cust->name, cust->gender, cust->race);
        printf(" 1.Yes. \n 2.No \n");
        printf("Choose :");
        scanf("%d", &opt);
        switch(opt){
        case(1):
            flCont=1;
            break;
        case(2):
            flCont=0;
            flag=0;
            break;
        default:
            printf("Input error.");
            flCont=0;
        break;
        }
}
    contNoFat();
}

void setSkill(struct skills *skill){
    int option, flag = 0;
    skill->str=0;
    skill->mgck=0;
    skill->speed=0;
    unsigned int totalPoints = 10;
    while(flag!=1){
        clear();
        printf(" \n \t You have %d points to set between your attributes. \n \t You cannot have more that 10 points in an attribute. \n \t Choose your attribute. \n", totalPoints);
        line();
        printf("  1. Add one point to Strength (currently %d points). \n Strength allows you to equip heavier armor and more powerful weapons and deal increased damage with a weapon. \n Strength also increases your maximum Hit Points. \n", skill->str);
        printf("  2. Add one point to Magicka (currently %d points). \n Magicka allows you to equip more powerful staffs and deal increased damage when spell-casting. \n Magicka also increases your maximum Mana Points. \n", skill->mgck);
        printf("  3. Add one point to Speed (currently %d points). \n Speed allows you to attack quicker, compared to your enemies. \n", skill->speed);
        printf("  4. Remove points from Strength. \n");
        printf("  5. Remove points from Magicka. \n");
        printf("  6. Remove points from Speed. \n");
        line();
        printf(" Choose :");
        scanf("%d", &option);

        line();
        switch(option){
            case(1):
                if(skill->str < 10){
                    skill->str++;
                    totalPoints--;
                }else {
                printf("\n \t You cannot have more that 10 points in an attribute. \n");
                contNoFat();
                }
                break;
            case(2):
                if(skill->mgck < 10){
                    skill->mgck++;
                    totalPoints--;
                }else {
                printf("\n \t You cannot have more that 10 points in an attribute. \n");
                contNoFat();
                }
                break;
            case(3):
                if(skill->speed < 10){
                    skill->speed++;
                    totalPoints--;
                }else {
                printf("\n \t You cannot have more that 10 points in an attribute. \n");
                contNoFat();
                }
                break;
            case(4):
                if(skill->str > 0){
                    skill->str--;
                    totalPoints++;
                }else{
                    printf(" You cannot remove points from an attribute you don't have any points in. \n");
                    contNoFat();
                }
                break;
            case(5):
                if(skill->mgck > 0){
                    skill->mgck--;
                    totalPoints++;
                }else{
                    printf(" You cannot remove points from an attribute you don't have any points in. \n");
                    contNoFat();
                }
                break;
            case(6):
                if(skill->speed > 0 ){
                    skill->speed--;
                    totalPoints++;
                }else{
                    printf(" You cannot remove points from an attribute you don't have any points in. \n");
                    contNoFat();
                }
                break;
            default:
                printf("Input Error. \n");
                contNoFat();
                break;
        }
    if(totalPoints<=0){
        clear();
        line();
        printf("\n \t You have used all your points. Are you satisfied with the results, or do you wish to try again? \n");
        printf(" Strength : %d points. \n Magicka : %d points. \n Speed : %d points. \n", skill->str, skill->mgck, skill->speed);
        printf(" 1. Continue. \n 2. Try again. \n");
        line();
        printf(" Choose :");
        scanf("%d", &option);
        line();
        switch(option){
            case(1):
                flag = 1;
                break;
            case(2):
                flag = 0;
                skill->str=0;
                skill->mgck=0;
                skill->speed=0;
                totalPoints=10;
                break;
            default:
                flag=0;
                flag = 0;
                skill->str=0;
                skill->mgck=0;
                skill->speed=0;
                totalPoints=10;
                printf("Input Error. Re-rolling.\n");
                contNoFat();
                break;
            }
        }
    }
       /* skill->str = rollSkill();
        skill->mgck = rollSkill();
        skill->speed = rollSkill();
        printf("\t Press any button to roll for your skills (0 to 10): \n");
        getch();
        printf(" You rolled %d Strength. \n", skill->str);
        printf(" You rolled %d Magicka. \n", skill->mgck);
        printf(" You rolled %d Speed. \n", skill->speed);
        printf(" Do you wish to change your skills?\n 1.Yes \n 2.No \n Choose:");
        scanf("%d", &option);

        switch(option){
        case(1):
            flag = 0;
            setSkill(skill);
            break;
        case(2):
            flag = 1;
            break;
        default:
            printf("Input Error. Re-rolling... \n");
            contNoFat();
            setSkill(skill);
            break;
        }*/
}

int leveling(struct items *lvl, struct skills *skill){
    clear();
    int option, flag = 2;
    if(lvl->exp<=0){lvl->exp=0;}
    if(lvl->exp >= lvl->expToLevel){
        lvl->lvl++;
        lvl->exp=lvl->exp - lvl->expToLevel;
        lvl->expToLevel = lvl->expToLevel + (0.6*lvl->lvl);
        lvl->maxHealth = lvl->maxHealth + (0.5*lvl->lvl);
        printf(" Congratulations! You have leveled up to level %d. \n",lvl->lvl);
        printf(" Your stats have increased : \n");
        printf(" Maximum Health increased to: %3.2f. \n", lvl->maxHealth);
        if(lvl->maxMana!=0){
            lvl->maxMana = lvl->maxMana + (0.5*lvl->lvl);
            printf(" Maximum Magicka increased to: %3.2f. \n", lvl->maxMana);
        }
        if(lvl->lvl%5 == 0){
            flag = 1;
            while(flag!=2){
                line();
                printf(" At this level you can choose to add one point to one of your stats. \n");
                printf(" Please select: \n 1. Add one point to Strength. \n 2. Add one point to Magicka.\n 3. Add one point to Speed. \n");
                printf(" Choose: ");
                scanf("%d", &option);
                switch(option){
                case(1):
                    skill->str++;
                    flag = 2;
                    contNoFat();
                break;
                case(2):
                    skill->mgck++;
                    flag = 2;
                    contNoFat();
                break;
                case(3):
                    skill->speed++;
                    flag = 2;
                    contNoFat();
                break;
                default:
                    printf("Input error. \n");
                    flag = 1;
                    contNoFat();
                break;
                }
            }
        }
        line();
        printf(" Experience needed for level %d : %3.2f. \n", lvl->lvl+1, lvl->expToLevel);
        contNoFat();
    }
}

void input(struct items *attr, struct skills *skill){
    clear();
    int option, flag = 0;
    while(flag!=1){
        clear();
        printf("\n \t Choose your specialization: \n");
        printf("\n \t You must have at least an equal amount of points in your attributes as \n \t \t the bonuses that the specialization gives. \n");
        line();
        printf("  1. Barbarian. \n A barbarian receives a bonus of +3 to Strength.\n Barbarians start with 0 gold pieces. \n");
        printf("  2. Wizard. \n A wizard receives a bonus of +3 to Magicka. \n Wizards start with 5 gold pieces. \n");
        printf("  3. Thief. \n A thief receives a bonus of +3 to Speed. \n Thieves start with 20 gold pieces. \n");
        printf("  4. Spellsword. \n A spellsword receives a bonus of +2 to Strength and a bonus of +1 to Magicka. \n Spellswords start with 10 gold pieces. \n");
        printf("  5. Battlemage. \n A battlemage receives a bonus of +2 to Magicka and a bonus of +1 to Strength. \n Battlemages start with 10 gold pieces. \n");
        printf("  6. Assassin. \n An assassin receives a bonus of +2 to Speed and a bonus of +1 to Strength. \n Assassins start with 10 gold pieces. \n");
        printf("  7. Knight. \n A knight receives a bonus of +2 to Strength and a bonus of +1 to Speed. \n Knights start with 10 gold pieces. \n");
        printf("  8. Warlock. \n A warlock receives a bonus of +2 to Magicka and a bonus of +1 to Speed. \n Warlock start with 5 gold pieces. \n");
        printf("  9. Nightblade. \n A nightblade receives a bonus of +2 to Speed and a bonus of +1 to Magicka. \n Nightblades start with 5 gold pieces. \n");
        printf(" 10. Bard. \n A bard receives a bonus of +1 to all attributes. \n Bards start with 15 gold pieces. \n");
        line();
        printf(" Choose :");
        scanf("%d", &option);
        line();

        switch(option){
        case(1):
            if(skill->str >= 3){
                attr->gold=0;
                skill->str = skill->str + 3;
                strcpy(attr->spec,"Barbarian");
                line();
                printf(" You have chosen to be a %s, increasing your Strength to %d",attr->spec, skill->str);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Barbarian, unless you have a minimum of 3 points in Strength. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(2):
            if(skill->mgck >= 3){
                attr->gold=5;
                skill->mgck = skill->mgck + 3;
                strcpy(attr->spec,"Wizard");
                line();
                printf(" You have chosen to be a %s, increasing your Magicka to %d",attr->spec, skill->mgck);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Wizard, unless you have a minimum of 3 points in Magicka. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(3):
            if(skill->speed >= 3){
                attr->gold=20;
                skill->speed = skill->speed + 3;
                strcpy(attr->spec,"Thief");
                line();
                printf(" You have chosen to be a %s, increasing your Speed to %d",attr->spec, skill->speed);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Thief, unless you have a minimum of 3 points in Speed. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(4):
            if(skill->str >=2 && skill->mgck >= 1){
                attr->gold=10;
                skill->str = skill->str + 2;
                skill->mgck = skill->mgck + 1;
                strcpy(attr->spec,"Spellsword");
                line();
                printf(" You have chosen to be a %s, increasing your Strength to %d and your Magicka to %d",attr->spec, skill->str, skill->mgck);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Spellsword, unless you have a minimum of 2 points in Strength and 1 point in Magicka. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(5):
            if(skill->str >= 1 && skill->mgck >=2){
                attr->gold = 10;
                skill->str = skill->str + 1;
                skill->mgck = skill->mgck + 2;
                strcpy(attr->spec,"Battlemage");
                line();
                printf(" You have chosen to be a %s, increasing your Strength to %d and your Magicka to %d",attr->spec, skill->str, skill->mgck);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Battlemage, unless you have a minimum of 2 points in Magicka and 1 point in Strength. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(6):
            if(skill->str >= 1 && skill->speed >= 2){
                attr->gold = 10;
                skill->str = skill->str + 1;
                skill->speed = skill->speed + 2;
                strcpy(attr->spec,"Assassin");
                line();
                printf(" You have chosen to be an %s, increasing your Strength to %d and your Speed to %d",attr->spec, skill->str, skill->speed);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be an Assassin, unless you have a minimum of 2 points in Speed and 1 point in Strength. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(7):
            if(skill->str >= 2 && skill->speed >= 1){
                attr->gold = 10;
                skill->str = skill->str + 2;
                skill->speed = skill->speed + 1;
                strcpy(attr->spec,"Knight");
                line();
                printf(" You have chosen to be a %s, increasing your Strength to %d and your Speed to %d",attr->spec,skill->str, skill->speed);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Knight, unless you have a minimum of 2 points in Strength and 1 point in Speed. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(8):
            if(skill->speed >= 1 && skill->mgck >= 2){
                attr->gold=5;
                skill->speed = skill->speed + 1;
                skill->mgck = skill->mgck + 2;
                strcpy(attr->spec,"Warlock");
                line();
                printf(" You have chosen to be a %s, increasing your Magicka to %d and your Speed to %d",attr->spec,skill->mgck, skill->speed);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Warlock, unless you have a minimum of 2 points in Magicka and 1 point in Speed. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(9):
            if(skill->mgck >= 1 && skill->speed >= 2){
                attr->gold=5;
                skill->mgck = skill->mgck + 1;
                skill->speed = skill->speed + 2;
                strcpy(attr->spec,"Nightblade");
                line();
                printf(" You have chosen to be a %s, increasing your Speed to %d and your Magicka to %d",attr->spec ,skill->speed, skill->mgck);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Nightblade, unless you have a minimum of 2 points in Speed and 1 point in Magicka. \n");
                contNoFat();
                flag = 0;
            }
        break;
        case(10):
            if(skill->str >= 1 && skill->mgck >= 1 && skill->speed >= 1){
                attr->gold=15;
                skill->str = skill->str + 1;
                skill->mgck = skill->mgck + 1;
                skill->speed = skill->speed + 1;
                strcpy(attr->spec,"Bard");
                line();
                printf(" You have chosen to be a %s, increasing your Strength to %d, your Magicka to %d and your Speed to %d",attr->spec,skill ->str, skill->mgck, skill->speed);
                contNoFat();
                flag = 1;
            }else {
                line();
                printf(" You can't be a Bard, unless you have a minimum of 1 point in every attribute. \n");
                contNoFat();
                flag = 0;
            }
        break;
        default:
            printf("Input error. \n");
            contNoFat();
            flag=0;
        break;
        }
    }
    attr->mPotions = 0;
    attr->hPotions = 0;
    attr->armor=0;
    attr->sword=0;
    attr->staff=0;
    attr->lvl = 1;
    attr->exp=0;
    attr->expToLevel=50;
   /* do{
    printf("Input health quantity (can't have more than %d): ", attr->maxHealth);
    scanf("%f", &attr->curHealth);
    }while(attr->curHealth > attr->maxHealth);
    printf("Input health potions quantity: ");
    scanf("%d", &attr->hPotions);
    do{
    printf("Input mana quantity (can't have more than %d): ", attr->maxMana);
    scanf("%f", &attr->curMana);
    }while(attr->curMana > attr->maxMana);
    printf("Input mana potions quantity: ");
    scanf("%d", &attr->mPotions);
    */
    clear();
    line();
    do{
    printf(" Input number of die sides (dice vary from 6 to 20): ");
    scanf("%d", &attr->sides);
    }while(attr->sides <= 5 || attr->sides >= 21);
    do{
    printf(" Input number of dice (number of dice may vary from 1 to 3): ");
    scanf("%d", &attr->numberDice);
    }while(attr->numberDice <= 0 || attr->numberDice >= 4);

    roll(attr);
    attr->maxHealth=100 + (1.5*skill->str) + (0.33*attr->rollDice);
    if(skill->mgck <= 0){
        attr->maxMana = 0; skill->mgck=0;
    }else{
        attr->maxMana=90 + (1.2*skill->mgck) + (0.1*attr->rollDice);
    }
    attr->maxFat = skill->speed + (0.1*attr->rollDice);
    attr->curHealth = attr->maxHealth;
    attr->curMana = attr->maxMana;
    attr->fatigue = attr->maxFat;
    attr->enKill = 0;
    attr->raceLen = strlen(attr->race);
    attr->specLen = strlen(attr->spec);
    //printf("race: %d,  \n gend:%d, \n spec:%d \n",attr->raceLen, attr->gendLen, attr->specLen);
    contNoFat();
}

void display(struct items *attr, struct skills *skill){
    clear();
    line();
    printf(" \t You are %s, a level %d %s %s %s. \n", attr->name, attr->lvl, attr->race, attr->gender, attr->spec);
    printf(" \t Experience needed to level up: %3.2f. \n", attr->expToLevel-attr->exp);
    line();
    printf(" \t You have the following skills: \n");
    printf(" You have %d skill points in Strength. \n", skill->str);
    printf(" You have %d skill points in Magicka. \n", skill->mgck);
    printf(" You have %d skill points in Speed. \n", skill->speed);
   // printf(" You have %d skill points in Charisma. \n", skill->charisma);
    line();
    printf(" \t You have the following attributes: \n");
    printf(" Current health : %3.2f, out of a total of %3.2f. \n", attr->curHealth, attr->maxHealth);
    printf(" Current mana : %3.2f, out of a total of %3.2f. \n", attr->curMana, attr->maxMana);
    printf(" Current fatigue: %d, out of a total of %d points. \n", attr->fatigue, attr->maxFat);
    line();
    printf(" \t Your inventory contains: \n");
    if(attr->gold!=1){
        printf(" You have %d gold pieces \n", attr->gold);
    }else {
        printf(" You have %d gold piece \n", attr->gold);
    }
    if(attr->hPotions == 1){
        printf(" You have %d health potion. \n", attr->hPotions);
    }
    else {
        printf(" You have %d health potions. \n", attr->hPotions);
    }
    if(attr->mPotions == 1){
        printf(" You have %d mana potion. \n", attr->mPotions);
    }
    else {
        printf(" You have %d mana potions. \n", attr->mPotions);
    }
    if(attr->armor == 0){
        printf(" You have no armor equipped. \n");
    }else {
        printf(" You have equipped : %s armor, with a +%d bonus to defense. \n", attr->armorType, attr->armor);
    }
    if(attr->sword == 0){
        printf(" You have no sword equipped. \n");
    }else {
        printf(" You have equipped : %s sword, with a +%d bonus to attack.\n", attr->swordType, attr->sword);
    }
    if(attr->staff == 0){
        printf(" You have no staff equipped. \n");
    }else {
        printf(" You have equipped : %s staff, with a +%d bonus to spell casting. \n", attr->staffType, attr->staff);
    }
    line();
    if(attr->numberDice == 1){
    printf(" You are rolling %d %d-sided die. \n", attr->numberDice, attr->sides);
    }else{
    printf(" You are rolling %d %d-sided dice. \n", attr->numberDice, attr->sides);
    }
    contNoFat();
}

void equip(struct items *eq, struct skills *sk){
    clear();
    int option, fl=0;
    while(fl==0){
        printf("\n \tSelect Equipment: \n");
        line();
        printf("  1.Equip Leather armor. \n");
        printf("  2.Equip Iron armor. \n");
        printf("  3.Equip Steel armor. \n");
        line();
        printf("  4.Equip Wooden sword. \n");
        printf("  5.Equip Iron sword. \n");
        printf("  6.Equip Steel sword. \n");
        line();
        printf("  7.Equip Birch staff. \n");
        printf("  8.Equip Ash staff. \n");
        printf("  9.Equip Maple staff. \n");
        printf(" 10.Equip Mahogany staff. \n");
        line();
        printf(" 11.Uneqip armor. \n");
        printf(" 12.Uneqip sword. \n");
        printf(" 13.Uneqip staff. \n");
        printf(" 14.Uneqip all. \n");
        line();
        printf(" Choose:");
        scanf("%d", &option);
        line();
        printf("\n");
        switch(option){
        case(1):
            eq->armor=(rand()%3)+3;
            strcpy(eq->armorType,"Leather");
            printf(" You have equipped : %s armor, which grants a bonus of +%d protection.", eq->armorType, eq->armor);
            continueScreen(eq);
            fl=1;
            break;
        case(2):
            if(sk->str<4){
                printf(" You need a minimum of 4 Strength to equip Iron armor.");
                contNoFat();
            }else{
            eq->armor=(rand()%4)+8;
            strcpy(eq->armorType,"Iron");
            printf(" You have equipped : %s armor, which grants a bonus of +%d protection.", eq->armorType, eq->armor);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(3):
            if(sk->str<8){
                printf(" You need a minimum of 8 Strength to equip Iron armor.");
                contNoFat();
            }else{
            eq->armor=(rand()%7)+13;
            strcpy(eq->armorType,"Steel");
            printf(" You have equipped : %s armor, which grants a bonus of +%d protection.", eq->armorType, eq->armor);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(4):
            eq->sword=(rand()%3)+2;
            strcpy(eq->swordType,"Wooden");
            printf(" You have equipped : %s sword, which grants a bonus of +%d attack.", eq->swordType, eq->sword);
            continueScreen(eq);
            fl=1;
            break;
        case(5):
            if(sk->str<3){
                printf(" You need a minimum of 3 Strength to equip Iron sword");
                contNoFat();
            }else{
            eq->sword=(rand()%4)+7;
            strcpy(eq->swordType,"Iron");
            printf(" You have equipped : %s sword, which grants a bonus of +%d attack.", eq->swordType, eq->sword);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(6):
            if(sk->str<6){
                printf(" You need a minimum of 6 Strength to equip Steel sword");
                contNoFat();
            }else{
            eq->sword=(rand()%7)+15;
            strcpy(eq->swordType,"Steel");
            printf(" You have equipped : %s sword, which grants a bonus of +%d attack.", eq->swordType, eq->sword);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(7):
            if(sk->mgck<2){
                printf(" You need a minimum of 2 Magicka to equip Birch staff");
                contNoFat();
            }else{
            eq->staff=2;
            strcpy(eq->staffType,"Birch");
            printf(" You have equipped : %s staff, which grants a bonus of +%d attack.", eq->staffType, eq->staff);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(8):
            if(sk->mgck<4){
                printf(" You need a minimum of 4 Magicka to equip Ash staff");
                contNoFat();
            }else{
            eq->staff=5;
            strcpy(eq->staffType,"Ash");
            printf(" You have equipped : %s staff, which grants a bonus of +%d attack.", eq->staffType, eq->staff);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(9):
            if(sk->mgck<7){
                printf(" You need a minimum of 7 Magicka to equip Maple staff");
                contNoFat();
            }else{
            eq->staff=7;
            strcpy(eq->staffType,"Maple");
            printf(" You have equipped : %s staff, which grants a bonus of +%d attack.", eq->staffType, eq->staff);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(10):
            if(sk->mgck<9){
                printf(" You need a minimum of 9 Magicka to equip Mahogany staff");
                contNoFat();
            }else{
            eq->staff=9;
            strcpy(eq->staffType,"Mahogany");
            printf(" You have equipped : %s staff, which grants a bonus of +%d attack.", eq->staffType, eq->staff);
            continueScreen(eq);
            }
            fl=1;
            break;
        case(11):
            if(eq->armor!=0){
                eq->armor=0;
                printf(" You have unequipped : %s armor.", eq->armorType);
                continueScreen(eq);
            }else{
                printf(" You have no armor to uneqip.");
                contNoFat();
            }
            fl=1;
            break;
        case(12):
            if(eq->sword!=0){
                eq->sword=0;
                printf(" You have unequipped : %s sword.", eq->swordType);
                continueScreen(eq);
            }else{
               printf(" You have no sword to uneqip.");
               contNoFat();
            }
            fl=1;
            break;
        case(13):
            if(eq->staff!=0){
                eq->staff=0;
                printf(" You have unequipped : %s staff.", eq->staffType);
                continueScreen(eq);
            }else{
                printf(" You have no staff to uneqip.");
                contNoFat();
            }
            fl=1;
            break;
        case(14):
            if(eq->armor!=0 && eq->sword!=0 && eq->staff){
                eq->armor=0;
                eq->sword=0;
                eq->staff=0;
                printf(" You have unequipped : %s armor, %s sword, %s staff.", eq->armorType, eq->swordType, eq->staffType);
                continueScreen(eq);
            }else if(eq->armor==0 && eq->sword!=0 && eq->staff!=0){
                eq->sword=0;
                eq->staff=0;
                printf(" You have unequipped : %s sword, %s staff.", eq->swordType, eq->staffType);
                continueScreen(eq);
            }else if(eq->sword == 0 &&eq->armor!=0 &&eq->staff!=0){
                eq->armor=0;
                eq->staff=0;
                printf(" You have unequipped : %s armor, %s staff.", eq->armorType, eq->staffType);
                continueScreen(eq);
            }else if(eq->staff == 0 &&eq->armor!=0 &&eq->sword!=0){
                eq->armor=0;
                eq->sword=0;
                printf(" You have unequipped : %s armor, %s sword", eq->armorType, eq->swordType);
                continueScreen(eq);
            }else if(eq->armor==0 && eq->sword ==0 &&eq->staff!=0){
                eq->staff=0;
                printf(" You have unequipped : %s staff.", eq->staffType);
                continueScreen(eq);
            }else if(eq->sword == 0 && eq->staff==0 &&eq->armor!=0){
                eq->armor=0;
                printf(" You have unequipped : %s armor", eq->armorType);
                continueScreen(eq);
            }else if(eq->staff == 0 && eq->armor==0 &&eq->sword!=0){
                eq->sword=0;
                printf(" You have unequipped : %s sword", eq->swordType);
                continueScreen(eq);
            }else if(eq->armor==0 && eq->sword ==0 && eq->staff==0 ){
                printf(" You have nothing to uneqip");
                contNoFat();
            }
            fl=1;
            break;
        default:
            printf(" Input error.");
            contNoFat();
            break;
        }
    }
}

int addHPotion(struct items *healing){
    clear();
    line();
    if(healing->gold >= 7){
        healing->hPotions++;
        printf(" You have bought one health potion and for the price of 7 gold pieces. \n");
        healing->gold=healing->gold-7;
        if(healing->hPotions != 1){
        printf(" You have %d health potions now. \n", healing->hPotions);
        }else {
        printf(" You have %d health potion now. \n", healing->hPotions);
        }
        printf(" Gold left: %d", healing->gold);
    }else{
        printf(" You lack the gold required to pay for a health potion.");
    }
    continueScreen(healing);
    return healing->hPotions;
}

int addMPotion(struct items *mana){
    clear();
    line();
    if(mana->gold >= 5){
        printf(" You have bought one mana potion and for the price of 5 gold pieces. \n");
        mana->gold=mana->gold-5;
        mana->mPotions++;
        printf(" You have obtained one mana potion. \n");
        if(mana->mPotions != 1){
        printf(" You have %d mana potions now. \n", mana->mPotions);
        }else {
        printf(" You have %d mana potion now. \n", mana->mPotions);
        }
    }else{
        printf(" You lack the gold required to pay for a mana potion.");
    }
    continueScreen(mana);
    return mana->mPotions;
}

void restFat(struct items *fat){
    clear();
    line();
    if(fat->fatigue < fat->maxFat){
        fat->fatigue++;
        printf(" You have rested and restored 1 point fatigue.\n You currently have %d points. \n", fat->fatigue);
    }else if(fat->fatigue >= fat->maxFat){
        fat->fatigue = fat->maxFat;
        printf(" You already have a maximum number of points in fatigue. \n");
    }
    contNoFat();
}

void restInn(struct items *fat){
    clear();
    line();
    if(fat->gold >= 10){
        fat->gold = fat->gold - 10;
        printf(" You have stayed the night at the local inn. \n");
        if(fat->fatigue < fat->maxFat){
            fat->fatigue = fat->fatigue + 5;
            printf(" You have rested and restored 5 point fatigue.\n You currently have %d points. \n", fat->fatigue);
        }else if(fat->fatigue >= fat->maxFat){
            fat->fatigue = fat->maxFat;
            printf(" You haven't restored any points in fatigue, because you already have a maximum number of points in fatigue. \n");
        }
        if(fat->curHealth < fat->maxHealth){
            fat->curHealth = fat->curHealth + (0.5*fat->maxHealth);
            if(fat->curHealth > fat->maxHealth){
                fat->curHealth = fat->maxHealth;
            }
            printf(" You have rested and restored %3.2f health.\n You currently have %3.2f health. \n", fat->maxHealth*0.5, fat->curHealth);
        }else {
            fat->curHealth = fat->maxHealth;
            printf(" You haven't restored any health, because you already at maximum health. \n");
        }
        if(fat->curMana < fat->maxMana){
            fat->curMana = fat->curMana + (0.5*fat->maxMana);
            if(fat->curMana > fat->maxMana){
                fat->curMana = fat->maxMana;
            }
            printf(" You have rested and restored %3.2f mana.\n You currently have %3.2f mana. \n", fat->maxMana*0.5, fat->curMana);
        }else {
            fat->curMana = fat->maxMana;
            printf(" You haven't restored any mana, because you already at maximum mana. \n");
        }
        contNoFat();
    }else {
        printf(" You lack the gold required to pay the innkeeper and you can't stay the night at the inn. \n");
        printf(" You instead spend the night out in the streets. \n");
        contNoFat();
        restFat(fat);
    }
}

float healing(struct items *healing){
    clear();
    line();
    roll(healing);
    if(healing->maxHealth == healing->curHealth){
        printf(" You are already at max health.\n");
        contNoFat();
        return healing->curHealth;
    }else{
        if(healing->hPotions <= 0){
            printf(" You have no potions left.\n");
            contNoFat();
            return healing->curHealth;
        }else{
        if(healing->rollDice < (0.33 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 10;
            healing->curHealth = healing->curHealth + healing->hRest;
            printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.33 * (healing->sides * healing->numberDice)) && healing->rollDice < (0.75 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 12;
            healing->curHealth = healing->curHealth + healing->hRest;
            printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.75 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 15;
            healing->curHealth = healing->curHealth + healing->hRest;
            printf(" You restored %3.2f health. \n", healing->hRest);
        }
           healing->hPotions -- ;
           if(healing->curHealth > healing->maxHealth){
            healing->curHealth = healing->maxHealth;
           }
        healing->exp = healing->exp + (0.2*healing->hRest);
        }
    }
    printf(" You currently have %3.2f health. \n", healing->curHealth);
    continueScreen(healing);
    return healing->curHealth;
}

float mana(struct items *mana){
    clear();
    line();
    roll(mana);
    if(mana->maxMana == mana->curMana){
        printf(" You are already at max Mana.\n");
        contNoFat();
        return mana->curMana;
    }else{
        if(mana->mPotions <= 0){
            printf(" You have no mana potions left.\n");
            contNoFat();
            return mana->curMana;
        }else{
        if(mana->rollDice < (0.33 * (mana->sides * mana->numberDice))){
            mana->mRest = ((mana->maxMana/100 )* 10);
            mana->curMana = mana->curMana + mana->mRest;
            printf(" You restored %3.2f mana. \n", mana->mRest);
        }else if(mana->rollDice > (0.33 * (mana->sides * mana->numberDice)) && mana->rollDice < (0.75 * (mana->sides * mana->numberDice))){
            mana->mRest = ((mana->maxMana/100 )* 15);
            mana->curMana = mana->curMana + mana->mRest;
            printf(" You restored %3.2f mana. \n", mana->mRest);
        }else if(mana->rollDice > (0.75 * (mana->sides * mana->numberDice))){
            mana->mRest = ((mana->maxMana/100 )* 20);
            mana->curMana = mana->curMana + mana->mRest;
            printf(" You restored %3.2f mana. \n", mana->mRest);
        }
           mana->mPotions -- ;
           if(mana->curMana > mana->maxMana){
            mana->curMana = mana->maxMana;
           }
           mana->exp = mana->exp + (0.2*mana->mRest);
        }
    }
    printf(" You have %3.2f mana. \n", mana->curMana);
    continueScreen(mana);
    return mana->curMana;
}

float damage(struct items *dmg){
    clear();
    roll(dmg);
    if(dmg->rollDice < (0.10 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 10 - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - (2*dmg->dmgTaken);
        printf(" Critical hit! You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.10 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.25 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 10 - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.25 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.33 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 9  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.33 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.40 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 8.5  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.40 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.50 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 8  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.50 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.6 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 7.5  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.6 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.75 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 7  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.75 * (dmg->sides * dmg->numberDice)) && dmg->rollDice < (0.9 * (dmg->sides * dmg->numberDice))){
        dmg->dmgTaken = (dmg->maxHealth/100) * 6  - (dmg->armor*0.33);
        dmg->curHealth = dmg->curHealth - dmg->dmgTaken;
        printf(" You were hit for %3.2f damage. \n", dmg->dmgTaken);
    }
    if(dmg->rollDice >= (0.9 * (dmg->sides * dmg->numberDice))){
        printf(" The enemy attack missed. \n");
    }
    if(dmg->curHealth <= 0){
        dmg->curHealth = 0;
        printf(" You are already dead. \n");
    }else{
    printf(" Your remaining health is %3.2f. \n", dmg->curHealth);
    }
    contNoFat();
    return dmg->curHealth;
}

int roll(struct items *dice){
    int oneDie[dice->sides];
    int rollValue = 0,rollNumber,rollSum,i,j,diceCounter = 1;
    for(i=0;i<=dice->sides-1;i++){
        oneDie[i]=diceCounter;
        diceCounter++;
    }
    for(j=0;j<=dice->numberDice-1;j++){
        rollNumber = rand()%(dice->sides);
        rollSum = oneDie[rollNumber];
        rollValue = rollValue + rollSum;
    }
    dice->rollDice = rollValue;
    return dice->rollDice;
}

int enemyroll(struct enemyStats *dice){
    int oneDie[dice->sides];
    int rollValue = 0,rollNumber,rollSum,i,j,diceCounter = 1;
    for(i=0;i<=dice->sides-1;i++){
        oneDie[i]=diceCounter;
        diceCounter++;
    }
    for(j=0;j<=dice->numberDice-1;j++){
        rollNumber = rand()%(dice->sides);
        rollSum = oneDie[rollNumber];
        rollValue = rollValue + rollSum;
    }
    dice->rollDice = rollValue;
    return dice->rollDice;
}

unsigned int rollSkill(int level){
    int skill;
    if (level<10){
        skill = (rand()%level)+1;
    }else{
        skill = (rand()%10)+1;
    }

    return skill;
}

float cast(struct items *dice, struct skills *magic){
    clear();
    int flag=0;
    float dmg = 0;
    if(dice->curMana<=0){
        printf(" You have no mana left and must consume a potion.\n");
        contNoFat();
        return dmg;
    }else {
        char castType[10];
        line();
        printf("\t Select Type of spell to cast: \n");
        printf(" 1. Beginner Spell (for Magicka >= 3). \n");
        printf(" 2. Apprentice Spell(for Magicka >= 5). \n");
        printf(" 3. Adept Spell(for Magicka >= 7). \n");
        printf(" 4. Master Spell(for Magicka >= 9) \n");
        printf(" 5. Grandmaster Spell (for Magicka >= 10). \n");
        printf(" 6. Cancel Cast. \n");
        line();
        printf(" Choose:");
        scanf("%d", &flag);
        line();
        if(flag==1){strcpy(castType,"Beginner");}
        else if(flag==2){strcpy(castType,"Apprentice");}
        else if(flag==3){strcpy(castType,"Adept");}
        else if(flag==4){strcpy(castType,"Master");}
        else if(flag==5){strcpy(castType,"Grandmaster");}
        else if(flag==6){
                flag=0;
                printf(" Canceling casting. \n");
                contNoFat();
                return dmg;
        }
        if(flag == 1 && magic->mgck < 3){
            printf(" You cannot cast %s Type spells. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 2 && magic->mgck < 5){
            printf(" You cannot cast %s Type spells. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 3 && magic->mgck < 7){
            printf(" You cannot cast %s Type spells. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 4 && magic->mgck < 9){
            printf(" You cannot cast %s Type spells. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 5 && magic->mgck < 10){
            printf(" You cannot cast %s Type spells. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }
        if(flag >= 1 && flag <= 5){
            dmg = spellDmg(dice, magic, flag, castType);
            dice->exp = dice->exp + (0.2*dmg);
            continueScreen(dice);
            dice->curMana = dice->curMana - (12*flag);
            return dmg;
        }else if(flag > 5){
            printf(" Input error. Failed to cast spell. \n");
            contNoFat();
            return dmg;
        }
    }
}

float spellDmg(struct items *dice, struct skills *magic, int flag, char castType[10]){
    float dmg = 0;
    roll(dice);
    if(dice->rollDice <= (0.10 * (dice->sides * dice->numberDice))){
        printf(" You tried to cast a spell, but have failed. \n");
        return dmg;
    }else if(dice->rollDice >= (0.10 * (dice->sides * dice->numberDice)) && dice->rollDice < (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice*(flag*0.1) + magic->mgck) * (flag*0.4) + dice->staff;
        printf(" You have casted a %s spell, doing %3.2f damage", castType, dmg);
    }else if(dice->rollDice >= (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice + magic->mgck) * (flag*0.5) + (dice->staff*2);
        printf(" You have casted a critical %s spell, doing %3.2f damage", castType, dmg);
        return dmg;
    }
    return dmg;
}

float attack(struct items *dice, struct skills *attack){
    clear();
    int flag=0;
    float dmg=0;
    char castType[7];
        line();
        printf("\t Select Type of attack: \n");
        printf(" 1. Light attack. \n");
        printf(" 2. Medium attack (Requires Strength >= 4). \n");
        printf(" 3. Heavy attack (Requires Strength >= 8).\n");
        printf(" 4. Power attack (Requires Strength >= 10).\n");
        printf(" 5. Cancel attack. \n");
        line();
        printf(" Choose:");
        scanf("%d", &flag);
        line();
        if(flag==1){strcpy(castType,"Light");}
        else if(flag==2){strcpy(castType,"Medium");}
        else if(flag==3){strcpy(castType,"Heavy");}
        else if(flag==4){strcpy(castType,"Power");}
        else if(flag==5){
                flag=0;
                printf(" Canceling attack. \n");
                contNoFat();
                return dmg;
        }
        if(flag == 2 && attack->str < 4){
            printf(" You lack the Strength for a %s attack. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 3 && attack->str < 8){
            printf(" You lack the Strength for a %s attack. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }else if(flag == 4 && attack->str < 10){
            printf(" You lack the Strength for a %s attack. \n", castType);
            flag = 0;
            contNoFat();
            return dmg;
        }
        if(flag >= 1 && flag <= 4){
            dmg = attackDmg(dice, attack, flag, castType);
            dice->exp = dice->exp + (0.2*dmg);
            continueScreen(dice);
            return dmg;
        }else if(flag > 5){
            printf(" Input error. Failed to attack. \n");
            contNoFat();
            return dmg;
        }
}

float attackDmg(struct items *dice, struct skills *attack, int flag, char castType[7]){
    float dmg = 0;
    roll(dice);
    if(dice->rollDice <= (0.10 * (dice->sides * dice->numberDice))){
        printf(" You tried to attack, but have failed. \n");
        return dmg;
    }else if(dice->rollDice >= (0.10 * (dice->sides * dice->numberDice)) && dice->rollDice < (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice*(flag*0.1) + attack->str) * (flag*0.4) + (0.33 * dice->sword);
        printf(" You have performed a %s attack, doing %3.2f damage.", castType, dmg);
    }else if(dice->rollDice >= (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice + attack->str) * (flag*0.5) + dice->sword;
        printf(" You have performed a critical %s attack, doing %3.2f damage.", castType, dmg);
        return dmg;
    }
    return dmg;
}

float enemyAttackDmg(struct enemyStats *dice, int flag){
    float dmg = 0;
    enemyroll(dice);
    if(dice->rollDice <= (0.20 * (dice->sides * dice->numberDice))){
        //printf(" You tried to attack, but have failed. \n");
        return dmg;
    }else if(dice->rollDice >= (0.20 * (dice->sides * dice->numberDice)) && dice->rollDice < (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice*(flag*0.1) + dice->str) * (flag*0.4) + (0.33 * dice->sword);
        //printf(" You have performed a %s attack, doing %3.2f damage.", castType, dmg);
    }else if(dice->rollDice >= (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice + dice->str) * (flag*0.5) + dice->sword;
        //printf(" You have performed a critical %s attack, doing %3.2f damage.", castType, dmg);
        return dmg;
    }
    return dmg;
}

float enemyMagicDmg(struct enemyStats *dice, int flag){
    float dmg = 0;
    enemyroll(dice);
    if(dice->rollDice <= (0.33 * (dice->sides * dice->numberDice))){
        //printf(" You tried to cast a spell, but have failed. \n");
        return dmg;
    }else if(dice->rollDice >= (0.33 * (dice->sides * dice->numberDice)) && dice->rollDice < (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice*(flag*0.1) + dice->mgck) * (flag*0.4) + dice->staff;
        //printf(" You have casted a %s spell, doing %3.2f damage", castType, dmg);
    }else if(dice->rollDice >= (0.90 * (dice->sides * dice->numberDice))){
        dmg = (dice->rollDice + dice->mgck) * (flag*0.5) + (dice->staff*2);
        //printf(" You have casted a critical %s spell, doing %3.2f damage", castType, dmg);
        return dmg;
    }
    dice->curMana=dice->curMana-(12*flag);
    return dmg;
}

float enemyHeal(struct enemyStats *healing){
    if(healing->rollDice < (0.33 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 10;
            healing->curHealth = healing->curHealth + healing->hRest;
            //printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.33 * (healing->sides * healing->numberDice)) && healing->rollDice < (0.75 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 12;
            healing->curHealth = healing->curHealth + healing->hRest;
           //printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.75 * (healing->sides * healing->numberDice))){
            healing->hRest = (healing->maxHealth/100 )* 15;
            healing->curHealth = healing->curHealth + healing->hRest;
            //printf(" You restored %3.2f health. \n", healing->hRest);
        }
           healing->hPotions -- ;
           if(healing->curHealth > healing->maxHealth){
            healing->curHealth = healing->maxHealth;
           }
    return healing->curHealth;
}

float enemyRestMana(struct enemyStats *healing){
    if(healing->rollDice < (0.33 * (healing->sides * healing->numberDice))){
            healing->mRest = (healing->maxMana/100 )* 10;
            healing->curMana = healing->curMana + healing->mRest;
            //printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.33 * (healing->sides * healing->numberDice)) && healing->rollDice < (0.75 * (healing->sides * healing->numberDice))){
            healing->mRest = (healing->maxMana/100 )* 12;
            healing->curMana = healing->curMana + healing->mRest;
            //printf(" You restored %3.2f health. \n", healing->hRest);
        }else if(healing->rollDice > (0.75 * (healing->sides * healing->numberDice))){
            healing->mRest = (healing->maxMana/100 )* 15;
            healing->curMana = healing->curMana + healing->mRest;
            //printf(" You restored %3.2f health. \n", healing->hRest);
        }
           healing->mPotions -- ;
           if(healing->curMana > healing->maxMana){
            healing->curMana = healing->maxMana;
           }
    return healing->curMana;
}

int randomStats(int j){
    int random;
    int arr[j];
    int i, k=0;
    for(i=0;i<=j-1;i++){
        k++;
        arr[i]=k;
    }
    random = (rand()%k);

    return arr[random];
}

int encounter(struct enemyStats *stats, struct items *attr, struct skills *skill){
    clear();
    int option, flag;
    stats->lvl = (rand()%attr->lvl)+1;
    stats->str = rollSkill(stats->lvl);
    stats->mgck = rollSkill(stats->lvl);
    stats->speed = rollSkill(stats->lvl);
    stats->sides = attr->sides;
    stats->numberDice = attr->numberDice;
    enemyroll(stats);
    stats->maxHealth = 90 + (1.5*stats->str) + (0.33*stats->rollDice);
    stats->maxMana = 70 + (1.2*stats->mgck) + (0.33*stats->rollDice);
    stats->curHealth  = stats->maxHealth;
    stats->curMana = stats->maxMana;
    stats->armor = randomStats(stats->lvl);
    stats->sword = randomStats(stats->lvl);
    stats->staff = randomStats(stats->lvl);
    stats->hPotions=(rand()%stats->lvl)+1;
    stats->mPotions=(rand()%stats->lvl)+1;
    stats->maxFat = stats->speed + (0.1*stats->rollDice);
    stats->fatigue = stats->maxFat;

    int i;
    i = rand()%(sizeof(stats->gendType)/sizeof(stats->gendType[0]));
    strcpy(stats->gender, stats->gendType[i]);
    i = rand()%(sizeof(stats->raceType)/sizeof(stats->raceType[0]));
    strcpy(stats->race, stats->raceType[i]);
    i = rand()%(sizeof(stats->enemyType)/sizeof(stats->enemyType[0]));
    strcpy(stats->enemy, stats->enemyType[i]);
    if(i == 3){
        stats->hPotions = stats->hPotions + 5;
        stats->mPotions = stats->mPotions + 5;
    }
    i = rand()%(sizeof(stats->armorVar)/sizeof(stats->armorVar[0]));
    strcpy(stats->armorType, stats->armorVar[i]);
    i = rand()%(sizeof(stats->swordVar)/sizeof(stats->swordVar[0]));
    strcpy(stats->swordType, stats->swordVar[i]);
    i = rand()%(sizeof(stats->staffVar)/sizeof(stats->staffVar[0]));
    strcpy(stats->staffType, stats->staffVar[i]);

    line();
    printf(" \t You have encountered a level %d %s %s %s with the \n \t \t following stats and inventory: \n", stats->lvl, stats->gender, stats->race, stats->enemy);
    printf(" Enemy Strength : %d. \n Enemy Magicka : %d. \n Enemy Speed : %d \n",stats->str,stats->mgck,stats->speed);
    printf(" Enemy Health: %3.2f. \n Enemy Mana: %3.2f. \n Enemy Fatigue : %d. \n",stats->maxHealth,stats->maxMana,stats->maxFat);
    printf(" The enemy is equipped with a %s armor that grants them a +%d bonus to protection. \n",stats->armorType,stats->armor);
    printf(" The enemy is equipped with a %s sword that grants them a +%d bonus to attack. \n",stats->swordType,stats->sword);
    printf(" The enemy is equipped with a %s staff that grants them a +%d bonus to spell casting. \n",stats->staffType,stats->staff);
    if(stats->hPotions != 1 && stats->mPotions != 1){
    printf(" The enemy is equipped with %d health potions and %d mana potions. \n", stats->hPotions,stats->mPotions);
    }else if(stats->hPotions == 1 && stats->mPotions != 1){
    printf(" The enemy is equipped with %d health potion and %d mana potions. \n", stats->hPotions,stats->mPotions);
    }else if(stats->hPotions !=1 && stats->mPotions == 1){
    printf(" The enemy is equipped with %d health potions and %d mana potion. \n", stats->hPotions,stats->mPotions);
    }else if(stats->hPotions == 1 && stats->mPotions == 1){
    printf(" The enemy is equipped with %d health potion and %d mana potion. \n", stats->hPotions,stats->mPotions);
    }
    line();
    printf(" What will you do? \n 1.Run. \n 2.Attack. \n Choose:");
    scanf("%d", &option);
    switch(option){
    case(1):
        printf("Ran away.\n");
        continueScreen(attr);
        return option;
        break;
    case(2):
        battle(stats,attr,skill);
        return option;
        break;
    default:
        printf("Input Error. Re-rolling... \n");
        contNoFat();
        encounter(stats,attr,skill);
        break;
    }
}

int battle(struct enemyStats *enstats, struct items *attr, struct skills *skill){
    int turn, option;
    int flStr, flMgck;
    float dmg;
    int flagAttack, flagMagic;
    int goldGain;

    if(enstats->str < 4){
        flStr=1;
    }else if(enstats->str >= 4 && enstats->str < 8){
        flStr=2;
    }else if(enstats->str >= 8 && enstats->str < 9){
        flStr=3;
    }else if(enstats->str >= 9){
        flStr=4;
    }

    if(enstats->mgck < 3){
        flMgck=1;
    }else if(enstats->mgck >= 3 && enstats->mgck < 4){
        flMgck=2;
    }else if(enstats->mgck >= 4 && enstats->mgck < 7){
        flMgck=3;
    }else if(enstats->mgck >= 7 && enstats->mgck < 9){
        flMgck=4;
    }else if(enstats->mgck >= 9){
        flMgck=5;
    }


    if (skill->speed >= enstats->speed){
        turn = 0;
        line();
        printf(" You have a higher or equal amount of points in Speed, compared to your enemy. \n You attack first. \n");
        line();
    }else {
        turn = 1;
        line();
        printf(" You have a lower amount of points in Speed, compared to your enemy. \n Your enemy attacks first. \n");
        line();
    }
    contNoFat();
    while(turn!=2){
       clear();
       if(enstats->curHealth <= 0){
        line();
        printf(" You have defeated the %s %s %s. \n", enstats->gender, enstats->race, enstats->enemy);
        printf(" You have gained %3.2f experience. \n",(0.5*enstats->maxHealth));
        goldGain = enstats->lvl + 0.1*enstats->maxHealth;
        printf(" You have looted %d gold. \n", goldGain);
        attr->gold = attr->gold + goldGain;
        attr->exp = attr->exp + (0.5*enstats->maxHealth);
        attr->enKill++;
        turn=2;
        contNoFat();
        }
        else if(attr->curHealth <= 0){
        line();
        printf(" You have been defeated. \n");
        turn=2;
        contNoFat();
        }else{
            line();
            printf(" Your health: %3.2f. \n", attr->curHealth);
            printf(" Enemy health: %3.2f. \n", enstats->curHealth);
            line();
            if(turn == 0){
                if(attr->fatigue<=0){
                    printf("You have no fatigue left and must skip your turn, in order to restore fatigue. \n");
                    attr->fatigue++;
                    turn = 1;
                    contNoFat();
                }else{
                    printf("\n \t Your turn. \n");
                    if(attr->curMana<=0){attr->curMana = 0;}
                    printf(" Your mana: %3.2f. \n",attr->curMana);
                    printf(" Health potions: %d. \n Mana potions: %d. \n", attr->hPotions, attr->mPotions);
                    line();
                    printf(" \t Select option: \n");
                    if(attr->armor!=0){
                        printf(" 1. Attack Enemy with %s weapon. \n", attr->swordType);
                    }else{
                        printf(" 1. Attack Enemy with your fists. \n");
                    }
                    printf(" 2. Attack Enemy with Spell. \n");
                    printf(" 3. Consume Health Potion. \n");
                    printf(" 4. Consume Mana Potion. \n");
                    printf(" 5. View your and your enemy's stats. \n");
                    line();
                    printf(" Choose:");
                    scanf("%d", &option);
                    line();
                    switch(option){
                    case(1):
                        dmg = attack(attr,skill) - (0.33*enstats->armor);
                        if(dmg<0){dmg = 0;}
                        flicker();
                        enstats->curHealth = enstats->curHealth - dmg;
                        printf("\n Taking into account armor, you have hit the enemy for %3.2f damage. \n", dmg);
                        flicker();
                        turn = 1;
                        contNoFat();
                        break;
                    case(2):
                        dmg = cast(attr,skill);
                        enstats->curHealth = enstats->curHealth - dmg;
                        flicker();
                        printf("\n You have hit the enemy for %3.2f damage. \n", dmg);
                        flicker();
                        turn = 1;
                        contNoFat();
                        break;
                    case(3):
                        attr->curHealth = healing(attr);
                        turn = 1;
                        break;
                    case(4):
                        attr->curMana = mana(attr);
                        turn = 1;
                        break;
                    case(5):
                        clear();
                        line();
                        printf(" \t Your stats: \n");
                        printf(" Health: %3.2f. \n Mana: %3.2f. \n Health Potions left: %d. \n Mana Potions left: %d. \n", attr->curHealth, attr->curMana, attr->hPotions, attr->mPotions);
                        printf(" Strength: %d. \n Magicka: %d. \n Speed: %d. \n", skill->str, skill->mgck, skill->speed);
                        line();
                        printf(" \t Enemy stats: \n");
                        printf(" Health: %3.2f. \n Mana: %3.2f. \n Health Potions left: %d. \n Mana Potions left: %d. \n", enstats->curHealth, enstats->curMana, enstats->hPotions, enstats->mPotions);
                        printf(" Strength: %d. \n Magicka: %d. \n Speed: %d. \n", enstats->str, enstats->mgck, enstats->speed);
                        line();
                        contNoFat();
                        turn = 0;
                        break;
                    default:
                        printf("Input Eror. \n");
                        contNoFat();
                        turn = 0;
                        break;
                    }
                }
            }else if(turn == 1){
                if(enstats->fatigue<=0){
                    printf(" The enemy has no fatigue left and they must skip their turn, in order to restore fatigue. \n");
                    enstats->fatigue++;
                    turn = 0;
                    contNoFat();
                }else{
                    printf("\t Enemy turn. \n");
                    int opt = 5;
                    option = (rand()%opt)+1;
                        if(enstats->curMana<=0){
                            opt=4;
                            enstats->curMana=0;
                            option=(rand()%opt)+1;
                        }
                        if(enstats->curHealth<=(0.33*enstats->maxHealth)&&enstats->hPotions>0){
                            option=3;
                        }
                        while(enstats->curHealth == enstats->maxHealth && option == 4){
                            option=(rand()%opt)+1;
                        }
                        while(enstats->curMana == enstats->maxMana && option == 3){
                            option=(rand()%opt)+1;
                        }
                    line();
                    switch(option){
                    case(1):
                        printf(" The enemy is attacking you with a weapon. \n");
                        flicker();
                        flagAttack = (rand()%flStr) +1;
                        dmg = enemyAttackDmg(enstats, flagAttack) - (0.33*attr->armor);
                        if(dmg<0){dmg = 0;}
                        attr->curHealth = attr->curHealth - dmg;
                        flicker();
                        printf(" You have been hit for %3.2f damage. \n", dmg);
                        enstats->fatigue--;
                        turn = 0;
                        contNoFat();
                        break;
                    case(2):
                        if(attr->curMana > 0){
                            flicker();
                            printf(" The enemy is attacking your mana. \n");
                            flagMagic = (rand()%flMgck) +1;
                            dmg = enemyMagicDmg(enstats, flagMagic);
                            attr->curMana = attr->curMana - dmg;
                            flicker();
                            printf(" You have been drained for %3.2f mana. \n", dmg);
                        }else if(attr->curMana <= 0){
                            flicker();
                            printf(" The enemy tried to drain your mana, but you have no mana left. \n");
                        }
                        enstats->fatigue--;
                        turn = 0;
                        contNoFat();
                        break;
                    case(3):
                        if(enstats->mPotions > 0){
                            printf(" The enemy is consuming a mana potion. \n");
                            enemyRestMana(enstats);
                            printf(" The enemy has restored %3.2f mana. \n", enstats->mRest);
                        }else if(enstats->mPotions <= 0){
                            printf(" The enemy looked in their inventory for a mana potion, but they have none left. \n");
                        }
                        enstats->fatigue--;
                        turn = 0;
                        contNoFat();
                        break;
                    case(4):
                        if(enstats->hPotions > 0){
                            printf(" The enemy is consuming a health potion. \n");
                            enemyHeal(enstats);
                            printf(" The enemy has restored %3.2f health. \n", enstats->hRest);
                        }else if(enstats->hPotions <= 0){
                            printf(" The enemy looked in their inventory for a health potion, but they have none left. \n");
                        }
                        enstats->fatigue--;
                        turn = 0;
                        contNoFat();
                        break;
                    case(5):
                        if(enstats->curMana > 0){
                            flicker();
                            printf(" The enemy is attacking you with a spell. \n");
                            flagMagic = (rand()%flMgck) +1;
                            dmg = enemyMagicDmg(enstats, flagMagic);
                            attr->curHealth = attr->curHealth - dmg;
                            flicker();
                            printf(" You have been hit for %3.2f damage. \n", dmg);
                        }else{
                            printf(" The enemy tried to attack you with a spell, but they have no Magicka left. \n");
                        }
                        enstats->fatigue--;
                        turn = 0;
                        contNoFat();
                        break;
                    default:
                        printf("Input Eror. \n");
                        contNoFat();
                        turn = 1;
                        break;
                    }
            }}
        }
    }
}

void writehallOfFame(struct items *it, struct hallOfFame *hof){
    FILE *fp;
    char *raceM, *gendM, *specM;
    int flag = 0;
    raceM = malloc(10*sizeof(it->race));
    gendM = malloc(7*sizeof(it->gender));
    specM = malloc(10*sizeof(it->spec));
    fp = fopen("hof.bd","rb");
    if(fp != NULL){
        while(1){
            if(ferror(fp)){
                //printf("Error in file. Good fucking luck. \n");
                break;
            }
            if(fread(&hof->id,sizeof(int),1,fp)!=1){
                //printf("W Error reading char id.\n");
                break;
            }
            if(hof->id == it->id){
                //printf(" Your name is already in the Hall of Fame. \n");
                flag = 1;
                break;
            }
            if(fread(&hof->nameLen,sizeof(unsigned int),1,fp)!=1){
                //printf("W Error reading char nameLen.\n");
                break;
            }
            hof->name = malloc(sizeof(char) * hof->nameLen);
            if(hof->name == NULL){printf("Error allocating memory for name");}else{
                if(fread(hof->name,sizeof(char),hof->nameLen,fp)!=hof->nameLen){
                    //printf("W Error reading char name.\n");
                    break;
                }
                hof->name[hof->nameLen] = '\0';
            }
            if(fread(&hof->lvl,sizeof(int),1,fp)!=1){
                //printf("W Error reading char level.\n");
                break;
            }
            if(fread(&hof->enKill,sizeof(int),1,fp)!=1){
                printf("W Error reading char enKill.\n");
                break;
            }
            if(fread(hof->race,sizeof(char),10,fp)!=10){
                //printf("W Error reading char race.\n");
                break;
            }
            if(fread(hof->gender,sizeof(char),7,fp)!=7){
                printf("W Error reading char gender.\n");
                break;
            }
            if(fread(hof->spec,sizeof(char),10,fp)!=10){
                //printf("W Error reading char spec.\n");
                break;
            }
        }
    }
    fclose(fp);
    if(flag!=1){
            fp =  fopen("hof.bd","ab");
            if(fp!=NULL){
                if(fwrite(&it->id,sizeof(int),1,fp)!=1){
                   // printf("Error writing char id.\n");
                }
                if(fwrite(&it->nameLen,sizeof(unsigned  int),1,fp)!=1){
                    //printf("Error writing char nameLen.\n");
                }
                if(fwrite(it->name,sizeof(char),it->nameLen,fp)!=it->nameLen){
                    //printf("Error writing char name.\n");
                }
                if(fwrite(&it->lvl,sizeof(int),1,fp)!=1){
                    //printf("Error writing char level.\n");
                }
                if(fwrite(&it->enKill,sizeof(int),1,fp)!=1){
                    //printf("Error writing char enKill.\n");
                }
                if(fwrite(it->race,sizeof(char),10,fp)!=10){
                    printf("Error writing char race.\n");
                }
                if(fwrite(it->gender,sizeof(char),7,fp)!=7){
                    printf("Error writing char gender.\n");
                }
                if(fwrite(it->spec,sizeof(char),10,fp)!=10){
                    printf("Error writing char spec.\n");
                }
                printf("Character written.");
                }
                rewind(fp);
                fclose(fp);
            }
            else if(flag == 1){
                 printf(" Your name is already in the Hall of Fame. \n");
            }
    contNoFat();
}

void viewhallOfFame(struct items *it, struct hallOfFame *hof){
    FILE *fp;
    char *raceM, *gendM, *specM;
    int flag = 0, i = 1;
    raceM = malloc(10*sizeof(it->race));
    gendM = malloc(7*sizeof(it->gender));
    specM = malloc(10*sizeof(it->spec));
    fp = fopen("hof.bd","rb");
    if(fp != NULL){
        while(1){
            if(ferror(fp)){
                //printf("Error in file. Good fucking luck. \n");
                break;
            }
            if(fread(&hof->id,sizeof(int),1,fp)!=1){
                //printf("W Error reading char id.\n");
                break;
            }
            if(fread(&hof->nameLen,sizeof(unsigned int),1,fp)!=1){
                //printf("W Error reading char nameLen.\n");
                break;
            }
            hof->name = malloc(sizeof(char) * hof->nameLen);
            if(hof->name == NULL){printf("Error allocating memory for name");}else{
                if(fread(hof->name,sizeof(char),hof->nameLen,fp)!=hof->nameLen){
                    //printf("W Error reading char name.\n");
                    break;
                }
                hof->name[hof->nameLen] = '\0';
            }
            if(fread(&hof->lvl,sizeof(int),1,fp)!=1){
                //printf("W Error reading char level.\n");
                break;
            }
            if(fread(&hof->enKill,sizeof(int),1,fp)!=1){
                //printf("W Error reading char enKill.\n");
                break;
            }
            if(fread(hof->race,sizeof(char),10,fp)!=10){
                //printf("W Error reading char race.\n");
                break;
            }
            if(fread(hof->gender,sizeof(char),7,fp)!=7){
                //printf("W Error reading char gender.\n");
                break;
            }
            if(fread(hof->spec,sizeof(char),10,fp)!=10){
                //printf("W Error reading char spec.\n");
                break;
            }
            line();
            printf("%d. %s, a level %d %s %s %s, that killed %d enemies. \n",i, hof->name, hof->lvl, hof->gender, hof->race,hof->spec, hof->enKill);
            i++;
            line();
        }
    }
    fclose(fp);
    contNoFat();
}

void emptyhallOfFame(){
    int ret;
    ret = remove("hof.bd");

    if(ret == 0) {
        printf("Hall of Fame has been emptied. \n");
    } else {
        printf("Error: unable to empty the Hall of Fame. \n");
    }
    contNoFat();
}

void hallOfFame(struct items *it, struct hallOfFame *hof){
    int opt;
    int flag = 1;
    while(flag == 1){
        clear();
        line();
        printf(" \t Welcome to the Hall of Fame. \n Here you can view heroes of past, or write your own name in the hall. \n Once you write your name once, you can't do it again. \n");
        printf(" 1. View the Hall of Fame. \n 2. Write your name in the Hall of Fame. \n 3. Empty the Hall of Fame. \n 4. Return to the menu. \n");
        printf("Choose: ");
        scanf("%d", &opt);

        switch(opt){
        case(1):
            viewhallOfFame(it, hof);
            flag = 1;
            clear();
            break;

        case(2):
            writehallOfFame(it, hof);
            flag = 1;
            clear();
            break;
        case(3):
            emptyhallOfFame();
            flag = 1;
            contNoFat();
            break;
        case(4):
            flag = 2;
            contNoFat();
            break;
        default:
            printf("Input error. \n");
            flag = 1;
            contNoFat();
            clear();
            break;
        }
     }
}

//end
