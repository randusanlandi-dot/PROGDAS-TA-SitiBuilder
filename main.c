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
    f.Name[49] = '\0';
    f.Food = food;
    f.HealthCare = healthcare;
    f.Housing = housing;
    f.Job = job;
    f.Income = income;
    f.Requirement = requirement;
    f.Cost = cost;
    return f;
}

void calculateIndexes(Facility facilities[], int facilityCount, int population, index *cityIndex, eBonus *bonus)
{
    float totalFood = 0.0f;
    float totalHealthcare = 0.0f;
    float totalHousing = 0.0f;
    float totalJob = 0.0f;

    for(int i = 0; i < facilityCount; i++)
    {
        totalFood += facilities[i].Food;
        totalHealthcare += facilities[i].HealthCare;
        totalHousing += facilities[i].Housing;
        totalJob += facilities[i].Job;
    }

    totalFood += bonus->eFood;
    totalHealthcare += bonus->eHealthcare;
    totalHousing += bonus->eHousing;
    totalJob += bonus->eJob;

    cityIndex->hunger = totalFood / (population * 3.0f);
    cityIndex->health = totalHealthcare / (population * 1.0f);
    cityIndex->housingBackLog = totalHousing / (population * 1.0f);
    cityIndex->employment = totalJob / (population * 1.0f);

    if (cityIndex->hunger > 1.0f) cityIndex->hunger = 1.0f;
    if (cityIndex->health > 1.0f) cityIndex->health = 1.0f;
    if (cityIndex->housingBackLog > 1.0f) cityIndex->housingBackLog = 1.0f;
    if (cityIndex->employment > 1.0f) cityIndex->employment = 1.0f;

    if (cityIndex->hunger < 0.0f) cityIndex->hunger = 0.0f;
    if (cityIndex->health < 0.0f) cityIndex->health = 0.0f;
    if (cityIndex->housingBackLog < 0.0f) cityIndex->housingBackLog = 0.0f;
    if (cityIndex->employment < 0.0f) cityIndex->employment = 0.0f;
}

Facility catalogue[] = {
    // page 1
    {"Basic Apartment", 0, 0, 25, 0, 0, 10, 150},
    {"Local Market", 20,  3,  5,  4,  30, 10,  200},
    {"Small Clinic",0, 18,  0,  2,  25, 10,  250},
    {"Vegetable Farm", 28,  2,  0,  3,  20, 10,  180},
    {"School", 0,  8,  5,  6,  15, 10,  220},

    // page 2
    {"Apartment Complex", 0,  0, 80,  0,   0, 100,  800},
    {"Supermarket", 65,  5, 10, 12, 120, 100, 1200},
    {"Hospital", 0, 70, 15, 10, 200, 100, 2500},
    {"Large Farm", 90, 8, 5, 8, 80, 100, 1100},
    {"Factory", 5, -10, 10, 45, 450, 100, 1800},

    // page 3
    {"High-Rise Housing", 0, 0, 350, 0, 0, 1000, 6500},
    {"Mega Mall", 220, 15, 40, 35, 800, 1000, 9500},
    {"University", 0, 45, 30, 60, 300, 1000, 7200},
    {"Industrial Park", 30,-25, 50, 180,2200, 1000, 8500},
    {"Solar Farm", 120, 20, 25, 15, 400, 1000, 6800},

    // page 4
    {"Skyscraper District", 0, 0,1200, 0, 0,10000, 45000},
    {"Tech Hub", 80, 60, 80, 220,6500,10000, 52000},
    {"Advanced Hospital", 0,280, 60, 45,1200,10000, 38000},
    {"Automated Factory", 150,-80,120, 450,8500,10000, 62000},
    {"Vertical Farm", 450, 30, 80, 60,1500,10000, 48000}
};

int catalogueCount = sizeof(catalogue) / sizeof(catalogue[0]);

