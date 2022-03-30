/**
 * @file modules.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Modulokkal kapcsolatos osztályok
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef modules_H
#define modules_H

#include "treenode.h"
#include "asyncExpression.h"
#include "parameters.h"
#include "identifier.h"
#include <vector>

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

    /**
     * @brief Optimalizálja a modul kifejezéseit, ha lehet
     */
    virtual void optimize() = 0;
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

    /**
     * @brief Optimalizálja a modul kifejezéseit, ha lehet
     */
    void optimize();
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

#endif //modules_H
