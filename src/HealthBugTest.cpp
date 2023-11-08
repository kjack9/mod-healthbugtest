/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class HealthBugTest_AllCreatureScript : public AllCreatureScript
{
    public:
    HealthBugTest_AllCreatureScript()
        : AllCreatureScript("HealthBugTest_AllCreatureScript") { }

    void OnCreatureAddWorld(Creature* creature) override
    {
        if (creature->GetMap()->IsDungeon())
        {
            creature->SetMaxHealth(500);
        }
    }

    void OnAllCreatureUpdate(Creature* creature, uint32 /*diff*/) override
    {
        if (creature->GetMap()->IsDungeon())
        {

            Map* creatureMap = creature->GetMap();

            if (creature->GetMaxHealth() != creatureMap->GetPlayersCountExceptGMs() * 1000)
            {
                creature->SetMaxHealth(creatureMap->GetPlayersCountExceptGMs() * 1000);
            }
        }
    }
};

// Add all scripts in one
void AddHealthBugTestScripts()
{
    new HealthBugTest_AllCreatureScript();
}
