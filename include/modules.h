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
#include <memtrace.h>

class CompilationUnit;
class LinkingUnit;

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
    virtual ~Module();

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

    /**
     * @brief Felépíti a modul szín-fáját
     * 
     * @param lu A színezési egység
     * @param expectedOut Elvárt kimenetek listája
     * @param inputs Bemeneti paraméterek színei
     */
    virtual void calcualteColorTree(LinkingUnit* lu, Color expectedOut[], Color inputs[]) = 0;

    /**
     * @brief Definiált változók újraösszegzése
     * 
     * @todo Máshol elvégezni
     * 
     * @return std::vector<Identifier> A definiált változók
     */
    virtual std::vector<Identifier> recalculateDefinedVariables() = 0;
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
    void calcualteColorTree(LinkingUnit* lu, Color expectedOut[], Color inputs[]);

    /**
     * @brief Visszaadja a modul utasításainak másolatát a megfelelő fordításokkal
     * 
     * @param translation Régi-új változóneév hozzárendelések
     * @return std::vector<AsyncExpression*> A modul utasításainak fordított másolata
     */
    std::vector<AsyncExpression*> linkModule(const Translator& translation) const;
    
    /**
     * @brief Feloldja a modul csatlakozás parancsait
     * 
     * A függvény után a modul nem tartalmaz csatlakozás parancsokat
     * 
     * @param modules Az összes definiált modul
     * @return AsyncModule* A modul
     */
    AsyncModule* link(std::map<const Identifier, Module*>& modules);

    EID addToBlueprint(Blueprint& bp) const;

    std::vector<Identifier> recalculateDefinedVariables();
};

/**
 * @brief Modul csatlakoztatás
 */
class ModuleConnection : public AsyncExpression {
    Identifier *identifier;     ///<Csatlakoztatott modul
    ParameterList *parameters;  ///<Csatlakozás paraméterei

    /**
     * @brief Új ModuleConnection létrehozása
     */
    ModuleConnection(){}
    
    public:
    /**
     * @brief Új ModuleConnection létrehozása
     * 
     * @param mc A másolandó kapcsolat
     */
    ModuleConnection(const ModuleConnection& mc);

    AsyncExpression* clone() const {return new ModuleConnection(*this);}

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

    /**
     * @brief Visszadaja a csatlakoztatt modul azonosítóját
     * 
     * @return const Identifier* A csatlakoztatott modul azonosítója
     */
    const Identifier* getIdentifier() const {return identifier;}

    /**
     * @brief Visszadaja a csatlakoztatt modul azonosítóját
     * 
     * @return Identifier* A csatlakoztatott modul azonosítója
     */
    ParameterList* getParameters() {return parameters;}

    void translate(const Translator& translation);
};

#endif //modules_H
