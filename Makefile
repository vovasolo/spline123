CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11 -fPIC
INCLUDES = -Isrc -Ilib -I/usr/include/eigen3 
PYINCLUDES = $(shell python3 -m pybind11 --includes)
ROOTINCLUDES = -I$(shell root-config --incdir)
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
OBJS = bsfit123.o bspline123d.o json11.o profileHist.o

spline: $(OBJS) wrap.o
	$(CXX) -shared -o spline.so $(OBJS) wrap.o

example: $(OBJS) example1d.o
	$(CXX) -o example1d $(OBJS) example1d.o $(ROOTLIBS)

json11.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) lib/json11.cpp
	
profileHist.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/profileHist.cpp

bspline123d.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/bspline123d.cpp
	
bsfit123.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/bsfit123.cpp

wrap.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $(PYINCLUDES) python/wrap.cpp
	
example1d.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $(ROOTINCLUDES) examples/example1d.cpp
	
clean:
	rm -f *.o

