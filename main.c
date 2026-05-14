#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    int Hunger;
    int Happiness;
    int Health;
    int Housing;
    int MaxEmployee;
    int Income;
    int Requirement;
    int Cost;
} Facility;

Facility createFacility(const char* name, int hunger, int happiness, int health, int housing, int maxEmployee, int income, int requirement, int cost) {
    Facility f;
    strncpy(f.Name, name, 50);
    f.Name[50] = '\0';
    f.Hunger = hunger;
    f.Happiness = happiness;
    f.Health = health;
    f.Housing = housing;
    f.MaxEmployee = maxEmployee;
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
    Facility facilities[MAXFACILITIES];
    char cityName[100];
    int facilityCount = 0;
    int population = 10;
    int happiness = 50;
    int hunger = 50;
    int health = 50;
    int day = 1;
    int money = 500;
    int jabodetabek = 0;
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

    facilities[facilityCount++] = createFacility("City Hall", 0, -20, 0, 0, 5, 50, 0, 0);
    
    while (1) {
        printf("---DAY %d---\n\n", day);

        break;
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
    menuLoop();
    return 0;
}