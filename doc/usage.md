# Használat {#usage}

## A program meghívása

### A program meghívása, és a segítség kiírása

    factolog -h

Kimenet:

    Program to compile factolog programs
    Usage:
    factolog [options] file
    Options:
    -d --dot            Also print dot output
    -n --no-blueprint   Don't print factorio blueprint
    -o --output   [arg] Write ouput to file instead of stdout
    -h --help           Display this help message
    -s --signals  [arg] Use the specified signal mapping. Has the format of sig[, sig]...

### A bemenet megadása

A bemenet egy fájlnév, vagy '-'. '-' esetén a program a bemenetet a standard bemeneten várja.

    factolog infile.fl

### Kimenet feldolgozása

A kimenet alapértelmezetten a standard kimenet. Ezt felül lehet írni a `-o` vagy `--output` kapcsolókkal. Ezek argumentuma a kimeneti fájlnév, vagy '-'. '-' a kimenet a standard kimenet. Ha a fájl már létezik, felülírásra kerül.

#### Dot kimenet

A dot kimenet kiírásához meg kell adni a `-d` vagy `--dot` kapcsolót. Ilyenkor a kimenet a megtervezett áramkör dot formában, mint cluster.

    factolog --dot infile.fl

#### Tervrajz kimenet

A tervrajz kiírása alapértelmezetten megtörténik, ha ez nem kívánt, ki lehet kapcsolni a `-n` vagy `--no-blueprint` kapcsolókkal.  
A tervrajz kimenet a Factorio-val kompatibilis JSON sztring. Ahhoz, hogy ez importálható legyen, el kell végezni a [megfelelő lépéseket](https://wiki.factorio.com/Blueprint_string_format). Ezek elvégzésének egy lehetséges módja (szükséges hozzá a `qpdf` csomag, ami a `zlib-flate` parancsot tartalmazza (Arch Linuxon)):

    printf "0%s\n" $(factolog test.fl | zlib-flate -compress=9 | base64)

A kimenet első sorai a megtervezett áramkörben a változó-jel összerendelések. Ezeket lehet befolyásolni a `-s` vagy `--signals` kapcsolókkal. Az többi sor a tervrajz sztring, amely már importálható. Ha rendelkezésre áll az `xsel` csomag, a tervrajz azonnal a vágólapra irányítható:

    printf "0%s\n" $(factolog test.fl | zlib-flate -compress=9 | base64) | xsel -ib

## Programok írása Factolog nyelven

A Factolog nyelv hasonlít a Verilog nyelvre, ami azonban merőben eltér a megszokott programozási nyelvektől, hiszen ezek hardverleíró nyelvek.

### Modulok

A program modulokból épül fel, minden modulnak van egy szinkronitása, egy neve, és be/kimenetei. Olyan modul, aminek nincsenek be/kimeneti hibás, hiszen akkor az sehogyan nem tud kapcsolatot létesíteni a külvilággal, így az teljesen felesleges. Jelenleg csak az aszinkoron (`async` modulok támogatottak.)  
Mineóden programban lennie kell egy `main` nevű modulnak, ez a legkülső modul, a főmodul.  
A modulok hivatkozhatnak egymásra, azaz kapcsolat lehet köztük, ez azonban nem lehet körkörös.

### Paraméterek

A moduloknak vannak be/kimeneteik, azaz paramétereik. A paramétereknek van irányuk, ez lehet bemeneti, vagy kimeneti. A modulok csatlakoztatásánál ezeket meg kell adni. A bemeneti és a kimeneti paraméterek is csak változókat kaphatnak.  
Példa két modullal (`main` és `add5`), amelyben a főmodul az `A` nevű bemeneti paraméterén megkapott számhoz egy almodul segítségével hozzáad ötöt, majd megszorozza kettővel, és az eredményt az `O` kimeneti paraméterén adja vissza a külvilágnak:

    async module main(in A, out O){
        //Átmeneti változó létrehozása az A+5 eredményének
        var tmp;

        //Modul csatlakoztatás
        add5(A, tmp);

        //Szorzás kettővel
        O = tmp*2;
    }

    //add5 modul definiálása
    //A paraméterek nevei lehetnek hosszabbak is
    async module add5(in A, out O){
        O = A+5;
    }

### Műveletek

A Factolog nyelvben jelenleg a következő műveletek elérhetők:

| Megnevezés       | Jelölés | Példa  | Eredmény | Megjegyzés                                                                                                       |
|------------------|---------|--------|----------|------------------------------------------------------------------------------------------------------------------|
| Összeadás        | `+`     | `5+2`  | `7`      |                                                                                                                  |
| Kivonás          | `-`     | `5-2`  | `3`      |                                                                                                                  |
| Bitenkénti ÉS    | `&`     | `5&2`  | `0`      |                                                                                                                  |
| Bitenkénti VAGY  | `\|`    | `5\|2` | `7`      |                                                                                                                  |
| Bitenkénti XOR   | `^`     | `5^2`  | `7`      |                                                                                                                  |
| Negálás          | `~`     | `~0`   | `1`      | A negálást csak 0-ra és 1-re értelmezi a program, így csak a legalsó bitet negálja                               |
| Szorzás          | `*`     | `5*2`  | `10`     |                                                                                                                  |
| Osztás           | `/`     | `5/2`  | `2`      | A C/C++ nyelvekhez hasonlóan az osztás egészek között zajlik, az osztás eredményének az egészrésze a végeredmény |
| Moduló           | `%`     | `5%2`  | `1`      |                                                                                                                  |
| Balra shiftelés  | `<<`    | `1<<2` | `4`      |                                                                                                                  |
| Jobbra shiftelés | `>>`    | `4>>2` | `1`      |                                                                                                                  |
| Hatványozás      | `**`    | `2**4` | `16`     |                                                                                                                  |

A műveletek között [precedencia](#Precedence) van, és zárójelezhetőek.

## Pédaprogramok

### NAND kapu

    async module NAND(in x, in y, out O){
        O = ~(x & y);
    }

### NOR kapu

    async module NOR(in x, in y, out O){
       O = ~(x | y);
    }

### RS flip-flop NAND kapukból

    async module NAND(in x, in y, out O){
        O = ~(x & y);
    }

    async module RS_FF(in NS, in NR, out Q, out NQ){
        NAND(NS, NQ, Q);
        NAND(Q, NR, NQ);
    }
