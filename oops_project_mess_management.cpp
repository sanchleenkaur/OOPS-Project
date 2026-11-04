#include <iostream>
#include<vector>
#include<iomanip>
using namespace std;

//abstract Class
class Person {
protected:
    int id;
    string name;

public:
    Person(int id, string name) : id(id), name(name) {}
    virtual ~Person() {}
    virtual void display()const = 0;
    int getId() const { return id; }
    string getName() const { return name; }};

//Student details
class Student:public Person{
    private:
    int meals;
    float balance;
    public:
    Student():Person(0,""),meals(0),balance(0.0){}
    Student(int i,string n,int m,int b):Person(id,name),meals(m),balance(b){}
    int getID(){return id;}
    void updateMeals(int count){meals+=count;}
    void updateBalance(float amount){balance+=amount;}
    void display() const override{
        cout<<"ID:"<<id<< "Name:"<<name<<" Meals:"<<meals<<" Balance:"<<balance<<endl;
    }
    //file handling 
   void save(ofstream &outFile)  {
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t len = name.size();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(name.c_str(), len);
        outFile.write(reinterpret_cast<const char*>(&totalMeals), sizeof(totalMeals));
        outFile.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
    }

    void load(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t len;
        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        char* buf = new char[len + 1];
        inFile.read(buf, len);
        buf[len] = '\0';
        name = string(buf);
        delete[] buf;
        inFile.read(reinterpret_cast<char*>(&totalMeals), sizeof(totalMeals));
        inFile.read(reinterpret_cast<char*>(&balance), sizeof(balance));
    }
};

//Expense Tracker
class Expense{
    double totalexpense;
    public:
    Expense(double t=0):totalexpense(t){}
    void updateExpense(double amt){
        totalexpense+=amt;
    }
    double getexpense(){return totalexpense;}
    double perMealRate(int totalMeals){
        return totalMeals==0.0?0:totalexpense/totalMeals;
    }
    
};
class Mess{
    private:
    vector<Student>student;
    string name;
    int id;
    Expense expense;
    public:
    void addMember(){
        Student s;
        cout<<"Enter ID:";
        cin>>id;
        cout<<"Enter Name:";
        cin>>name;
        student.push_back(Student(id,name,0,0.0));
        cout<<"Student added succesfully!\n";
    }
    void display(){
        cout<<"Mess Member List:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(12) << "Meals" << setw(10) << "Balance" << endl;
        cout << "--------------------------------------------------\n";
        for (const auto &m : student) {
            m.display();
        }
    }
    void addMeals(){
        int id,meal;
        cout<<"Enter ID to log meals:";
        cin>>id;
        for(auto &m:student){
            if(m.getId()==id){
                cout<<"Enter number of meals to add:";
                cin>>meal;
                m.updateMeals(meal);
                cout<<"Meals updated!\n";return;
            }}cout<<"Member not found!\n";
        }
        
        void updateexpense(){
            double amount;
            cout<<"Enter grocery expense:";
            cin>>amount;
            expense.updateExpense(amount);
            cout<<"Expense Updated.Total Expense:"<<expense.getexpense()<<endl;
        }
        
        //file handling code
void saveToFile(){
    ofstream outfile "mess_oop_data.dat",ios::binary);
    size_t count=student.size();
    outFile.write(reinterpret_cast<const *char*>(&count),sizeof(count));
    for(const auto& s:student){
        s->save(outFile);}
    outFile.close();
    cout<<"Data saved securely!\n";
}
void loadFromFile(){
    ifstream inFile("mess_oop_data.dat",ios::binary);
    if(inFile!)return;
    size_t count;
    inFile.read(reinterpret_cast<char*>(&count),sizeof(count));
    student.clear();
    for(int i=0;i<count;i++){
        auto s=male<Student>();
        s->load(inFile);
        student.pushback(move(s));}
    inFile.close();
}
       
        
    };
    

 int main() {
    Mess messSystem;
    messSystem.loadFromFile();

    int choice;
    do {
        cout << "\n======MESS MANAGEMENT SYSTEM======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Member List\n";
        cout << "3. Log Meals\n";
        cout << "4. Add Daily Expense\n";
        cout << "5. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: messSystem.addMember(); break;
            case 2: messSystem.display(); break;
            case 3: messSystem.addMeals(); break;
            case 4: messSystem.updateexpense(); break;
            case 5: messSystem.saveToFile(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
