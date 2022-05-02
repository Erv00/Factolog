# Összefoglalás

Alább olvasható a feladatsepcifikáció, és az algoritmus felszínes összefoglalója.


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

A program parancssori használatra készült, bemeneteet képes mind a standard bemenetről, mind fájlból olvasni. A bemeneti fájlnevet meg kell adni, mint argumentum. Lehet fájlnév, vagy '-'. '-' esetén a standard bemenetről olvas.

A kimenetek között kapcsolókkal lehet váltani. A következő kapcsolók elérhetőek:

| Hosszú kapcsoló | Rövid kapcsoló | Argumentum      | Leírás                                                                   |
|-----------------|----------------|-----------------|--------------------------------------------------------------------------|
| --dot           | -d             |                 | Dot kimenet kiírása a standard kimenetre                                 |
| --no-blueprint  | -n             |                 | Letiltja a Factorio tervrajz kemenetet                                   |
| --output        | -o             | fájl vagy '-'   | A Factorio tervrajz kimenet kiírási célja. '-' esetén a standard kimenet |
| --help          | -h             |                 | Segítség és kapcsolók kiírása, majd kilépés                              |
| --signals       | -s             | jel0[, jel1]... | A fő modul bemeneteinek és kimeneteinek színeinek a beállítása           |

## Hibakezelés

A programnak tudnia kell kezelni a hibás bemeneteket, mind szintaktikai, mind szemantikai értelemben. Hiba esetén a program figyelmezteti a programozót, majd kilép. A programnak nem kell tudnia kezelni a jelterjedési sebességből eredő problémákat.

## Tesztelés

A program tesztelésére unit teszteket kell készíteni. Ezeknek mind helyes és helytelen bemeneteket is tartalmazniuk kell. Integration tesztelést is kell végezni.


# Algoritmus 

Mivel a nyelv egy [LL(1)](https://en.wikipedia.org/wiki/LL_parser) nyelv, az absztrakt szintaxisfa felépítéséhez a program egy [rekurzívan leszálló elemzőt](https://en.wikipedia.org/wiki/Recursive_descent_parser) használ.   
A program előszőr lexémákra (```Token```) bontja a bemenetet, majd a [megadott](nyelv-felépítése) nyelvtan szabályait követve feldolgozza azt. A 'main' lexémával kezdi, ami maga a program. Utána (a pluszjel miatt) egy vagy több 'async_module'-t vár. A program megkeresi a nyelvtanban az 'async_module' definícióját, majd annak megfelelően dolgozza fel a következő tokeneket. Így bejárja a nyelvtan elemeit, és ha eljut egy terminálisig, akkor azt feldolgozza és visszadja. Mivel a program több mudult tartalmazhat, valójában nem fa, hanem erdő a futás végeredménye, amelyben minden modul külön fa.

Az áramkörök szintetizálása egy ma is aktív kutatási terület. A programnak nem célja hogy a legjobb áramkört generálja, elég ha működik.  
Az absztrakt szintaxisfa felépítése után a program szemantikailag ellenőrzi a programot. Ebben a lépésben sokmindent megvizsgál, többek között, hogy a modulhívások feloldhatóak-e.  
A szemantikai ellenőrzést követi a fa optimalizálása. A program képes a műveleteket elvégezni, ha azok csak konstansok között vannak.  
A szintetizálás a következő lépés. A 'main' modulból kiindulva a program sorra veszi a modul utasításait. Ha modulhivatkozást talál, lecseréli azt a hivatkozott modul utasításaira és azokban a változóneveket lecseréli a megfelelőekre. Az új utasítások a lista végére kerülnek. Ha a program a lista végére ér, akkor már csak elemi utasítások vannak a fában. A program az aritmetikai műveleteket aritmetikai kombinátorokra (műveletvégző egységegre) cseréli, és megpróbálja őket elhelyezni a tervrajzban. Fontos, hogy az összeköttetések csak megadott hosszúságuak lehetnek. A kapcsolatok kiépítésekor a program ezt vizsgálja, és ha nem teljseíthető a program megpróbál egy jobb helyet keresni az adott kobinátornak. Ehhez kiszámítja a kívánt helyet a kapcsolatok végpontjainak átlagolásával, majd onnan egy floodfill algoritmussal bejárja a tervrajzot és helyet keres.  
Miután sikeresen elhelyezett és összekötött mindent, minden elemet átalakít JSON sztringgé, ami a program kimenete. Ezt [a megfelelő módon](https://wiki.factorio.com/Blueprint_string_format) kódolva megkapható a Factorio által is értelmezhető sztring.
