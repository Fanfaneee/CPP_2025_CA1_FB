#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct projectCrochet{
    int id;
    string name;
    string yarnType;
    float hookSize;
    string stitchType;
    float time;
    float price;
    string finalUse;
};




void parseLine(string line,projectCrochet &project)
{

    string temp;
    stringstream ss(line);
    getline(ss, temp,',');
    project.id=stoi(temp);
    getline(ss, project.name, ',');
    getline(ss, project.yarnType, ',');
    getline(ss, temp ,',');
    project.hookSize=stof(temp);
    getline(ss, project.stitchType, ',');
    getline(ss, temp ,',');
    project.time=stof(temp);
    getline(ss, temp ,',');
    project.price=stof(temp);
    getline(ss,project.finalUse, ',');


}




void load(string fname, vector<projectCrochet> &data)
{
    ifstream fin(fname);

    if(fin)
    {
        string line;
        while(getline(fin, line))
        {
            projectCrochet stud;
            parseLine(line, stud);
            data.push_back(stud);
        }
        fin.close();
    }
    else
    {
        cout << "Error opening file." <<endl;
    }
}



void display(const vector<projectCrochet> &projects) {
    cout << left
         << setw(5)  << "Id"
         << setw(30) << "Project Name"
         << setw(15) << "Yarn Type"
         << setw(10) << "Hook Size"
         << setw(20) << "Stitch Type"
         << setw(12) << "Time (hours)"
         << setw(10) << "Price"
         << setw(15) << "Final Use" << endl;


    for (const auto &project : projects) {
        cout << left
            << setw(5)  << project.id
              << setw(30) << project.name
              << setw(15) << project.yarnType
              << setw(10) << project.hookSize
              << setw(20) << project.stitchType
              << setw(12) << project.time
              << setw(10) << project.price
              << setw(15) << project.finalUse << endl;

    }
}

int findIndexOf(const vector<projectCrochet> &projects, string name) {
    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].name == name) {
            return i;
        }
    }
    return -1;

}


int main() {
    vector<projectCrochet> projects;
    string filename = "./cmake-build-debug/data.csv";
    load(filename,projects);
    display(projects);
    string nameSearch;
    cout<< "Entrez le nom du projet recherché :";
    getline(cin, nameSearch);
    int index = findIndexOf(projects, nameSearch);

    if (index != -1) {
        cout << "Projet trouvé :"<<endl;
        display({projects[index]});
    } else {
        cout << "Projet non trouvé."<<endl;
    }


    return 0;
}
