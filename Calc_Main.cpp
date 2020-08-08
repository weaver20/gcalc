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
        if(!input || output) {
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
            if(curr_line.empty()){
                throw EmptyInput();
            }
            if (curr_line == "reset") { // ********** RESET **********
                calc.reset();
            } else if (curr_line == "who") { // ********** WHO **********
                cout << calc << endl;
            } else if (startsWith(curr_line, "delete")) { // ********** DELETE **********
                std::string rest = trim(curr_line.substr(6));
                if(rest[0] != '('){
                    throw CommandNotInFormat();
                }
                std::string delete_candidate = curr_line.substr(curr_line.find('('));
                if (delete_candidate[delete_candidate.length() - 1] != ')') {
                    throw CommandNotInFormat();
                }
                delete_candidate = delete_candidate.substr(1);
                delete_candidate.pop_back();
                calc.delete_graph(trim(delete_candidate));
            } else if (startsWith(curr_line, "print")) { // ********** PRINT **********
                std::string rest = trim(curr_line.substr(5));
                if(rest[0] != '('){
                    throw CommandNotInFormat();
                }
                std::string print_candidate = curr_line.substr(curr_line.find('(') + 1);
                if (print_candidate[print_candidate.length() - 1] != ')') {
                    throw CommandNotInFormat();
                }
                print_candidate.pop_back();
                calc.getGraph(trim(print_candidate)).print(out);
            } else if (curr_line == "quit") { // ********** QUIT **********
                break;
            } else // ********** GRAPH NAME INSERTED **********
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
                    calc.addGraph(left_variable, Graph(literals));
                } else if (literals[0] == '!') {
                    calc.addGraph(left_variable, !calc.getGraph(trim(literals.substr(1))));
                } else {
                    if (findOperatorIndex(literals) == 0
                    or findOperatorIndex(literals) == literals.length() - 1) {
                        throw CommandNotInFormat();
                    }
                    size_t operator_index = findOperatorIndex(literals);
                    if (operator_index == std::string::npos) {
                        calc.addGraph(left_variable,
                                      calc.getGraph(trim(literals.substr(0, literals.length()))));
                    } else {
                        std::string g1, g2;
                        g1 = trim(literals.substr(0, operator_index));
                        g2 = trim(literals.substr(operator_index + 1));
                        calc.addGraph(left_variable,
                                      calc.calculate(g1, literals[operator_index], g2));
                    }
                }
            }
        }

        catch (InvalidFileName &e) {
            out << e.what();
        }

        catch (CommandNotInFormat &e) {
            out << e.what();
        }

        catch (AbsentGraph &e) {
            out << e.what();
        }

        catch (InvalidVertexName& e) {
            out << e.what();
        }

        catch (AssignmentOperatorAbsence &e) {
            out << e.what();
        }

        catch (InvalidGraphString &e) {
            out << e.what();
        }

        catch (InvalidGraphVariable& e) {
            out << e.what();
        }

        catch (SelfCircle& e) {
            out << e.what();
        }

        catch (SavedWordInserted& e) {
            out << e.what();
        }

        catch (GraphException& e) {
            out << e.what();
        }

        catch (CalcException &e) {
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

        /*  Calc calc;
          std:: string graph = "G1";
          Graph g("{v1, v2 | <v1, v2>}");
          calc.addGraph(graph, g);*/

        /*std::string str = "G1 = {v1, v2}";
        if(str.find('<') != std::string::npos){
            cout << "1" <<endl;
        }
        if(str.find('>') != std::string::npos){
            cout << "2" << endl;
        }
        return 0;*/
    }
}



































