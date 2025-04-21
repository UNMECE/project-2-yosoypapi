#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Student 
{
protected:
    std::string firstName;
    std::string lastName;
    double gpa;
    int gradYear;
    std::string gradSemester;
    int enrolledYear;
    std::string enrolledSemester;
    std::string level; 
public:
    Student() : firstName("N/A"), lastName("N/A"), gpa(0.0), gradYear(0), gradSemester("N/A"),
                enrolledYear(0), enrolledSemester("N/A"), level("undergrad") {}

    virtual ~Student() {}
    void setName(const std::string &first, const std::string &last) 
    {
        firstName = first;
        lastName = last;
    }
    void setGPA(double g) { gpa = g; }
    void setGradYear(int year) { gradYear = year;}
    void setGradSemester(const std::string &sem) { gradSemester = sem;}
    void setEnrolledYear(int year) { enrolledYear = year; }
    void setEnrolledSemester(const std::string &sem) { enrolledSemester = sem;}
    void setLevel(const std::string &lvl) { level = lvl;}
    virtual void writeToFile(std::ofstream &outfile) const 
    {
        outfile << firstName << " " << lastName << "\n";
        outfile << "GPA: " << gpa << "\n";
        outfile << "Graduation: " << gradSemester << " " << gradYear << "\n";
        outfile << "Enrolled: " << enrolledSemester << " " << enrolledYear << "\n";
        outfile << "Level: " << level << "\n";
    }
};
class Art_Student : public Student 
{
private:
    std::string art_emphasis; 
public:
    Art_Student() : art_emphasis("Art ") {}

    void setArtEmphasis(const std::string &emph) 
    {
        art_emphasis = emph;
    }

    void writeToFile(std::ofstream &outfile) const override 
    {
        outfile << "Art Student:\n";
        Student::writeToFile(outfile);
        outfile << "Art Emphasis: " << art_emphasis << "\n\n";
    }
};
class Physics_Student : public Student 
{
private:
    std::string concentration; 
public:
    Physics_Student() : concentration("physics") {}

    void setConcentration(const std::string &conc) 
    {
        concentration = conc;
    }
    void writeToFile(std::ofstream &outfile) const override 
    {
        outfile << "Physics Student:\n";
        Student::writeToFile(outfile);
        outfile << "Concentration: " << concentration << "\n\n";
    }
};
int main() 
{
    std::vector<Art_Student*> art_students;
    std::vector<Physics_Student*> physics_students;
    for (int i = 0; i < 5; ++i) 
    {
        Art_Student* a = new Art_Student();
        a->setName("ArtFirst" + std::to_string(i), "ArtLast" + std::to_string(i));
        a->setGPA(3.5 + i * 0.1);
        a->setGradYear(2026 + i);
        a->setGradSemester("Spring");
        a->setEnrolledYear(2022);
        a->setEnrolledSemester("Fall");
        a->setLevel("undergrad");
        a->setArtEmphasis(i % 3 == 0 ? "Art" : i % 3 == 1 ? "Art History" : "Art Education");
        art_students.push_back(a);
    }
    for (int i = 0; i < 5; ++i) 
    {
        Physics_Student* p = new Physics_Student();
        p->setName("PhysFirst" + std::to_string(i), "PhysLast" + std::to_string(i));
        p->setGPA(3.6 + i * 0.1);
        p->setGradYear(2027 + i);
        p->setGradSemester("Fall");
        p->setEnrolledYear(2023);
        p->setEnrolledSemester("Spring");
        p->setLevel("grad");
        p->setConcentration(i % 2 == 0 ? "physics" : " Sciences");
        physics_students.push_back(p);
    }
    std::ofstream outfile("student_info.dat");
    if (outfile.is_open()) 
    {
        for (const auto &a : art_students) 
        {
            a->writeToFile(outfile);
        }
        for (const auto &p : physics_students) 
        {
            p->writeToFile(outfile);
        }
        outfile.close();
    } else 
    {
        std::cerr << "can't open file.\n";
    }
    for (auto a : art_students) 
    {
        delete a;
    }
    for (auto p : physics_students)
    {
        delete p;
    }
    return 0;
}
