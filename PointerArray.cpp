#include <iostream>
#include <cstring>
#include <string>

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
    char* AM;
    std::string Name;
    unsigned int Semester;
    unsigned int Passed_classes;
    float* Grades;
    unsigned int Courses;
    Course* Courses_t; 
public:
    /* Constructor */
    Student(const char* am, const std::string& name, unsigned int semester = 1, unsigned int passed_classes = 0, float* grades = nullptr, unsigned int courses = 0, Course* courses_t = nullptr)
        : Name(name), Semester(semester), Passed_classes(passed_classes), Courses(courses){
        AM = new char[strlen(am) + 1];  //Allocating memory for the arrays
        strcpy(AM, am);
        Grades = new float[Passed_classes];
        for (int i = 0; i < Passed_classes; i++){
            Grades[i] = grades[i];
        }
        Courses_t = new Course[Courses];
        for (int i = 0; i < Courses; i++){
            Courses_t[i] = courses_t[i];
        }
    }

    /* Copy Constructor */
    Student(const Student& student)
        : Name(student.Name), Semester(student.Semester), Passed_classes(student.Passed_classes), Courses(student.Courses){
        AM = new char[strlen(student.AM) + 1];  //Allocating memory for the arrays
        strcpy(AM, student.AM);
        Grades = new float[Passed_classes];
        for (int i = 0; i < Passed_classes; i++){
            Grades[i] = student.Grades[i];
        }
        Courses_t = new Course[Courses];
        for (int i = 0; i < Courses; i++){
            Courses_t[i] = student.Courses_t[i];
        }
    }

    /* Destructor */
    ~Student(){ 
        delete[] AM;
        AM = nullptr;
        delete[] Grades;
        Grades = nullptr;
        delete[] Courses_t;
        Courses_t = nullptr;
    }
    
    /* Setters */
    void setCourses(unsigned int courses){
        delete[] Courses_t;  //Deleting the current array
        Courses = courses;
        Courses_t = new Course[Courses];  //Allocating new memory and updating the size of the array

    }
    void setCoursesTaken(Course* courses_t){
        delete[] Courses_t;  //Deleting the current array
        Courses_t = new Course[Courses];  //Allocating new memory
        for (int i = 0; i < Courses; i++){
            Courses_t[i] = courses_t[i];
        }
    }
    void setAM(const char* am){
        delete[] AM;  //Deleting current memory
        AM = new char[strlen(am) + 1];  //Allocating new memory
        strcpy(AM, am);
    }
    void setName(const std::string& name){
        Name = name;
    }
    void setSemester(unsigned int semester){
        Semester = semester;
    }
    void setPassedClasses(unsigned int passed_classes){
        delete[] Grades;  //Deleting current memory
        Passed_classes = passed_classes;
        Grades = new float[Passed_classes]; //Allocating new memory and updating the size of the array
    }
    void setGrades(const float* grades){
        delete[] Grades;  //Deleting current memory
        Grades = new float[Passed_classes];  //Allocating new memory
        for (int i = 0; i < Passed_classes; i++){
            Grades[i] = grades[i];
        }
    }

    /* Getters */
    unsigned int getCourses() const{  //Getters
        return Courses;
    }
    Course getCoursesTaken(int index) const{
        if (index >=0 && index <= Courses){
            return Courses_t[index];
        }
        return Course();  //Return default constructed Course
        
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
    char* getAM() const{
        return AM;
    }
    float getGrades(unsigned int index) const{
        if (index >=0 && index < Passed_classes){
            return Grades[index];
        } 
        return 0;  //Return 0 to avoid junk
    }

    void addGrade(const float grade){  //Add a grade in the array
        float* tmp = new float[Passed_classes + 1];  //Allocating memory for a temporary array
        for (int i = 0; i < Passed_classes; i++){  //Copy everything from Grades array to tmp array
            tmp[i] = Grades[i];
        }
        tmp[Passed_classes] = grade;  //Set the grade parameter at the end of the array
        delete[] Grades;  //Delete the current Grades array
        Grades = tmp;  //Set the Grades array as the tmp array
        Passed_classes++;  //Increase the passes classes by 1
    }
    
    /* Overloading Operators */
    Student& operator+=(const Course& course){  //+= Overload to add a course on the courses taken array of a student
        Course* tmp = new Course[Courses + 1];  //Same proccess as the addGrade() method but in this case we return this student
        for (int i = 0; i < Courses; i++){
            tmp[i] = Courses_t[i];
        }
        tmp[Courses] = course;
        delete[] Courses_t;
        Courses_t = tmp;
        Courses++;
        return *this;
    }
    Student& operator=(const Student& student){ //= Overload to assign the attributes of another student to this one
        if (this == &student){  //If they are the same student return this student
            return *this; 
        }
        delete[] AM;  //Delete all the allocated memory
        delete[] Grades;
        delete[] Courses_t;
        Name = student.Name;  //Same process as the copy constructor but in this case we return this student
        Semester = student.Semester;
        Passed_classes = student.Passed_classes;
        Courses = student.Courses;
        AM = new char[strlen(student.AM) + 1];
        strcpy(AM, student.AM);
        Grades = new float[Passed_classes];
        for (int i = 0; i < Passed_classes; i++){
            Grades[i] = student.Grades[i];
        }
        Courses_t = new Course[Courses];
        for (int i = 0; i < Courses; i++){
            Courses_t[i] = student.Courses_t[i];
        }
        return *this;
    }

    bool operator==(const Student& student) const{  //== Overload to compare semesters
        return Semester == student.Semester;
        
    }
    bool operator!=(const Student& student) const{ //!= Overload to compare semesters
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
        for (int i = 0; i < Passed_classes; i++){
            channel <<  "Class " << i + 1 <<": " << Grades[i] << std::endl;
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
    float grades1[2] = {4, 6};
    Course courses[3] = {
        Course("2222", "Mathematics", 1),
        Course("4242", "Computer Science", 2),
        Course("5656", "Physics", 3)
    };
    Course newCourse("7890", "English", 1);
    const char AM1[] = "23456";
    const char AM2[] = "2889";

    Student s1(AM1, "John", 5, 2, grades1, 3, courses);
    Student s2(AM2, "Steve", 2, 2, grades1, 3, courses);
    
    std::cout << s1;
    s1.printGrades(std::cout);

    s1 += newCourse;

    std::cout << s1;
    s1.printGrades(std::cout);

    s1 = s2;

    std::cout << s1;
    s1.printGrades(std::cout);

    if(s1 < s2){
        std::cout << "s1 is in a later semester than s2" << std::endl;
    }
    else{
        std::cout << "s2 is in a later semester than s1" << std::endl;
    }

    return 0; 
}