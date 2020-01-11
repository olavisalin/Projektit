#include "date.hh"
#include <iostream>

Date::Date(unsigned int day, unsigned int month, unsigned int year):
    day_(day), month_(month), year_(year)
{
    if ( month_ > 12 || month_ < 1){
        month_ = 1;
    }
    if ( day_ > month_sizes[month_ - 1]
         || (month_ == 2 && is_leap_year()
             && day > month_sizes[month - 1 ] + 1) ){
        day_ = 1;
    }

}

Date::~Date()
{

}

void Date::advance_by_loan_length()
{
    advance_by(LOAN_LENGTH);
}

void Date::advance_by(unsigned int days)
{
    day_ = day_ + days;
    while ( day_ > month_sizes[month_ - 1] ){
        if ( month_ == 2 && day_ == 29 ){
            return;
        }
        day_ = day_ - month_sizes[month_ - 1];
        if ( month_ == 2 && is_leap_year() ){
            day_--;
        }
        month_++;

        if ( month_ > 12 ){
            month_ = month_ - 12;
            year_++;
        }
    }
}

void Date::show()
{
    std::cout << "Today is ";
    std::cout << to_string() <<  std::endl;
}

std::string Date::to_string() const
{
    std::string str = ""
            + std::to_string(day_)
            + '.'
            + std::to_string(month_)
            + '.'
            + std::to_string(year_);

    return str;
}

unsigned int Date::getDay() const
{
    return day_;
}

unsigned int Date::getMonth() const
{
    return month_;
}

unsigned int Date::getYear() const
{
    return year_;
}

bool Date::operator==(Date &rhs) const
{
    return day_ == rhs.day_ && month_ == rhs.month_ && year_ == rhs.year_ ;
}

bool Date::operator<(Date &rhs) const
{
    return (year_ * 10000 + month_ * 100 + day_ ) <
            ( rhs.year_ * 10000 + rhs.month_ * 100 + rhs.day_);
}

bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && (!(year_ % 100 == 0) || (year_ % 400 == 0));
}

