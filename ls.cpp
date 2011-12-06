/****************************
    Louis Fernandez
    Project for Living Social
    12/5/2011
****************************/

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

//Data storage
vector<string> name, item, merchant, address;
vector<int> num;
vector<double> price;
vector< vector<int> > data;

//Checks if an element is in the vector, if so return location, else add to vector and return location
template <class T>
int addToVector(vector<T>& vec, T input)
{   int i;
    for(i=0; i<vec.size(); ++i)
        if (vec[i] == input) return i;
    vec.push_back(input);
    return i;
}
//Finds if a value is in the vector and returns location, -1 on not found
template <class T>
int findValue(vector<T>& vec, T input)
{
    int i;
    for(i=0; i<vec.size(); ++i)
        if (vec[i] == input) return i;
    return -1;
}
//Finds first tab after start in input and returns the location
int breakPoint(string input, int start)
{
    int i;
    for(i=start;i<input.length();++i)
    {
        if (input[i] == '\t')
        {   break;
        }
    }
    return i;
}

//Enter the search loop
void search()
{
    while(1)
    {
        cout << "What would you like to search for? (h for help)" << endl;
        string input;
        cin >> input;

        if(input == "h")
        {   cout << "n for Purchaser Name\ni for Item Description\np for Item Price\nc for Purchase Count\na for Merchant Address\nm for Merchant Name\nq for quit\n";
            continue;
        } else if (input == "q")
        {   return;
        } else if (input != "n" && input != "i" && input!="p" && input!="c" && input!="a" && input!="m")//If not a valid choice
        {   cout << "Invalid Input" << endl;
            continue;
        }

        cout << "Input search value" << endl;
        string searchVal;
        cin.ignore(80, '\n');
        getline(cin, searchVal);

        //loc is the value of the second input in subtable
        //col is which value is being searched for
        int col = -1;
        int loc = -1;
        //Find loc and col
        if(input == "n")
        {   loc = findValue(name, searchVal);
            if(loc == -1)
            {   cout << "Purchaser Name not found" << endl;
                continue;
            }
            col = 0;
            cout << "For Purchaser Name " << searchVal << ":" << endl;
        } else if(input == "i")
        {   loc = findValue(item, searchVal);
            if(loc == -1)
            {   cout << "Item Description not found" << endl;
                continue;
            }
            col = 1;
            cout << "For Item Description " << searchVal << ":" << endl;
        } else if(input == "p")
        {   loc = findValue(price, atof(searchVal.c_str()));
            if(loc == -1)
            {   cout << "Item Price not found" << endl;
                continue;
            }
            col = 2;
            cout << "For Item Price " << searchVal << ":" << endl;
        } else if(input == "c")
        {   loc = findValue(num, atoi(searchVal.c_str()));
            if(loc == -1)
            {   cout << "Purchase Count not found" << endl;
                continue;
            }
            col = 3;
            cout << "For Purchase Count " << searchVal << ":" << endl;
        } else if(input == "a")
        {   loc = findValue(address, searchVal);
            if(loc == -1)
            {   cout << "Merchant Address not found" << endl;
                continue;
            }
            col = 4;
            cout << "Merchant Address " << searchVal << ":" << endl;
        } else if(input == "m")
        {   loc = findValue(merchant, searchVal);
            if(loc == -1)
            {   cout << "Merchant Name not found" << endl;
                continue;
            }
            col = 5;
            cout << "For Merchant Name " << searchVal << ":" << endl;
        }
        //Search for data in main table and print
        for(int i=0; i<data.size(); ++i)
        {
            if (data[i][col] == loc)
            {   cout << name[data[i][0]] << " " 
                     << item[data[i][1]] << " "
                     << price[data[i][2]] << " "
                     << num[data[i][3]] << " "
                     << address[data[i][4]] << " "
                     << merchant[data[i][5]] << endl;
            }
        }
        
    }
}

double newinput()
{
    //Read in file, check for validity
    string filename;
    cout << "Please input file name: " << endl;
    cin >> filename;
    double sum = 0;
    ifstream infile(filename.c_str());
    if(!infile.is_open())
    {   cout << "Invalid file name"<<endl;
        return 0;
    }
    //Read through whole document
    string line;
    getline (infile, line);
    while(infile.good())
    {   getline (infile, line);
        if(line.length() == 0)
        {   continue;
        }

        vector<int> newline;
        //Parse and add to vectors
        int start = 0;
        int end = breakPoint(line, start);
        string val = line.substr(start, end-start);
        newline.push_back(addToVector(name, val));

        start = end+1;
        end = breakPoint(line, start);
        val = line.substr(start, end-start);
        newline.push_back(addToVector(item, val));

        start = end+1;
        end = breakPoint(line, start);
        val = line.substr(start, end-start);
        newline.push_back(addToVector(price, atof(val.c_str())));
        double p = atof(val.c_str());

        start = end+1;
        end = breakPoint(line, start);
        val = line.substr(start, end-start);
        newline.push_back(addToVector(num, atoi(val.c_str())));    
        int n = atoi(val.c_str());

        start = end+1;
        end = breakPoint(line, start);
        val = line.substr(start, end-start);
        newline.push_back(addToVector(address, val));    

        start = end+1;
        end = breakPoint(line, start);
        val = line.substr(start, end-start);
        newline.push_back(addToVector(merchant, val));

        sum += p*n;
        data.push_back(newline);
    

    }
    cout << "Added Value: " << sum << endl;
    return sum;
    
}
int main()
{   double sum = 0;
    //Main Loop
    while(1)
    {   cout << "What would you like to do?(h for help)" << endl;
        string input;
        cin >> input;
        if (input == "h")
        {   cout << "s\tSearch\ni\tInput New Data\nq\tQuit\n";
        } else if (input == "s")
        {   search();
        } else if (input == "i")
        {   sum += newinput();
            cout << "Total sum: " << sum << endl;
        } else if (input == "q")
        {   cout << "Thanks!" << endl;
            return 0;
        } else
        {   cout << "Invalid input. h for help" << endl;
            continue;
        }   
    }
}
