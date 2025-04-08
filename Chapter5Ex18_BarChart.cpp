/*
File Name: Chapter5Ex18_BarChart.cpp
Developer: Luke Pritchard
Date: 04/07/2025
Requirements:
- Read population data from People.txt (values only)
- Display bar chart with one asterisk per 1,000 people
- Use arrays to store years and population values
- Input validation for file and data
- Program should be modular and repeatable
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Function Prototypes
bool LoadPopulationData(const string& filename, const int years[], int populations[], int& count);
void DisplayChart(const int years[], const int populations[], int count);
bool AskToRepeat();

int main()
{
    const string filename = "People.txt";
    const int MAX_YEARS = 6;
    const int years[MAX_YEARS] = { 1900, 1920, 1940, 1960, 1980, 2000 };
    int populations[MAX_YEARS];
    int count;

    bool repeat = true;

    while (repeat)
    {
        if (LoadPopulationData(filename, years, populations, count))
        {
            DisplayChart(years, populations, count);
        }
        else
        {
            cout << "ERROR: Could not open People.txt or file contains invalid data.\n";
        }

        repeat = AskToRepeat();
    }

    cout << "Thank you for using the population chart program.\n";
    return 0;
}

/*
   LoadPopulationData
   Reads population values from the file into the populations array
   Matches them to the fixed years array
   Returns true if successful and valid, false otherwise
*/
bool LoadPopulationData(const string& filename, const int years[], int populations[], int& count)
{
    ifstream file(filename);
    count = 0;

    if (!file)
        return false;

    int value;
    while (file >> value && count < 6)
    {
        if (value < 0)
        {
            cout << "ERROR: Invalid population number in file.\n";
            return false;
        }

        populations[count] = value;
        count++;
    }

    file.close();

    return count == 6;
}

/*
   DisplayChart
   Prints the population chart with one * per 1,000 people
*/
void DisplayChart(const int years[], const int populations[], int count)
{
    cout << "\nPRAIRIEVILLE POPULATION GROWTH\n";
    cout << "(Each * represents 1,000 people)\n";

    for (int i = 0; i < count; i++)
    {
        cout << setw(6) << years[i] << " ";
        for (int j = 0; j < (populations[i] / 1000); j++)
            cout << "*";
        cout << endl;
    }
}

/*
   AskToRepeat
   Asks the user if they want to rerun the chart; validates input.
   Updated to properly clear the input buffer after multiple loops so buffer does not get misaligned after multiple runs.
*/
bool AskToRepeat()
{
    string input;
    char choice;

    while (true)
    {
        cout << "\nWould you like to run the program again? (Y/N): ";
        getline(cin, input);

        if (input.length() > 0)
        {
            choice = toupper(input[0]);
            if (choice == 'Y') return true;
            if (choice == 'N') return false;
        }

        cout << "ERROR: Please enter Y or N.\n";
    }
}
