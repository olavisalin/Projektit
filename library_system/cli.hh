/* Module: cli
 * -----------
 * Handles taking the user input and checking if it's in the correct form.
 *
 * TIE-0220x S2019
 * */
#ifndef CLI_HH
#define CLI_HH

#include "library.hh"
#include <string>
#include <vector>
#include <memory>

const std::string ERROR = "Error: Unknown command or wrong amount/type of parameters.";
const std::vector<std::string> EXITS = { "EXIT" , "QUIT", "E", "Q" };

// All of the function types the cli supports. Should the params parsing be done
// in the called function instead?
using no_param = void (Library::*)();
using one_param = void (Library::*)(const std::string&);
using two_param = void (Library::*)(const std::string&, const std::string&);
using three_param = void (Library::*)(const std::string&, const std::string&, const std::string&);
using date_param = void (Library::*)(int, int, int);
using int_param = void(Library::*)(int);

struct cmd{
    std::vector<std::string> names_;
    no_param func0_;
    one_param func1_;
    two_param func2_;
    three_param func3_;
    date_param func_date_;
    int_param func_i_;
};

class Cli
{
public:
    // The database that is going to be used is given as a parameter.
    Cli(std::shared_ptr<Library> db);
    ~Cli();

    /* Description: Runs the interface.
     * Return values:
     *  True    - Normal command
     *  False   - Exit command
     */
    bool exec_prompt();

private:
    std::shared_ptr<Library> database_;

    // Stores the arguments from current command.
    std::vector<std::string> args_;

    // Pointer to the recognized command.
    const cmd* recognized_;

    // Printed for every query
    const std::string PROMPT = "CMD> ";

    // Parses the given input to different arguments
    void parseCommand(const std::string& line);

    /* Description: Sets the recognized_ to point at the correct
     * CommandInfo.
     * Return values:
     *  Amount of arguments - Command can be executed
     *  -1                  - Exit command
     *  -2                  - Invalid amount of parameters
     *  -3                  - Command not recognized.
     */
    int checkCommandType();

    // To make code more readable. Could also be different constants but this
    // groups them better.
    enum Commandtypes {QUIT = -1, NO_PARAMETERS = 1, ONE_PARAMETER = 2,
                       TWO_PARAMETER = 3, THREE_PARAMETER = 4,
                       DATE_PARAMETER = 5, INT_PARAMETER = 6,
                       EMPTY = 0, UNKNOWN = -3,
                       WRONG_PARAMETERS = -2};


    // Constant table that contains the different commands that the CLI can
    // recognize.
    std::vector<cmd> const COMMANDS = {
        {{"EXIT","QUIT","Q","LOPETA"}, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"BOOKS"}, &Library::all_books, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"BOOK INFO"}, &Library::all_books_with_info, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"BORROWERS"}, &Library::all_borrowers, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"BORROWER INFO"}, &Library::all_borrowers_with_info, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"ADD BORROWER", "AP"}, nullptr, nullptr, nullptr, &Library::add_borrower, nullptr, nullptr},
        {{"SET DATE", "DATE"}, nullptr, nullptr, nullptr, nullptr, &Library::set_date, nullptr},
        {{"LOANED", "LOANS"}, &Library::loaned_books, nullptr, nullptr, nullptr, nullptr, nullptr},
        {{"LOANS BY", "LB"}, nullptr, &Library::loans_by, nullptr, nullptr, nullptr, nullptr},
        {{"LOAN"}, nullptr, nullptr, &Library::loan, nullptr, nullptr, nullptr},
        {{"RENEW"}, nullptr, &Library::renew_loan, nullptr, nullptr, nullptr, nullptr},
        {{"RETURN"}, nullptr, &Library::return_loan, nullptr, nullptr, nullptr, nullptr},
        {{"ADVANCE"}, nullptr, nullptr, nullptr, nullptr, nullptr, &Library::advance_date}
    };

    bool is_numeric(std::string s, bool zero_allowed);

};

#endif // CLI_HH
