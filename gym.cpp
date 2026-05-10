#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

class Member
{
protected:
    int age;
    string name, plan, phone_no, duration, memberID;

public:
    Member(string tname, string tplan, string tphone_no, int tage, string tduration, int serial)
    {
        name = tname;
        plan = tplan;
        phone_no = tphone_no;
        age = tage;
        duration = tduration;
        memberID = generateID(serial);
    }

    void saveToFile()
    {
        ofstream file("members.txt", ios::app);
        file << memberID << "," << name << "," << age << "," << plan << "," << duration << "," << phone_no << endl;
        file.close();
    }

    string generateID(int serial)
    {
        string id = "";

        id += toupper(name[0]);
        id += toupper(name[1]);
        id += phone_no.substr(phone_no.length() - 3);
        id += toupper(plan[0]);
        id += toupper(duration[0]);
        if (serial < 10)
            id += "00" + to_string(serial);
        else if (serial < 100)
            id += "0" + to_string(serial);
        else
            id += to_string(serial);

        return id;
    }

    void display()
    {
        cout << "Member ID : " << memberID << endl;
        cout << "Name      : " << name << endl;
        cout << "Age       : " << age << endl;
        cout << "Plan      : " << plan << endl;
        cout << "Duration  : " << duration << endl;
        cout << "Phone     : " << phone_no << endl;
    }
};
class Trainer
{
protected:
    string name, splz, phone_no, TrainerID;

public:
    Trainer(string tname, string tsplz, string tphone_no, int tserial)
    {
        name = tname;
        splz = tsplz;
        phone_no = tphone_no;
        TrainerID = generateID(tserial);
    }

    void saveToFile()
    {
        ofstream file("trainer.txt", ios::app);
        file << TrainerID << "," << name << "," << splz << "," << phone_no << endl;
        file.close();
    }

    string generateID(int tserial)
    {
        string id = "";
        if (tserial < 10)
            id += "00" + to_string(tserial);
        else if (tserial < 100)
            id += "0" + to_string(tserial);
        else
            id += to_string(tserial);

        return id;
    }

    void display()
    {
        cout << "Trainer ID : " << TrainerID << endl;
        cout << "Name      : " << name << endl;
        cout << "Specialization  : " << splz << endl;
        cout << "Phone     : " << phone_no << endl;
    }
};

class RegularMember : public Member
{
public:
    float Monthlyfee;
    RegularMember(string tname, string tplan, string tphone_no, int tage, string tduration, int serial, float tfee) : Member(tname, tplan, tphone_no, tage, tduration, serial)
    {
        Monthlyfee = tfee;
    }
    void display()
    {
        Member::display();
        cout << "Monthly Fee   : " << Monthlyfee << endl;
    }
};

class PremiumMember : public Member
{
public:
    float Monthlyfee;
    string trainer_name;
    int locker_no;
    PremiumMember(string tname, string tplan, string tphone_no, int tage, string tduration, int serial, float tfee, string ttrainer_name, int tlocker_no) : Member(tname, tplan, tphone_no, tage, tduration, serial)
    {
        Monthlyfee = tfee;
        trainer_name = ttrainer_name;
        locker_no = tlocker_no;
    }
    void display()
    {
        Member::display();
        cout << "Locker No     : " << locker_no << endl;
        cout << "Trainer Name  : " << trainer_name << endl;
        cout << "Monthly Fee   : " << Monthlyfee << endl;
    }
};

void showMenu()
{
    cout << "-----------GYM----------" << endl;
    cout << "1. Add Members" << endl;
    cout << "2. View Members" << endl;
    cout << "3. Mark Attendence" << endl;
    cout << "4. Add trainer" << endl;
    cout << "5. Delete Member" << endl;
    cout << "6. Exit" << endl;
};

int main()
{
    int tage, serial = 001, choicegym, tserial = 001;
    string tname, tplan, tphone_no, tduration, tsplz;

    while (true)
    {
        showMenu();
        cout << "Enter Your Choice : ";
        cin >> choicegym;
        switch (choicegym)
        {
        case 1:
        {
            cout << "----Add Members----";
            cout << "Name      : ";
            cin >> tname;
            cout << "Age       : ";
            cin >> tage;
            cout << "Plan      : ";
            cin >> tplan;
            cout << "Duration  : ";
            cin >> tduration;
            cout << "Phone     : ";
            cin >> tphone_no;

            Member m1(tname, tplan, tphone_no, tage, tduration, serial);

            m1.display();
            m1.saveToFile();
            serial++;
            break;
        }
        case 2:
        {
            ifstream file("members.txt");
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string id, name, age, plan, duration, phone;
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, age, ',');
                getline(ss, plan, ',');
                getline(ss, duration, ',');
                getline(ss, phone, ',');

                cout << "Member ID : " << id << endl;
                cout << "Name      : " << name << endl;
                cout << "Age       : " << age << endl;
                cout << "Plan      : " << plan << endl;
                cout << "Duration  : " << duration << endl;
                cout << "Phone     : " << phone << endl;
                cout << "-------------------------" << endl;
            }
            file.close();
            break;
        }
        case 3:
        {
            string searchID;
            cout << "Enter Member ID : ";
            cin >> searchID;

            ifstream file("members.txt");
            string line;
            bool found = false;

            time_t t = time(0);
            string date = ctime(&t);

            while (getline(file, line))
            {
                stringstream ss(line);
                string id;
                getline(ss, id, ',');

                if (id == searchID)
                {
                    found = true;
                    break;
                }
            }
            file.close();

            if (found)
            {
                ofstream afile("attendance.txt", ios::app);
                afile << searchID << "," << date;
                afile.close();
                cout << "Attendance marked for " << searchID << endl;
                cout << "Date : " << date << endl;
            }
            else
            {
                cout << "Member not found!" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "----Add Trainers----";
            cout << "Name      : ";
            cin >> tname;
            cout << "Specialization : ";
            cin >> tsplz;
            cout << "Phone     : ";
            cin >> tphone_no;

            Trainer t1(tname, tsplz, tphone_no, tserial);

            t1.display();
            t1.saveToFile();
            tserial++;
            break;
        }
        case 5:
        {
            bool found = false;
            while (getline(file, line))
            {
                if (line.find(searchID) != string::npos)
                {
                    found = true;
                }
                else
                {
                    lines.push_back(line);
                }
            }
            file.close();

            if (found)
            {
                ofstream outfile("members.txt");
                for (string l : lines)
                {
                    outfile << l << endl;
                }
                outfile.close();
                cout << "Member deleted!" << endl;
            }
            else
            {
                cout << "Member ID not found!" << endl;
            }
        }
        case 6:
        {
            cout << "Exiting..." << endl;
            return 0;
        }
        }
    }
    return 0;
}