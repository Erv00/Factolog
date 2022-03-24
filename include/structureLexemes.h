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

std::ostream& dotConnection(std::ostream& os, const void *from, const void *to);
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
     * @return Identifier* A tokenekből előállított AST
     * @sa AST 
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
     * @return AsyncExpression* A tokenekből előállított AST
     * @sa AST 
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
     * @return VariableDeclaration* A tokenekből előállított AST
     * @sa AST 
     */
    static VariableDeclaration* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
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
     * @return Assignment* A tokenekből előállított AST
     * @sa AST 
     */
    static Assignment* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
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
     * @return Parameter* A tokenekből előállított AST
     * @sa AST 
     */
    static Parameter* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
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
     * @return ParameterList* A tokenekből előállított AST
     * @sa AST 
     */

    static ParameterList* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
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
     * @return ParameterListDeclaration* A tokenekből előállított AST
     * @sa AST 
     */

    static ParameterListDeclaration* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};

/**
 * @brief Modul leírása
 * 
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
     * @return AsyncModule* A tokenekből előállított AST
     * @sa AST 
     */
    static AsyncModule* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
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
     * @return ModuleConnection* A tokenekből előállított AST
     * @sa AST 
     */
    static ModuleConnection* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};
#endif //lexemes_H
