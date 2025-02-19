#include <iostream>
#include <string>
#include <vector>

class Course{
private:
    std::string CourseId;
    std::string Name;
    unsigned int Semester;
public:
    /* Constructor */
    Course(const std::string& courseId = "", const std::string& name = "", unsigned int semester = 0)
        : CourseId(courseId), Name(name), Semester(semester) {} 
};

class Student{
private:
    std::string AM;
    std::string Name;
    unsigned int Semester;
    unsigned int Passed_classes;
    std::vector<float> Grades;
    std::vector<Course> Courses_t;
public:
    /* Constructor */
    Student(const std::string& am, const std::string& name, unsigned int semester = 1, unsigned int passed_classes = 0,const std::vector<float>& grades = {}, const std::vector<Course>& courses_t = {})
        : AM(am), Name(name), Semester(semester), Passed_classes(passed_classes), Grades(grades), Courses_t(courses_t) {}

    /* Copy Constructor */
    Student(const Student& student)
        : AM(student.AM), Name(student.Name), Semester(student.Semester), Passed_classes(student.Passed_classes), Grades(student.Grades), Courses_t(student.Courses_t) {}

    /* Setters */
    void setAM(const std::string& am){
        AM = am;
    }
    void setName(const std::string& name){
        Name = name;
    }
    void setSemester(unsigned int semester){
        Semester = semester;
    }
    void setPassedClasses(unsigned int passed_classes){
        Passed_classes = passed_classes;
        Grades.resize(Passed_classes);  //Update the size of the Grades vector
    }
    void setGrades(const std::vector<float>& grades){
        Grades = grades;
    }
    void setCoursesTaken(const std::vector<Course>& courses_t){
        Courses_t = courses_t;
    }

    /* Getters */
    std::string getAM() const{
        return AM;
    }
    std::string getName() const{
        return Name;
    }
    unsigned int getSemester() const{
        return Semester;
    }
    unsigned int getPassedClasses() const{
        return Passed_classes;
    }
    float getGrades(unsigned int index) const{
        if (index >= 0 && index <= Grades.size()){
            return Grades[index];
        }
        return 0;  //Return 0 to avoid junk
    }
    unsigned int getCourses() const{
        return Courses_t.size();
    }
    Course getCoursesTaken(unsigned int index) const{
        if (index >= 0 && index <= Courses_t.size()){
            return Courses_t[index];
        }
        return Course();  //Return default constructed Course
    }

    void addGrade(const float grade){  //Add a grade in the vector
        Grades.push_back(grade);
        Passed_classes++;
    }

    /* Overloading Operators */
    Student& operator+=(const Course& course){  //=+ Overload to add a new course in the vector of courses of a student
        Courses_t.push_back(course);
        return *this;
    }
    Student& operator=(const Student& student){  //= Overload to assign the attributes of another student to this one
        if (this == &student){  //If they are the same student return this student
            return *this;
        }
        AM = student.AM;
        Name = student.Name;
        Semester = student.Semester;
        Passed_classes = student.Passed_classes;
        Grades = student.Grades;
        Courses_t = student.Courses_t;
        return *this;
    }
    bool operator==(const Student& student) const{  //== Overload to compare semesters
        return Semester == student.Semester;
        
    }
    bool operator!=(const Student& student) const{  //!= Overload to compare semesters 
        return Semester != student.Semester;
    }
    bool operator>(const Student& student) const{  //> Overload to compare semesters 
        return Semester > student.Semester;
    }
    bool operator<(const Student& student) const{  //< Overload to compare semesters 
        return Semester < student.Semester;
    }
    bool operator>=(const Student& student) const{  //>= Overload to compare semesters 
        return Semester >= student.Semester;
    }
    bool operator<=(const Student& student) const{  //<= Overload to compare semesters 
        return Semester <= student.Semester;
    }

    void printGrades(std::ostream& channel) const{  //Print grades in the channel the user wants
        for (int i = 0; i < Grades.size(); i++){
            channel << "Class " << i + 1 << ": " << Grades[i] << std::endl;;
        }
        channel << std::endl;
    }

    friend std::ostream& operator <<(std::ostream& output, Student& student);  //friend key word - To have access on private members
};

std::ostream& operator<<(std::ostream& output, Student& student)  //Overloading the << operator of the std::ostream class
{
    output << "AM: " << student.getAM() << ", Name: " << student.getName() << ", Semester: " << student.getSemester() << std::endl;
    return output;
}

int main()
{
    std::vector<float> grades1 = {4, 6};
    std::vector<Course> courses = {
        Course("2222", "Mathematics", 1),
        Course("4242", "Computer Science", 2),
        Course("5656", "Physics", 3)
    };
    Course newCourse("7890", "English", 1);
    std::string AM1 = "2234";
    std::string AM2 = "7738";

    Student s1(AM1, "John", 5, 2, grades1, courses);
    Student s2(AM2, "Steve", 2, 2, grades1, courses);
    
    std::cout << s1;
    s1.printGrades(std::cout);

    s1 += newCourse;

    std::cout << s1;
    s1.printGrades(std::cout);

    s1 = s2;

    std::cout << s1;
    s1.printGrades(std::cout);

    if (s1 < s2) {
        std::cout << "s1 is in a later semester than s2" << std::endl;
    } else {
        std::cout << "s2 is in a later semester than s1" << std::endl;
    }

    return 0;

}