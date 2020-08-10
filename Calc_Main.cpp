#include "Calc_Main.h"
#include "Auxilaries.h"
#include "Calc.h"

using std::endl;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using namespace mtm;

int main(int argc, char* argv[]){
    if(BATCH_MODE){
        ifstream input(argv[1]);
        ofstream output(argv[2]);
        if(!input || !output) {
            std::cerr << OpenFileError().what();
            return 0;
        }
        start(input, output, BATCH);
    }
    else if(SHELL_MODE){
        start(cin, cout, INTERACTIVE);
    }
    else{
        std::cerr << RunError().what();
        return 0;
    }
    return 0;
}


void start(istream& in, ostream& out, Mode mode) {
    Calc calc;
    std::string curr_line;
    if (mode == INTERACTIVE) {
        out << "Gcalc>";
    }
    while (std::getline(in, curr_line)) {
        try {
            curr_line = trim(curr_line);
            // ********** Checking for empty input **********
            if(curr_line.empty()){
                throw EmptyInput();
            }
            // ********** RESET **********
            if (curr_line == "reset") {
                calc.reset();
            }
                // ********** WHO **********
            else if (curr_line == "who") {
                out << calc;
            }
                // ********** SAVE **********
            else if(startsWith(curr_line, "save")){
                std::string rest = trim(curr_line.substr(4));
                if(rest[0] != '(' or !endsWith(rest, ")")){
                    throw CommandNotInFormat();
                }
                rest.pop_back();
                rest = trim(rest.substr(1));
                size_t delimeter_pos = rest.find(',');
                if(delimeter_pos == std::string::npos){
                    throw CommandNotInFormat();
                }
                std::string graph_data = trim(rest.substr(0, delimeter_pos));
                std::string file_name = trim(rest.substr(delimeter_pos + 1));
                calc.save(calc.generate(graph_data), file_name);
                // ********** LOAD **********
            }
                // ********** DELETE **********
            else if (startsWith(curr_line, "delete")) {
                std::string rest = trim(curr_line.substr(6));
                if(rest[0] != '(' or endsWith(rest, ")")){
                    throw CommandNotInFormat();
                }
                std::string delete_candidate = curr_line.substr(curr_line.find('('));
                if (delete_candidate[delete_candidate.length() - 1] != ')') {
                    throw CommandNotInFormat();
                }
                delete_candidate = delete_candidate.substr(1);
                delete_candidate.pop_back();
                calc.delete_graph(trim(delete_candidate));
            }
                // ********** PRINT **********
            else if (startsWith(curr_line, "print")) {
                std::string rest = trim(curr_line.substr(5));
                if(rest[0] != '('){
                    throw CommandNotInFormat();
                }
                std::string print_candidate = curr_line.substr(curr_line.find('(') + 1);
                if (print_candidate[print_candidate.length() - 1] != ')') {
                    throw CommandNotInFormat();
                }
                print_candidate.pop_back();
                calc.generate(print_candidate).print(out);
            }
                // ********** QUIT **********
            else if (curr_line == "quit") {
                break;
            }
                // ********** GRAPH NAME INSERTED **********
            else
            {
                std::string left_variable, literals;
                size_t assignment_pos = curr_line.find('=');
                if (assignment_pos == std::string::npos) {
                    throw AssignmentOperatorAbsence();
                }
                left_variable = trim(curr_line.substr(0, assignment_pos));
                Calc::checkSavedFunction(left_variable);
                Calc::checkLeftVariable(left_variable);
                literals = trim(curr_line.substr(assignment_pos + 1));
                if (literals[0] == '{') {
                    calc.addGraph(left_variable, calc.generate(literals));
                }
                else if(literals[0] == '!'){
                    calc.addGraph(left_variable, calc.generate(literals));
                }
                else {
                    size_t operator_index = findOperatorIndex(literals);
                    if (operator_index == 0 or findOperatorIndex(literals) == literals.length() - 1) {
                        throw CommandNotInFormat();
                    }
                    // Assigning existing graph into another graph
                    if (operator_index == std::string::npos) {
                        calc.addGraph(left_variable,
                                      calc.getGraph(trim(literals.substr(0, literals.length()))));
                    } else {
                        std::string g1, g2;
                        g1 = trim(literals.substr(0, operator_index));
                        g2 = trim(literals.substr(operator_index + 1));
                        calc.addGraph(left_variable,
                                      calc.generate(literals));
                    }
                }
            }
        }

        catch (GraphException& e) {
            out << e.what();
        }

        catch (CalcException& e) {
            out << e.what();
        }

        catch (Exception& e) {
            out << e.what();
        }

        catch (std::bad_alloc &e) {
            std::cerr << "   FATAL ERROR: Allocation Failure! \n";
            break;
        }

        catch (...) {
            cout << "Error: Unknown Error 101. \n";
        }

        if (mode == INTERACTIVE) {
            out << "Gcalc>";
        }
    }
}


