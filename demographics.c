#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 2000
#define MAX_FIELD_LENGTH 100
#define MAX_FIELDS 52
#define DEFAULT_NUM_ENTRIES 4000
#define CNTY "County"
#define ST "State"
#define EDU_BACH "Education.Bachelor's Degree or Higher"
#define EDU_HS "Education.High School or Higher"
#define ETHN_AMER "Ethnicities.American Indian and Alaska Native Alone"
#define ETHN_ASN "Ethnicities.Asian Alone"
#define ETHN_BLK "Ethnicities.Black Alone"
#define ETHN_LAT "Ethnicities.Hispanic or Latino"
#define ETHN_PI "Ethnicities.Native Hawaiian and Other Pacific Islander Alone"
#define ETHN_TWO "Ethnicities.Two or More Races"
#define ETHN_WHT "Ethnicities.White Alone"
#define ETHN_WHT_NOT_LAT "Ethnicities.White Alone not Hispanic or Latino"
#define INC_MED_HOUS "Income.Median Household Income"
#define INC_PER_CAP "Income.Per Capita Income"
#define INC_BEL_POV "Income.Persons Below Poverty Level"
#define POP_2014 "Population.2014 Population"

// create county_data struct to store data for each county
struct county_data
{
    char county[50];     // County
    char state[20];      // State
    float education[2];  // education[0] = Bachelor's Degree or Higher, education[1] = High School or Higher
    float ethinicity[8]; // Array to hold each ethnicity field
    // ethinicity[0] = Ethnicities.American Indian and Alaska Native Alone
    // ethinicity[1] = Ethnicities.Asian Alone
    // ethinicity[2] = Ethnicities.Black Alone
    // ethinicity[3] = Ethnicities.Hispanic or Latino
    // ethinicity[4] = Ethnicities.Native Hawaiian and Other Pacific Islander Alone
    // ethinicity[5] = Ethnicities.Two or More Races
    // ethinicity[6] = Ethnicities.White Alone
    // ethinicity[7] = Ethnicities.White Alone not Hispanic or Latino
    int med_house_inc;     // Income.Median Household Income
    int per_cap_inc;       // Income.Per Capita Income
    float per_bel_poverty; // Income.Persons Below Poverty Level
    int population_2014;   // Population.2014 Population
};

// display relevant fields given an entry
void display(struct county_data entry)
{
    printf("====================================================\n");
    printf("County: %s\n", entry.county);
    printf("State: %s\n", entry.state);
    printf("Bachelor's Degree or Higher: %.2f\n", entry.education[0]);
    printf("High School or Higher: %.2f\n", entry.education[1]);
    printf("American Indian and Alaska Native Alone: %.2f\n", entry.ethinicity[0]);
    printf("Asian Alone: %.2f\n", entry.ethinicity[1]);
    printf("Black Alone: %.2f\n", entry.ethinicity[2]);
    printf("Hispanic or Latino: %.2f\n", entry.ethinicity[3]);
    printf("Native Hawaiian and Other Pacific Islander Alone: %.2f\n", entry.ethinicity[4]);
    printf("Two or More Races: %.2f\n", entry.ethinicity[5]);
    printf("White Alone: %.2f\n", entry.ethinicity[6]);
    printf("White Alone not Hispanic or Latino: %.2f\n", entry.ethinicity[7]);
    printf("Median Household Income: %d\n", entry.med_house_inc);
    printf("Per Capita Income: %d\n", entry.per_cap_inc);
    printf("Persons Below Poverty Level: %.2f\n", entry.per_bel_poverty);
    printf("2014 Population: %d\n", entry.population_2014);
    printf("====================================================\n");
}

// given a string, remove surrounding quote marks
void remove_quotes(char *str)
{
    memmove(str, str + 1, strlen(str)); // Shift left
    str[strlen(str) - 1] = '\0';        // Null-terminate
}

// given a string and str array, parse the string into the array
void parse(char *line, char *fields[MAX_FIELDS])
{
    int count = 0;
    char *token = strtok(line, ",");
    // read data into fields array
    while (token != NULL)
    {
        // remove quotes then add to fields
        remove_quotes(token);
        fields[count++] = token;

        token = strtok(NULL, ",");
    }
}

