/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

//the space between individual ints to patch
const unsigned char node_offset = 0x1B; 
//the beginning of the 2.1 part of the code, offset by the amount of nodes preceding it
const size_t base_address_21 = 0x10C582 - (node_offset * 0x10); 

/**
 * See README for a more in-depth explanation of what this does
 */
$execute {
	//This part of the code fixes misalignments introduced in update 2.0
    static const size_t addresses[] = {0x10C519, 0x10C534, 0x10C560};
    for(unsigned char i = 0; i < (sizeof(addresses) / sizeof(size_t)); i++){
    	auto res = Mod::get()->patch(reinterpret_cast<void*>(base::get() + addresses[i]), { i + (size_t)(0x0D) });
    }

    //This part of the code fixes misalignments introduced in update 2.1
    for(unsigned char i = 0x10; i < 53; i++){
        size_t address = (node_offset * i) + base_address_21;
    	auto res = Mod::get()->patch(reinterpret_cast<void*>(base::get() + address), { i });
    }

    //change check that checks whether 2.0 nodes should even be loaded
    auto res = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x10C35B), { 0x9 });
    //change check that checks whether 2.1 nodes should even be loaded
    res = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x10C558), { 0x35 });
}