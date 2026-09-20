#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINS 100
#define MAX_COMPLAINTS 100

// Structure for Waste Bin
struct WasteBin
{
    int id;
    char area[50];
    float capacity;
    float filled;
};

// Structure for Complaint
struct Complaint
{
    int id;
    char name[50];
    char area[50];
    char description[200];
};

// Global variables
struct WasteBin bins[MAX_BINS];
struct Complaint complaints[MAX_COMPLAINTS];

int binCount = 0;
int complaintCount = 0;

// Function declarations
void loadBins();
void saveBins();
void loadComplaints();
void saveComplaints();

void addBin();
void viewBins();
void checkBinStatus();
void collectWaste();

void addComplaint();
void viewComplaints();

void generateReport();

int main()
{
    int choice;

    // Load saved data from files
    loadBins();
    loadComplaints();

    do
    {
        printf("\n\n==============================================");
        printf("\n       SMART WASTE MANAGEMENT SYSTEM");
        printf("\n              URBAN INDIA");
        printf("\n==============================================");

        printf("\n1. Add Waste Bin");
        printf("\n2. View All Waste Bins");
        printf("\n3. Check Bin Status");
        printf("\n4. Collect Waste");
        printf("\n5. Add Citizen Complaint");
        printf("\n6. View Complaints");
        printf("\n7. Generate Report");
        printf("\n8. Exit");

        printf("\n----------------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBin();
                break;

            case 2:
                viewBins();
                break;

            case 3:
                checkBinStatus();
                break;

            case 4:
                collectWaste();
                break;

            case 5:
                addComplaint();
                break;

            case 6:
                viewComplaints();
                break;

            case 7:
                generateReport();
                break;

            case 8:
                printf("\nThank you for using Smart Waste Management System!");
                break;

            default:
                printf("\nInvalid choice! Please try again.");
        }

    } while(choice != 8);

    return 0;
}


/*=================================================
              FILE HANDLING FUNCTIONS
=================================================*/

// Load bins from file
void loadBins()
{
    FILE *fp;

    fp = fopen("bins.txt", "r");

    if(fp == NULL)
    {
        return;
    }

    binCount = 0;

    while(binCount < MAX_BINS &&
          fscanf(fp, "%d %49s %f %f",
                 &bins[binCount].id,
                 bins[binCount].area,
                 &bins[binCount].capacity,
                 &bins[binCount].filled) == 4)
    {
        binCount++;
    }

    fclose(fp);
}


// Save bins to file
void saveBins()
{
    FILE *fp;
    int i;

    fp = fopen("bins.txt", "w");

    if(fp == NULL)
    {
        printf("\nError opening bins file!");
        return;
    }

    for(i = 0; i < binCount; i++)
    {
        fprintf(fp, "%d %s %.2f %.2f\n",
                bins[i].id,
                bins[i].area,
                bins[i].capacity,
                bins[i].filled);
    }

    fclose(fp);
}


// Load complaints
void loadComplaints()
{
    FILE *fp;

    fp = fopen("complaints.txt", "r");

    if(fp == NULL)
    {
        return;
    }

    complaintCount = 0;

    while(complaintCount < MAX_COMPLAINTS &&
          fscanf(fp, "%d %49s %49s %[^\n]",
                 &complaints[complaintCount].id,
                 complaints[complaintCount].name,
                 complaints[complaintCount].area,
                 complaints[complaintCount].description) == 4)
    {
        complaintCount++;
    }

    fclose(fp);
}


// Save complaints
void saveComplaints()
{
    FILE *fp;
    int i;

    fp = fopen("complaints.txt", "w");

    if(fp == NULL)
    {
        printf("\nError opening complaints file!");
        return;
    }

    for(i = 0; i < complaintCount; i++)
    {
        fprintf(fp, "%d %s %s %s\n",
                complaints[i].id,
                complaints[i].name,
                complaints[i].area,
                complaints[i].description);
    }

    fclose(fp);
}


/*=================================================
              WASTE BIN FUNCTIONS
=================================================*/

// Add new waste bin
void addBin()
{
    if(binCount >= MAX_BINS)
    {
        printf("\nMaximum number of bins reached!");
        return;
    }

    printf("\n\n========== ADD WASTE BIN ==========");

    printf("\nEnter Bin ID: ");
    scanf("%d", &bins[binCount].id);

    printf("Enter Area/Ward name: ");
    scanf("%49s", bins[binCount].area);

    printf("Enter Bin Capacity (kg): ");
    scanf("%f", &bins[binCount].capacity);

    printf("Enter Current Waste (kg): ");
    scanf("%f", &bins[binCount].filled);

    if(bins[binCount].capacity <= 0)
    {
        printf("\nCapacity must be greater than zero.");
        return;
    }

    if(bins[binCount].filled < 0 ||
       bins[binCount].filled > bins[binCount].capacity)
    {
        printf("\nInvalid waste quantity!");
        return;
    }

    binCount++;

    saveBins();

    printf("\nWaste bin added successfully!");

    if((bins[binCount - 1].filled /
        bins[binCount - 1].capacity) * 100 >= 80)
    {
        printf("\nALERT: This bin is 80%% or more full!");
    }
}


