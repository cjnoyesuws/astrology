#include <iostream>
#include "sqlite3pp.h"
#include <stdio.h>
#include <stdlib.h>
#include "ConfigLoader.h"
#include "TextManager.h"

using namespace std;

int main()
{
    main_config.load("/home/cnoyes/astrology/data/conf");
    printf(main_config.getConfigData().getDataDir().c_str());
    printf(main_config.getConfigData().getReportDb().c_str());
    TextManager *p = TextManager::GetManager(main_config.getConfigData());
    std::string str = "PLANETS";
    int rep = p->OpenText(str);
    std::string str2 = p->GetRegText(rep,4,5);
    printf(str2.c_str());
    delete p;
    return 0;
}
