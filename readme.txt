compile into main.exe (random testing):
    g++ main.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o main -std=c++20
    .\main.exe

tests:
    g++ tests.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o tests -std=c++20
    .\tests.exe

game:
    g++ game.cpp pointwell.cpp statblock.cpp playercharacter.cpp item.cpp itemmanager.cpp buff.cpp ability.cpp monster.cpp -o game -std=c++20
    .\game.exe
