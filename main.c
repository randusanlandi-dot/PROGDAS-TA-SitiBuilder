#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXHAPPY 100
#define MAXHUNGER 100
#define MAXHEALTH 100
#define MAXFACILITIES 1000

const char* jabodetabekList[] = {
        "jakarta",
        "bogor",
        "depok",
        "tangerang",
        "bekasi",
        "jabodetabek",
    };

typedef struct {
    char Name[50];
    int Food;
    int HealthCare;
    int Housing;
    int Job;
    int Income;
    int Requirement;
    int Cost;
} Facility;

typedef struct {
    int money;
} values;

// bonus values from errands
typedef struct {
    float eFood;
    float eHealthcare;
    float eHousing;
    float eJob;
} eBonus;

// index
typedef struct {
    float hunger;
    float health;
    float housingBackLog;
    float employment;
    float happiness;
} index;

Facility createFacility(const char* name, int food, int healthcare, int housing, int job, int income, int requirement, int cost) {
    Facility f;
    strncpy(f.Name, name, 50);
    f.Name[50] = '\0';
    f.Food = food;
    f.HealthCare = healthcare;
    f.Housing = housing;
    f.Job = job;
    f.Income = income;
    f.Requirement = requirement;
    f.Cost = cost;
    return f;
}

void printAbout() {
    int choice;
    printf("-------------------\n");
    printf(" About SitiBuilder\n");
    printf("-------------------\n\n");
    printf("This is a simulator game that mimics building a real-life ecosystem within\n");
    printf("cities by playing as a humble Mayor. Your goal is to expand your population\n");
    printf("while accomodating to your people's needs by providing a balanced variety of\n");
    printf("facilities and services.\n\n");
    printf("As the mayor, you need to juggle between growing your city and keeping a stable\n");
    printf("income. To grow your population, you need to spend your money to build more\n");
    printf("houses and facilities to keep them happy. To keep your money stable, you need\n");
    printf("to provide jobs to your citizens, which will decrease their happiness.\n\n");

    printf("Enter any number to return to main menu: ");
    scanf("%d", &choice);
    printf("\n");
}

void printHowToPlay() {
    int choice;
    printf("-------------------------\n");
    printf(" How to play SitiBuilder\n");
    printf("-------------------------\n\n");
    printf("The simulator runs on a day-to-day basis where you will encounter scenarios\n");
    printf("each day. As the Mayor, you are tasked to respond to each scenario according\n");
    printf("to you and your city's needs.\n\n");
    printf("You will also have the opportunity to build certain facilities using your\n");
    printf("collected money to keep the town growing.\n\n");
    printf("Highscores will be kept (hopefully) in the form of days and population size,\n\n");

    printf("Enter any number to return to main menu: ");
    scanf("%d", &choice);
    printf("\n");
}

void gameLoop() {
    // starting values
    Facility facilities[MAXFACILITIES];
    char cityName[100];
    int facilityCount = 0;
    int population = 10;
    int week = 1;
    int jabodetabek = 0;

    // totalvalues
    float food = 0;
    float healthcare = 0;
    float housing = 0;
    float job = 0;

    // errands
    values cityValues = {0};
    eBonus errandBonus = {0};
    index cityIndex = {0};

    cityValues.money = 500;

    int choice;

    printf("--------------\n");
    printf(" Introduction\n");
    printf("--------------\n\n");
    
    printf("Welcome to your city! It's your first day as a mayor.\n");
    printf("Your first job is to name your brand new city!\n");
    printf("What is the name of your city?: ");
    scanf(" %99[^\n]", cityName);
    printf("\n");

    char cityTest[100];
    strcpy(cityTest, cityName);
    for (int i = 0; cityTest[i]; i++) {
        cityTest[i] = tolower(cityTest[i]);
    }

    for (int i = 0; sizeof(jabodetabekList)/sizeof(jabodetabekList[0]); i++) {
        if (strstr(cityTest, jabodetabekList[i]) != NULL) {
            jabodetabek = 1;
            break;
        }
    }

    if (jabodetabek) {
        printf("-------------\n");
        printf(" Game Over !\n");
        printf("-------------\n");
        printf("Unfortunately, you cannot save the Jabodetabeks!\n\n");

        printf("Enter any number to return to main menu: ");
        scanf("%d", &choice);
        printf("\n");
    }

    facilities[facilityCount++] = createFacility("City Hall", 0, 0, 0, 5, 50, 0, 0);
    
    while (1) {
        printf("---WEEK %d---\n\n", week);
        break;
    }
}

void errands(values *v, eBonus *e, index *i){
    int num = rand() % 100 + 1;
    int check = rand() % 5 + 1;
    int check2 = rand() % 3 + 1;
    int failSafe = 0;

    switch (check) {
        case 1: //Hunger
            if(i->hunger >= num) {
                switch(check2){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;

        case 2: //Health
            if(i->health >= num) {
                switch(check2){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;

        case 3: //Housing
            if(i->health >= num) {
                switch(check2){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;
        case 4: //Employment
            if(i->health >= num) {
                switch(check2){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;
        case 5: //Happiness
            if(i->health >= num) {
                switch(check2){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;
    }

    if(failSafe == 1){
        switch(num) {
            case 0 ... 9:
                break;
            case 10 ... 19:
                break;
            case 20 ... 29:
                break;
            case 30 ... 39:
                break;
            case 40 ... 49:
                break;
            case 50 ... 59:
                break;
            case 60 ... 69:
                break;
            case 70 ... 79:
                break;
            case 80 ... 89:
                break;
            case 90 ... 99:
                break;
            case 100:
                printf("OH NO!!! KHASLANA HAS LAUNCEHD A METEOR ON YOUR TOWN WITH E1 CERYDRA!");
                
                break;
        }
    }
}



void menuLoop() {
    int choice;
    while (1) {
        printf("----------------------------------\n");
        printf(" Welcome to SitiBuilder! Ver. 1.0\n");
        printf("----------------------------------\n");
        printf(" 1. Start Simulation\n");
        printf(" 2. About\n");
        printf(" 3. How to Play\n");
        printf(" 4. Exit\n\n");
        printf("Select: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                gameLoop();
                break;   
            case 2:
                printAbout();
                break;
            case 3:
                printHowToPlay();
                break;
            case 4:
                printf("Thank you for playing SitiBuilder!");
                return;
        }
    }
}

int main() {
    srand(time(NULL));
    menuLoop();
    return 0;
}