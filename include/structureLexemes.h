/**
 * @file structureLexemes.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Strukturális lexémák
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef lexemes_H
#define lexemes_H

#include <vector>

#include "treenode.h"
#include "lexer.h"
#include "mathLexemes.h"

#include <memtrace.h>

class AsyncExpression;
class ParameterListDeclaration;
class ParameterList;

/**
 * @brief Kapcsolat hoz létre a két objektum között
 * 
 * @param os Kimeneti stream
 * @param from Kapcsolat kiindulása
 * @param to Kapcsolat végpontja
 * @return std::ostream& Kimeneti stream
 */
std::ostream& dotConnection(std::ostream& os, const void *from, const void *to);

/**
 * @brief Csomópont létrehozása megadott paraméterekkel
 * 
 * @param os Kimeneti stream
 * @param obj Objektum
 * @param label Csomópont címkéje
 * @param style Csomópont stílusa
 * @return std::ostream& Kimeneti stream
 */
std::ostream& dotNode(std::ostream& os, const void *obj, const char *label, const char *style);


/**
 * @brief Azonosító
 */
class Identifier : public Value{
    std::string name;   ///<Az azonosító neve

    /**
     * @brief Új Identifier létrehozása
     * @param name Az azonosító neve 
     */
    Identifier(std::string name):name(name){};

    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Identifier* A tokenekből előállított @ref AST
     * @sa @ref AST 
     * @throws UnexpectedSymbolError Ha a következő Token nem érvényes azonosító
     */
    static Identifier* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Az azonosító neve
     * 
     * @return std::string& Az azonosító neve
     */
    const std::string& getName()const {return name;};

    /**
     * @brief Összehasonlít két azonosítót
     * 
     * @param b A másik azonosító
     * @return true Ha betűrendben b később van
     * @return false Egyébként
     */
    bool operator<(const Identifier& b) const{
        return name < b.name;
    }

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A változó létezése
     * @li A változónak már van értéke (Erre csak figyelmeztetés van)
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Aszinkron kifejezés
 */
class AsyncExpression : public TreeNode {
    public:
    /**
     * @brief AsyncExpression felszabadítása
     */
    virtual ~AsyncExpression(){};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return AsyncExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static AsyncExpression* parse(Lexer& lex);
};

/**
 * @brief Változó(k) deklarálása
 */
class VariableDeclaration : public AsyncExpression {
    std::vector<Identifier*> varsDeclared;  ///<Deklarált változók

    public:
    /**
     * @brief VariableDeclaration felszabadítása
     */
    ~VariableDeclaration(){
        for(size_t i=0; i<varsDeclared.size(); i++)
            delete varsDeclared[i];
    }

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return VariableDeclaration* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static VariableDeclaration* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A változók nem létezése
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Értékadás
 */
class Assignment : public AsyncExpression {
    Identifier *to;         ///<Az értéket kapó változó
    ValueExpression *val;   ///<A kapott érték

    public:
    /**
     * @brief Assignment felszabadítása
     */
    ~Assignment(){delete to; delete val;};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Assignment* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static Assignment* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Semantikailag ellenőrzi az egyenlőségadást
     * 
     * Ellenőrzött tulajdonságok:
     * @li Baloldal létezik
     * @li Jobboldal helyes
     * @li Van-e már a baloldalhoz rendelve érték
     * 
     * @param cu Fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Modul paraméter
 */
class Parameter : public TreeNode {
    public:
    /**
     * @brief Paraméter iránya
     */
    enum Direction {IN, OUT};
    
    private:
    enum Direction direction;   ///<Paraméter iránya
    Identifier* identifier;     ///<Paraméter neve
    
    public:
    /**
     * @brief Parameter felszabadítása
     */
    ~Parameter(){delete identifier;};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Parameter* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static Parameter* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Visszaadja a paraméter irányát
     * 
     * @return enum Direction A paraméter iránya
     */
    enum Direction getDirection() const {return direction;}
    
