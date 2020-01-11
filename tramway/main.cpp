/* Tramway : Template code
 *
 * Desc:
 * The program reads information about rasse_lines from imput file,
 * stores it into datastructure and enables handling of the data
 * for the user.

 * Program author ( Fill with your own info )
 * Name: Olavi Salin
 * Student number: 284132
 * UserID: salino ( Necessary due to gitlab folder naming. )
 * E-Mail: olavi.salin@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <set>
#include <algorithm>
#include <cctype>

using namespace std;

//Datastructure that contains all the lines as keys and vector of
// all the stations of the line as a value.
map< string, vector<string> > rasse_map;

// Contains all the stations from every line.
set< string > stations;


// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << endl;
}

// Checks if a :param:station is included in :param:line
// Returns true if so.
bool is_already(string line, string station){
    bool is_already = false;

    for( string stat : rasse_map.at(line) ){

        if ( stat == station ){
            is_already = true;
            break;
        }
    }
    return is_already;
}


// Checks a row from the input file.
// Returns true if the format is not approved.
bool check_format(string row){
    bool is_error = false;
    string::size_type break_point;
    break_point = row.find(";");
    string second_part = row.substr(break_point+1);

    if (row == ""){
        is_error = true;
    }
    else if (break_point == string::npos){
        is_error = true;
    }
    else if (break_point == 0){
        is_error = true;
    }
    else if (break_point == row.size()+1 ){
        is_error = true;
    }
    else if(second_part.find(";") != string::npos){
        is_error = true;
    }
    return is_error;
}


// Asks the user for input file and stores the data into
// Datastructures "rasse_map" and "stations". Returns true, if read succesfully.
bool read_file()
{
    bool read_succesfully = true;
    string input_file = "";
    cout << "Give a name for input file: ";
    getline(cin, input_file);

    ifstream file(input_file);
    if ( not file ) {
        cout << "Error: File could not be read." << endl;
        read_succesfully = false;
    }
    else {
        string row;
        vector<string> stations_in_route = {};
        string::size_type break_point;

        while( getline(file, row) ){

            if( check_format(row) ){
                cout<< "Error: Invalid format in file."<< endl;
                read_succesfully = false;
                break;
            }
            else{
                break_point = row.find(";");
                string line = row.substr(0, break_point);
                string station = row.substr(break_point + 1);

                // New line will be added.
                if( rasse_map.find(line) == rasse_map.end() ){
                    rasse_map.insert({line, stations_in_route});
                    rasse_map.at(line).push_back(station);

                // Error in the input file, if a station is more than once at a specific line.
                }else if(is_already(line,station)){
                    cout<< "Error: Station/line already exists."<< endl;
                    read_succesfully = false;
                    break;

                // New station for a line will be added.
                }else{
                    rasse_map.at(line).push_back(station);

                // New station will be added in set of all stations.
                }if( stations.find(station) == stations.end() ){
                    stations.insert(station);                   
                }
            }
        }
    }
    return read_succesfully;
}


// Split function from older assigment with a modification to cope with hipsus.
vector< string > split( string line, char separator, char hipsu = '"'){
vector< string > parts = { };

    for( ;; ) {
        string::size_type break_point = line.find(separator);
        string::size_type a_hipsu = line.find(hipsu);

        if ( a_hipsu == 0){
            string copy = line.substr(a_hipsu+1, line.size());

            if (copy.find(hipsu) != string::npos){
                string::size_type b_hipsu = copy.find(hipsu);
                string new_part = copy.substr(0, b_hipsu);
                parts.push_back(new_part);
                line.erase(0, b_hipsu+2);
            }
        }if (line == ""){
            return parts;

        }if (break_point == string::npos){
            parts.push_back(line);
            return parts;

        }if (break_point == 0){
            line.erase(0,1);

        }else{
            string new_part = line.substr(0, break_point);
            parts.push_back(new_part);
            line.erase(0, break_point+1);
        }
    }
}


// Asks user for input, processes it with split func and returns
// the input as a vector to the main function. The reason to use this
// function is to make the main sweet and short.
vector<string> ui_loop(){
    string line;
    cout << "tramway> ";
    getline(cin, line);
    vector<string> parts = split(line, ' ');
    return parts;
}


// Prints all the lines.
void print_lines(){
    cout<< "All tramlines in alphabetical order:"<< endl;

    for (pair<string, vector<string>> data: rasse_map){
        cout<< data.first <<endl;
    }
}


// Prints all the stations in a specific line (:param:line).
void stations_in_line(string line){
    cout<< "Line " << line;
    cout<< " goes through these stations in the order they are listed:" <<endl;

    for( string station : rasse_map.at(line) ){
        cout<< " - "<< station<< endl;
    }
}


// Prints all the lines the :param:station is included in.
void lines_station_is_in(string param_station){
    set<string> lines = {};

    // Goes trough every line and station.
    for (pair<string, vector<string>> data: rasse_map){
        for(string station : data.second){
            if (station == param_station){
                lines.insert(data.first);
            }
        }
    }
    cout<< "Station "<< param_station<< " can be found on the following lines:" <<endl;

    for(string line: lines){
        cout<< " - " << line << endl;
    }
}


// Adds param:station: into the vector of stations included in param:line:.
// Places it in front of param:nextstation:.
void add_station(string line, string station, string nextstation){

    vector<string>::iterator position;
    // Finds the iterator pointing on :param:nextstation.
    position = find(rasse_map.at(line).begin(), rasse_map.at(line).end(), nextstation);
    // Adds the station to right position.
    rasse_map.at(line).insert(position, station);
    cout<< "Station was added."<< endl;
}


// Removes a :param:station from the datastructure.
void remove_station(string station){

    for (pair<string, vector<string>> data: rasse_map){
        for(string stat : data.second){
            if (stat == station){
                vector<string>::iterator position;
                position = find(rasse_map.at(data.first).begin(), rasse_map.at(data.first).end(), station);
                rasse_map.at(data.first).erase(position);
            }
        }
    }
    cout<< "Station was removed from all lines." << endl;
}


// Function that splits the command given by the user into pieces, checks if the input
// is valid and makes right things happen. The parameter is a strings vector created by
// the split function. This is a horrible if-structure-jungle,
// but making tons of small functions is not my cup of tea.
void command_center(vector<string> param){

    // Transforms all the letters in the command to lowercase letters.
    // Found from internet.
    string command = param.at(0);
    transform(command.begin(), command.end(), command.begin(),
        [](unsigned char c){ return tolower(c); });

    if ( command == "lines" and param.size() == 1 ){
        print_lines();

    }else if ( command == "line" and param.size() == 2 ){

            if( rasse_map.find(param.at(1)) == rasse_map.end() ){
                cout<< "Error: Line could not be found." << endl;

            }else{               
                stations_in_line(param.at(1));
            }

    }else if ( command == "stations" and param.size() == 1 ){
        cout<< "All stations in alphabetical order:"<<endl;

        for( string station : stations ){
            cout<< station<< endl;
        }

    }else if ( command == "station" and param.size() == 2 ){

        if ( stations.find(param.at(1)) == stations.end() ){
            cout<< "Error: Station could not be found." << endl;

        }else{
            lines_station_is_in(param.at(1));
        }

    }else if (  command == "addline" and param.size() == 2 ){

            if( rasse_map.find(param.at(1)) != rasse_map.end() ){
                cout<< "Error: Station/line already exists." << endl;

            }else{              
                vector<string> stations_in_route = { };
                rasse_map.insert({param.at(1), stations_in_route});
                cout<< "Line was added." << endl;
            }

    }else if (  command == "addstation" and param.size() >= 3 ){

        if( rasse_map.find(param.at(1)) == rasse_map.end() ){
            cout<< "Error: Line could not be found." << endl;

        }else if ( is_already(param.at(1), param.at(2)) ){
            cout<< "Error: Station/line already exists."<< endl;

        }else{

            // If there is no third parameter (param.at(3)) or it is not included
            // in the list of stations at the specific line (param.at(1)), the station(param.at(2))
            // will be added in the back of the list.
            if ( param.size()==3 or not is_already(param.at(1), param.at(3)) ){
                rasse_map.at(param.at(1)).push_back(param.at(2));
                stations.insert(param.at(2));
                cout<< "Station was added."<< endl;

            }else{
                // Adds station into correct position and adds station
                // also in the set of stations.
                add_station(param.at(1), param.at(2), param.at(3));
                stations.insert(param.at(2));
            }
        }

    }else if( command == "remove" and param.size() == 2 ){

        if( stations.find(param.at(1)) == stations.end() ){
            cout<< "Error: Station could not be found." << endl;

        }else{
            remove_station(param.at(1));
            stations.erase(param.at(1));
        }

    }else{
        cout<< "Error: Invalid input."<< endl;
        }
}


// Short and sweet main.
int main()
{
    print_rasse();
    if(!read_file())
        return EXIT_FAILURE;
    while(true){
        vector<string> commands = ui_loop();
        if(commands.at(0) == "QUIT" or commands.at(0) ==  "quit"){
            break;
        }
        command_center(commands);
    }
    return EXIT_SUCCESS;
}
