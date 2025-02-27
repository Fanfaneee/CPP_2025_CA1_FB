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
/*
question2 findIndexOf(vector, string)
This function take 2 parameters, a vector of projects and a name and will return the index of the project that match the name
*/
int findIndexOf(const vector<projectCrochet> &projects, string name) {
    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].name == name) {
            return i;
        }
    }
    return -1;

}
/*
question3  mapOfYarnType(vector)
This function take a parameter vector and will return a map of a string and integer this map associate all the possible yarn type and the number of project using each yarn type
*/
map<string, int> mapOfYarnType(vector<projectCrochet> &projects) {
    map<string, int> yarnType;
    vector<projectCrochet>::iterator iter = projects.begin();
    while (iter != projects.end()) {
        yarnType[iter->yarnType]++;

        iter++;
    }
    return yarnType;
}
/*
question4  filterByFinalUse
This function will return all the project by the final use that the user enter
*/

vector<projectCrochet> filterByFinalUse(const vector<projectCrochet> &projects, const string &category) {
    vector<projectCrochet> filteredProjects;

    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].finalUse == category) {
            filteredProjects.push_back(projects[i]);
        }
    }
    return filteredProjects;
}

/*
 this function will give the average time of all the project, the project that take the less of time and the project that take the most of time
 */
void analyzeTimeOfProjects(const vector<projectCrochet> &projects, int &avgTime, projectCrochet &minTimeProject, projectCrochet &maxTimeProject) {

    int totalTime = 0;
    minTimeProject = projects[0];
    maxTimeProject = projects[0];
    for (int i = 0; i < projects.size(); i++) {
        totalTime += projects[i].time;

        if (projects[i].time < minTimeProject.time) {
            minTimeProject = projects[i];
        }

        if (projects[i].time > maxTimeProject.time) {
            maxTimeProject = projects[i];
        }
    }
    avgTime = totalTime / projects.size();
}
/*
question6 matchName
this function will return the vector of projects that partially match the name the user enter
*/
vector<projectCrochet> matchName(vector<projectCrochet> &projects, string &stringToMatch) {
    vector<projectCrochet> matchingProject;
    for (size_t i = 0; i < projects.size(); i++) {
        if (projects[i].name.find(stringToMatch) != string::npos) {
            matchingProject.push_back(projects[i]);
        }
    }
    return matchingProject;
}

/*
question7 sortByPrice
this fonction will display the data sorted by descending price
*/

void sortByPriceDescending(vector<projectCrochet> &projects) {
    for (int i = 0; i < projects.size(); i++) {
        for (int j = i + 1; j < projects.size(); j++) {
            if (projects[i].price < projects[j].price) {
                swap(projects[i], projects[j]);
            }
        }
    }
    display(projects);
}

void question1(const vector<projectCrochet> &projects) {
    display(projects);
}

void question2(const vector<projectCrochet> &projects) {
    string nameSearch;
    cout << "Enter the exact name of the project you are searching for: ";
    getline(cin, nameSearch);

    int index = findIndexOf(projects, nameSearch);
    if (index != -1) {
        cout << "Project found:" << endl;
        display({projects[index]});
    } else {
        cout << "Project not found." << endl;
    }
}

void question3(vector<projectCrochet> &projects) {
    map<string, int> countYarnType = mapOfYarnType(projects);
    cout << "Number of projects by yarn type :" << endl;


    map<string, int>::iterator iter;
    for (iter = countYarnType.begin(); iter != countYarnType.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }
}


void question4(const vector<projectCrochet> &projects) {
    string categorySearch;
    cout << "Enter a final use (Blanket, Baby, Home Decor, Accessory, Kitchen): ";
    getline(cin, categorySearch);

    vector<projectCrochet> filteredProjects = filterByFinalUse(projects, categorySearch);
    if (!filteredProjects.empty()) {
        cout << "Projects matching the final use '" << categorySearch << "':" << endl;
        display(filteredProjects);
    } else {
        cout << "No project found for the final use '" << categorySearch << "'." << endl;
    }
}

