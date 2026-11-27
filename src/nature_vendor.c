// Pokémon Center service vendor (stands left of the counter in every Hoenn Pokémon Center).
// Service 1: free nature change. Writes the mon's hidden nature, which is the nature the game
// uses for stats, the summary screen, Synchronize, Everstone breeding and flavor likes, so the
// personality value (shininess, gender, Unown/Spinda/Wurmple forms) is never touched.
#include "global.h"
#include "event_data.h"
#include "list_menu.h"
#include "malloc.h"
#include "pokemon.h"
#include "script_menu.h"
#include "string_util.h"
#include "constants/pokemon.h"

static const u8 *const sStatAbbrevs[NUM_STATS] =
{
    [STAT_HP]    = COMPOUND_STRING("HP"),
    [STAT_ATK]   = COMPOUND_STRING("Atk"),
    [STAT_DEF]   = COMPOUND_STRING("Def"),
    [STAT_SPEED] = COMPOUND_STRING("Spe"),
    [STAT_SPATK] = COMPOUND_STRING("SpA"),
    [STAT_SPDEF] = COMPOUND_STRING("SpD"),
};

// Reads party slot VAR_0x8004. Puts its current nature in VAR_0x8005 and the name in gStringVar2.
void NatureVendor_BufferCurrentNature(void)
{
    u32 nature = GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_HIDDEN_NATURE);
    gSpecialVar_0x8005 = nature;
    StringCopy(gStringVar2, gNaturesInfo[nature].name);
}

// Pushes all 25 natures onto the dynmultichoice stack as "Adamant  +Atk -SpA", id = nature.
void NatureVendor_PushNatureOptions(void)
{
    u32 i;
    for (i = 0; i < NUM_NATURES; i++)
    {
        struct ListMenuItem item;
        u8 *name = Alloc(32);
        u8 *end = StringCopy(name, gNaturesInfo[i].name);
        if (gNaturesInfo[i].statUp != gNaturesInfo[i].statDown)
        {
            end = StringAppend(end, COMPOUND_STRING(" +"));
            end = StringAppend(end, sStatAbbrevs[gNaturesInfo[i].statUp]);
            end = StringAppend(end, COMPOUND_STRING(" -"));
            StringAppend(end, sStatAbbrevs[gNaturesInfo[i].statDown]);
        }
        item.name = name;
        item.id = i;
        MultichoiceDynamic_PushElement(item);
    }
}

// Puts the name of nature VAR_0x8006 in gStringVar2.
void NatureVendor_BufferNewNature(void)
{
    StringCopy(gStringVar2, gNaturesInfo[gSpecialVar_0x8006].name);
}

// Gives party slot VAR_0x8004 nature VAR_0x8006 and recalculates its stats right away.
void NatureVendor_SetNature(void)
{
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    u32 nature = gSpecialVar_0x8006;
    if (nature >= NUM_NATURES)
        return;
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);
    CalculateMonStats(mon);
}
