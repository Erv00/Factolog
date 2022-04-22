/**
 * @file blueprint.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Factorio tervrajz
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef blueprint_H
#define blueprint_H

#include <map>
#include <string>
#include <vector>
#include "modules.h"
#include "combinator.h"

#include <memtrace.h>

/**
 * @brief Factorio tervrajz
 */
class Blueprint {
    const unsigned int POLE_REACH;  ///< A tápok lefedási mérete
    const unsigned int POLE_DIM;    ///< A tápok oldalainak hossza
    const std::string POLE_NAME;    ///< A tápok Factorio prototype neve
    std::string name;               ///< A tervrajz neve

    std::map<EID, Entity*> entities;    ///< A tervrajzban lévő elemek
    /**
     * @brief A tervrajzban lévő elemek.
     * 
     * Egy POLE_REACH x POLE_REACH méretű tömb, gyorsan lehet benne üres helyet keresni.
     * 
     */
    Entity **area;

    float x;    ///< A következő szabadnak vélt hely. Csak heurisztika
    float y;    ///< A következő szabadnak vélt hely. Csak heurisztika

    public:
    /**
     * @brief Új Blueprint létrehozása
     * 
     * @param reach A tápok lefedési mérete
     * @param dim A tápok oldalainak hossza
     * @param poleName A tápok Factorio prototype neve
     * @param module A modul amiből a tervrajz elkészítendő
     */
    Blueprint(const unsigned int reach, const unsigned int dim, const std::string poleName, const Module* module);
    
    /**
     * @brief Blueprint felszabadítása
     */
    ~Blueprint();
    
    /**
     * @brief Kapcsolatot teremt két kombinátor között
     * 
     * @param from A kimeneti kombinátor, vagy 0 a buszhoz 
     * @param to A bementei kombinátor, vagy 0 a buszhoz
     */
    void connect(EID from, EID to);

    /**
     * @brief Új elem hozzáadása
     * 
     * Beállítja az elem pozícióját
     * Az elem pozíciója a kapcsolatok kialakítása közben változhat
     * 
     * @param e A hozzáadandó elem
     * @return EID A hozáadott elem azonosítója
     */
    EID addEntity(Entity *e);
    
    /**
     * @brief Új elem hozzáadása
     * 
     * Beállítja az elem pozícióját.
     * Az elem pozíciója a kapcsolatok kialakítása közben változhat
     * 
     * @param e A hozzáadandó elem
     * @param x Az új X koordináta
     * @param y Az új Y koordináta
     * @return EID A hozáadott elem azonosítója
     */
    EID addEntity(Entity *e, float x, float y);

    /**
     * @brief Elem emozdítása
     * 
     * @warning A függvény nem ellenőrzi, hogy a hely szabad-e. Ez a hívó feladata!
     * 
     * @param e Az elmozdítandó elem
     * @param newPos Az új pozíció
     */
    void moveEntity(Entity *e, const Position& newPos);

    /**
     * @brief Új oszlapba viszi a heurisztikus értékeket
     */
    void openColumn(){y=0;x++;}

    /**
     * @brief Szabad hely keresése egy pozíció közelében
     * 
     * A megadott pozíció közelében keres szabad helyet floodfill-lel.
     * Az algoritmus a bal és fel irányokat preferálja, ez pusztán esztétikaiokokból van így.
     * 
     * @param pos A kívánt pozíció, a keresés kiindulópontja
     * @param maxDist Maximum távolság a kiindulópoziciótól
     * @param ignore Az első ignore találat átugrása
     * @return Position A legközelebbi szabad hely
     */
    Position getOpenPositionNear(const Position& pos, float maxDist, int ignore=0) const;

    /**
     * @brief Visszaadja az elemeket
     * 
     * @return const std::map<EID, Entity*>& Az összes eltárolt elem
     */
    const std::map<EID, Entity*>& getEntities() const {return entities;}

    /**
     * @brief A tervrajz neve
     * 
     * @return std::string A tervrajz neve
     */
    std::string getName() const {return name;}

    /**
     * @brief Meghatározza az adott helyen lévő elemet
     * 
     * @warning Ezzel lehet módosítani a táblát. A tábla konzisztenciájának megtartása a hívó feladata!
     * 
     * @param pos A vizsgált pozíció
     * @return Entity*& Referencia a helyre
     */
    Entity*& at(const Position& pos);

    /**
     * @brief Meghatározza az adott helyen lévő elemet
     * 
     * @param pos A vizsgált pozíció
     * @return Entity* const& Referencia a helyre
     */
    Entity* const & at(const Position& pos) const;

    /**
     * @brief Meghatározza, hogy az adott helyre elfér-e egy kombinátor
     * 
     * A kombinátorok mérete a Factorio-ból adódóan 1 széles 2 magas
     * 
     * @param pos A viszgálandó pozíció
     * @return true Ha oda elfér egy kombinátor
     * @return false Ha nem fér oda kombinátor
     */
    bool canCombinatorFit(const Position& pos) const;

    /**
     * @brief Terület kirajzolása debug célra
     * 
     * @param os A kimeneti stream
     */
    void printArea(std::ostream& os) const;
};

/**
 * @brief Tervrajz kiírása JSON formában
 * 
 * @param os A kimeneti stream
 * @param bp A kiírandó tervrajz
 * @return std::ostream& A kimeneti stream
 */
std::ostream& operator<<(std::ostream& os, const Blueprint& bp);

#endif //blueprint_H
