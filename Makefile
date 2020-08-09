CC=/usr/local/bin/gcc
CXX = /usr/local/bin/g++
COMP_FLAG = -std=c++11 -Wall -Werror -g --pedantic-errors
LIB_FLAG = -I/usr/local/include/python3.6m -fPIC
DEBUG_FLAG = -DNDEBUG
ZIP_NAME = gcalc.zip
EXEC = graph
PY_EXEC = libgraph.a PythonInterface.o _graph.so graph_wrap.cxx
OBJS = Calc_Main.o Graph.o Calc.o Auxilaries.o Exception.o CalcException.o GraphException.o
LIB_OBJS = PythonInterface.o Graph.o GraphException.o Auxilaries.o Exception.o
PROJ_FILES = Auxiliaries.cpp Auxiliaries.h Calc.cpp Calc.h CalcExceptions.cpp CalcExceptions.h \
Exceptions.cpp Exceptions.h Graph.cpp Graph.h Grap	hCalc.cpp Calc_Main.h GraphException.cpp GraphException.h \
 PythonInterface.cpp PythonInterface.h Makefile graph.i

$(EXEC): $(OBJS)
	$(CXX) $(COMP_FLAG) $(DEBUG_FLAG) $(OBJS) -o $(EXEC)

Calc_Main.o: Calc_Main.cpp Calc_Main.h Graph.h Auxilaries.h Calc.h \
 GraphException.h Exception.h CalcException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o Calc_Main.o

Graph.o: Graph.cpp Graph.h Auxilaries.h Calc.h GraphException.h \
Exception.h CalcException.h
	$(CXX) -fPIC  -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o Graph.o

Calc.o: Calc.cpp Calc.h Auxilaries.h Graph.h GraphException.h \
 Exception.h CalcException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o Calc.o

Exception.o: Exception.cpp Exception.h
	$(CXX) -fPIC  -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o Exception.o

CalcException.o: CalcException.cpp CalcException.h Exception.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o CalcException.o

GraphException.o: GraphException.cpp GraphException.h Exception.h
	$(CXX)   -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o GraphException.o

Auxilaries.o: Auxilaries.cpp Calc_Main.h Graph.h Auxilaries.h Calc.h \
 GraphException.h Exception.h CalcException.h
	$(CXX)  -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) $^ -o Auxilaries.o

PythonInterface.o: PythonInterface.cpp PythonInterface.h Auxilaries.h Graph.h Calc.h \
 GraphException.h Exception.h CalcException.h
	$(CXX) -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) PythonInterface.cpp -o PythonInterface.o

libgraph.a: $(LIB_OBJS)
	ar -rs $@ $^

swig: libgraph.a
	swig -c++ -python -o graph_wrap.cxx graph.i
	$(CXX) -std=c++11 -Wall -Werror -g --pedantic-errors -DNDEBUG -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.cxx libgraph.a -o _graph.so

tar:
	zip $(ZIP_NAME) $(PROJ_FILES)

clean:
	rm -f $(OBJS) $(EXEC) $(PY_EXEC) $(ZIP_NAME) *.h.gch