// View all bins
void viewBins()
{
    int i;
    float percentage;

    if(binCount == 0)
    {
        printf("\nNo waste bins available.");
        return;
    }

    printf("\n\n================ ALL WASTE BINS ================");

    printf("\n%-8s %-15s %-12s %-12s %-12s",
           "ID", "AREA", "CAPACITY", "FILLED", "STATUS");

    printf("\n--------------------------------------------------");

    for(i = 0; i < binCount; i++)
    {
        percentage =
            (bins[i].filled / bins[i].capacity) * 100;

        printf("\n%-8d %-15s %-12.2f %-12.2f ",
               bins[i].id,
               bins[i].area,
               bins[i].capacity,
               bins[i].filled);

        if(percentage >= 80)
        {
            printf("FULL");
        }
        else if(percentage >= 50)
        {
            printf("MEDIUM");
        }
        else
        {
            printf("LOW");
        }
    }

    printf("\n==================================================");
}


// Check individual bin status
void checkBinStatus()
{
    int id;
    int i;
    int found = 0;
    float percentage;

    printf("\nEnter Bin ID: ");
    scanf("%d", &id);

    for(i = 0; i < binCount; i++)
    {
        if(bins[i].id == id)
        {
            found = 1;

            percentage =
                (bins[i].filled / bins[i].capacity) * 100;

            printf("\nBin ID: %d", bins[i].id);
            printf("\nArea: %s", bins[i].area);
            printf("\nCapacity: %.2f kg", bins[i].capacity);
            printf("\nCurrent Waste: %.2f kg", bins[i].filled);
            printf("\nFill Level: %.2f%%", percentage);

            if(percentage >= 80)
            {
                printf("\nStatus: FULL");
                printf("\nALERT: Waste collection required!");
            }
            else if(percentage >= 50)
            {
                printf("\nStatus: MEDIUM");
            }
            else
            {
                printf("\nStatus: LOW");
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("\nBin not found!");
    }
}


// Collect waste
void collectWaste()
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Bin ID for waste collection: ");
    scanf("%d", &id);

    for(i = 0; i < binCount; i++)
    {
        if(bins[i].id == id)
        {
            found = 1;

            printf("\nCollected %.2f kg waste from %s.",
                   bins[i].filled,
                   bins[i].area);

            bins[i].filled = 0;

            saveBins();

            printf("\nBin status updated to EMPTY.");
            break;
        }
    }

    if(found == 0)
    {
        printf("\nBin not found!");
    }
}


/*=================================================
              COMPLAINT FUNCTIONS
=================================================*/

// Add citizen complaint
void addComplaint()
{
    if(complaintCount >= MAX_COMPLAINTS)
    {
        printf("\nMaximum complaints reached!");
        return;
    }

    printf("\n\n========== ADD COMPLAINT ==========");

    complaints[complaintCount].id = complaintCount + 1;

    printf("\nEnter Citizen Name: ");
    scanf("%49s", complaints[complaintCount].name);

    printf("Enter Area/Ward: ");
    scanf("%49s", complaints[complaintCount].area);

    printf("Enter Complaint: ");
    scanf(" %[^\n]",
          complaints[complaintCount].description);

    complaintCount++;

    saveComplaints();

    printf("\nComplaint submitted successfully!");
}


// View complaints
void viewComplaints()
{
    int i;

    if(complaintCount == 0)
    {
        printf("\nNo complaints available.");
        return;
    }

    printf("\n\n=============== CITIZEN COMPLAINTS ===============");

    for(i = 0; i < complaintCount; i++)
    {
        printf("\n\nComplaint ID: %d",
               complaints[i].id);

        printf("\nCitizen: %s",
               complaints[i].name);

        printf("\nArea: %s",
               complaints[i].area);

        printf("\nComplaint: %s",
               complaints[i].description);
    }

    printf("\n===================================================");
}


/*=================================================
                REPORT FUNCTION
=================================================*/

// Generate report
void generateReport()
{
    int i;
    int full = 0;
    int medium = 0;
    int low = 0;

    float totalCapacity = 0;
    float totalWaste = 0;
    float percentage;

    if(binCount == 0)
    {
        printf("\nNo bin data available.");
        return;
    }

    for(i = 0; i < binCount; i++)
    {
        totalCapacity += bins[i].capacity;
        totalWaste += bins[i].filled;

        percentage =
            (bins[i].filled / bins[i].capacity) * 100;

        if(percentage >= 80)
        {
            full++;
        }
        else if(percentage >= 50)
        {
            medium++;
        }
        else
        {
            low++;
        }
    }

    printf("\n\n================ SYSTEM REPORT ================");

    printf("\nTotal Waste Bins      : %d", binCount);
    printf("\nFull Bins (80%%+)      : %d", full);
    printf("\nMedium Bins            : %d", medium);
    printf("\nLow Bins               : %d", low);

    printf("\nTotal Capacity         : %.2f kg",
           totalCapacity);

    printf("\nCurrent Waste          : %.2f kg",
           totalWaste);

    printf("\nTotal Complaints       : %d",
           complaintCount);

    if(totalCapacity > 0)
    {
        printf("\nOverall Fill Level     : %.2f%%",
               (totalWaste / totalCapacity) * 100);
    }

    printf("\n================================================");
}
