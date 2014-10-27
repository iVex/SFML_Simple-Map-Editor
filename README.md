SFML_Simple-Map-Editor
======================

Compiled with Visual C++ 2012 and SFML 2.1
<br/>
Screenshot:<br/>
![Alt text](http://i.imgur.com/tqg8kww.png "Screenshot without borders")
<br/>
Working on linux: <br/>
![Alt text](http://i.imgur.com/5H4YtvM.png "Xubuntu")

## Usage on linux:
In Commands.h, change:
` #include "dirent.h" `
by:
` #include <dirent.h> `
<br/><br/>
Then in Map.cpp, change:
` _map[i][n] = std::stoi(word); `
by:
` _map[i][n] = stoi(word); `
(Or add `using namespace std;` on top of the file)
<br/><br/>
Compile and run using:
```
g++ -std=c++0x *.cpp -o sfml-editor -lsfml-graphics -lsfml-window -lsfml-system
./sfml-editor
```