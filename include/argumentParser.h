/**
 * @file argumentParser.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief Parancssori kapcsolók feldolgozása
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef argumentParser_H
#define argumentParser_H

#include <vector>
#include <string>
#include <getopt.h>
#include <memtrace.h>

/**
 * @brief Adott kapcsolókhoz tartozó konfiguráció
 * 
 */
class Configuration {
    std::string inputFile;              ///< Bemeneti fájlnév
    std::string outFile;                ///< Kimenetei fájlnév
    std::vector<std::string> signals;   ///< Jelek nevei
    bool _printDot;                     ///< Kell dot kimenet?
    bool _printBlueprint;               ///< Kell blueprint kimenet?

    /**
     * @brief Átalakítja a hosszú kapcsolókat röviddé
     * 
     * @param long_options A hosszú kapcsolók listája NULL-al lezárva
     * @return std::string A kapcsolók rövid leírása
     */
    static std::string longOptionsToShort(const struct option long_options[]);
    
    /**
     * @brief Felbontja a sztringet ,-knél
     * 
     * @param str A felbontandó sztring
     * @return std::vector<std::string> A stringdarabok, trimmelve és a , nélkül
     */
    static std::vector<std::string> parseTranslation(const char* str);
    
    /**
     * @brief Kiírja a kapcsolókat, és hozzájuk a segítésget
     * 
     * @param options A kapcsolók
     * @param help A hozzájuk tartozó segítség
     * @return std::string A kiírandó sztring
     */
    static std::string printOptions(const struct option options[], const char* help[]);

    public:
    /**
     * @brief Új Configuration létrehozása
     * 
     * Az első argumentum nem kerül feldolgozásra, viszont a segítség kiírásához kell!
     * 
     * @param argc Az argumentumok száma
     * @param argv Az argumentumok
     */
    Configuration(int argc, char *argv[]);

    /**
     * @brief Visszaadja a bementei fájl nevét
     * 
     * @return std::string A bemeneti fájl neve
     */
    std::string getInputFile() const {return inputFile;}
    
    /**
     * @brief Visszaadja a kimeneti fájl nevét
     * 
     * @return std::string A kimeneti fájl neve
     */
    std::string getOutFile() const {return outFile;}

    /**
     * @brief Visszadja, hogy kérünk-e tervrajz kimenetet
     * 
     * @return true Ha kell tervrajz kimenet
     * @return false Egyébként
     */
    bool printBlueprint() const {return _printBlueprint;}
    
    /**
     * @brief Visszadja, hogy kell-e dot kimenet
     * 
     * @return true Ha kell dot kimenet
     * @return false Egyébként
     */
    bool printDot() const {return _printDot;}

    /**
     * @brief Visszadja a jeleket
     * 
     * @return std::vector<std::string> A jelek
     */
    std::vector<std::string> getSignals() const {return signals;}
};

#endif //argumentParser_H
