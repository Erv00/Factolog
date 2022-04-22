/**
 * @file entity.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Áramkörbe köthető elemek alaposztály
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef entity_H
#define entity_H

#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <memtrace.h>

#include "position.h"

class ValueExpression;

/**
 * @brief Elemek egyedi azonosítója
 */
typedef unsigned int EID;

/**
 * @brief Áramkörbe köthető elem
 * 
 * Az áramkör a Factorio "Circuit Network"-jére vonatkozik
 * 
 */
class Entity {
    protected:
    EID id;                     ///< Az elem azonosítója, 0-nál nagyobb
    std::string prototypeName;  ///< Factorio prototype neve
    Position pos;               ///< Pozíció
    unsigned int outSignal;     ///< A kimeneti jel színe
    unsigned int inSignal[2];   ///< A bemeneti jelek színei, lehet csak a 0.-at használja
    bool         inConst[2];    ///< Igaz, ha valamelyik operandus nem jel, hanem konstans
    const int reach;            ///< Összeköttetések maximum hossza

    std::vector<EID> outgoingRedConnections;    ///< Bejövő piros kapcsolatok
    std::vector<EID> incomingRedConnections;    ///< Kimenő piros kapcsolatok
    std::vector<EID> outgoingGreenConnections;  ///< Bejövő zöld kapcsolatok
    std::vector<EID> incomingGreenConnections;  ///< Kimenő zöld kapcsolatok

    static unsigned int GLOBAL_ENTITY_ID;   ///< Blueprint-en belül minden elemnek egyedi azonosító kell

    public:
    /**
     * @brief Új Entity létrehozása
     * 
     * @param pName Factorio prototípusnév
     * @param reach Összeköttetések maximum hossza
     * @param x X pozíció
     * @param y Y pozíció
     */
    Entity(std::string pName, int reach, float x = 0, float y = 0);

    /**
     * @brief Entity felszabadítása
     */
    virtual ~Entity(){}

    /**
     * @brief Bemenet megjelölése mint konstans
     * 
     * @param side A beállítandó jel indexe. A 0 a 'bal' bemenet
     * @param value A konstans értéke
     */
    void setConst(int side, unsigned int value);

    /**
     * @brief Pozíció beállítása
     * 
     * @param nX Új X koordináta
     * @param nY Új Y koordináta
     * @warning A Blueprint-ben tárolt helyzet frissítése a hívó feladata
     */
    void setPos(float nX, float nY){pos.x=nX; pos.y=nY;}

    /**
     * @brief Pozíció beállítása
     * 
     * @param p Az új pozíció
     * @warning A Blueprint-ben tárolt helyzet frissítése a hívó feladata
     */
    void setPos(const Position& p){setPos(p.x,p.y);}

    /**
     * @brief Új bejövő kapcsolat hozzáadása
     * 
     * @param from A kapcsolat kiindulópontjának azonosítója
     * @param red Igaz, ha a kapcsolat a piros hálózathoz van
     */
    void addIncomingConnection(EID from, bool red=true);

    /**
     * @brief Új kimenő kapcsolat hozzáadása
     * 
     * @param to A kapcsolat végpontjának azonosítója
     * @param red Igaz, ha a kapcsolat a piros hálózathoz van
     */
    void addOutgoingConnection(EID to, bool red=true);

    /*==================================================
                GETTERS
    ==================================================*/

    /**
     * @brief Visszaadja az elem azonosítóját
     * 
     * @return EID Az elem azonosítóját
     */
    EID getEID() const {return id;}

    /**
     * @brief Visszaadja a kapcsolatok maximum távolságát
     * 
     * @return int A kapcsolatok maximum távolságát
     */
    int getReach() const{return reach;}

    /**
     * @brief Visszaadja az elem pozícióját
     * 
     * @return Position& Az elem pozíciója
     */
    Position& getPosition() {return pos;}

    /**
     * @brief Visszaadja az elem pozícióját
     * 
     * @return const Position& Az elem pozíciója
     */
    const Position& getPosition() const {return pos;}

    /**
     * @brief Előről kezdi az egyedi azonosítók kiosztását
     */
    static void resetGlobalID() {GLOBAL_ENTITY_ID = 1;}

    /**
     * @brief Meghatározza a Factorio tervrajzban szereplő "connection" objektumot
     * 
     * Nem minden elemre van értelmezve, de a tervrajzban szerepelhet üresen is
     * 
     * @return std::string A "connection" objektum JSON formában
     */
    virtual std::string getConnectionString() const;

    /**
     * @brief Meghatározza az elem Factorio tervraját
     * 
     * @return std::string Az elem tervrajz objektuma JSON formátumban
     */
    virtual std::string toBlueprint() const = 0;

    /**
     * @brief Ellenőrzi az elem kapcsolatait
     * 
     * @param entities Az összes elem
     * @return true Igaz, ha egyik kapcsolat sem haladja meg a maximum hosszát
     * @return false Egyébként
     */
    bool checkConnections(const std::map<EID, Entity*>& entities) const;

    /**
     * @brief Ellenőrzi az elem kapcsolatait
     * 
     * @param entities Az összes elem
     * @param conns Az ellenőrizendő kapcsolatok
     * @return true Igaz, ha egyik kapcsolat sem haladja meg a maximum hosszát
     * @return false Egyébként
     */
    bool checkConnections(const std::map<EID, Entity*>& entities, const std::vector<EID>& conns) const;
    
    /**
     * @brief Megadja az elem által kívánt pozíciót
     * 
     * A kívánt pozícióban a kapcsoaltok összhossza minimális.
     * Ez a kapcsoaltok végpontjainak átlagolásával számítható ki
     * 
     * @param entities Az összes elem
     * @return Position A kívánt pozíció
     */
    Position getDesiredPosition(const std::map<EID, Entity*>& entities) const;
    
    /**
     * @brief Megadja a távolságot a másik elemhez
     * 
     * @param e A másik elem
     * @return float A távolság
     */
    float distanceTo(const Entity& e) const;

    /**
     * @brief Visszadja a kapcsolatok számát
     * 
     * @return int A kapcsolatok száma
     */
    int connections() const;
};


#endif //entity_H
