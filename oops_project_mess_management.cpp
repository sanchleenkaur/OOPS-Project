#include<bits.stdc++.h>
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
    Student(int i,string n,int m,int b):Person(i,n),meals(m),balance(b){}
    int getID(){return id;}
    void updateMeals(int count){meals+=count;}
    void updateBalance(float amount){balance+=amount;cout<<balance;}
    void display() const override{
        cout << left << setw(10) << id << setw(20) <<name << setw(12) << meals<< setw(10) <<balance << endl;

    }
    //file handling 
    void save(ofstream &outFile)  {
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t len = name.size();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(name.c_str(), len);
        outFile.write(reinterpret_cast<const char*>(&meals), sizeof(meals));
        outFile.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
    }

    void load(ifstream &inFile)  {
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t len;
        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        char* buf = new char[len + 1];
        inFile.read(buf, len);
        buf[len] = '\0';
        name = string(buf);
        delete[] buf;
        inFile.read(reinterpret_cast<char*>(&meals), sizeof(meals));
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
        cin.ignore();
        cout<<"Enter Name:";
        getline(cin,name);
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
        float amount;
        cout<<"Enter ID to log meals:";
        cin>>id;
        bool found=false;
        for(auto &m:student){
            if(m.getId()==id){
                found=true;
                cout<<"Enter number of meals to add:";
                cin>>meal;
                m.updateMeals(meal);
                amount=float(meal*50);
                m.updateBalance(amount);
                cout<<"Meals updated!\n";
                break;
            }
        }
            if(!found){
                cout<<"Member not found!\n";
            }
        }
    void updateBalance(){
        int id;
        float amount;
        cout<<"Enter ID to update balance:";
        cin>>id;
        for(auto &m:student){
            if(m.getId()==id){
                cout<<"Enter amount:";
                cin>>amount;
                m.updateBalance(amount);
                cout<<"Balance updated!\n";return;
            }}cout<<"Member not found!\n";
        }
        void updateexpense(){
            double amount;
            cout<<"Enter grocery expense:";
            cin>>amount;
            expense.updateExpense(amount);
            cout<<"Expense Updated.\nTotal Expense:"<<expense.getexpense()<<endl;
        }
        
        //file handlind code
        void saveToFile() {
        ofstream outFile("mess_oop_data.dat", ios::binary);
        size_t count = student.size();
        outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for ( auto& s : student) {
            s.save(outFile);
        }
        outFile.close();
        cout << "Data saved securely via polymorphism!\n";
    }

    void loadFromFile() {
        ifstream inFile("mess_oop_data.dat", ios::binary);
        if (!inFile) return;

        size_t count;
        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
        student.clear();
        for (size_t i = 0; i < count; ++i) {
            Student* s=new Student();
            s->load(inFile);
            student.push_back(*s);
            delete s;
        }
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
        cout << "4. Update Balance\n";
        cout << "5. Add Daily Expense\n";
        cout << "6. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: messSystem.addMember(); break;
            case 2: messSystem.display(); break;
            case 3: messSystem.addMeals(); break;
            case 4:messSystem.updateBalance();break;
            case 5: messSystem.updateexpense(); break;
            case 6: messSystem.saveToFile(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

  
