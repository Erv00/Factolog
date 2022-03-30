/**
 * @file parameters.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Paraméterekkel kapcsolatos osztályok
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef parameters_H
#define parameters_H

#include "treenode.h"
#include "lexer.h"
#include "valueExpression.h"
#include "identifier.h"

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


#endif //parameters_H
