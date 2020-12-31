spellCheck.exe: spellCheck.o hash.o
		g++ -o spellCheck.exe spellCheck.o hash.o

spellCheck.o: spellCheck.cpp hash.h
		g++ -c spellCheck.cpp

hash.o: hash.cpp hash.h
		g++ -c hash.cpp

debug:
		g++ -g -o p1Debug.exe spellCheck.cpp hash.cpp

clean:
		rm -f *.exe *.o *.stackdump *~

backup:
		test -d backups || mkdir backups
			cp *.cpp backups
				cp *.h backups
				
p:
		chmod a+rx *.txt

