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
    int check = rand() % 4 + 1;
    int check2 = rand() % 3 + 1;
    int failSafe = 0;
    int choice = 0;

    switch (check) {
        case 1: //Hunger
            if(i->hunger * 100 >= num) {
                switch(check2){
                    case 1:
                        printf("You recieve an idea to make a food charity event (300$) to your town.\n What do you do?\n");
                        printf("1. Make\n2+. Not Make\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 300;
                            i->hunger += 0.3;
                            printf("\nYou hosted the charity event, Your people are slightly less hungry!\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 100;
                            i->hunger -= 0.15;
                            printf("\nYou didn't host the charity event, as you go on about your day you found a 100$ bill on the ground.\nYour people are slightly more hungry but you are now 100$ richer!\n");
                        } 

                        break;
                    case 2:
                        printf("You recieve an idea to make a Free Nutritious Meal initiative (400$) to your town's local school.\nWhat do you do?\n");
                        printf("1. Make\n2+. Not Make\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 400;
                            i->health -= 0.2;
                            i->hunger += 0.1;
                            printf("\nYour students got food poisoning and your people are critizising your decisions!\nHey they're atleast a bit less hungry");
                        } 
                        else if (choice >= 2) {
                            v->money += 400;
                            printf("\nYou decided to keep your tax money, maybe this was for the best.\n");
                        } 
                        break;
                    case 3:
                        printf("Your towns food import is taking longer to arrive, your citizens may go hugry but you have the choice to speed it up (300$).\n What do you do?\n");
                        printf("1. Speed it up\n2+. Dont't speed it up\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 300;
                            i->hunger += 0.2;
                            printf("\nYour food managed to arrive on time, Your people are slightly less hungry!\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 200;
                            i->hunger -= 0.2;
                            printf("\nYour food arrived late.\n Your people are slightly more hungry.\n");
                        } 
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;

        case 2: //Health
            if(i->health * 100 >= num) {
                switch(check2){
                    case 1: 
                        printf("Your towns air has been growing rather polluted.\nWould you put some effort in fixing the air pollution (300$)\n");
                        printf("1. Fix\n2+. Not fix\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 300;
                            i->health += 0.2;
                            printf("\nYour town is more habitable!\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 100;
                            i->health -= 0.2;
                            printf("\nYour air is making your citizens more unhealthy.\n");
                        } 
                        break;
                    case 2: 
                        printf("Oh no!\nYour towns factories dumped waste into your water supply! Are you going to save it (400$)?\n");
                        printf("1. Save\n2+. Not save\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 400;
                            i->health += 0.2;
                            printf("\nYour towns water supply is saved!\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 150;
                            i->health -= 0.35;
                            printf("\nYour towns drinking water is cooked.\n");
                        } 
                        break;
                    case 3: 
                        printf("A Virus broke out in your city!.\nYou need to develop a vaccine to cure it (350$)!\n");
                        printf("1. Develop\n2+. Do not develop\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 350;
                            printf("\nThe virus slowly disappeared!\n");
                        } 
                        else if (choice >= 2) {
                            i->health -= 0.2;
                            printf("\nYour town became a breeding den for the virus.\n");
                        } 
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;

        case 3: //Housing
            if(i->housingBackLog * 100 >= num) {
                switch(check2){
                    case 1: // homeless shelter
                        printf("Someone raised the idea of developing more homeless shelters\n Do you agree with this idea (400$)\n");
                        printf("1. Agree\n2+. Not agree\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 400;
                            i->housingBackLog += 0.4;
                            printf("\nThe people loved your decision!\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 300;
                            printf("\nYou got a bit richer by not doing that.\n");
                        } 
                        break;
                        break;
                    case 2:
                        printf("Some people think that the homeless are a disturbance and should be off the streets\n They're telling you to a Do you agree with this idea (400$)\n");
                        printf("1. Agree\n2+. Not agree\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            i->health -= 0.15;
                            printf("\nYour homeless population became less healthy.\n");
                        } 
                        else if (choice >= 2) {
                            printf("\nYou did the bare minimum.\n");
                        break;
                    case 3: 
                        printf("An earthquake just happened in your city\nThey're looking at you for recontructions(350$) do you do it?\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 350;
                            printf("\nYour houses are bigger and better.\n");
                        } 
                        else if (choice >= 2) {
                            i->housingBackLog -= 0.3;
                            printf("\nThe houses were not saved.\n");
                        }
                        break;
                    }
                }
            } else{
                failSafe = 1;
            }
            break;
        case 4: //Employment
            if(i->employment * 100 >= num) {
                switch(check2){
                    case 1: 
                        printf("You had an idea to open more jobs for your people(200$)\nDo you follow through with this idea?\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 200;
                            i->employment += 0.15;
                            printf("\nYour people are more employed.\n");
                        } 
                        else if (choice >= 2) {
                            v->money += 100;
                            i->employment -= 0.1;
                            printf("\nThe people are still yearning for employment.\n");
                        }
                        break;
                    case 2: 
                        printf("Due to the decreasing education rate your unemployment rate is increasing\nDo you try to fix your education system(250$)\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            v->money -= 250;
                            i->employment += 0.2;
                            printf("\nYour people are more employed.\n");
                        } 
                        else if (choice >= 2) {
                            i->employment -= 0.2;
                            printf("\nThe people are still under educated.\n");
                        }
                        break;
                    case 3: 
                        printf("The city needs to make a new public holiday to comemorrate an event, but this will lead to people not working\nDo you follow through with this idea?\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", choice);

                        if(choice == 1) {
                            i->employment -= 0.15;
                            i->health += 0.1;
                            printf("\nYour people had a nice holiday increasing their health.\n");
                        } 
                        else if (choice >= 2) {
                            i->employment += 0.1;
                            i->health -= 0.15;
                            printf("\nThe people are still doing their jobs.\n");
                        }
                        break;
                }
            } else{
                failSafe = 1;
            }
            break;
    }

    if(failSafe == 1){
        switch(num) {
            case 0 ... 19: // people want more variety and junk food (hunger and health)
                printf("Your people wants more convinient junk food access\nDo you follow through with this idea?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                if(choice == 1) {
                    i->health -= 0.15;
                    i->hunger += 0.15;
                    printf("\nYour peoples tummy are more full but they are less healthy.\n");
                } 
                else if (choice >= 2) {
                    i->health += 0.15;
                    i->hunger -= 0.15;
                    printf("\nYour people are not satisfied but they are more healthy.\n");
                }
                break;
            case 20 ... 49: // Someone wants to make a data center (increase job, lowers housing)
                printf("Someone wants to make a data center but in the process will need to tear down some housing\nDo you follow through with this idea?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                if(choice == 1) {
                    i->housingBackLog -= 0.15;
                    i->employment += 0.15;
                    printf("\nYour peoples have more jobs but less housing.\n");
                } 
                else if (choice >= 2) {
                    i->housingBackLog += 0.15;
                    i->employment -= 0.15;
                    printf("\nYour people have live another day without a data center.\n");
                }
                break;
            case 50 ... 79: // better work conditions (health and employment)
                printf("Your people held a protest for better workers right\nDo you give them what they want?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                if(choice == 1) {
                    i->health += 0.15;
                    i->employment -= 0.15;
                    printf("\nYour people became healthier but less work is being done.\n");
                } 
                else if (choice >= 2) {
                    i->health -= 0.15;
                    i->employment += 0.15;
                    printf("\nYour people are not satisfied but they are working more.\n");
                }
                break;
            case 80 ... 90: // weather home (housing and health)
                printf("Your contruction workers feel overworked but you need buildings to be made before a deadline\nDo you try to push them more?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                if(choice == 1) {
                    i->health -= 0.15;
                    i->housingBackLog += 0.15;
                    printf("\nThe deadline was met but your workers became sick.\n");
                } 
                else if (choice >= 2) {
                    i->health += 0.15;
                    i->housingBackLog -= 0.15;
                    printf("\nThe deadline wasnt met but your workers are healthy.\n");
                }
                break;
            case 91 ... 95: // longer lunch breaks (hunger and employment)
                printf("The people want longer lunch breaks\nDo you follow through with this idea?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                if(choice == 1) {
                    i->employment -= 0.15;
                    i->hunger += 0.15;
                    printf("\nYour people have more time to eat! but less time to work.\n");
                } 
                else if (choice >= 2) {
                    i->employment += 0.15;
                    i->hunger -= 0.15;
                    printf("\nYour people are not satisfied but they are working more.\n");
                }
                break;
            case 96 ... 99:
                printf("A Blessing from Cyrene has blessed your town\n");
                printf("Do you accept the gift?\n");
                printf("1+. Accept gift\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                i->employment += 0.2;
                i->health += 0.2;
                i->housingBackLog += 0.2;
                i->hunger += 0.2;

                break;
            case 100:
                printf("OH NO!!! KHASLANA WITH E1 CERYDRA HAS LAUNCEHD A METEOR ON YOUR TOWN!\n");
                printf("MAYOR QUICK WHAT DO WE DO???\n");
                printf("1. Accept fate\n2. Option 1\n3+. Option 2\n");
                printf("Input Choice: ");
                scanf("%d", choice);

                i->employment = 0;
                i->health = 0;
                i->housingBackLog = 0;
                i->hunger = 0;

                printf("\n Your town got destroyed :(\n");
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