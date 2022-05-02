# Precedencia {#Precedence}

A Factolog nyelvben 3 precedencia-szint van.  
A legmagasabb precedenciaszinten (azaz a legelőször végrehajtott művelet) a `**`, azaz a hatványozás az egyetlen művelet.  

A második precedenciaszinten (azaz a másodszor végrehajtott műveletek) a `*`, `/`, `%` `<<` és a `>>` áll, ahol a jelölések a C/C++ nyelvben megszokott műveleteket jelölik.  

A harmadik precedenciaszinten a `+`, `-`, `&`, `|`, `^` műveletek állnak, ahol a `^` a kizáró vagyot (XOR-t), a többi pedig a C/C++ nyelvben megszokott műveleteket jelölik.  

A műveletek zárójelezhetők, a matematikában megszokott módon viselkedik a kifejezés.
