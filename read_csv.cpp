#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


void read_csv(string filename){


    string fname =  "../schedule/" + filename;

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file (fname, ios::in);
    if(file.is_open())
    {
        cout << "File " << filename << " is open" << endl;

        while(getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout<<"Could not open the file\n";
}