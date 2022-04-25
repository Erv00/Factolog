# Házi feladat

Programozás alapjai 2  
Specifikáció  
Pektor Ervin  
GR7EK7  
2022. április 22.

# Pontosított feladatspecifikáció

A feladat egy Verilog-szerű hardverleíró nyelv (innentől Factolog) készítése. A nyelvnek csak aszinkron hálókkal kell tudnia dolgozni. A bemenet egy szöveges fájl, amely factolog nyelven írt programot tartalmaz, a kimenet a megtervezett hardver absztrakt szintaxisfája dot nyelven és/vagy a [Factorio](https://www.factorio.com/) nevű játékhoz tervrajz tömörítés és kódolás nélkül.

## Specifikáció

### Nyelv felépítése

A nyelvnek a felépítése a következő:

    main := async_module+

    async_module := "async module" identifier "(" parameter_list_declaration? "){" async_expression+ "}"

    identifier := (\alpha | "_") (\alnum | "_")*

    async_expression := var_declaration | module_connection | assignment

    var_declaration := "var" identifier ("," identifier)* ";"
    module_connection := identifier "(" parameter_list ");"
    assignment := identifier "=" expression ";"

    parameter_list_declaration := direction identifier ("," direction identifier)*;
    direction := "in" | "out"

    parameter_list := value ("," value)*


    expression := term ( ("+" | "-" | "&" | "|" | "^") term )*
    term := factor ( ("*" | "/" | "%" | "<<" | ">>") factor )*
    factor := unary_expression ( "**" unary_expression )*
    unary_expression := unary_operator? ( "(" expression ")" | value )

    value := \num | identifier

    binary_operator := "+" | "-" | "*" | "/" | "%" | "<<" | ">>" | "&" | "|" | "^"

    unary_operator := "~" | "-" | "+"

Ahol a literálisok idézőjelek között vannak, `*`-gal jelzett lexémák nullszor vagy többször szügségesek, a `+`-szal jelzettek legalább egyszer. A zárojelek csoportosításra szolgálnak. A `|` a VAGY utasítás, vagy a bal oldali lexéma vagy a jobboldali lexémát várja. A `<<` illetve `>>` shiftelést, a `%` modulo, a `^` XOR műveleteket jelölnek. A programban a `//` jelektől a sor végéig tartó kommentet jelöl.

## Factorio tervrajz

A tervrajzak kompatibilisnek kell lennie a [Factorio](https://www.factorio.com/) nevű játékkal. A tervrajzok részletes leírása [itt](https://wiki.factorio.com/Blueprint_string_format) található.

## IO

A programnak parancssorból kell működnie és képesnek kell lennie mind fájlból, mind a standard bemenetről olvasnia. A kimenetet fájlba, vagy a standard outra kell kiírni. A kimenetek között kapcsolókkal lehet váltani.

## Hibakezelés

A programnak tudnia kell kezelni a hibás bemeneteket, mind szintaktikai, mind szemantikai értelemben. Hiba esetén a program figyelmezteti a programozót, majd kilép. A programnak nem kell tudnia kezelni a jelterjedési sebességből eredő problémákat.

## Testelés

A program tesztelésére unit teszteket kell készíteni. Ezeknek mind helyes és helytelen bemeneteket is tartalmazniuk kell. Integration tesztelést is kell végezni.

# Osztályok és kapcsolataik

Alább láthatóak az osztályok és az UML diagrammjaik. Az átláthatóság érdekében egyes diagrammok nem tartalmazzák az aggregációs nyilakat. A teljes UML diagramm [lejjebb](#összegző-uml-diagramm) megtekinthető.

## Token

Egy lexémát ábrázol. A Token osztály UML diagrammja:

![Token](plan/token.svg)

## Lexer

A bemenet lexikai feldolgozásáért a Lexer osztály felel. Ez lexémákra, azaz a legkisebb értelmes részekre bontja a bemenetet. A Lexer osztály UML diagrammja:

![Lexer](plan/lexer.svg)

## TreeNode

A program legfontosabb része az Absztrakt szintaxisfa. Ennek a reprezentálására a TreeNode osztály és leszármazottai adnak lehetőséget. Ezek UML diagrammja:

![TreeNode és leszármazottjai](plan/tree_node.svg)


## CompilationUnit

A CompilationUnit osztály a bemenet szemantikai ellenőrzésére szolgál. Tartalmazza többek között a változókat, és azok állapotát. A CompilationUnit UML diagrammja:

![CompilationUnit](plan/compilation_unit.svg)

## LinkingUnit

Ez az osztály a modulhivatkozások feloldásáért és a jelütközések elkerüléséért felel. A LinkingUnit osztály UML diagrammja:

![LinkingUnit](plan/linking_unit.svg)

## Translator

A LinkingUnit mellett a Translator is fontos szerepet játszik a modulhivatkozások fordításában. Ez az osztály az azonosítók egyediségét biztosítja, és a fordításért felelős. A Translator osztály UML diagrammja:

![Translator](plan/translator.svg)

## Compiler

A fordítási folyamatot a Compiler osztály foglalja össze. A fomalyamat részletes leírásáról [később](#algoritmus) lesz szó. A Compiler osztály UML diagrammja:

![Compiler](plan/compiler.svg)

## Entity, Pole, ArithmeticCombinator

A Factorio tervrajzok elemeit (a Factorio dokumentáció szerint ```Entity```, de a program csak azok leszármazottait, az elemeket kezeli) az Entity osztály írja le. Ezen belül is csak két típussal foglalkozik a program, amelyeket a Pole és Combinator osztályok valósítanak meg. A Pole áramot és közös bemenet-teret biztosít a kombinátoroknak, amelyek a műveleteket végzik. Ezen osztályok UML diagrammja:

![Entity, Pole, Combinator](plan/entity_pole_combinator.svg)

## Signal

A különböző elemek közötti kapcsolatokért felelős osztály. A Signal osztály UML diagrammja:

![Signal](plan/signal.svg)

## Blueprint

A Factorio tervjazot reprezentáló osztály. A tervrajz felépítéséért felel. A Blueprint osztály UML diagrammja:

![Blueprint](plan/blueprint.svg)

## Összegző UML diagramm

A program teljes UML diagrammja:
![CompleteUML](plan/complete.svg)

## Hibakezelés

A program sokféle hibába ütközhet, ezek rövid leírása és UML diagrammja alább látható:

| Osztály                     | Leírás                                                      |
|-----------------------------|-------------------------------------------------------------|
| TokenExpectedError          | Adott tokent várt a programm                                |
| UnableToRepresentError      | A megadott konstans túlcsordulást okoz                      |
| UnexpectedSympolError       | Másik tokent kapott a program, mint várt                    |
| EmptyParameterListError     | A modulnak nincsenek paraméterei                            |
| MismatchedParametersError   | A paraméterek száma vagy iránya nem egyezik az elvárttal    |
| ModuleAlreadyDefinedError   | Már létezik modul ilyen névvel                              |
| ModuleNotDefinedError       | Nem létezik ilyen modul                                     |
| UndefinedVariableError      | Ilyen változó nem létezik ebben a szkópban                  |
| VariableAlreadyDefinedError | Ilyen változó már létezik ebben a szkópban                  |
| VariableReassignmentError   | Ennek a változónak már volt értéke, azt nem lehet felülírni |

A hibákat leíró osztályok UML diagrammja:

![Errors](plan/exceptions.svg)


# Algoritmus

Mivel a nyelv egy [LL(1)](https://en.wikipedia.org/wiki/LL_parser) nyelv, az absztrakt szintaxisfa felépítéséhez a program egy [rekurzívan leszálló elemzőt](https://en.wikipedia.org/wiki/Recursive_descent_parser) használ.   
A program előszőr lexémákra (```Token```) bontja a bemenetet, majd a [megadott](#nyelv-felépítése) nyelvtan szabályait követve feldolgozza azt. A 'main' lexémával kezdi, ami maga a program. Utána (a pluszjel miatt) egy vagy több 'async_module'-t vár. A program megkeresi a nyelvtanban az 'async_module' definícióját, majd annak megfelelően dolgozza fel a következő tokeneket. Így bejárja a nyelvtan elemeit, és ha eljut egy terminálisig, akkor azt feldolgozza és visszadja. Mivel a program több mudult tartalmazhat, valójában nem fa, hanem erdő a futás végeredménye, amelyben minden modul külön fa.

Az áramkörök szintetizálása egy ma is aktív kutatási terület. A programnak nem célja hogy a legjobb áramkört generálja, elég ha működik.  
Az absztrakt szintaxisfa felépítése után a program szemantikailag ellenőrzi a programot. Ebben a lépésben sokmindent megvizsgál, többek között, hogy a modulhívások feloldhatóak-e.  
A szemantikai ellenőrzést követi a fa optimalizálása. A program képes a műveleteket elvégezni, ha azok csak konstansok között vannak.  
A szintetizálás a következő lépés. A 'main' modulból kiindulva a program sorra veszi a modul utasításait. Ha modulhivatkozást talál, lecseréli azt a hivatkozott modul utasításaira és azokban a változóneveket lecseréli a megfelelőekre. Az új utasítások a lista végére kerülnek. Ha a program a lista végére ér, akkor már csak elemi utasítások vannak a fában. A program az aritmetikai műveleteket aritmetikai kombinátorokra (műveletvégző egységegre) cseréli, és megpróbálja őket elhelyezni a tervrajzban. Fontos, hogy az összeköttetések csak megadott hosszúságuak lehetnek. A kapcsolatok kiépítésekor a program ezt vizsgálja, és ha nem teljseíthető a program megpróbál egy jobb helyet keresni az adott kobinátornak. Ehhez kiszámítja a kívánt helyet a kapcsolatok végpontjainak átlagolásával, majd onnan egy floodfill algoritmussal bejárja a tervrajzot és helyet keres.  
Miután sikeresen elhelyezett és összekötött mindent, minden elemet átalakít JSON sztringgé, ami a program kimenete. Ezt [a megfelelő módon](https://wiki.factorio.com/Blueprint_string_format) kódolva megkapható a Factorio által is értelmezhető sztring.
