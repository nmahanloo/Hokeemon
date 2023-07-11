// NimaMahanloo_Hokeemon.cpp
// HW6 Hokeemon - CISP 400
// FLC - Professor Fowler
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <string>
#include <iomanip>
using namespace std;
// An structure for each question in play mode
struct question
{
    string q = "??";
    string a1 = "??";
    string a2 = "??";
    string a3 = "??";
    string a4 = "??";
    int key = 0;
    question* next = nullptr;
    question* prev = nullptr;
    int qNum = 1;
};
// An structure for each food in feed mode
 struct food
 {
    string f = "??";
    food* next = nullptr;
    food* prev = nullptr;
    int fNum = 1;
 };
// Program base class
class Creature
{
    public:
        Creature(int monNum){initialCharacter(monNum);}
        Creature(int &hungerLevel, int &boredomLevel, string &ch, int monNum){setHokeemon(hungerLevel, boredomLevel, ch, monNum);}
        void setHokeemon(int&, int&, string&, int);
        virtual void initialCharacter(int &monNum)
        {
            qListSize = 1;
            fListSize = 1;
            questions = new question;
            foods = new food;
            first = questions;
            last = first;
            fFirst = foods;
            fLast = fFirst;
            identifier();
        }
        void identifier();
        void societyStatus(vector <Creature*>);
        void societyMenu(vector <Creature*>);
        int selectHokeemon(vector <Creature*>);
        int hokeemonMenu();
        void pushQList(string input)
        {
            if ((last->a4[0] != '?') && (last->a4[1] != '?'))
            {
                last->next = new question;
                last->next->qNum = last->qNum + 1;
                last = last->next;
                qListSize++;
            }
            if (input[input.size()-1] == '?')
            {
                last->q = input;
            }
            else if ((last->a1[0] == '?') && (last->a1[1] == '?'))
            {
                last->a1 = input;
                if (input[0] == '*')
                {
                    last->key = 1;
                }
            }
            else if ((last->a2[0] == '?') && (last->a2[1] == '?'))
            {
                last->a2 = input;
                if (input[0] == '*')
                {
                    last->key = 2;
                }
            }
            else if ((last->a3[0] == '?') && (last->a3[1] == '?'))
            {
                last->a3 = input;
                if (input[0] == '*')
                {
                    last->key = 3;
                }
            }
            else if ((last->a4[0] == '?') && (last->a4[1] == '?'))
            {
                last->a4 = input;
                if (input[0] == '*')
                {
                    last->key = 4;
                }
            }
        }
        void pushFList(string input)
        {
            if ((fLast->f[0] != '?') && (fLast->f[1] != '?'))
            {
                fLast->next = new food;
                fLast->next->fNum = fLast->fNum + 1;
                fLast = fLast->next;
                fListSize++;
            }
            fLast->f = input;
        }
        // Polymorphic function to load questions into linked list
        virtual void loadQuestions()
        {
            string input;
            ifstream readFile ("questions.txt");
            {
                if(readFile.is_open())
                {
                    while (!(readFile.eof()))
                    {
                        getline(readFile, input);
                        pushQList(input);
                    }
                }
                else
                {
                    cout << "Error: Can not open file!" << endl;
                }
            }
            readFile.close();
        }
        // Polymorphic function to load food list into linked list
        virtual void loadFoods()
        {
            string input;
            ifstream readFile ("foods.txt");
            {
                if(readFile.is_open())
                {
                    while (!(readFile.eof()))
                    {
                        getline(readFile, input);
                        pushFList(input);
                    }
                }
                else
                {
                    cout << "Error: Can not open file!" << endl;
                }
            }
            readFile.close();
        }
        void printQList()
        {
            question* curr = first;
            while (curr != nullptr)
            {
                cout << curr->q << endl << curr->a1 << endl << curr->a2 << endl << curr->a3 << endl << curr->a4 << endl << endl;
                curr = curr->next;
            }
        }
        void printFList()
        {
            food* curr = fFirst;
            while (curr != nullptr)
            {
                cout << curr->fNum << " : " << curr->f << endl;
                curr = curr->next;
            }
        }
        /// Feature 1 - Listen
        // A polymorphic function to display current Hokeemon status
        virtual void listen()
        {
            cout << setw(24) << left << "Hokeemon no. " << monNo << endl
            << setw(24) << left << "Hokeemon Character : " << character << endl
            << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
            << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
            if (hunger == 9)
            {
                cout << endl << "Hokeemon : I'm very hungry! please gimme some foods!" << endl;
            }
                else if (hunger < 9)
            {
                cout << "Hokeemon : Please make your decision?" << endl;
            }
            if (boredom >= 15)
            {
                cout << "I'm bored so much! I need to play with you please!" << endl << endl;
            }
            else if (boredom < 15)
            {
                cout << "I'm OK!" << endl << endl;
            }
        }
        /// Feature 2 - Play
        // A polymorphic function for play mode
        virtual void play()
        {
            question* curr;
            bool retry = true;
            bool correct = false;
            int i = 0, j = 0, r = 0;
            const int qSize = 4, aSize = 4;
            int selectedQuestion = -1, selectedAns = -1;
            int answer = 0;
            int point = 0;
            vector <int> que;
            vector <int> ans;
            char a = '?';
            cout << "Hokeemon : Please lets play together and answer my questions!" << endl << endl;
            while ((retry == true) && (i < qSize))
            {
                correct = false;
                if (ans.size() > 0)
                {
                    ans.clear();
                }
                curr = first;
                selectedQuestion = rand() %qListSize + 1;
                retry = false;
                while ((curr != nullptr) && (curr->qNum != selectedQuestion))
                {
                    curr = curr->next;
                }
                for (j = 0; j < que.size(); j++)
                {
                    if (que.at(j) == selectedQuestion)
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    i++;
                    que.push_back(selectedQuestion);
                    cout << i << " : " << curr->q << endl;
                    retry = true;
                    j = 0;
                    while ((retry == true) && (j < aSize))
                    {
                        selectedAns = rand() %aSize + 1;
                        retry = false;
                        for (r = 0; r < ans.size(); r++)
                        {
                            if (selectedAns == ans.at(r))
                            {
                                retry = true;
                            }
                        }
                        if (retry == false)
                        {
                            j++;
                            retry = true;
                            if (ans.size() == 0)
                            {
                                cout << " A) ";
                            }
                            else if (ans.size() == 1)
                            {
                                cout << " B) ";
                            }
                            else if (ans.size() == 2)
                            {
                                cout << " C) ";
                            }
                            else if (ans.size() == 3)
                            {
                                cout << " D) ";
                                retry = false;
                            }
                            else
                            {
                                cout << "vector ans error!" << endl;
                            }
                            ans.push_back(selectedAns);
                            if (selectedAns == 1)
                            {
                                if (curr->a1[0] == '*')
                                {
                                    cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                                }
                                else
                                {
                                    cout << curr->a1 << endl;
                                }
                            }
                            else if (selectedAns == 2)
                            {
                                if (curr->a2[0] == '*')
                                {
                                    cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                                }
                                else
                                {
                                    cout << curr->a2 << endl;
                                }
                            }
                            else if (selectedAns == 3)
                            {
                                if (curr->a3[0] == '*')
                                {
                                    cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                                }
                                else
                                {
                                    cout << curr->a3 << endl;
                                }
                            }
                            else if (selectedAns == 4)
                            {
                                if (curr->a4[0] == '*')
                                {
                                    cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                                }
                                else
                                {
                                    cout << curr->a4 << endl;
                                }
                            }
                        }
                    }
                    cout << "Please select answer > ";
                    a = '?';
                    while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
                    {
                        cin >> a;
                    }
                    if ((a == 'A') || (a == 'a'))
                    {
                        if (ans.at(0) == curr->key)
                        {
                            correct = true;
                            point++;
                        }
                    }
                    else if ((a == 'B') || (a == 'b'))
                    {
                        if (ans.at(1) == curr->key)
                        {
                            correct = true;
                            point++;
                        }
                    }
                    else if ((a == 'C') || (a == 'c'))
                    {
                        if (ans.at(2) == curr->key)
                        {
                            correct = true;
                            point++;
                        }
                    }
                    else if ((a == 'D') || (a == 'd'))
                    {
                        if (ans.at(3) == curr->key)
                        {
                            correct = true;
                            point++;
                        }
                    }
                    if (correct == false)
                    {
                        cout << "Incorrect!" << endl;
                    }
                    else
                    {
                        cout << "Correct!" << endl;
                    }
                    cout << endl;
                    retry = true;
                }
            }
            if (point == aSize)
            {
                boredom -= 4;
                cout << "Congratulation! You answered all as correct!" << endl
                << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
            }
            else
            {
                cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
            }
            PassTime();
            identifier();
        }
        /// Feature 3 - Feed
        // A polymorphic function to feed Hokeemon
        virtual void feed()
        {
            food* curr;
            int r, i, j = 0, current = -1;
            bool retry = true;
            const int fSize = 4, aSize = 4;
            int selectedFood = 0;
            vector <int> fShow;
            char foodNum = '?';
            cout << "Hokeemon : Please gimme some foods!" << endl << endl;
            for (i = 0; i < fSize; i++)
            {
                foodNum = '?';
                if (fShow.size() > 0)
                {
                    fShow.clear();
                }
                j = 0;
                retry = true;
                while ((retry == true) && (j < aSize))
                {
                    curr = fFirst;
                    selectedFood = rand() %fListSize + 1;
                    retry = false;
                    for (r = 0; r < fShow.size(); r++)
                    {
                        if (fShow.at(r) == selectedFood)
                        {
                            retry = true;
                        }
                    }
                    if (retry == false)
                    {
                        while ((selectedFood != curr->fNum) && (curr != nullptr))
                        {
                            curr = curr->next;
                        }
                        if (selectedFood == curr->fNum)
                        {
                            fShow.push_back(curr->fNum);
                            cout << j+1 << ": " << curr->f << " ";
                            if (fShow.size() < aSize)
                            {
                                retry = true;
                            }
                            j++;
                        }
                    }
                }
                cout << endl << "Please gimme one of them > ";
                while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
                {
                    cin >> foodNum;
                }
                curr = fFirst;
                current = (int(foodNum))-48-1;
                while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
                {
                    curr = curr->next;
                }
                if (curr != nullptr)
                {
                    cout << "Wow! I love " << curr->f << ", It is delicious, Thanks" << endl << endl;
                }
            }
            hunger -= 4;
            cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
            PassTime();
            identifier();
        }
        /// Specification 1 - PassTime
        // A function to increase current hokeemon humger anfd boredom level by one after each round
        void PassTime(){hunger++; boredom++; cout << "Hunger and Boredom levels increased by one cause time pass!" << endl << endl;}
    protected:
        int hunger;
        int boredom;
        int qListSize;
        int fListSize;
        int monNo;
        string mood;
        string hStatus;
        string character;
        string tell;
        question* questions;
        question* first;
        question* last;
        food* foods;
        food* fFirst;
        food* fLast;
};
// A function to identify hunger and boredom levels useful for display them to user in more friendly style
void Creature::identifier()
{
    if (hunger == 0)
    {
        hStatus = "Full";
    }
    else if (hunger == 1)
    {
        hStatus = "10%";
    }
    else if (hunger == 2)
    {
        hStatus = "20%";
    }
    else if (hunger == 3)
    {
        hStatus = "30%";
    }
    else if (hunger == 4)
    {
        hStatus = "40%";
    }
    else if (hunger == 5)
    {
        hStatus = "50%";
    }
    else if (hunger == 6)
    {
        hStatus = "60%";
    }
    else if (hunger == 7)
    {
        hStatus = "70%";
    }
    else if (hunger == 8)
    {
        hStatus = "80%";
    }
    else if (hunger == 9)
    {
        hStatus = "90%";
    }
    else if (hunger == 10)
    {
        hStatus = "Starvation";
    }
    if ((boredom > -1) && (boredom < 5))
        mood = "Happy";
    else if ((boredom > 4) && (boredom < 10))
        mood = "OK";
    else if ((boredom > 9) && (boredom < 15))
        mood = "Frustrated";
    else if (boredom > 14)
        mood = "Mad";
}
// Initialize the class members
void Creature::setHokeemon(int &hungerLevel, int &boredomLevel, string &ch, int monNum)
{
        hunger = hungerLevel;
        boredom = boredomLevel;
        character = ch;
        monNo = monNum;
        qListSize = 1;
        fListSize = 1;
        questions = new question;
        foods = new food;
        first = questions;
        last = first;
        fFirst = foods;
        fLast = fFirst;
        identifier();
}
/// specification 4 - Display died and alive hokeemons
// Display more information and statics about hokeemons to user
void Creature::societyStatus(vector <Creature*> Hokeemon)
    {
        int normalAnimals = 0, angryAnimals = 0, coolAnimals = 0, greedyAnimals = 0, depressAnimals = 0;
        int impoliteAnimals = 0, shyAnimals = 0, letteredAnimals = 0;
        int died = 0;
        int total = 0;
        int num;
        cout << "Hokeemons in Mad level : ";
        for (num = 0; num < Hokeemon.size(); num++)
        {
            if (Hokeemon[num]->character == "Normal")
            {
                normalAnimals++;
            }
            else if (Hokeemon[num]->character == "Angry")
            {
                angryAnimals++;
            }
            else if (Hokeemon[num]->character == "Cool")
            {
                coolAnimals++;
            }
            else if (Hokeemon[num]->character == "Greedy")
            {
                greedyAnimals++;
            }
            else if (Hokeemon[num]->character == "Depressive")
            {
                depressAnimals++;
            }
            else if (Hokeemon[num]->character == "Impolite")
            {
                impoliteAnimals++;
            }
            else if (Hokeemon[num]->character == "Shy")
            {
                shyAnimals++;
            }
            else if (Hokeemon[num]->character == "Lettered")
            {
                letteredAnimals++;
            }
            if (Hokeemon[num]->hunger == 10)
            {
                died++;
            }
        }
    total = Hokeemon.size() - died;
    cout << endl
    << setw(40) << left << "Normal characters : " << normalAnimals << endl
    << setw(40) << left << "Total Angry characters : " << angryAnimals << endl
    << setw(40) << left << "Total cool characters : " << coolAnimals << endl
    << setw(40) << left << "Total greedy characters : " << greedyAnimals << endl
    << setw(40) << left <<"Total depressive characters : " << depressAnimals << endl
    << setw(40) << left << "Total impolite characters : " << impoliteAnimals << endl
    << setw(40) << left << "Total shy characters : " << shyAnimals << endl
    << setw(40) << left << "Total lettered characters : " << letteredAnimals << endl
    << setw(40) << left << "Total died : " << died << endl
    << setw(40) << left << "Total alive Hokeemons : " << total << endl << endl;
}
// Calculate some necessary information about hokeemons for Main Menu
void Creature::societyMenu(vector <Creature*> Hokeemon)
{
    int n;
    const int societySize = Hokeemon.size();
    vector <int> hunger90;
    vector <int> hunger80;
    vector <int> hunger70;
    vector <int> hunger60;
    vector <int> hunger50;
    vector <int> hunger40;
    vector <int> hunger30;
    vector <int> hunger20;
    vector <int> hunger10;
    vector <int> hunger00;
    vector <int> boreHap;
    vector <int> boreOkk;
    vector <int> boreFru;
    vector <int> boreMad;
    for (n = 0; n < Hokeemon.size(); n++)
    {
        if (Hokeemon.at(n)->hunger == 0)
        {
            hunger00.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 1)
        {
            hunger10.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 2)
        {
            hunger20.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 3)
        {
            hunger30.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 4)
        {
            hunger40.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 5)
        {
            hunger50.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 6)
        {
            hunger60.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 7)
        {
            hunger70.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 8)
        {
            hunger80.push_back(n);
        }
        else if (Hokeemon.at(n)->hunger == 9)
        {
            hunger90.push_back(n);
        }
        if (Hokeemon.at(n)->mood == "Happy")
        {
            boreHap.push_back(n);
        }
        else if (Hokeemon.at(n)->mood == "OK")
        {
            boreOkk.push_back(n);
        }
        else if (Hokeemon.at(n)->mood == "Frustrated")
        {
            boreFru.push_back(n);
        }
        else if (Hokeemon.at(n)->mood == "Mad")
        {
            boreMad.push_back(n);
        }
    }
    cout << "Hokeemons Status > " << endl << endl;
    cout << setw(27) << left << "Hunger 90% (Danger zone) : ";
    if (hunger90.size() > 0)
    {
        for (n = 0; n < hunger90.size(); n++)
        {
            cout << hunger90.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger90.size() << endl << setw(27) << left << "Hunger 80% : ";
    if (hunger80.size() > 0)
    {
        for (n = 0; n < hunger80.size(); n++)
        {
            cout << hunger80.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger80.size() << endl << setw(27) << left << "Hunger 70% : ";
    if (hunger70.size() > 0)
    {
        for (n = 0; n < hunger70.size(); n++)
        {
            cout << hunger70.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger70.size() << endl << setw(27) << left << "Hunger 60% : ";
    if (hunger60.size() > 0)
    {
        for (n = 0; n < hunger60.size(); n++)
        {
            cout << hunger60.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger60.size() << endl << setw(27) << left << "Hunger 50% : ";
    if (hunger50.size() > 0)
    {
        for (n = 0; n < hunger50.size(); n++)
        {
            cout << hunger50.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger50.size() << endl << setw(27) << left << "Hunger 40% : ";
    if (hunger40.size() > 0)
    {
        for (n = 0; n < hunger40.size(); n++)
        {
            cout << hunger40.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger40.size() << endl << setw(27) << left << "Hunger 30% : ";
    if (hunger30.size() > 0)
    {
        for (n = 0; n < hunger30.size(); n++)
        {
            cout << hunger30.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger30.size() << endl << setw(27) << left << "Hunger 20% : ";
    if (hunger20.size() > 0)
    {
        for (n = 0; n < hunger20.size(); n++)
        {
            cout << hunger20.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger20.size() << endl << setw(27) << left << "Hunger 10% : ";
    if (hunger10.size() > 0)
    {
        for (n = 0; n < hunger10.size(); n++)
        {
            cout << hunger10.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger10.size() << endl << setw(27) << left << "No Hunger (Perfect) : ";
    if (hunger00.size() > 0)
    {
        for (n = 0; n < hunger00.size(); n++)
        {
            cout << hunger00.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << hunger00.size() << endl << endl << setw(27) << left << "Mad (Danger) : ";
    if (boreMad.size() > 0)
    {
        for (n = 0; n < boreMad.size(); n++)
        {
            cout << boreMad.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << boreMad.size() << endl << setw(27) << left << "Frusted : ";
    if (boreFru.size() > 0)
    {
        for (n = 0; n < boreFru.size(); n++)
        {
            cout << boreFru.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << boreFru.size() << endl << setw(27) << left << "OK : ";
    if (boreOkk.size() > 0)
    {
        for (n = 0; n < boreOkk.size(); n++)
        {
            cout << boreOkk.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << boreOkk.size()  << endl << setw(27) << left << "Happy : ";
    if (boreHap.size() > 0)
    {
        for (n = 0; n < boreHap.size(); n++)
        {
            cout << boreHap.at(n) + 1 << " ";
        }
    }
    else
    {
        cout << "N/A";
    }
    cout << setw(3) << " ";
    cout << "\t\tTotal : " << boreHap.size()  << endl << endl;
}
/// Program main greeting - Main Menu
// Display some necessary live information about alive hokeemons to user and get user choice in
int Creature::selectHokeemon(vector <Creature*> Hokeemon)
{
    bool errorFlag = false;
    char* hokeemonNum = (char*)malloc(sizeof(char));
    hokeemonNum[0] = '\0';
    int rate, index, i;
    int hokeeNum = 0;
    while ((hokeemonNum[0] == '\0') || (errorFlag == true))
    {
        cout << "For more details please press <D>" << endl
        << "To quit please press <Q>" << endl
        << "To continue with a hokeemon please enter it's number" << endl << "> ";
        cin >> hokeemonNum;
        if (((hokeemonNum[0] == 'D') && (hokeemonNum[1] == '\0')) || ((hokeemonNum[0] == 'd') && (hokeemonNum[1] == '\0')))
        {
            societyStatus(Hokeemon);
            hokeemonNum[0] = '\0';
        }
        else if (((hokeemonNum[0] == 'Q') && (hokeemonNum[1] == '\0')) || ((hokeemonNum[0] == 'q') && (hokeemonNum[1] == '\0')))
        {
            hokeeNum = -1;
            hokeemonNum = "Quit";
        }
        else
        {
            rate = 1;
            for (index = 0; hokeemonNum[index] != '\0'; index++)
            {
                if (!(isdigit(hokeemonNum[index])))
                {
                    errorFlag = true;
                }
                if (index > 0)
                {
                    rate *= 10;
                }
            }
        }
    }
    if (hokeeNum != -1)
    {
        for (i = 0; i < index; i++)
        {
            hokeeNum += rate * (int(hokeemonNum[i])-48);
            rate /= 10;
        }
    }
    cout << endl;
    return hokeeNum;
}
/// Specification 2 - Select Menu for Listen, Play, Feed or quit
/// Specification 4 and 5 - Die for hunger level 10 and unresponsive mood for boredom level 20
int Creature::hokeemonMenu()
{
    char userChoice = '?';
    int choice = 0;
    if (hunger >= 10)
    {
        cout << "Not accessible: This Hokeemon died cause starvation because your fault!" << endl << endl;
        choice = 4;
    }
    else if (boredom >= 20)
    {
        cout << "Not accessible: This Hokeemon is unresponsive cause your fault!" << endl << endl;
    }
    else
    {
        cout << "1 - Listen" << endl << "2 - Play" << endl << "3 - feed" << endl
        << "4 - Previous Menu" << endl << "Q - quit" << endl << "> ";
        while ((userChoice != '1') && (userChoice != '2') && (userChoice != '3') && (userChoice != '4') && (userChoice != 'q') && (userChoice != 'Q'))
        {
            cin >> userChoice;
        }
        cout << endl;
        if ((userChoice == 'q') || (userChoice == 'Q'))
        {
            choice = -1;
        }
        else
        {
            choice = int(userChoice)-48;
        }
    }
    return choice;
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : normal character
class normalHokeemon : public Creature
{
    public:
        normalHokeemon(int monNum) : Creature (monNum) {initialCharacter(monNum);}
        normalHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        /*void listen();
        void play();
        void feed();*/
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void normalHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %10;
    boredom = rand() %10;
    character = "Normal";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question sets for normal character
void normalHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "What is my family name?";
    last->a1 = "Mon"; last->a2 = "Hokee"; last->a3 = "Hokeemon"; last->a4 = "*None";
    last->key = 4;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "How is my look like?";
    last->a1 = "*Beautiful"; last->a2 = "Nice"; last->a3 = "Cool"; last->a4 = "Ugly";
    last->key = 1;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "How old is me?";
    last->a1 = "Higher than hundred"; last->a2 = "Higher than twenty"; last->a3 = "*Less than a day"; last->a4 = "None";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Guess that what is my skin color?";
    last->a1 = "*Green"; last->a2 = "Blue"; last->a3 = "Red"; last->a4 = "Pink";
    last->key = 1;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Who are you?";
    last->a1 = "*One of them" ; last->a2 = "A gal"; last->a3 = "A child"; last->a4 = "A guy";
    last->key = 1;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for normal character
void normalHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Popcorn";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Banana";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Pretzel";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Nuts";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Chips";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : angry character
class angryHokeemon : public Creature
{
    public:
        angryHokeemon (int monNum) : Creature (monNum) {initialCharacter(monNum);}
        angryHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void angryHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %10;
    boredom = 15;
    character = "Angry";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// load question set for angry character
void angryHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "What are you doing now?";
    last->a1 = "*I want to play with you"; last->a2 = "I want to suffer you"; last->a3 = "I'm wasting your time"; last->a4 = "I want to make you busy";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "Am i a stupid creature?";
    last->a1 = "Yes, Exactly!"; last->a2 = "*No, You are smart"; last->a3 = "You are just an animal"; last->a4 = "You are angry now!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "May i bit you?";
    last->a1 = "Shut up ugly!"; last->a2 = "No, If you do that then yo will be dead!"; last->a3 = "*No please, just be relax and have a long breath!"; last->a4 = "Yes";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Am i right?";
    last->a1 = "I don't know"; last->a2 = "Yes"; last->a3 = "No"; last->a4 = "*For what?";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Am i crazy?";
    last->a1 = "Yes" ; last->a2 = "A little bit"; last->a3 = "*No, just you are upset right now"; last->a4 = "None";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// load food set for angry character
void angryHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Cold water";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Gum";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Honey";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Jerky";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Cookie";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode - for angry character
void angryHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : Hey! I'm very hungry! Shame on you!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : Hey! What do you can to do?!" << endl;
    }
    if (boredom >= 15)
    {
        cout << "You frustrated and bored me as too much! I gonna to kill you!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "Always you are a looser!" << endl << endl;
    }
}
// Play mode - for angry character
void angryHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : Hey! Lets play! You are a looser!" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode - for angry character
void angryHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Gimme my foods right now!" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "Still I'm waiting! Come on! Gimme that! > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << curr->f << " is not bad!" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : cool character
class coolHokeemon : public Creature
{
    public:
        coolHokeemon (int monNum) : Creature (monNum) {initialCharacter(monNum);}
        coolHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void coolHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %10;
    boredom = rand() %5;
    character = "Cool";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// load question set for cool character
void coolHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "How are you today?";
    last->a1 = "*Thanks, Fine!"; last->a2 = "Angry"; last->a3 = "So what?!"; last->a4 = "Be silent petty!";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "You have very nice look like?";
    last->a1 = "Yes, Exactly!"; last->a2 = "*Thanks"; last->a3 = "So what?!"; last->a4 = "Shut up!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "May i have you as my friend?";
    last->a1 = "Shut up ugly!"; last->a2 = "No"; last->a3 = "*Yes, It's my pleasure!"; last->a4 = "Of course not!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Lets play more together in feature?";
    last->a1 = "No"; last->a2 = "I'm not animal like you"; last->a3 = "Never"; last->a4 = "*Sure";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Are you like soccer?";
    last->a1 = "No" ; last->a2 = "I hate that!"; last->a3 = "*Yes, That's a Popular sport"; last->a4 = "It's not your business";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// load food set for coll character
void coolHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Pepsi";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Pizza";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Subway";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Nuts";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Banana";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for cool character
void coolHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : Hi! How are you today? May i have some foods?" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : Be relax! Don't be rush for your decision?" << endl;
    }
    if (boredom >= 15)
    {
        cout << "I need to have enjoying time with you!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "Always you are cool!" << endl << endl;
    }
}
// Play mode for cool character
void coolHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : Hey! Lets play and have fun together!" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for cool character
void coolHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Hey! Please gimme some foods please" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "Please gimme one of them > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "I love " << curr->f << "! It was So delicious! Thanks" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : greedy character
class greedyHokeemon : public Creature
{
    public:
        greedyHokeemon (int monNum) : Creature (monNum) {initialCharacter(monNum);}
        greedyHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void greedyHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %3 + 7;
    boredom = rand() %10 + 5;
    character = "Greedy";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question set for greedy character
void greedyHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "May i eat for entire of day?";
    last->a1 = "*Yes, but that is not good for your health!"; last->a2 = "No, you can't chobby!"; last->a3 = "No, You must make me just happy pet!"; last->a4 = "Sad, I have not extra money to give you eat monkey!";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "May i go and sleep?";
    last->a1 = "Yes, That's better useless!"; last->a2 = "*Sure but i will be more happy if talk with me a little bit before that"; last->a3 = "No, You are my animal so just play"; last->a4 = "Nope, I should teach you more morality!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I need to your all foods?";
    last->a1 = "Shut the f*** up!"; last->a2 = "What did you say sh**?!"; last->a3 = "*You are free to eat but for one person volume!"; last->a4 = "Noisy animal!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Do you like to eat cakes and cookies!?";
    last->a1 = "Nope"; last->a2 = "Not your business!"; last->a3 = "What?!!!"; last->a4 = "*Sure but a little bit weekly";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Am i fat?";
    last->a1 = "Yes like peace of sh**!" ; last->a2 = "Ugly and nasty!"; last->a3 = "*No, You are beautiful but you need to have better diet and exercises to be healthy"; last->a4 = "Yeah! So what?!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for greedy character
void greedyHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Cookie";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Cake";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Popcorn";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Chips";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Chocolate";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for greedy character
void greedyHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << "Hokeemon : Hey! I'm very very hungry! Gimme a lot foods! I want all of them!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : Do you want to gimme more foods?" << endl;
    }
    if (boredom >= 15)
    {
        cout << "Hey! I need to play a lot with you!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "Always play with just me!" << endl << endl;
    }
}
// Play mode for greedy character
void greedyHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : Lets play a lot together forever" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for greedy character
void greedyHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Gimme a lot foods faster" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "gimme more faster > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "I want more and more " << curr->f << "!" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : depressive character
class depressHokeemon : public Creature
{
    public:
        depressHokeemon (int monNum) : Creature (monNum) {initialCharacter(monNum);}
        depressHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void depressHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %4;
    boredom = rand() %5 + 10;
    character = "Depressive";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question set for depressive character
void depressHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "I'm very sad!?";
    last->a1 = "*I understand you"; last->a2 = "So what?! Just play!"; last->a3 = "Shut up and play!"; last->a4 = "Sad?! You are just an animal!";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "May i cry?";
    last->a1 = "Yes, you can cry but after your dead!"; last->a2 = "*Sure but may i help you and make you happy?"; last->a3 = "No, Shut up and just play"; last->a4 = "No never!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I feel nobody like me!?";
    last->a1 = "Exactly, Who like an ugly creature?!"; last->a2 = "Just be silent and die!"; last->a3 = "*No, I like you"; last->a4 = "Just play!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I want to die!?";
    last->a1 = "I understand"; last->a2 = "Perfect so i can help you for that!"; last->a3 = "Shut up and just play useless!"; last->a4 = "*Don't, Life is beautiful but you are just upset right now";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Am i ugly?";
    last->a1 = "Yes, like peace of sh**!" ; last->a2 = "Ugly and nasty!"; last->a3 = "*No, You are beautiful!"; last->a4 = "Yeah! So what?!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for depressive character
void depressHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Chocolate";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Honey";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Cookie";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Sugar";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Candy";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for depressive character
void depressHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : I'm very hungry but i want to be died!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : I have no appetite Make your choice!" << endl;
    }
    if (boredom >= 15)
    {
        cout << "I'm very boring but doesn't matter!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "I just want to sleep!" << endl << endl;
    }
}
// Play mode for depressive character
void depressHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : I'm not happy but play!" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for depressive character
void depressHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Do you want to gimme foods?!" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "I have no appetites > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "No need more!" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : impolite character
class impoliteHokeemon : public Creature
{
    public:
        impoliteHokeemon (int monNum) : Creature (monNum) {initialCharacter(monNum);}
        impoliteHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void impoliteHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %2 + 7;
    boredom = rand() %15 + 1;
    character = "Impolite";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question set for impolite character
void impoliteHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "I'm going to kill you!?";
    last->a1 = "You can't!"; last->a2 = "I should kill you right now before!"; last->a3 = "Shut up and play!"; last->a4 = "*Be nice please!";
    last->key = 4;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "Who the hell are you sh**?";
    last->a1 = "I'm your punisher!"; last->a2 = "*I'm your friend! Please be nice!"; last->a3 = "What the f***?!"; last->a4 = "I kill you right now sh**!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Why you are ugly like a sh**!?";
    last->a1 = "Exactly, I'm very ugly!"; last->a2 = "Just be silent and die!"; last->a3 = "*No, I'm not! Be nice please!"; last->a4 = "F*** you monkey!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I want to f*** you right now!?";
    last->a1 = "I understand"; last->a2 = "Shut up! I f*** you before right now!"; last->a3 = "Shut the f*** up useless animal!"; last->a4 = "*Be nice! You can't!";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I see you in the hell!?";
    last->a1 = "No, i will kill you before!" ; last->a2 = "You are already dead and will be in the hell!"; last->a3 = "*Be nice! I hope not!"; last->a4 = "Yes! So f***ing what?!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for impolite character
void impoliteHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Vodka";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Blood";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Cigar";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Drug";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Pepper";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for impolite character
void impoliteHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : Hey! I'm very very hungry rascal! Gimme my foods or i drop some s*** oh your head?!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : What you want to do about my foods stupid?!" << endl;
    }
    if (boredom >= 15)
    {
        cout << "I'm a lot bored rascal!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "Always i f*** you!" << endl << endl;
    }
}
// Play mode for impolite character
void impoliteHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : Hey looser! Are you ready to be fu***d?" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for impolite character
void impoliteHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Gimme my foods faster a**h***!" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "Gimme that faster s*** > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "Tast of " << curr->f << " was like a s***! So f***ing what now?!" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : shy character
class shyHokeemon : public Creature
{
    public:
        shyHokeemon(int monNum) : Creature (monNum) {initialCharacter(monNum);}
        shyHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void shyHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %10;
    boredom = rand() %5 + 11;
    character = "Shy";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question set for shy character
void shyHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "May i be silent?";
    last->a1 = "*Yes but I want to play and enjoy with you"; last->a2 = "No, you can't!"; last->a3 = "No, You must make me happy pet!"; last->a4 = "Sad, You should be funny for me monkey!";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "May i go and sleep?";
    last->a1 = "Yes, That's better ugly!"; last->a2 = "*Sure but i will be more happy if talk with me a little bit before that"; last->a3 = "No, You are my animal so just play"; last->a4 = "Nope, I should teach you more morality!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "......mmmm.....!?";
    last->a1 = "Shut the f*** up!"; last->a2 = "What did you say shit?!"; last->a3 = "*You are very beautiful! What is your name?"; last->a4 = "Noisy animal!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "I like always to play with just myself!?";
    last->a1 = "I understand"; last->a2 = "You can not do that anymore!"; last->a3 = "What?!!!"; last->a4 = "*Sure but it will be my pleasure if play with me a little bit";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Am i ugly?";
    last->a1 = "Yes like peace of sh**!" ; last->a2 = "Ugly and nasty!"; last->a3 = "*No, You are beautiful!"; last->a4 = "Yeah! So what?!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for shy character
void shyHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Pepsi";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Chips";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Popcorn";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Cookie";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Chocolate";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for shy character
void shyHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : I'm very hungry please!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : ...I'm shying... !" << endl;
    }
    if (boredom >= 15)
    {
        cout << "I need to play please!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "I need to be hide!" << endl << endl;
    }
}
// Play mode for shy character
void shyHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : lets play please" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for shy character
void shyHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : Gimme my foods please" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "More foods please > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "Thanks!" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
/// Specifications 6 and 7 - Abstract child class
/// Feature 4 - Hokeemon different characters : lettered character
class letteredHokeemon : public Creature
{
    public:
        letteredHokeemon(int monNum) : Creature (monNum) {initialCharacter(monNum);}
        letteredHokeemon(int hungerLevel, int boredomLevel, string ch, int monNum) : Creature(hungerLevel, boredomLevel, ch, monNum){}
        void initialCharacter(int);
        void loadQuestions();
        void loadFoods();
        void listen();
        void play();
        void feed();
    private:
};
/// Specification 3 - Hunger and Boredom Levels Random initializing
// Initializing
void letteredHokeemon::initialCharacter(int monNum)
{
    hunger = rand() %10;
    boredom = rand() %15;
    character = "Lettered";
    monNo = monNum;
    qListSize = 1;
    fListSize = 1;
    questions = new question;
    foods = new food;
    first = questions;
    last = first;
    fFirst = foods;
    fLast = fFirst;
    identifier();
    loadQuestions();
    loadFoods();
}
// Load question set for lettered character
void letteredHokeemon::loadQuestions()
{
    int i = 1;
    last->q = "What is the corporation in the US?";
    last->a1 = "*Political power"; last->a2 = "I don't know!"; last->a3 = "A lot company available as corporation in US!"; last->a4 = "Do not ask again!";
    last->key = 1;
    last->qNum = 1;
    last->next = new question;
    last = last->next;
    last->q = "Who was the John Luck?";
    last->a1 = "My boy friend!"; last->a2 = "*Political Scientist"; last->a3 = "I don't know!"; last->a4 = "Your grandpa!";
    last->key = 2;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "What is Freemasonry?";
    last->a1 = "Just a community!"; last->a2 = "I don't know!"; last->a3 = "*British lead secret society"; last->a4 = "Not important!";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "Why world war II happened!?";
    last->a1 = "Cause Hitler and natzies!"; last->a2 = "I don't know!"; last->a3 = "For racism!"; last->a4 = "*Because Hitler was not agreed with current political power as cartel in the world";
    last->key = 4;
    last->qNum = ++i;
    qListSize++;
    last->next = new question;
    last = last->next;
    last->q = "As historical evidences who is the real pure Aryan race people?";
    last->a1 = "American" ; last->a2 = "European"; last->a3 = "*Iranian"; last->a4 = "Indian";
    last->key = 3;
    last->qNum = ++i;
    qListSize++;
}
// Load food set for lettered character
void letteredHokeemon::loadFoods()
{
    int i = 1;
    fLast->f = "Banana";
    fLast->fNum = i;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Nuts";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Honey";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Apple";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
    fLast->f = "Water";
    fLast->fNum = ++i;
    fListSize++;
    fLast->next = new food;
    fLast = fLast->next;
}
// Listen mode for lettered character
void letteredHokeemon::listen()
{
    cout << setw(24) << left << "Hokeemon no. " << monNo << endl
    << setw(24) << left << "Hokeemon Character : " << character << endl
    << setw(24) << left << "Hunger level : " << hunger << " (" << hStatus << ")" << endl
    << setw(24) << left << "Boredom level : " << boredom << " (" << mood << ")" << endl << endl;
    if (hunger == 9)
    {
        cout << endl << "Hokeemon : I'm very hungry please!" << endl;
    }
    else if (hunger < 9)
    {
        cout << "Hokeemon : Decision and destiny! Please make your decision?" << endl;
    }
    if (boredom >= 15)
    {
        cout << "I need to play a lot with you if possible please!" << endl << endl;
    }
    else if (boredom < 15)
    {
        cout << "Everything is about inside our minds! I'm fine!" << endl << endl;
    }
}
// Play mode for lettered character
void letteredHokeemon::play()
{
    question* curr;
    bool retry = true;
    bool correct = false;
    int i = 0, j = 0, r = 0;
    const int qSize = 4, aSize = 4;
    int selectedQuestion = -1, selectedAns = -1;
    int answer = 0;
    int point = 0;
    vector <int> que;
    vector <int> ans;
    char a = '?';
    cout << "Hokeemon : The world is like a serious game! lets play this short funny game together too please" << endl << endl;
    while ((retry == true) && (i < qSize))
    {
        correct = false;
        if (ans.size() > 0)
        {
            ans.clear();
        }
        curr = first;
        selectedQuestion = rand() %qListSize + 1;
        retry = false;
        while ((curr != nullptr) && (curr->qNum != selectedQuestion))
        {
            curr = curr->next;
        }
        for (j = 0; j < que.size(); j++)
        {
            if (que.at(j) == selectedQuestion)
            {
                retry = true;
            }
        }
        if (retry == false)
        {
            i++;
            que.push_back(selectedQuestion);
            cout << i << " : " << curr->q << endl;
            retry = true;
            j = 0;
            while ((retry == true) && (j < aSize))
            {
                selectedAns = rand() %aSize + 1;
                retry = false;
                for (r = 0; r < ans.size(); r++)
                {
                    if (selectedAns == ans.at(r))
                    {
                        retry = true;
                    }
                }
                if (retry == false)
                {
                    j++;
                    retry = true;
                    if (ans.size() == 0)
                    {
                        cout << " A) ";
                    }
                    else if (ans.size() == 1)
                    {
                        cout << " B) ";
                    }
                    else if (ans.size() == 2)
                    {
                        cout << " C) ";
                    }
                    else if (ans.size() == 3)
                    {
                        cout << " D) ";
                        retry = false;
                    }
                    else
                    {
                        cout << "vector ans error!" << endl;
                    }
                    ans.push_back(selectedAns);
                    if (selectedAns == 1)
                    {
                        if (curr->a1[0] == '*')
                        {
                            cout << curr->a1.substr(1, curr->a1.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a1 << endl;
                        }
                    }
                    else if (selectedAns == 2)
                    {
                        if (curr->a2[0] == '*')
                        {
                            cout << curr->a2.substr(1, curr->a2.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a2 << endl;
                        }
                    }
                    else if (selectedAns == 3)
                    {
                        if (curr->a3[0] == '*')
                        {
                            cout << curr->a3.substr(1, curr->a3.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a3 << endl;
                        }
                    }
                    else if (selectedAns == 4)
                    {
                        if (curr->a4[0] == '*')
                        {
                            cout << curr->a4.substr(1, curr->a4.size()-1) << endl;
                        }
                        else
                        {
                            cout << curr->a4 << endl;
                        }
                    }
                }
            }
            cout << "Please select answer > ";
            a = '?';
            while ((a != 'A') && (a != 'a') && (a != 'B') && (a != 'b') && (a != 'C') && (a != 'c') && (a != 'D') && (a != 'd'))
            {
                cin >> a;
            }
            if ((a == 'A') || (a == 'a'))
            {
                if (ans.at(0) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'B') || (a == 'b'))
            {
                if (ans.at(1) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'C') || (a == 'c'))
            {
                if (ans.at(2) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            else if ((a == 'D') || (a == 'd'))
            {
                if (ans.at(3) == curr->key)
                {
                    correct = true;
                    point++;
                }
            }
            if (correct == false)
            {
                cout << "Incorrect!" << endl;
            }
            else
            {
                cout << "Correct!" << endl;
            }
            cout << endl;
            retry = true;
        }
    }
    if (point == aSize)
    {
        boredom -= 4;
        cout << "Congratulation! You answered all as correct!" << endl
        << "Bonuses:" << endl << "Boredom level decreased by -4" << endl << endl;
    }
    else
    {
        cout << "Failed! You just answered " << point << " question(s) correctly!" << endl << endl;
    }
    PassTime();
    identifier();
}
// Feed mode for lettered character
void letteredHokeemon::feed()
{
    food* curr;
    int r, i, j = 0, current = -1;
    bool retry = true;
    const int fSize = 4, aSize = 4;
    int selectedFood = 0;
    vector <int> fShow;
    char foodNum = '?';
    cout << "Hokeemon : If possible Some foods please" << endl << endl;
    for (i = 0; i < fSize; i++)
    {
        foodNum = '?';
        if (fShow.size() > 0)
        {
            fShow.clear();
        }
        j = 0;
        retry = true;
        while ((retry == true) && (j < aSize))
        {
            curr = fFirst;
            selectedFood = rand() %fListSize + 1;
            retry = false;
            for (r = 0; r < fShow.size(); r++)
            {
                if (fShow.at(r) == selectedFood)
                {
                    retry = true;
                }
            }
            if (retry == false)
            {
                while ((selectedFood != curr->fNum) && (curr != nullptr))
                {
                    curr = curr->next;
                }
                if (selectedFood == curr->fNum)
                {
                    fShow.push_back(curr->fNum);
                    cout << j+1 << ": " << curr->f << " ";
                    if (fShow.size() < aSize)
                    {
                        retry = true;
                    }
                    j++;
                }
            }
        }
        cout << endl << "Please may i have more? > ";
        while ((!(isdigit(foodNum))) || ((int(foodNum)-48) < 1) || ((int(foodNum)-48) > aSize))
        {
            cin >> foodNum;
        }
        curr = fFirst;
        current = (int(foodNum))-48-1;
        while ((curr != nullptr) && (fShow.at(current) != curr->fNum))
        {
            curr = curr->next;
        }
        if (curr != nullptr)
        {
            cout << "Thank you so much for " << curr->f << " !" << endl << endl;
        }
    }
    hunger -= 4;
    cout << "Bonuses:" << endl << "hunger level decreased by -4" << endl << endl;
    PassTime();
    identifier();
}
int main()
{
    srand(time(0));
    bool quitFlag = false;
    int userChoice = -2;
    int hokeeTask = 0;
    const int societySize = 10;
    int n, creatureType, hokeeNum;
    normalHokeemon normalmon(1);
    angryHokeemon angrymon(1);
    coolHokeemon coolmon(1);
    shyHokeemon shymon(1);
    depressHokeemon depressmon(1);
    letteredHokeemon letteredmon(1);
    impoliteHokeemon impolitemon(1);
    greedyHokeemon greedymon(1);
    vector <Creature*> society;
    for (n = 0; n < societySize; n++)
    {
        hokeeNum = n+1;
        // Random Society Hokeemons character generated
        creatureType = rand() %8;
        if (creatureType == 0)
        {
            normalmon.initialCharacter(hokeeNum);
            society.push_back(&normalmon);
        }
        else if (creatureType == 1)
        {
            angrymon.initialCharacter(hokeeNum);
            society.push_back(&angrymon);
        }
        else if (creatureType == 2)
        {
            coolmon.initialCharacter(hokeeNum);
            society.push_back(&coolmon);
        }
        else if (creatureType == 3)
        {
            greedymon.initialCharacter(hokeeNum);
            society.push_back(&greedymon);
        }
        else if (creatureType == 4)
        {
            depressmon.initialCharacter(hokeeNum);
            society.push_back(&depressmon);
        }
        else if (creatureType == 5)
        {
            impolitemon.initialCharacter(hokeeNum);
            society.push_back(&impolitemon);
        }
        else if (creatureType == 6)
        {
            shymon.initialCharacter(hokeeNum);
            society.push_back(&shymon);
        }
        else if (creatureType == 7)
        {
            letteredmon.initialCharacter(hokeeNum);
            society.push_back(&letteredmon);
        }
    }
    while (!(quitFlag))
    {
        hokeeTask = 0;
        userChoice = 0;
        society.at(0)->societyMenu(society);
        userChoice = society.at(0)->selectHokeemon(society);
        if (userChoice == -1)
        {
            quitFlag = true;
        }
        else
        {
            while ((hokeeTask != 4) && (quitFlag == false))
            {
                hokeeTask = society.at(userChoice-1)->hokeemonMenu();
                if (hokeeTask == -1)
                {
                    quitFlag = true;
                }
                else if (hokeeTask == 1)
                {
                    society.at(userChoice-1)->listen();
                }
                else if (hokeeTask == 2)
                {
                    society.at(userChoice-1)->play();
                }
                else if (hokeeTask == 3)
                {
                    society.at(userChoice-1)->feed();
                }
            }
        }
    }
    return 0;
}
