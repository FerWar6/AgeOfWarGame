#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>


#ifdef DEBUG_MODE
#define DebugLn(msg) \
        std::cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << " in " << __func__ << "(): " << msg << std::endl;
#else
#define DebugLn(msg) 
#endif

#endif 
