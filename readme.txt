compile into main.exe:
    g++ main.cpp -o main -std=c++20

compile into main.exe (multiple files):
    g++ main.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o main -std=c++20

run main.exe:
    .\main.exe

tests:
    g++ tests.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o tests -std=c++20
    .\tests.exe

game:
    g++ game.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o game -std=c++20
    .\game.exe