void question5(const vector<projectCrochet> &projects) {
    int avgTime;
    projectCrochet minProject, maxProject;

    analyzeTimeOfProjects(projects, avgTime, minProject, maxProject);

    cout << "Average projects time: " << avgTime << " hours" << endl;
    cout << "Fastest project: " << minProject.name << " (" << minProject.time << " hours)" << endl;
    cout << "Longest project: " << maxProject.name << " (" << maxProject.time << " hours)" << endl;
}

void question6(vector<projectCrochet> &projects) {
    string stringToMatch;
    cout << "Enter the partial name of a project (Amigurumi, Crochet, Blanket...): ";
    getline(cin, stringToMatch);

    vector<projectCrochet> projectsMatchName = matchName(projects, stringToMatch);
    display(projectsMatchName);
}

void question7(vector<projectCrochet> &projects) {
    cout << "List of projects by descending price:" << endl;
    sortByPriceDescending(projects);
}


int main() {

    vector<projectCrochet> projects;
    string filename = "./cmake-build-debug/data.csv";
    load(filename,projects);

    int choice;

    do {
        cout << "******MENU******" << endl;
        cout << "1. Display all projects" << endl;
        cout << "2. Search for a project by exact name" << endl;
        cout << "3. Count projects by yarn type" << endl;
        cout << "4. Filter projects by final use" << endl;
        cout << "5. Analyze project times" << endl;
        cout << "6. Search for projects by partial name" << endl;
        cout << "7. Sort and display projects by descending price" << endl;
        cout << "-1. Quit" << endl;
        cout << "****************" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: question1(projects); break;
            case 2: question2(projects); break;
            case 3: question3(projects); break;
            case 4: question4(projects); break;
            case 5: question5(projects); break;
            case 6: question6(projects); break;
            case 7: question7(projects); break;
            case -1: cout << "Exiting program." << endl; break;
            default: cout << "Invalid option, try again." << endl;
        }

    } while (choice != -1);


// Question 1 display:
    /*
    display(projects);


//question 2 findIndexOf       search the exact name and return the project (fonction return int)
    string nameSearch;
    cout<< "Enter the exact name of the project that you search :";
    getline(cin, nameSearch);
    int index = findIndexOf(projects, nameSearch);

    if (index != -1) {
        cout << "Project found :"<<endl;
        display({projects[index]});
    } else {
        cout << "Project not found."<<endl;
    }

// Question 3 Which yarn


    map<string, int> countYarnType = mapOfYarnType(projects);
    cout << "Number of projects by yarn type :" << endl;


    map<string, int>::iterator iter;
    for (iter = countYarnType.begin(); iter != countYarnType.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }


//question4 Search final use
    string categorySearch;
    cout<< "Enter a final use (Blanket,Baby,Home Decor,Accessory,Kitchen) ";
    getline(cin, categorySearch);
    vector<projectCrochet> filteredProjects = filterByFinalUse(projects, categorySearch); //
    if (!filteredProjects.empty()) {
        cout << "Project matching the final use " << categorySearch << "' :" << endl;
        display(filteredProjects); //
    } else {
        cout << "Not project found for the final use " << categorySearch << "'." << endl;
    }


//question 5 time by project

    int avgTime;
    projectCrochet minProject, maxProject;

    analyzeTimeOfProjects(projects, avgTime, minProject, maxProject);

    cout << "Average project time : " << avgTime << " hours" << endl;
    cout << "Fastest project : " << minProject.name << " (" << minProject.time << " hours)" << endl;
    cout << "Longest project : " << maxProject.name << " (" << maxProject.time << " hours)" << endl;





//question6 search a project by name or partial name
    string stringToMatch;
    cout << "Enter the name or the partial name of a project : (Amigurumi, Crochet, Blanket...)";
    getline(cin, stringToMatch);
    vector<projectCrochet> projectsMatchName = matchName(projects, stringToMatch);
    display(projectsMatchName);


//question 7   List of project by descending price
    cout<<"List of project by descending price"<<endl;
    sortByPriceDescending(projects);

*/

    return 0;





}