// read entries in csv file pointer and add to an array of county_data structs
void read_demo_file(FILE *fp, struct county_data *data_list)
{
    // read data from demographics file
    char header_buf[MAX_LINE_LENGTH];
    // read the header row, parse and add it to headers array
    char *headers[MAX_FIELDS];
    fgets(header_buf, sizeof(header_buf), fp);
    header_buf[strlen(header_buf) - 1] = '\0';
    parse(header_buf, headers);
    // read lines with data
    char buf[MAX_LINE_LENGTH];
    int count = 0; // line number = count + 2

    // read each line and parse
    while (fgets(buf, sizeof(buf), fp))
    {
        char *data_fields[MAX_FIELDS];
        // remove \n from the line
        buf[strlen(buf) - 1] = '\0';
        // parse data into the fields
        parse(buf, data_fields);
        struct county_data temp;
        int error_found = 0;
        // look for relevant fields
        for (int i = 0; i < MAX_FIELDS; i++)
        {
            if (strcmp(headers[i], CNTY) == 0)
            {
                if (data_fields[i] == NULL)
                {
                    error_found = 1;
                }
                strcpy(temp.county, data_fields[i]);
            }
            else if (strcmp(headers[i], ST) == 0)
            {
                if (data_fields[i] == NULL)
                {
                    error_found = 1;
                }
                strcpy(temp.state, data_fields[i]);
            }
            else if (strcmp(headers[i], EDU_BACH) == 0)
            {
                temp.education[0] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], EDU_HS) == 0)
            {
                temp.education[1] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_AMER) == 0)
            {
                temp.ethinicity[0] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_ASN) == 0)
            {
                temp.ethinicity[1] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_BLK) == 0)
            {
                temp.ethinicity[2] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_LAT) == 0)
            {
                temp.ethinicity[3] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_PI) == 0)
            {
                temp.ethinicity[4] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_TWO) == 0)
            {
                temp.ethinicity[5] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_WHT) == 0)
            {
                temp.ethinicity[6] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], ETHN_WHT_NOT_LAT) == 0)
            {
                temp.ethinicity[7] = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], INC_MED_HOUS) == 0)
            {
                temp.med_house_inc = atoi(data_fields[i]);
            }
            else if (strcmp(headers[i], INC_PER_CAP) == 0)
            {
                temp.per_cap_inc = atoi(data_fields[i]);
            }
            else if (strcmp(headers[i], INC_BEL_POV) == 0)
            {
                temp.per_bel_poverty = strtof(data_fields[i], NULL);
            }
            else if (strcmp(headers[i], POP_2014) == 0)
            {
                temp.population_2014 = atoi(data_fields[i]);
            }
            if (error_found == 1)
            {
                fprintf(stderr, "Found error on line %d, skipping", (count + 2));
                break;
            }
        }
        if (error_found == 1)
        {
            continue;
        }
        data_list[count++] = temp;
    }
    fprintf(stdout, "Loaded %d entries.\n", count);
}

void read_ops(FILE *fp, struct county_data *data_list, int list_length)
{
    // read the lines in ops file
    char read_buf[MAX_LINE_LENGTH];
    while (fgets(read_buf, sizeof(read_buf), fp))
    {
        // remove \n from buf
        read_buf[strlen(read_buf) - 1] = '\0';
        if (strcmp(read_buf, "population-total") == 0)
        {
            // from entries in data_list, add population to total
            int pop_tot = 0;
            for (int i = 0; i < list_length; i++)
            {
                pop_tot += data_list[i].population_2014;
            }
            fprintf(stdout, "2014 population: %d\n", pop_tot);
        }
        else if (strcmp(read_buf, "display") == 0)
        {
            // display each entry in data_list
            for (int i = 0; i < list_length; i++)
            {
                display(data_list[i]);
            }
        }
        else if (strstr(read_buf, "filter-state:"))
        {
            // save the state abbreviation to filter
            char *filterstate = (strstr(read_buf, "filter-state:") + 13);
            // create new array to hold the filtered entries
            struct county_data new_list[list_length];
            int counter = 0;
            for (int i = 0; i < list_length; i++)
            {
                // add new entries by filter
                if (strcmp(data_list[i].state, filterstate) == 0)
                {
                    new_list[i] = data_list[i];
                    counter++;
                }
            }
            // set data_list to new_list
            list_length = counter;
            data_list = new_list;
            printf("Filter: state == %s (%d entries)\n", filterstate, counter);
        }
    }
}

int main(int argc, char const *argv[])
{
    // if both demographics and operations files are not included, exit
    if (argc < 3)
    {
        printf("Not enough files included.");
        exit(EXIT_FAILURE);
    }
    // save names of the files provided
    char *demographics_file = argv[1];
    char *op_file = argv[2];

    // open both files for reading, check if they exist
    FILE *dm_fp = fopen(demographics_file, "r");
    if (dm_fp == NULL)
    {
        perror("Could not access Demographics file.");
        exit(EXIT_FAILURE);
    }
    FILE *op_fp = fopen(op_file, "r");
    if (op_fp == NULL)
    {
        perror("Could not access Operations file.");
        exit(EXIT_FAILURE);
    }

    // allocate memory for array of county_data structs
    struct county_data *data_list = (struct county_data *)malloc(DEFAULT_NUM_ENTRIES * sizeof(struct county_data));
    if (data_list == NULL)
    {
        printf("Memory not allocated.");
        exit(EXIT_FAILURE);
    }
    // load entries into program
    read_demo_file(dm_fp, data_list);
    // read and do operations
    read_ops(op_fp, data_list, DEFAULT_NUM_ENTRIES);
    // close files
    fclose(dm_fp);
    fclose(op_fp);
    // free memory
    free(data_list);
    exit(EXIT_SUCCESS);
    return 0;
}
