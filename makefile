target:main.o suffix.o NFA.o DFA.o MinDfa.o ismatch.o
		g++ -o target main.o suffix.o NFA.o DFA.o MinDfa.o ismatch.o
main.o:main.cpp suffix.h NFA.h DFA.h MinDfa.h ismatch.h
		g++ -c main.cpp
suffix.o:suffix.cpp suffix.h
		g++ -c suffix.cpp
NFA.o:NFA.cpp NFA.h
		g++ -c NFA.cpp
DFA.o:DFA.cpp DFA.h
		g++ -c DFA.cpp
MinDfa.o:MinDfa.cpp MinDfa.h
		g++ -c MinDfa.cpp
ismatch.o:ismatch.cpp ismatch.h
		g++ -c ismatch.cpp
clean:
		rm main.o suffix.o NFA.o DFA.o MinDfa.o ismatch.o