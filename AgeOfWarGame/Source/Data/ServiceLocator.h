#pragma once

#include <stdexcept>

#include "Data/DataManager.h"

namespace ServiceLocator {
    inline DataManager* dataManager = nullptr;
    inline DataManager* GetDataManager() { return dataManager; }
    inline void SetDataManager(DataManager* dm) { dataManager = dm; }
}

namespace sl = ServiceLocator;