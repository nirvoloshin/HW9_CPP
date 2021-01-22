CXX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -std=c++11 
EXEC = firewall.exe
CPPS = string.cpp field.cpp ip.cpp port.cpp
RM = rm -rf *.o libfirewall.so firewall.exe

###### Rules #######

all:firewall.exe

libfirewall.so: string.cpp field.cpp ip.cpp port.cpp
	$(CXX) $(CXXFLAGS) -shared $(CPPS) -o libfirewall.so

firewall.exe: libfirewall.so string.cpp field.cpp ip.cpp port.cpp 
	$(CXXLINK) $(CXXFLAGS) main.cpp -o firewall.exe -lfirewall -linput -L.

#Short syntax

string.cpp: string.h

ip.cpp: ip.h string.h field.h

port.cpp: port.h string.h field.h

field.cpp: field.h ip.h port.h string.h

clean:
	$(RM) 