void buildFacility(Facility facilities[], int *facilityCount, values *v, int population)
{
    if (*facilityCount >= MAXFACILITIES) {
        printf("Maximum number of facilities reached!\n");
        return;
    }

    int page = 1;
    const int itemsPerPage = 5;

    while (1) {
        printf("\n=== FACILITY CATALOGUE - Page %d ===\n", page);
        printf("Population: %d | Money: $%d\n\n", population, v->money);

        int start = (page - 1) * itemsPerPage;
        int end = start + itemsPerPage;
        if (end > catalogueCount) end = catalogueCount;

        for (int i = start; i < end; i++) {
            int displayNum = (i - start) + 1;   // 1 to 5

            if (catalogue[i].Requirement > population) {
                printf("%d. [LOCKED] %s (Req: %d pop)\n", displayNum, catalogue[i].Name, catalogue[i].Requirement);
            } else {
                printf("%d. %s | Cost: $%d\n", displayNum, catalogue[i].Name, catalogue[i].Cost);
                printf("   F:%d  HC:%d  Hs:%d  J:%d  Inc:%d\n",
                       catalogue[i].Food, catalogue[i].HealthCare,
                       catalogue[i].Housing, catalogue[i].Job, catalogue[i].Income);
            }
        }

        printf("\n6. Next Page    7. Previous Page\n");
        printf("0. Back\n");
        printf("Select: ");
        
        int choice;
        scanf("%d", &choice);

        if (choice == 0) return;
        if (choice == 6) { 
            if (start + itemsPerPage < catalogueCount) page++;
            continue; 
        }
        if (choice == 7) { 
            if(page > 1) page--; 
            continue; 
        }

        if (choice < 1 || choice > (end - start)) {
            printf("Invalid selection!\n");
            continue;
        }

        int realIndex = start + (choice - 1);
        Facility *selected = &catalogue[realIndex];

        if (selected->Requirement > population) {
            printf("This facility is locked. You need more population.\n");
            continue;
        }

        if (v->money <= 0) {
            printf("You cannot build new facilities while in debt!\n");
            continue;
        }

        if (v->money < selected->Cost) {
            printf("\nWARNING: This purchase will put you into DEBT.\n");
            printf("Current: $%d → After: $%d\n", v->money, v->money - selected->Cost);
            printf("Are you sure? (1 = Yes, 0 = No): ");
            
            int confirm;
            scanf("%d", &confirm);
            if (confirm != 1) {
                printf("Purchase cancelled.\n");
                continue;
            }
        }

        v->money -= selected->Cost;
        facilities[*facilityCount] = *selected;
        (*facilityCount)++;

        printf("\nSuccessfully built: %s!\n", selected->Name);
        
        printf("Press any number to continue: ");
        scanf("%d", &choice);
    }
}

void calculateHappiness(index *i)
{
    i->happiness = (i->hunger * 25.0f) + (i->health * 25.0f) + (i->housingBackLog * 25.0f) + (i->employment * 25.0f);
    if (i->happiness > 100.0f) i->happiness = 100.0f;
    if (i->happiness < 0.0f)   i->happiness = 0.0f;
}

