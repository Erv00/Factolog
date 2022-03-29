/**
 * @file mathLexemes.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Matematikai lexémák
 * @version 0.1
 * @date 2022-03-24
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef mathLexemes_H
#define mathLexemes_H

#include "lexer.h"
#include "treenode.h"

#include <memtrace.h>

/**
 * @brief Base class az értéket hordozó osztályoknak 
 */
class ValueExpression : public TreeNode {
    public:
    /**
     * @brief Value Expression felszabadítása
     */
    virtual ~ValueExpression(){};
}; 

/**
 * @brief 2 operandusú műveletek base class-a
 */
class BinaryExpression : public ValueExpression {
    protected:
    ValueExpression* left;  ///<Bal oldal
    ValueExpression* right; ///<Jobb oldal

    public:
    /**
     * @brief Új BinaryExpression létrehozása
     */
    BinaryExpression():left(NULL),right(NULL){}
    
    /**
     * @brief BinaryExpression felszabadítása
     */
    virtual ~BinaryExpression(){
        delete left;
        delete right;
    };

    /**
     * @brief Szemantika ellenőrzést végez
     * 
     * Ellenőrzött tulajdonságok:
     * @li A bal és jobb oldal helyessége
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const{
        left->checkSemantics(cu);
        right->checkSemantics(cu);
    }
};

/**
 * @brief Egyes precendenciaszintű művelet 
 * @sa Precedence
 */
class Expression : public BinaryExpression {
    public:
    /**
     * @brief Egyes precedenciaszintű műveletek
     * @sa Precedence
     */
    enum BinaryOperator {
        PLUS, MINUS, AND, OR, XOR
    };

    private:
    enum BinaryOperator op; ///<Végzendő művelet

    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ValueExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ValueExpression* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};

/**
 * @brief Kettes precedenciaszintű művelet
 * @sa Precedence
 */
class Term : public BinaryExpression {
    public:
    /**
     * @brief Kettes precedenciaszintű műveletek
     * @sa Precedence
     */
    enum BinaryOperator {
        MUL, DIV, MOD, LSHIFT, RSHIFT
    };

    private:
    enum BinaryOperator op; ///< Elvégzendő művelet

    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ValueExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ValueExpression* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};

/**
 * @brief Harmadik precedenciaszintű művelet
 * 
 * Ezen a precedenciaszinten csak a hatványozás (**) áll
 * 
 * @sa Precedence
 */
class Factor : public BinaryExpression {
    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ValueExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ValueExpression* parse(Lexer& lex);

    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};

/**
 * @brief Unáris operátor
 */
class UnaryExpression : public ValueExpression {
    public:
    /**
     * @brief Unáris operátorok
     */
    enum Operator {PLUS, MINUS, NOT};
    enum Operator op;       ///<Elvégzendő művelet
    ValueExpression *expr;  ///<Kifejezés, amire alkalmazni kell az operátort

    /**
     * @brief Új UnaryExpression létrehozása
     */
    UnaryExpression(){op=PLUS;expr=NULL;};

    /**
     * @brief UnaryExpression felszabadítása
     */
    ~UnaryExpression(){delete expr;};


    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return ValueExpression* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static ValueExpression* parse(Lexer& lex);

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
     * @li A kifejezés
     * 
     * @param cu A fordítási egység
     */
    void checkSemantics(CompilationUnit& cu) const;
};

/**
 * @brief Érték
 */
class Value : public ValueExpression {
    public:
    /**
     * @brief Value felszabadítása
     */
    virtual ~Value(){};

    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Value* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */
    static Value* parse(Lexer& lex);
};

/**
 * @brief Konstans számérték
 */
class Number : public Value {
    int value;  ///<Szémkonstans

    /**
     * @brief Új Number létrehozása
     * @param val A számkonstans
     */
    Number(int val):value(val){};

    public:
    /**
     * @brief Tokenek értelmezése 
     * 
     * @param lex Tokeneket tartalmazó lexer
     * @return Number* A tokenekből előállított @ref AST
     * @sa @ref AST 
     */

    static Number* parse(Lexer& lex);
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    std::ostream& printDot(std::ostream& os) const;
};

#endif //mathLexemes_H
