#include "date.hh"
#include "library.hh"
#include "loan.hh"
#include <iostream>
#include <memory>

Loan::Loan(Book* title, Person* borrower, std::vector<int> borrow_date) :
    borrower_(borrower),
    due_to_(new Date(borrow_date.at(0), borrow_date.at(1), borrow_date.at(2))),
    renews_left_(DEFAULT_RENEWAL_AMOUNT),
    title_(title)
{
    // Parameter icnludes the date of the day when borrowed, due_to is one
    // loan lenght later.
    due_to_->advance_by_loan_length();
}

Loan::~Loan()
{

}

void Loan::print_info(Date& today, bool print_borrower)
{
    // We want to print 0, when the loan is not late and 1, when it is.
    // is_late_code represents the number to be printed.
    int is_late_code = 0;
    if ( !is_late(today)){
        is_late_code = 1;
    }

    // Printed in both cases.
    std::cout << title_->get_title() << " : ";


    if(print_borrower){
        // printed only in loaned_books case.
        std::cout << borrower_->get_name() << " : ";
    }
    // Printed in both cases.
    std::cout << due_to_->to_string() << " : " << is_late_code << std::endl;
}

// another represents the current day.
bool Loan::is_late(Date& another)
{
    if ( due_to_->operator < (another ) ){
        return 0;
    }
    else{
        return 1;
    }
}

