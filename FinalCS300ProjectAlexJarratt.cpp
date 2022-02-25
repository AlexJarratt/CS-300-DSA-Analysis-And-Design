/*
* Name: Final CS 300 Project
* Author: Alex Jarratt
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <search.h>
#include <algorithm>
using namespace std;

/*
 * It will iterate through all the lines in file and
 * call the given callback on each line.
 * This unfortunately does limit the manipulability of the print.
 */
bool iterateFile(string fileName, function<void(const string&)> callback)
{
    // Open the File
    ifstream in(fileName.c_str());
    // Check if object is valid
    if (!in)
    {
        cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }
    string str;
    // Read the next line from File untill it reaches the end.
    while (getline(in, str))
    {
        // Call the given callback
        callback(str);
    }
    //Close The File
    in.close();
    return true;
}
//Calls vector to swap values in it. Start refers to first value of vector, while end refers to last value of vector.
int partitionClass(vector<string>& vecOfStr, int start, int end) {
    //calling variables.
    int l = start;
    int h = end;

    //variable that determines a temp storage and manipulates index values to swap them
    int pivot = (start + (end - start) / 2);
    //Calling variable.
    bool finished = false;

    //while finished is not true
    while (!finished) {
        //while vecOfStr of start compares to the value of (vector of pivot) is less than 0
        while (vecOfStr[l].compare(vecOfStr[pivot]) < 0) {
            //grow l (start)
            ++l;
        }
        //while vecOfStr of pivot compares to the value of (vector of end) is less than 0
        while (vecOfStr[pivot].compare(vecOfStr[h]) < 0) {
            //shrink h (end)
            --h;
        }
        //if l(start) is greater than or equal to h(end). Start will start at 0, meaning this makes that l hit the midpoint with h.
        if (l >= h) {
            //End loop of while statements
            finished = true;
        }
        //Otherwise
        else
        {
            //Finally swaps the strings of vecOfStr of the l and h index values.
            swap(vecOfStr[l], vecOfStr[h]);
            //grows start and shrinks end
            ++l;
            --h;
        }
    }
    //return end value at final manipulation. This will be the smallest form of end.
    return h;
}
//The fast form of sorting vector values. Called Class.
void SortingClasses(vector<string>& vecOfStr, int start, int end) {
    //Calling variables. Only needed here.
    unsigned int mid = 0;
    //If start integer is greater than or equal to end integer
    if (start >= end) {
        //Final value
        return;
    }

    //Calling paritionClass to mid for recursive calling.
    mid = partitionClass(vecOfStr, start, end);

    //starts the sort of vector targetting the partitioned mid and the first value for the swap. Repeats based on partition call in mid
    SortingClasses(vecOfStr, start, mid);
    //starts the sort of vector targetting partitioned mid +1 and the final value for the swap. Repeats based upon partition call in mid
    SortingClasses(vecOfStr, mid + 1, end);
    
}

//generic function to search all types.
template < typename T>
//two types. bool for true/false on if value exists in vector, then string to print out the result of the search in the form of Class Id.
pair<bool, string > findInVector(const vector<T>& vecOfStr, const T& SpecificClass)
{
    //calling variable.
    pair<bool, string > result;
    // Find given element in vector. Element being whatever specificClass calls.
    auto it = find(vecOfStr.begin(), vecOfStr.end(), SpecificClass);
    //if iterator is not at the end of vecOfStr.
    if (it != vecOfStr.end())
    {
        //Index value of the item. In this case, there are no purely integer values, so this should give the class Id.
        result.second = distance(vecOfStr.begin(), it);
        //Boolean true/false for if value is in vector.
        result.first = true;
    }
    else
    {
        //Does not exist in vector.
        result.first = false;
        //Impossible Index value. Made a string as the class Id will be a string.
        result.second = " - 1";
    }
    //return the values.
    return result;
}

int main(int argc, char* argv[])
{
    //variable calling. res is called as a bool as iterateFile is a bool. iterateFile needed to be binary true/false for it to work well.
    string fileImport;
    bool res = true;
    //calling making keyboard commands
    switch (argc)
    {
        //This loads the file. The case 1 in the menu section tells what file to load.
    case 2:
       fileImport = argv[1];
        break;
    default:
        //Part of the sample output. Included once at program start.
        cout << "Thank you for using this program.";
        //Formatting
        cout << "\n" << endl;
        cout << "Welcome to the course planner." << endl;
    }

    //Vector called for storage of file.
    vector<string> vecOfStr;

    //Seems familiar. Does not do anything for 4-8 and 0, simply repeats the menu.
    int choice = 0;
    while (choice != 9) {
        //Formatting
        cout << "\n" << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;
        //Repeated prompt of user input
        cout << "What would you like to do? ";
        //Formatting
        cout << "\n" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            //Prompt Input from user
            cout << "Please Enter a File Name:\n";
            //Input to input variable
            cin >> fileImport;
            //Formatting
            cout << "\n";
            break;
        case 2:
            //Call given lambda function for each line in file
            cout << "Here is a sample schedule:\n" << endl;
            res = iterateFile(fileImport, [&](const string& str) //fileImport is the input variable now filled with the variable
                {
                    // Add to vector
                    vecOfStr.push_back(str);
                });
            //if res exists.
            if (res)
            {
                
                for (string& line : vecOfStr) {
                    //Sorts the entire vector for each line of the vector minus 1.
                    SortingClasses(vecOfStr, 0, vecOfStr.size() - 1);
                    //prints the vector lines.
                    cout << line << endl;
                }
                    
            }
            break;
        //Does not Work. Unfortunately.
        //Comments here are my thoughts on how it is supposed to run, but I lack the specific knowledge to actually make it work
        //I believed that referring back to the file is not correct for the purpose of the assignment,
            //even if that would be easier to implement.
        case 3:
            //variable for holding input
            string specificClass;
            //clarifiying response for input variable
            cout << "What course do you want to know more about?" << endl;
            //Makes the input go to the variable
            cin >> specificClass;
            //If specificClass is not empty/null
            if (specificClass != "") {
                //calls findInVector for the specificClass string of vecOfStr
                pair<bool, string> result = findInVector<string>(vecOfStr, specificClass);
                //if first result of findInVector exists and is valid
                if (result.first)
                    //print first result of findInVector
                    cout << result.first << endl;
                else
                    //Entire file does not possess the specificClass
                    cout << "Class does not exist" << endl;
            }
            break;
        }
    }
//I have included a copy of the ABCU text file in the source files. For reasons beyond me, the program works much better with
//a copy of the text file in the same location as the cpp file than not having it.
}