int calculateWeeklyIncome(Facility facilities[], int facilityCount, index *cityIndex)
{
    int total = 0;
    for(int i = 0; i < facilityCount; i++)
    {
        total += facilities[i].Income;
    }
    
    total = (int)(total * cityIndex->employment);
    
    return total;
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

void doResearch(values *v, Facility facilities[], int facilityCount, eBonus *bonus, 
                index *cityIndex, int population)
{
    int choice;
    printf("\n=== RESEARCH CENTER ===\n");
    printf("Current Money: $%d\n\n", v->money);
    
    printf("1. Raw City Statistics     ($25)\n");
    printf("2. City Index Report       ($40)\n");
    printf("3. Satisfaction & Forecast ($70)\n");
    printf("4. Back to Menu\n\n");
    printf("Select: ");
    scanf("%d", &choice);

    if (choice == 1) {
        if (v->money < 25) {
            printf("Not enough money!\n");
            return;
        }
        v->money -= 25;

        float totalFood = 0, totalHealth = 0, totalHousing = 0, totalJob = 0;

        for(int i = 0; i < facilityCount; i++) {
            totalFood += facilities[i].Food;
            totalHealth += facilities[i].HealthCare;
            totalHousing += facilities[i].Housing;
            totalJob += facilities[i].Job;
        }

        totalFood += bonus->eFood;
        totalHealth += bonus->eHealthcare;
        totalHousing += bonus->eHousing;
        totalJob += bonus->eJob;

        printf("\n--- RAW CITY STATISTICS ---\n");
        printf("Total Food Supply      : %.1f\n", totalFood);
        printf("Total Healthcare       : %.1f\n", totalHealth);
        printf("Total Housing          : %.1f\n", totalHousing);
        printf("Total Jobs             : %.1f\n", totalJob);
        printf("Population             : %d\n", population);

    }
    else if (choice == 2) {
        if (v->money < 40) {
            printf("Not enough money!\n");
            return;
        }
        v->money -= 40;

        calculateIndexes(facilities, facilityCount, population, cityIndex, bonus);

        printf("\n--- CITY INDEX REPORT ---\n");
        printf("Hunger Satisfaction    : %.2f (%.0f%%)\n", cityIndex->hunger, cityIndex->hunger*100);
        printf("Health                 : %.2f (%.0f%%)\n", cityIndex->health, cityIndex->health*100);
        printf("Housing                : %.2f (%.0f%%)\n", cityIndex->housingBackLog, cityIndex->housingBackLog*100);
        printf("Employment             : %.2f (%.0f%%)\n", cityIndex->employment, cityIndex->employment*100);
    }
    else if (choice == 3) {
        if (v->money < 70) {
            printf("Not enough money!\n");
            return;
        }
        v->money -= 70;

        calculateIndexes(facilities, facilityCount, population, cityIndex, bonus);
        calculateHappiness(cityIndex);

        float popChange = 0.0f;
        if (cityIndex->happiness > 50.0f)
            popChange += (cityIndex->happiness - 50.0f) * 0.18f;
        else if (cityIndex->happiness < 50.0f)
            popChange -= (50.0f - cityIndex->happiness) * 0.25f;

        if (cityIndex->hunger < 0.5f)
            popChange -= (0.5f - cityIndex->hunger) * population * 0.12f;
        if (cityIndex->health < 0.5f)
            popChange -= (0.5f - cityIndex->health) * population * 0.10f;
        if (cityIndex->housingBackLog < 0.5f)
            popChange -= (0.5f - cityIndex->housingBackLog) * population * 0.15f;
        if (cityIndex->employment < 0.5f)
            popChange -= (0.5f - cityIndex->employment) * population * 0.13f;

        printf("\n--- CITY SATISFACTION & FORECAST ---\n");
        printf("Overall Happiness      : %.1f / 100\n", cityIndex->happiness);
        printf("Expected Pop Change    : %.0f\n", popChange);
        printf("(Next week's population will be approx %d)\n", population + (int)popChange);
    }
    else {
        printf("Cancelled.\n");
        return;
    }

    printf("\nResearch completed.\n");
}

void errands(values *v, eBonus *e, index *i)
{
    int num = rand() % 100 + 1;
    int check = rand() % 4 + 1;
    int check2 = rand() % 3 + 1;
    int failSafe = 0;
    int choice = 0;

    switch (check) {
        case 1:
            if (i->hunger * 100 >= num) {
                switch(check2){
                    case 1:
                        printf("You receive an idea to make a food charity event (300$) to your town.\nWhat do you do?\n");
                        printf("1. Make\n2+. Not Make\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 300;
                            e->eFood += 15.0f;
                            printf("\nYou hosted the charity event. Your people are less hungry!\n");
                        }
                        else {
                            v->money += 100;
                            e->eFood -= 7.5f;
                            printf("\nYou didn't host the event. You found 100$ but people are hungrier.\n");
                        }
                        break;

                    case 2:
                        printf("You receive an idea to make a Free Nutritious Meal initiative (400$) to your town's local school.\nWhat do you do?\n");
                        printf("1. Make\n2+. Not Make\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 400;
                            e->eFood += 5.0f;
                            e->eHealthcare -= 10.0f;
                            printf("\nYour students got food poisoning! Mixed results.\n");
                        }
                        else {
                            v->money += 400;
                            printf("\nYou decided to keep your tax money.\n");
                        }
                        break;

                    case 3:
                        printf("Your town's food import is taking longer to arrive. Speed it up? (300$)\n");
                        printf("1. Speed it up\n2+. Don't\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 300;
                            e->eFood += 10.0f;
                            printf("\nFood arrived on time!\n");
                        }
                        else {
                            v->money += 200;
                            e->eFood -= 10.0f;
                            printf("\nFood arrived late. People are hungrier.\n");
                        }
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;

        case 2:
            if (i->health * 100 >= num) {
                switch(check2){
                    case 1:
                        printf("Your town's air has been growing rather polluted.\nFix it? (300$)\n");
                        printf("1. Fix\n2+. Not fix\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 300;
                            e->eHealthcare += 10.0f;
                            printf("\nAir quality improved!\n");
                        }
                        else {
                            v->money += 100;
                            e->eHealthcare -= 10.0f;
                            printf("\nAir is making citizens more unhealthy.\n");
                        }
                        break;

                    case 2:
                        printf("Oh no! Factories dumped waste into the water supply! Save it? (400$)\n");
                        printf("1. Save\n2+. Not save\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 400;
                            e->eHealthcare += 10.0f;
                            printf("\nWater supply saved!\n");
                        }
                        else {
                            v->money += 150;
                            e->eHealthcare -= 17.5f;
                            printf("\nWater supply is contaminated...\n");
                        }
                        break;

                    case 3:
                        printf("A Virus broke out in your city! Develop vaccine? (350$)\n");
                        printf("1. Develop\n2+. Do not\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 350;
                            e->eHealthcare += 15.0f;
                            printf("\nThe virus has been contained!\n");
                        }
                        else {
                            e->eHealthcare -= 10.0f;
                            printf("\nThe virus spreads uncontrollably...\n");
                        }
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;

        case 3:
            if (i->housingBackLog * 100 >= num) {
                switch(check2){
                    case 1:
                        printf("Someone raised the idea of developing more homeless shelters (400$)\n");
                        printf("1. Agree\n2+. Not agree\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 400;
                            e->eHousing += 20.0f;
                            printf("\nThe people loved your decision!\n");
                        }
                        else {
                            v->money += 300;
                            printf("\nYou saved money by not building them.\n");
                        }
                        break;

                    case 2:
                        printf("Some people think the homeless are a disturbance (400$)\n");
                        printf("1. Agree\n2+. Not agree\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            e->eHealthcare -= 7.5f;
                            printf("\nHomeless population became less healthy.\n");
                        }
                        else {
                            printf("\nYou did the bare minimum.\n");
                        }
                        break;

                    case 3:
                        printf("An earthquake hit your city! Reconstruct? (350$)\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 350;
                            e->eHousing += 15.0f;
                            printf("\nHouses rebuilt better than before!\n");
                        }
                        else {
                            e->eHousing -= 15.0f;
                            printf("\nMany houses were not saved.\n");
                        }
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;

        case 4:
            if (i->employment * 100 >= num) {
                switch(check2){
                    case 1:
                        printf("You had an idea to open more jobs (200$)\nDo you follow through?\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 200;
                            e->eJob += 7.5f;
                            printf("\nMore people are now employed.\n");
                        }
                        else {
                            v->money += 100;
                            e->eJob -= 5.0f;
                            printf("\nPeople are still looking for jobs.\n");
                        }
                        break;

                    case 2:
                        printf("Education rate is dropping, increasing unemployment. Fix it? (250$)\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            v->money -= 250;
                            e->eJob += 10.0f;
                            printf("\nEducation improved. More people employed.\n");
                        }
                        else {
                            e->eJob -= 10.0f;
                            printf("\nUnemployment continues to rise.\n");
                        }
                        break;

                    case 3:
                        printf("The city wants a new public holiday. Approve?\n");
                        printf("1. Yes\n2+. No\n");
                        printf("Input Choice: ");
                        scanf("%d", &choice);
                        if(choice == 1) {
                            e->eJob -= 7.5f;
                            e->eHealthcare += 5.0f;
                            printf("\nPeople enjoyed the holiday and became healthier.\n");
                        }
                        else {
                            e->eJob += 5.0f;
                            e->eHealthcare -= 7.5f;
                            printf("\nPeople kept working.\n");
                        }
                        break;
                }
            } else {
                failSafe = 1;
            }
            break;
    }

    if (failSafe == 1) {
        switch(num) {
            case 0 ... 19:
                printf("Your people want more convenient junk food access.\nDo you allow it?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                if(choice == 1) {
                    e->eFood += 7.5f;
                    e->eHealthcare -= 7.5f;
                    printf("\nPeople are fuller but less healthy.\n");
                }
                else {
                    e->eFood -= 7.5f;
                    e->eHealthcare += 7.5f;
                    printf("\nPeople are healthier but less satisfied.\n");
                }
                break;

            case 20 ... 49:
                printf("Someone wants to build a data center but it requires tearing down housing.\nDo you allow it?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                if(choice == 1) {
                    e->eHousing -= 7.5f;
                    e->eJob += 7.5f;
                    printf("\nData center built. More jobs, but less housing.\n");
                }
                else {
                    e->eHousing += 7.5f;
                    e->eJob -= 7.5f;
                    printf("\nNo data center. Housing preserved.\n");
                }
                break;

            case 50 ... 79:
                printf("Your people held a protest for better workers' rights.\nDo you give in?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                if(choice == 1) {
                    e->eHealthcare += 7.5f;
                    e->eJob -= 7.5f;
                    printf("\nWorkers are happier and healthier, but productivity dropped.\n");
                }
                else {
                    e->eHealthcare -= 7.5f;
                    e->eJob += 7.5f;
                    printf("\nWorkers are unhappy but production continues.\n");
                }
                break;

            case 80 ... 90:
                printf("Your construction workers feel overworked. Push them harder?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                if(choice == 1) {
                    e->eHealthcare -= 7.5f;
                    e->eHousing += 7.5f;
                    printf("\nDeadline met, but workers got sick.\n");
                }
                else {
                    e->eHealthcare += 7.5f;
                    e->eHousing -= 7.5f;
                    printf("\nDeadline missed, but workers are healthy.\n");
                }
                break;

            case 91 ... 95:
                printf("The people want longer lunch breaks.\nDo you approve?\n");
                printf("1. Yes\n2+. No\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                if(choice == 1) {
                    e->eJob -= 7.5f;
                    e->eFood += 7.5f;
                    printf("\nPeople have more time to eat, but less work gets done.\n");
                }
                else {
                    e->eJob += 7.5f;
                    e->eFood -= 7.5f;
                    printf("\nPeople are working more but are less happy.\n");
                }
                break;

            case 96 ... 99:
                printf("A Blessing from Cyrene has blessed your town!\n");
                printf("Do you accept the gift? (1+. Accept)\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                e->eFood += 10.0f;
                e->eHealthcare += 10.0f;
                e->eHousing += 10.0f;
                e->eJob += 10.0f;
                printf("\nA wonderful blessing! All aspects of the city improved.\n");
                break;

            case 100:
                printf("OH NO!!! KHASLANA WITH E1 CERYDRA HAS LAUNCHED A METEOR ON YOUR TOWN!\n");
                printf("MAYOR QUICK WHAT DO WE DO???\n");
                printf("1. Accept fate\n2. Option 1\n3+. Option 2\n");
                printf("Input Choice: ");
                scanf("%d", &choice);
                e->eFood = -9999.0f;
                e->eHealthcare = -9999.0f;
                e->eHousing = -9999.0f;
                e->eJob = -9999.0f;
                printf("\nYour town has been destroyed...\n");
                break;
        }
    }
}

void gameLoop() {
    Facility facilities[MAXFACILITIES];
    char cityName[100];
    int facilityCount = 0;
    int population = 10;
    int highestPopulation = 10;
    int week = 1;
    int jabodetabek = 0;
    int debtWeeks = 0;

    values cityValues = {500};
    eBonus errandBonus = {0};
    index cityIndex = {0};

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
    for (int i = 0; i < sizeof(jabodetabekList)/sizeof(jabodetabekList[0]); i++) {
        if (strstr(cityTest, jabodetabekList[i]) != NULL) {
            jabodetabek = 1;
            break;
        }
    }

    if (jabodetabek) {
        printf("-------------\n Game Over !\n-------------\n");
        printf("Unfortunately, you cannot save the Jabodetabeks!\n\n");
        int dummy; scanf("%d", &dummy);
        return;
    }

    facilities[facilityCount++] = createFacility("City Hall", 0, 5, 5, 8, 80, 0, 0);
    facilities[facilityCount++] = createFacility("Basic Housing", 0, 0, 15, 0, 0, 0, 0);
    facilities[facilityCount++] = createFacility("Local Market", 18, 2, 0, 3, 20, 0, 0);
    facilities[facilityCount++] = createFacility("Community Clinic", 0, 12, 0, 2, 15, 0, 0);
    facilities[facilityCount++] = createFacility("Small Farm", 22, 0, 0, 2, 10, 0, 0);

    while (1) {
        int errandsThisWeek = 0;
        int errandsRemaining = 0;

        errandsThisWeek = 1 + (rand() % 3);                   

        if (population >= 100)   errandsThisWeek += 1;
        if (population >= 1000)  errandsThisWeek += 1;
        if (population >= 10000) errandsThisWeek += 1;


        if (population >= 10000) {
            errandsThisWeek = 4 + (rand() % 3);   // 4-6
        }

        errandsRemaining = errandsThisWeek;

        while (1) {
            printf("\n--- WEEK %d ---\n", week);
            printf("Population : %d\n", population);
            printf("Money      : $%d\n", cityValues.money);
            printf("Errands    : %d / %d\n\n", errandsRemaining, errandsThisWeek);

            printf("1. Do Errands\n");
            printf("2. Build Facilities\n");
            printf("3. Do Research\n");
            printf("4. Continue to Next Week\n");
            printf("Select: ");

            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                if (errandsRemaining > 0) {
                    printf("\nHandling errand...\n\n");
                    errands(&cityValues, &errandBonus, &cityIndex);
                    errandsRemaining--;
                } else {
                    printf("\nNo more errands left this week!\n");
                }
            }
            else if (choice == 2) {
                buildFacility(facilities, &facilityCount, &cityValues, highestPopulation);
            }
            else if (choice == 3) {
                doResearch(&cityValues, facilities, facilityCount, &errandBonus, &cityIndex, population);
            }
            else if (choice == 4) {
                if (errandsRemaining > 0) {
                    printf("\nYou still have %d errands left! Finish them first.\n", errandsRemaining);
                } else {
                    printf("\nEnding Week %d...\n", week);
                    break;
                }
            }
            else {
                printf("\nInvalid choice!\n");
            }
        }

        calculateIndexes(facilities, facilityCount, population, &cityIndex, &errandBonus);
        calculateHappiness(&cityIndex);
        int weeklyIncome = calculateWeeklyIncome(facilities, facilityCount, &cityIndex);
        cityValues.money += weeklyIncome;

        if (population < (int)(highestPopulation * 0.4f)) {
            printf("\n=====================================\n");
            printf(" GAME OVER - CITY COLLAPSED\n");
            printf("=====================================\n");
            printf("Your population dropped below 40%% of its peak.\n");
            printf("Final Population: %d | Highest: %d\n", population, highestPopulation);
            printf("You survived %d weeks.\n", week-1);
            int dummy; scanf("%d", &dummy);
            return;
        }

        if (cityValues.money < 0) {
            debtWeeks++;
            if (debtWeeks == 1) {
                printf("\nWARNING: Your city is now in debt!\n");
            } else if (debtWeeks == 3) {
                printf("\n!!! CRITICAL WARNING: You have been in debt for 3 weeks!\n");
                printf("   If this continues, the city will go bankrupt.\n");
            } else if (debtWeeks >= 4) {
                printf("\n=====================================\n");
                printf(" GAME OVER - BANKRUPT\n");
                printf("=====================================\n");
                printf("You were in debt for too long.\n");
                printf("Final Population: %d | Weeks Survived: %d\n", population, week-1);
                int dummy; scanf("%d", &dummy);
                return;
            }
        } else {
            debtWeeks = 0;
        }

        if (cityIndex.happiness <= 0.0f) {
            printf("\n=====================================\n");
            printf(" GAME OVER - RIOT & TOTAL COLLAPSE\n");
            printf("=====================================\n");
            printf("Happiness reached 0. The citizens rioted and destroyed the city.\n");
            printf("Final Population: %d | Highest: %d\n", population, highestPopulation);
            int dummy; scanf("%d", &dummy);
            return;
        }

        if (population > highestPopulation) {
            highestPopulation = population;
            printf("\nNew Population Record! Highest Population: %d\n", highestPopulation);
        }

        float popChange = 0.0f;

        if (cityIndex.happiness > 50.0f) {
            popChange += (cityIndex.happiness - 50.0f) * 0.18f;
        } 
        else if (cityIndex.happiness < 50.0f) {
            popChange -= (50.0f - cityIndex.happiness) * 0.25f;
        }

        if (cityIndex.hunger < 0.5f)
            popChange -= (0.5f - cityIndex.hunger) * population * 0.12f;
        
        if (cityIndex.health < 0.5f)
            popChange -= (0.5f - cityIndex.health) * population * 0.10f;
        
        if (cityIndex.housingBackLog < 0.5f)
            popChange -= (0.5f - cityIndex.housingBackLog) * population * 0.15f;
        
        if (cityIndex.employment < 0.5f)
            popChange -= (0.5f - cityIndex.employment) * population * 0.13f;

        population += (int)popChange;

        if (population < 1) population = 1;

        week++;

        if (week > 1000) {
            printf("\nGame reached maximum weeks (testing limit).\n");
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
                printf("Thank you for playing SitiBuilder!\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n\n");
        }
    }
}

int main() {
    srand(time(NULL));
    menuLoop();
    return 0;
}