#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

struct projectCrochet{
    int id;
    string name;
    string yarnType;
    float hookSize;
    string stitchType;
    int time;
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

//question1 display
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

//question2 findIndexOf

int findIndexOf(const vector<projectCrochet> &projects, string name) {
    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].name == name) {
            return i;
        }
    }
    return -1;

}

//question3
map<string, int> mapOfYarnType(vector<projectCrochet> &projects) {
    map<string, int> yarnType;
    vector<projectCrochet>::iterator iter = projects.begin();
    while (iter != projects.end()) {
        yarnType[iter->yarnType]++;

        iter++;
    }
    return yarnType;
}

//question4  filterByFinalUse

vector<projectCrochet> filterByFinalUse(const vector<projectCrochet> &projects, const string &category) {
    vector<projectCrochet> filteredProjects;

    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].finalUse == category) {
            filteredProjects.push_back(projects[i]);
        }
    }
    return filteredProjects;
}

//question5
tuple<int, projectCrochet> analizeTimeOfProjects(vector<projectCrochet> &projects) {
    vector<projectCrochet> lessTimeProject;
    vector<projectCrochet> higherTimeProject;
    vector<projectCrochet>::iterator iter = projects.begin();
}

//question6 matchName

vector<projectCrochet> matchName(vector<projectCrochet> &projects, string stringToMatch) {
    vector<projectCrochet> matchingProject;
    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].name.find(stringToMatch) != string::npos) {
            matchingProject.push_back(projects[i]);
        }
    }
    return matchingProject;
}


//question7 sortByPrice
//fonction qui vas

int main() {
    vector<projectCrochet> projects;
    string filename = "./cmake-build-debug/data.csv";
    load(filename,projects);

// Question 1 display:

    display(projects);

//question 2 findIndexOf       search the exact name and return the project (fonction return int)
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

// Question 3 Which yarn


    map<string, int> countYarnType = mapOfYarnType(projects);
    cout << "Nombre de projets par type de fil :" << endl;


    map<string, int>::iterator iter;
    for (iter = countYarnType.begin(); iter != countYarnType.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }


//question4 Search final use
    string categorySearch;
    cout<< "Enter a catégory (Blanket) ";
    getline(cin, categorySearch);
    vector<projectCrochet> filteredProjects = filterByFinalUse(projects, categorySearch); //
    if (!filteredProjects.empty()) {
        cout << "Projets correspondant à la catégorie '" << categorySearch << "' :" << endl;
        display(filteredProjects); //
    } else {
        cout << "Aucun projet trouvé pour la catégorie '" << categorySearch << "'." << endl;
    }


//question 5





//question6 search a project by partial name
    string stringToMatch;
    cout << "Enter the name or the partial name of a project : (Amigurumi, Crochet, Blanket...)";
    getline(cin, stringToMatch);
    vector<projectCrochet> projectsMatchName = matchName(projects, stringToMatch);
    display(projectsMatchName);


    return 0;





}