    /**
     * @brief Visszadja a paraméter azonosítóját
     * 
     * @return const Identifier* A paraméter azonosítója
     */
    const Identifier* getIdentifier() const {return identifier;}
};

/**
 * @brief Paraméterlista
 */
class ParameterList : public TreeNode {
    std::vector<ValueExpression*> parameters;    ///< Paraméterek nevei
   
    public:
    /**
     * @brief ParameterList felszabadítása
     */
    ~ParameterList(){
        for(size_t i=0; i<parameters.size(); i++)
            delete parameters[i];
    };

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ParameterList* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */

    static ParameterList* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Visszaadja a megadott paraméterek számát
     * 
     * @return size_t A megadott paraméterek száma
     */
    size_t length() const {return parameters.size();}

    /**
     * @brief Visszaadja az idx-edik paramétert
     * 
     * @param idx Index
     * @return const ValueExpression* Az idx-edik paraméter
     */
    const ValueExpression* operator[](size_t idx) const {return parameters[idx];}

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A paraméterek tulajdonságai
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Modul paramétereinek deklarálása 
 */
class ParameterListDeclaration : public TreeNode {
    std::vector<Parameter*> parameters; ///<Deklarált paraméterek
    
    public:
    /**
     * @brief ParameterListDeclaration felszabadítása
     */
    ~ParameterListDeclaration(){
        for(size_t i=0; i<parameters.size(); i++)
            delete parameters[i];
    }

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ParameterListDeclaration* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */

    static ParameterListDeclaration* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Visszaadja a lehetséges paraméterek számát 
     * 
     * @return size_t A lehetséges paraméterek száma
     */
    size_t length() const {return parameters.size();}

    /**
     * @brief Visszaadja az idx-edik paramétert
     * 
     * @param idx Index
     * @return const Parameter* Az idx-edik paraméter
     */
    const Parameter* operator[](size_t idx) const {return parameters[idx];}

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A paraméterek egyedisége
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Modul leírása
 */
class Module : public TreeNode {
    protected:
    Identifier* identifier;                 ///<Modul azonosítója
    ParameterListDeclaration* parameters;   ///<Modul paraméterei
   
    public:
    /**
     * @brief Module felszabadítása
     */
    virtual ~Module(){delete identifier;delete parameters;};

    /**
     * @brief Megadja a modul azonosítóját
     * 
     * @return const Identifier* A modul azonosítója
     */
    const Identifier* getIdentifier() const {return identifier;}

    /**
     * @brief Visszaadja a modul paraméterlistáját
     * 
     * @return const ParameterListDeclaration* A modul paraméterlistája
     */
    const ParameterListDeclaration* getParameters() const {return parameters;}
};

/**
 * @brief Aszinkron modul
 */
class AsyncModule : public Module {
    std::vector<AsyncExpression*> expressions;  ///<A modul kifejezései
    
    public:
    /**
     * @brief AsyncModule felszabadítása
     */
    ~AsyncModule(){
        for(size_t i=0; i<expressions.size(); i++)
            delete expressions[i];
    };

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return AsyncModule* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static AsyncModule* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A paraméterek tulajdonságai
     * @li A kifejezések
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Modul csatlakoztatás
 */
class ModuleConnection : public AsyncExpression {
    Identifier *identifier;     ///<Csatlakoztatott modul
    ParameterList *parameters;  ///<Csatlakozás paraméterei
    
    public:
    /**
     * @brief ModuleConnection felszabadítása
     */
    ~ModuleConnection(){delete identifier; delete parameters;};
    
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ModuleConnection* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ModuleConnection* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;

    /**
     * @brief Semantikailag ellenőrzi a csatlakozást
     * 
     * Ellenőrzött tulajdonságok:
     * @li Modul létezik
     * @li Paraméterek helyesek
     * 
     * @param cu Fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};
#endif //lexemes_H
