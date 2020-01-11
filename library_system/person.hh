/* Module: Person
 * --------------
 * Represents a single person, either an author or an borrower.
 *
 * TIE-0220x S2019
 * */
#ifndef PERSON_HH
#define PERSON_HH

#include <string>

class Person
{
public:
    // Constructor.
    Person(std::string name, std::string email, std::string address);
    ~Person();

    // Get the person's name.
    std::string get_name() const;

    // Persons info printed neatly.
    void print_info() const;

private:
    std::string name_;
    std::string email_;
    std::string address_;
};

#endif // PERSON_HH
