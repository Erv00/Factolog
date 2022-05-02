# Abstract Syntax Tree {#AST}

A bemenet feldolgozásának központi eleme az absztrakt szintakszisfa. Erről részletes leírás az [interneten](https://en.wikipedia.org/wiki/Abstract_syntax_tree) található, illetve egy rövid összefoglalás a program szempontjából alább olvasható.  

A fában minden cúcs egy [közös ősből](@ref factolog::TreeNode) származik, és pointereket tartalmaz a gyerekeire. A csúcsok típusa és a fa topológiája reprezentálja a bemenetet. A program ezt felépíti a bemenet alapján, majd ellenőrzi annak helyességét, és végül ebből állítja elő a dot illetve a tervrajz kimenetét.
