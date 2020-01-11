/* Module: Date
 * ------------
 * Represents a single date, that can be compared and advanced
 * by a some number of days.
 *
 * TIE-0220x S2019
 * */
#ifndef DATE_HH
#define DATE_HH

#include <string>
#include <vector>

// Month lengths. Leap year february is handled in the code.
unsigned int const month_sizes[12] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };
// Default loan lenght
const unsigned int LOAN_LENGTH = 28;

class Date
{
public:
    // Constructor. If any of the params is out of sensible limits,
    // default value of 1 is used instead.
    Date(unsigned int day, unsigned int month, unsigned int year);
    ~Date();

    // Calls the advance_by with default LOAN_LENGHT
    void advance_by_loan_length();

    // Advances the date with given amount of days.
    // Can't be anvanced by negative amounts.
    void advance_by(unsigned int days);

    // Prints the date.
    void show();

    // Returns the str representation of the date: dd.mm.yyyy
    std::string to_string() const;

    // Self-descriptive getters
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;

    // Comparison operators
    bool operator==(Date& rhs) const;
    bool operator<(Date& rhs) const;

private:
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    bool is_leap_year() const;
};

#endif // DATE_HH
