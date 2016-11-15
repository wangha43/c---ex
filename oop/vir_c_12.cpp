#include <iostream>
#include <string>
#include <vector>

class Doctor;
class Patient{
private: 
    std::string m_name;
    std::vector<Doctor *>m_doctor;

    void addDoctor(Doctor *);

public:
    Patient(std::string name):m_name(name){}

    friend std::ostream & operator <<(std::ostream &out,const Patient &pat);

    std::string getname() const{
        return m_name;
    }
    friend Doctor;
};

class Doctor{
private:
    std::string m_name;
    std::vector<Patient *> m_patient;

public:
    Doctor(std::string name):m_name(name){}

    void addPatient(Patient *pat){
        m_patient.push_back(pat);
        pat->addDoctor(this);
    }

//reload the << operator
    friend std::ostream& operator <<(std::ostream &out,const Doctor &doc){
        unsigned int length = doc.m_patient.size();
        if (length == 0)
        {
            out <<doc.m_name << "has no patient now";
        }
        return out;
    }

    std::string getName() const { return m_name; }
};

void Patient::addDoctor(Doctor* doc){
    m_doctor.push_back(doc);
}

std::ostream & operator <<(std::ostream &out,const Patient &pat){
    unsigned int length = pat.m_doctor.size();
    if (length == 0)
    {
        std::cout << pat.getname() << " has no doctors right now";
        return out;
    }
 
    out << pat.m_name << " is seeing doctors: ";
    for (unsigned int count = 0; count < length; ++count)
        out << pat.m_doctor[count]->getName() << ' ';
 
    return out;
}

int main(int argc, char const *argv[])
{
    Patient *p1 = new Patient("Dave");
    Patient *p2 = new Patient("Frank");
    Patient *p3 = new Patient("Betsy");
 
    Doctor *d1 = new Doctor("James");
    Doctor *d2 = new Doctor("Scott");
 
    d1->addPatient(p1);
 
    d2->addPatient(p1);
    d2->addPatient(p3);
 
    std::cout << *d1 << '\n';
    std::cout << *d2 << '\n';
    std::cout << *p1 << '\n';
    std::cout << *p2 << '\n';
    std::cout << *p3 << '\n';
 
    delete p1;
    delete p2;
    delete p3;
    
    delete d1;
    delete d2;
    return 0;
}