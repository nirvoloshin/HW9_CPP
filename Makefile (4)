CXX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -std=c++11 
EXEC = firewall.exe
CPPS = string.cpp field.cpp ip.cpp port.cpp
HEADERS = string.h ip.h port.h field.h
RM = rm -rf *.o libfirewall.so firewall.exe

###### Rules #######

all:firewall

libfirewall.so: $(CPPS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -fpic -shared $(CPPS) -o libfirewall.so

firewall: libfirewall.so string.cpp field.cpp ip.cpp port.cpp 
	$(CXXLINK) $(CXXFLAGS) main.cpp -o firewall.exe -lfirewall -linput -L.

clean:
	$(RM) 



