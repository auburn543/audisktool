CFLAGS = -c -Wall

project2 : main.o auDiskTool.o Configuration.o CommandLine.o Report.o
	g++ -g main.cpp auDiskTool.cpp Configuration.cpp CommandLine.cpp Report.cpp -o project2

main.o : main.cpp
	g++ ${CFLAGS} main.cpp

auDiskTool.o : auDiskTool.cpp auDiskTool.h
	g++ ${CFLAGS} auDiskTool.cpp

Configuration.o : Configuration.cpp Configuration.h
	g++ ${CFLAGS} Configuration.cpp

CommandLine.o : CommandLine.cpp CommandLine.h
	g++ ${CFLAGS} CommandLine.cpp

Report.o : Report.cpp Report.h
	g++ ${CFLAGS} Report.cpp 
