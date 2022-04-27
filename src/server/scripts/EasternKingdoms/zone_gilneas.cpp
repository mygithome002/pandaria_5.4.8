/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"

enum Gilneas
{
    SPELL_PING_GILNEAN_CROW                 = 93275,
    SPELL_SUMMON_RAVENOUS_WORGEN_1          = 66836,
    SPELL_SUMMON_RAVENOUS_WORGEN_2          = 66925,
    SPELL_SHOOT_INSTAKILL                   = 67593, // Visual problem
    SPELL_COSMETIC_ATTACK                   = 69873,
    SPELL_PULL_TO                           = 67357,
    SPELL_GET_SHOT                          = 67349,

    EVENT_START_TALK_WITH_CITIZEN           = 1,
    EVENT_TALK_WITH_CITIZEN_1               = 2,
    EVENT_TALK_WITH_CITIZEN_2               = 3,
    EVENT_TALK_WITH_CITIZEN_3               = 4,

    EVENT_START_DIALOG                      = 1,
    EVENT_START_TALK_TO_GUARD               = 2,
    EVENT_TALK_TO_GUARD_1                   = 3,
    EVENT_TALK_TO_GUARD_2                   = 4,
    EVENT_RESET_DIALOG                      = 5,

    PRINCE_LIAM_GREYMANE_TEXT_00            = 0,
    PRINCE_LIAM_GREYMANE_TEXT_01            = 1,
    PRINCE_LIAM_GREYMANE_TEXT_02            = 2,

    EVENT_JUMP_TO_PRISON                    = 1,
    EVENT_AGGRO_PLAYER                      = 2,
    EVENT_FORCE_DESPAWN                     = 3,

    EVENT_COSMETIC_ATTACK                   = 1,
    EVENT_JUMP_TO_PLAYER                    = 2,
    EVENT_SHOOT_JOSIAH                      = 3,

    PHASE_ROOF                              = 0,
    PHASE_COMBAT                            = 1,

    WORGEN_ID_ROOF_1                        = 0,
    WORGEN_ID_ROOF_2                        = 1,
    WORGEN_ID_ROOF_3                        = 2,
    WORGEN_ID_ROOF_4                        = 3,
    WORGEN_ID_ROOF_5                        = 4,
    WORGEN_ID_ROOF_6                        = 5,
    WORGEN_ID_ROOF_7                        = 6,

    WORGEN_ID_CATHEDRAL_1                   = 7,
    WORGEN_ID_CATHEDRAL_2                   = 8,
    WORGEN_ID_CATHEDRAL_3                   = 9,
    WORGEN_ID_CATHEDRAL_4                   = 10,
    WORGEN_ID_CATHEDRAL_5                   = 11,
    WORGEN_ID_CATHEDRAL_6                   = 12,
    WORGEN_ID_CATHEDRAL_7                   = 13,
    WORGEN_ID_CATHEDRAL_8                   = 14,
    WORGEN_ID_CATHEDRAL_9                   = 15,

    NPC_PANICKED_CITIZEN_GATE               = 44086,
    NPC_WORGEN_RUNT                         = 35456,
    NPC_WORGEN_RUNT_2                       = 35188,
    NPC_WORGEN_ALPHA                        = 35170,
    NPC_WORGEN_ALPHA_2                      = 35167,
    NPC_LORNA_CROWLEY                       = 35378,
    NPC_GENERIC_TRIGGER_LAB                 = 35374,

    SAY_JOSIAH_AVERY_1                      = 0,
    SAY_JOSIAH_AVERY_2                      = 1,
    SAY_JOSIAH_AVERY_3                      = 2,
    SAY_JOSIAH_AVERY_4                      = 3,
    SAY_JOSIAH_AVERY_5                      = 4,
    SAY_JOSIAH_AVERY_6                      = 5,

    SPELL_SAVE_CYNTHIA                      = 68597,
    SPELL_SAVE_ASHLEY                       = 68598,
    SPELL_SAVE_JAMES                        = 68596,

    PLAYER_SAY_CYNTHIA                      = 0,
    PLAYER_SAY_ASHLEY                       = 1,
    PLAYER_SAY_JAMES                        = 2,

    NPC_JAMES                               = 36289,
    NPC_CYNTHIA                             = 36287,
    NPC_ASHLEY                              = 36288,

    EVENT_TALK_TO_PLAYER                    = 1,
    EVENT_START_RUN                         = 2,
    EVENT_OPEN_DOOR                         = 3,
    EVENT_RESUME_RUN                        = 4,
    EVENT_CRY                               = 5,

    CHILDREN_TEXT_ID                        = 0,

    GO_DOOR_TO_THE_BASEMENT                 = 196411
};

Position const runt2SummonJumpPos = { -1671.915f, 1446.734f, 52.28712f };
Position const alphaSummonJumpPos = { -1656.723f, 1405.647f, 52.74205f };
Position const alpha2SummonJumpPos = { -1675.44f, 1447.495f, 52.28762f };

Position const josiahJumpPos = { -1796.63f, 1427.73f, 12.4624f };

uint32 const runtHousePathSize1 = 13;

Position const worgenRuntHousePath1[runtHousePathSize1] =
{
    { -1734.77f, 1527.007f, 55.2133f },
    { -1729.345f, 1526.495f, 55.4231f },
    { -1723.921f, 1525.982f, 55.6329f },
    { -1718.885f, 1525.88f, 55.89785f },
    { -1718.002f, 1516.054f, 55.36457f },
    { -1718.162f, 1512.458f, 55.41572f },
    { -1717.852f, 1508.871f, 55.64134f },
    { -1717.868f, 1507.03f, 55.78084f },
    { -1717.939f, 1498.912f, 56.2076f },
    { -1717.975f, 1494.827f, 56.34147f },
    { -1717.666f, 1491.978f, 56.46574f },
    { -1717.708f, 1491.591f, 56.51286f },
    { -1717.708f, 1491.591f, 56.51286f },
};

uint32 const runtHousePathSize2 = 11;

Position const worgenRuntHousePath2[runtHousePathSize2] =
{
    {-1705.29f, 1527.974f, 57.49218f },
    {-1709.63f, 1527.464f, 56.81163f },
    {-1713.971f, 1526.953f, 56.13107f },
    {-1718.249f, 1525.915f, 55.91631f },
    {-1718.002f, 1516.054f, 55.36457f },
    {-1718.162f, 1512.458f, 55.41572f },
    {-1717.852f, 1508.871f, 55.64134f },
    {-1717.866f, 1507.038f, 55.7804f },
    {-1717.928f, 1498.872f, 56.20963f },
    {-1717.947f, 1496.298f, 56.29393f },
    {-1717.947f, 1496.298f, 56.29393f },
};

uint32 const runtHousePathSize3 = 8;

Position const worgenRuntHousePath3[runtHousePathSize3] =
{
    {-1717.74f, 1514.99f, 55.37629f },
    {-1717.75f, 1513.727f, 55.39608f },
    {-1717.76f, 1512.465f, 55.41587f },
    {-1717.787f, 1508.872f, 55.64124f },
    {-1717.799f, 1507.277f, 55.74761f },
    {-1717.864f, 1498.657f, 56.22049f },
    {-1717.887f, 1495.557f, 56.31728f },
    {-1717.887f, 1495.557f, 56.31728f },
};

uint32 const runtHousePathSize4 = 11;

Position const worgenRuntHousePath4[runtHousePathSize4] =
{
    { -1727.101f, 1527.078f, 55.5045f },
    { -1724.719f, 1526.731f, 55.60394f },
    { -1722.337f, 1526.383f, 55.70337f },
    { -1718.885f, 1525.88f, 55.89785f },
    { -1718.002f, 1516.054f, 55.36457f },
    { -1718.162f, 1512.458f, 55.41572f },
    { -1717.852f, 1508.871f, 55.64134f },
    { -1717.845f, 1507.113f, 55.77633f },
    { -1717.81f, 1498.482f, 56.22932f },
    { -1717.793f, 1494.123f, 56.37141f },
    { -1717.793f, 1494.123f, 56.37141f },
};

uint32 const runtHousePathSize5 = 11;

Position const worgenRuntHousePath5[runtHousePathSize5] =
{
    { -1709.699f, 1527.335f, 56.34836f },
    { -1713.974f, 1526.625f, 56.13234f },
    { -1718.249f, 1525.915f, 55.91631f },
    { -1718.002f, 1516.054f, 55.36457f },
    { -1718.162f, 1512.458f, 55.41572f },
    { -1717.852f, 1508.871f, 55.64134f },
    { -1717.891f, 1506.948f, 55.78529f },
    { -1718.047f, 1499.267f, 56.18964f },
    { -1718.125f, 1495.405f, 56.31914f },
    { -1717.693f, 1492.178f, 56.45717f },
    { -1717.693f, 1492.178f, 56.45717f },
};

uint32 const runtHousePathSize6 = 9;

Position const worgenRuntHousePath6[runtHousePathSize6] =
{
    { -1718.083f, 1532.09f, 56.25435f },
    { -1718.104f, 1524.071f, 55.80854f },
    { -1718.125f, 1516.053f, 55.36273f },
    { -1718.134f, 1512.459f, 55.41573f },
    { -1718.143f, 1508.866f, 55.64067f },
    { -1718.151f, 1506.013f, 55.83052f },
    { -1718.167f, 1499.665f, 56.16953f },
    { -1718.172f, 1497.578f, 56.24289f },
    { -1718.172f, 1497.578f, 56.24289f },
};

uint32 const runtHousePathSize7 = 9;

Position const worgenRuntHousePath7[runtHousePathSize7] =
{
    { -1718.083f, 1532.09f, 56.25435f },
    { -1718.104f, 1524.071f, 55.80854f },
    { -1718.125f, 1516.053f, 55.36273f },
    { -1718.134f, 1512.459f, 55.41573f },
    { -1718.143f, 1508.866f, 55.64067f },
    { -1718.151f, 1506.013f, 55.83052f },
    { -1718.167f, 1499.665f, 56.16953f },
    { -1718.172f, 1497.578f, 56.24289f },
    { -1718.172f, 1497.578f, 56.24289f },
};

uint32 const runtCathedralPathSize1 = 10;

Position const worgenRuntCathedralPath1[runtCathedralPathSize1] =
{
    { -1612.885f, 1492.154f, 67.03599f },
    { -1618.054f, 1489.644f, 68.5475f },
    { -1623.222f, 1487.134f, 70.05901f },
    { -1629.727f, 1483.976f, 72.59077f },
    { -1630.914f, 1483.4f, 72.92308f },
    { -1632.244f, 1482.754f, 72.91827f },
    { -1636.865f, 1480.51f, 68.61356f },
    { -1638.087f, 1479.916f, 67.58314f },
    { -1638.852f, 1479.545f, 66.56925f },
    { -1638.852f, 1479.545f, 66.56925f },
};

uint32 const runtCathedralPathSize2 = 7;

Position const worgenRuntCathedralPath2[runtCathedralPathSize2] =
{
    { -1618.982f, 1489.76f, 68.56043f },
    { -1625.62f, 1487.033f, 71.4378f },
    { -1632.258f, 1484.306f, 74.31516f },
    { -1634.6f, 1483.343f, 72.61462f },
    { -1636.067f, 1482.741f, 70.69682f },
    { -1639.282f, 1481.42f, 66.99659f },
    { -1639.282f, 1481.42f, 66.99659f },
};

uint32 const runtCathedralPathSize3 = 6;

Position const worgenRuntCathedralPath3[runtCathedralPathSize3] =
{
    { -1637.957f, 1493.445f, 67.77746f },
    { -1638.569f, 1489.736f, 68.47077f },
    { -1639.182f, 1486.027f, 69.16409f },
    { -1640.578f, 1477.564f, 64.01109f },
    { -1640.676f, 1476.976f, 63.45144f },
    { -1640.676f, 1476.976f, 63.45144f },
};

uint32 const runtCathedralPathSize4 = 5;

Position const worgenRuntCathedralPath4[runtCathedralPathSize4] =
{
    { -1628.66f, 1482.281f, 71.34027f },
    { -1630.399f, 1481.66f, 71.33196f },
    { -1632.139f, 1481.039f, 71.32365f },
    { -1639.006f, 1478.586f, 65.77306f },
    { -1639.006f, 1478.586f, 65.77306f },
};


uint32 const runtCathedralPathSize5 = 9;

Position const worgenRuntCathedralPath5[runtCathedralPathSize5] =
{
    { -1620.279f, 1484.46f, 67.03528f },
    { -1622.424f, 1483.882f, 68.05564f },
    { -1624.568f, 1483.304f, 69.076f },
    { -1628.933f, 1482.127f, 70.91297f },
    { -1632.153f, 1481.259f, 71.52889f },
    { -1637.776f, 1479.743f, 67.45475f },
    { -1638.956f, 1479.425f, 66.41499f },
    { -1639.354f, 1479.318f, 65.98292f },
    { -1639.354f, 1479.318f, 65.98292f },
};

uint32 const runtCathedralPathSize6 = 10;

Position const worgenRuntCathedralPath6[runtCathedralPathSize6] =
{
    { -1633.998f, 1495.233f, 68.24403f },
    { -1634.344f, 1491.3f, 70.41303f },
    { -1634.689f, 1487.368f, 72.58203f },
    { -1634.735f, 1486.842f, 72.91134f },
    { -1634.837f, 1485.684f, 73.20835f },
    { -1634.987f, 1483.981f, 72.29824f },
    { -1635.084f, 1482.868f, 71.9163f },
    { -1635.166f, 1481.939f, 70.77574f },
    { -1635.809f, 1474.621f, 63.4636f },
    { -1635.809f, 1474.621f, 63.4636f },
};

uint32 const runtCathedralPathSize7 = 7;

Position const worgenRuntCathedralPath7[runtCathedralPathSize7] =
{
    { -1629.975f, 1494.066f, 70.64719f },
    { -1631.979f, 1491.585f, 71.31316f },
    { -1633.984f, 1489.104f, 71.97912f },
    { -1634.991f, 1487.856f, 72.09129f },
    { -1636.631f, 1485.826f, 71.53807f },
    { -1640.601f, 1480.912f, 65.49457f },
    { -1640.601f, 1480.912f, 65.49457f },
};

uint32 const runtCathedralPathSize8 = 8;

Position const worgenRuntCathedralPath8[runtCathedralPathSize8] =
{
    { -1620.879f, 1491.133f, 70.67613f },
    { -1622.665f, 1489.818f, 71.04526f },
    { -1624.451f, 1488.503f, 71.41438f },
    { -1630.469f, 1484.073f, 73.09648f },
    { -1631.376f, 1483.405f, 73.20229f },
    { -1632.245f, 1482.765f, 72.92912f },
    { -1635.605f, 1480.292f, 68.99215f },
    { -1635.605f, 1480.292f, 68.99215f },
};

Position const worgenRuntJumpPos[] =
{
    { -1694.03f, 1466.33f, 52.2872f },
    { -1688.92f, 1455.69f, 52.2871f },
    { -1699.46f, 1468.43f, 52.2871f },
    { -1697.73f, 1469.52f, 52.2871f },
    { -1701.65f, 1470.94f, 52.2871f },
    { -1693.91f, 1468.46f, 52.2872f },
    { -1697.30f, 1464.65f, 52.2871f },

    { -1681.57f, 1455.77f, 52.2871f },
    { -1677.47f, 1454.94f, 52.2871f },
    { -1677.71f, 1452.2f,  52.2871f },
    { -1677.66f, 1450.93f, 52.2871f },
    { -1672.56f, 1448.06f, 52.2871f },
    { -1683.13f, 1455.39f, 52.2871f },
    { -1669.81f, 1442.34f, 52.2871f },
    { -1674.15f, 1448.9f,  52.2871f },
};

Position const WorgenRuntHousePos[] =
{
    { -1729.345f, 1526.495f, 55.47962f, 6.188943f },
    { -1709.63f, 1527.464f, 56.86086f, 3.258752f },
    { -1717.75f, 1513.727f, 55.47941f, 4.704845f },
    { -1724.719f, 1526.731f, 55.66177f, 6.138319f },
    { -1713.974f, 1526.625f, 56.21981f, 3.306195f },
    { -1718.104f, 1524.071f, 55.81641f, 4.709816f },
    { -1718.262f, 1518.557f, 55.55954f, 4.726997f },

    { -1618.054f, 1489.644f, 68.45153f, 3.593639f },
    { -1625.62f, 1487.033f, 71.27762f, 3.531424f },
    { -1638.569f, 1489.736f, 68.55273f, 4.548815f },
    { -1630.399f, 1481.66f, 71.41516f, 3.484555f },
    { -1622.424f, 1483.882f, 67.67381f, 3.404875f },
    { -1634.344f, 1491.3f, 70.10101f, 4.6248f },
    { -1631.979f, 1491.585f, 71.11481f, 4.032866f },
    { -1627.273f, 1499.689f, 68.89395f, 4.251452f },
    { -1622.665f, 1489.818f, 71.03797f, 3.776179f },
};

uint8 const JamesPathLenght = 6;
Position const JamesPath[][JamesPathLenght] =
{
    {
        { -1925.925049f, 2539.176514f, 1.392833f, 0.0f },
        { -1913.658203f, 2545.986328f, 1.465530f, 0.0f },
        { -1904.370728f, 2552.793213f, 1.132485f, 0.0f },
        { -1900.970459f, 2550.849365f, 0.714445f, 0.0f },
        { -1886.868774f, 2540.282471f, 1.706371f, 0.0f },
        { -1882.739746f, 2543.941865f, 1.628683f, 0.0f },
    },
};

uint8 const CynthiaPathLenght = 6;
Position const CynthiaPath[][CynthiaPathLenght] =
{
    {
        { -1947.965088f, 2518.669434f, 1.826697f, 0.0f },
        { -1923.350830f, 2521.841553f, 1.586985f, 0.0f },
        { -1917.197632f, 2520.494385f, 2.297501f, 0.0f },
        { -1890.082031f, 2519.952148f, 1.425827f, 0.0f },
        { -1886.868774f, 2540.282471f, 1.706371f, 0.0f },
        { -1882.739746f, 2543.941865f, 1.628683f, 0.0f },
    },
};

uint8 const AshleyPathLenght = 13;
Position const AshleyPath[][AshleyPathLenght] =
{
    {
        { -1928.023682f, 2558.467285f, 12.733648f, 0.0f },
        { -1928.248901f, 2553.930176f, 12.734390f, 0.0f },
        { -1923.981567f, 2552.113770f, 12.736046f, 0.0f },
        { -1919.301514f, 2563.295166f, 3.579522f, 0.0f },
        { -1930.442017f, 2562.145996f, 3.579824f, 0.0f },
        { -1941.160156f, 2566.118896f, 1.392157f, 0.0f },
        { -1940.852295f, 2543.049072f, 1.392157f, 0.0f },
        { -1919.504517f, 2543.273926f, 1.392157f, 0.0f },
        { -1913.658203f, 2545.986328f, 1.465530f, 0.0f },
        { -1904.370728f, 2552.793213f, 1.132485f, 0.0f },
        { -1900.970459f, 2550.849365f, 0.714445f, 0.0f },
        { -1886.868774f, 2540.282471f, 1.706371f, 0.0f },
        { -1882.739746f, 2543.941865f, 1.628683f, 0.0f },
    },
};

uint8 const childrenBasementPathLenght = 3;
Position const childrenBasementPath[][childrenBasementPathLenght] =
{
    {
        { -1879.062378f, 2546.958984f, -0.130342f, 0.0f },
        { -1873.854980f, 2550.903564f, -5.898719f, 0.0f },
        { -1868.589844f, 2536.521240f, -6.365717f, 0.0f },
    },
};

const std::string PlayerText[3] =
{
    "It's not safe here. Go to the Allens' basement.",
    "Join the others inside the basement next door. Hurry!",
    "Your mother's in the basement next door. Get to her now!",
};

struct npc_gilneas_crow : public ScriptedAI
{
    npc_gilneas_crow(Creature* creature) : ScriptedAI(creature) { }

    uint32 spawn;
    bool flying;

    void Reset() override
    {
        flying = false;
        spawn = 0;
        me->SetPosition(me->GetCreatureData()->posX, me->GetCreatureData()->posY, me->GetCreatureData()->posZ, me->GetCreatureData()->orientation);
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_PING_GILNEAN_CROW)
        {
            if (!flying)
            {
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetDisableGravity(true);
                flying = true;
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!flying)
            return;

        if (spawn <= diff)
        {
            me->GetMotionMaster()->MovePoint(0, (me->GetPositionX() + irand(-15, 15)), (me->GetPositionY() + irand(-15, 15)), (me->GetPositionZ() + irand(5, 15)));
            spawn = urand (500, 1000);
        }
        else spawn -= diff;

        if ((me->GetPositionZ() - me->GetCreatureData()->posZ) >= 20.0f)
        {
            me->DisappearAndDie();
            me->RemoveCorpse(true);
            flying = false;
        }
    }
};

struct npc_gilneas_city_guard_gate : public ScriptedAI
{
    npc_gilneas_city_guard_gate(Creature* creature) : ScriptedAI(creature) { }

    EventMap m_events;
    uint8 m_say;
    uint8 m_emote;
    ObjectGuid m_citizenGUID;

    void Reset() override
    {
        if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
            m_events.ScheduleEvent(EVENT_START_TALK_WITH_CITIZEN, 10 * IN_MILLISECONDS, 30 * IN_MILLISECONDS);
    }

    void UpdateAI(uint32 diff) override
    {
        m_events.Update(diff);

        while (uint32 eventId = m_events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_START_TALK_WITH_CITIZEN:
                {
                    m_citizenGUID = GetRandomCitizen();
                    m_emote = RAND(EMOTE_ONESHOT_COWER, EMOTE_STATE_TALK, EMOTE_ONESHOT_CRY, EMOTE_ONESHOT_BEG, EMOTE_ONESHOT_EXCLAMATION, EMOTE_ONESHOT_POINT);
                    m_say = 0;

                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_citizenGUID))
                        npc->HandleEmoteCommand(m_emote);

                    m_events.ScheduleEvent(EVENT_TALK_WITH_CITIZEN_1, 2 * IN_MILLISECONDS + 200, 3 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_TALK_WITH_CITIZEN_1:
                {
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_citizenGUID))
                        npc->AI()->Talk(m_say);

                    m_events.ScheduleEvent(EVENT_TALK_WITH_CITIZEN_2, 5 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_TALK_WITH_CITIZEN_2:
                {
                    Talk(m_say);
                    m_events.ScheduleEvent(EVENT_TALK_WITH_CITIZEN_3, 5 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_TALK_WITH_CITIZEN_3:
                {
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_citizenGUID))
                        npc->HandleEmoteCommand(EMOTE_STATE_NONE);

                    m_events.ScheduleEvent(EVENT_START_TALK_WITH_CITIZEN, 5 * IN_MILLISECONDS, 30 * IN_MILLISECONDS);
                    break;
                }
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void FillCitizenList()
    {
        listOfCitizenGUID.clear();
        std::list<Creature*> listOfCitizen;
        me->GetCreatureListWithEntryInGrid(listOfCitizen, NPC_PANICKED_CITIZEN_GATE, 35.0f);

        for (std::list<Creature*>::iterator itr = listOfCitizen.begin(); itr != listOfCitizen.end(); ++itr)
            listOfCitizenGUID.push_back((*itr)->GetGUID());
    }

    ObjectGuid GetRandomCitizen()
    {
        if (listOfCitizenGUID.empty())
            FillCitizenList();

        uint8 rol = urand(0, listOfCitizenGUID.size() - 1);
        std::list<ObjectGuid>::iterator itr = listOfCitizenGUID.begin();
        std::advance(itr, rol);
        return (*itr);
    }

private:
    std::list<ObjectGuid> listOfCitizenGUID;
};

struct npc_prince_liam_greymane : public ScriptedAI
{
    npc_prince_liam_greymane(Creature *c) : ScriptedAI(c) { }

    EventMap _events;

    void Reset() override
    {
        _events.RescheduleEvent(EVENT_START_DIALOG, 1 * IN_MILLISECONDS);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_START_DIALOG:
                {
                    _events.ScheduleEvent(EVENT_RESET_DIALOG, 2 * MINUTE * IN_MILLISECONDS);
                    _events.ScheduleEvent(EVENT_START_TALK_TO_GUARD, 1 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_START_TALK_TO_GUARD:
                {
                    Talk(PRINCE_LIAM_GREYMANE_TEXT_00);
                    _events.ScheduleEvent(EVENT_TALK_TO_GUARD_1, 15 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_TALK_TO_GUARD_1:
                {
                    Talk(PRINCE_LIAM_GREYMANE_TEXT_01);
                    _events.ScheduleEvent(EVENT_TALK_TO_GUARD_2, 18 * IN_MILLISECONDS);
                    break;
                }
                case EVENT_TALK_TO_GUARD_2:
                {
                    Talk(PRINCE_LIAM_GREYMANE_TEXT_02);
                    break;
                }
                case EVENT_RESET_DIALOG:
                {
                    Reset();
                    break;
                }
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

struct npc_worgen_runt : public ScriptedAI
{
    npc_worgen_runt(Creature* creature) : ScriptedAI(creature)
    {
        Initialize();
    }

    void Initialize()
    {
        _worgenID = 0;
        _wayPointCounter = 0;
        _jumped = false;
        _playerGuid = 0;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.SetPhase(PHASE_COMBAT);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        me->setActive(true);
        _events.SetPhase(PHASE_ROOF);
        _events.ScheduleEvent(EVENT_FORCE_DESPAWN, 70 * IN_MILLISECONDS, 0, PHASE_ROOF);
        _playerGuid = summoner->GetGUID();

        if (me->GetEntry() == NPC_WORGEN_RUNT_2)
            me->GetMotionMaster()->MoveJump(runt2SummonJumpPos, 16.0f, 4.371286f);

        if (me->GetEntry() == NPC_WORGEN_ALPHA)
        {
            me->GetMotionMaster()->MoveJump(alphaSummonJumpPos, 14.0f, 5.395287f);

            me->m_Events.AddLambdaEventAtOffset([this]()
            {
                me->GetMotionMaster()->MovePoint(0, -1676.767944f, 1442.418457f, 52.287319f, true);
            }, 2500);
        }

        if (me->GetEntry() == NPC_WORGEN_ALPHA_2)
            me->GetMotionMaster()->MoveJump(alpha2SummonJumpPos, 17.0f, 4.937166f);
    }

    void DoAction(int32 action) override
    {
        _worgenID = action;

        switch (_worgenID)
        {
            case WORGEN_ID_ROOF_1:
                _wayPointCounter = runtHousePathSize1;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize1, worgenRuntHousePath1, runtHousePathSize1);
                break;
            case WORGEN_ID_ROOF_2:
                _wayPointCounter = runtHousePathSize2;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize2, worgenRuntHousePath2, runtHousePathSize2);
                break;
            case WORGEN_ID_ROOF_3:
                _wayPointCounter = runtHousePathSize3;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize3, worgenRuntHousePath3, runtHousePathSize3);
                break;
            case WORGEN_ID_ROOF_4:
                _wayPointCounter = runtHousePathSize4;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize4, worgenRuntHousePath4, runtHousePathSize4);
                break;
            case WORGEN_ID_ROOF_5:
                _wayPointCounter = runtHousePathSize5;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize5, worgenRuntHousePath5, runtHousePathSize5);
                break;
            case WORGEN_ID_ROOF_6:
                _wayPointCounter = runtHousePathSize6;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize6, worgenRuntHousePath6, runtHousePathSize6);
                break;
            case WORGEN_ID_ROOF_7:
                _wayPointCounter = runtHousePathSize7;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize7, worgenRuntHousePath7, runtHousePathSize7);
                break;
            case WORGEN_ID_CATHEDRAL_1:
                _wayPointCounter = runtCathedralPathSize1;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize1, worgenRuntCathedralPath1, runtCathedralPathSize1);
                break;
            case WORGEN_ID_CATHEDRAL_2:
                _wayPointCounter = runtCathedralPathSize2;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize2, worgenRuntCathedralPath2, runtCathedralPathSize2);
                break;
            case WORGEN_ID_CATHEDRAL_3:
                _wayPointCounter = runtCathedralPathSize3;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize3, worgenRuntCathedralPath3, runtCathedralPathSize3);
                break;
            case WORGEN_ID_CATHEDRAL_4:
                _wayPointCounter = runtCathedralPathSize4;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize4, worgenRuntCathedralPath4, runtCathedralPathSize4);
                break;
            case WORGEN_ID_CATHEDRAL_5:
                _wayPointCounter = runtCathedralPathSize5;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize5, worgenRuntCathedralPath5, runtCathedralPathSize5);
                break;
            case WORGEN_ID_CATHEDRAL_6:
                _wayPointCounter = runtCathedralPathSize6;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize6, worgenRuntCathedralPath6, runtCathedralPathSize6);
                break;
            case WORGEN_ID_CATHEDRAL_7:
                _wayPointCounter = runtCathedralPathSize7;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize7, worgenRuntCathedralPath7, runtCathedralPathSize7);
                break;
            case WORGEN_ID_CATHEDRAL_8:
                _wayPointCounter = runtCathedralPathSize8;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize8, worgenRuntCathedralPath8, runtCathedralPathSize8);
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(5 * IN_MILLISECONDS);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == _wayPointCounter && !_jumped)
        {
            _jumped = true;
            _events.ScheduleEvent(EVENT_JUMP_TO_PRISON, 1 * IN_MILLISECONDS);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !_events.IsInPhase(PHASE_ROOF))
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_FORCE_DESPAWN:
                    me->DespawnOrUnsummon();
                    break;
                case EVENT_JUMP_TO_PRISON:
                    me->GetMotionMaster()->MoveJump(worgenRuntJumpPos[_worgenID], 16.0f, _worgenID < WORGEN_ID_CATHEDRAL_1 ? 19.2911f : frand(3.945607f, 4.852813f));
                    me->SetHomePosition(worgenRuntJumpPos[_worgenID]);
                    _events.ScheduleEvent(EVENT_AGGRO_PLAYER, 2 * IN_MILLISECONDS);
                    break;
                case EVENT_AGGRO_PLAYER:
                    if (Unit* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                        if (me->IsAIEnabled && me->GetHomePosition().IsInDist(player, 100.0f))
                            me->AI()->AttackStart(player);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    uint32 _worgenID;
    uint32 _wayPointCounter;
    bool _jumped;
    ObjectGuid _playerGuid;
    EventMap _events;
};

class spell_gen_gilneas_prison_periodic_dummy : public SpellScript
{
    PrepareSpellScript(spell_gen_gilneas_prison_periodic_dummy);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_SUMMON_RAVENOUS_WORGEN_1) ||
            !sSpellMgr->GetSpellInfo(SPELL_SUMMON_RAVENOUS_WORGEN_2))
            return false;
        return true;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            switch (RAND(0, 1))
            {
                case 0:
                    caster->CastSpell(caster, SPELL_SUMMON_RAVENOUS_WORGEN_1, true);
                    for (uint8 i = 0; i < 7; i++)
                        if (Creature* runt = caster->SummonCreature(NPC_WORGEN_RUNT, WorgenRuntHousePos[i]))
                            runt->AI()->DoAction(i);
                    break;
                case 1:
                    caster->CastSpell(caster, SPELL_SUMMON_RAVENOUS_WORGEN_2, true);
                    for (uint8 i = 7; i < 16; i++)
                        if (Creature* runt = caster->SummonCreature(NPC_WORGEN_RUNT, WorgenRuntHousePos[i]))
                            runt->AI()->DoAction(i);
                    if (RAND(0, 1) == 1)
                        for (uint8 i = 0; i < RAND(1, 3); i++)
                            if (Creature* runt = caster->SummonCreature(NPC_WORGEN_RUNT, WorgenRuntHousePos[i]))
                                runt->AI()->DoAction(i);
                    break;
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_gen_gilneas_prison_periodic_dummy::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

struct npc_josiah_avery : public ScriptedAI
{
    npc_josiah_avery(Creature* creature) : ScriptedAI(creature) { }

    uint32 _text_timer;
    uint32 _current_text;

    void Reset() override
    {
        _text_timer = 20 * IN_MILLISECONDS;
        _current_text = 1;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!me->GetVictim() && me->FindNearestPlayer(20.0f))
        {
            if (_text_timer <= diff)
            {
                switch (_current_text)
                {
                    case 1:
                        Talk(SAY_JOSIAH_AVERY_1);
                        _current_text++;
                        break;
                    case 2:
                        Talk(SAY_JOSIAH_AVERY_2);
                        _current_text++;
                        break;
                    case 3:
                        Talk(SAY_JOSIAH_AVERY_3);
                        _current_text++;
                        break;
                    case 4:
                        Talk(SAY_JOSIAH_AVERY_4);
                        _current_text++;
                        break;
                    case 5:
                        Talk(SAY_JOSIAH_AVERY_5);
                        _current_text++;
                        break;
                    case 6:
                        Talk(SAY_JOSIAH_AVERY_6);
                        _current_text = 1;
                        break;
                }

                _text_timer = 20 * IN_MILLISECONDS;
            }
            else
            {
                _text_timer -= diff;
            }
            return;
        }
    }
};

struct npc_josiah_avery_worgen_form : public PassiveAI
{
    npc_josiah_avery_worgen_form(Creature* creature) : PassiveAI(creature) { }

    void IsSummonedBy(Unit* summoner) override
    {
        _playerGuid = summoner->GetGUID();

        me->m_Events.AddLambdaEventAtOffset([this, summoner]()
        {
            me->SetFacingToObject(summoner);
            _events.ScheduleEvent(EVENT_COSMETIC_ATTACK, 500);
        }, 200);
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
    {
        if (spell->Id == SPELL_SHOOT_INSTAKILL)
            me->CastSpell(me, SPELL_GET_SHOT);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(5 * IN_MILLISECONDS);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_COSMETIC_ATTACK:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                    {
                        DoCast(player, SPELL_COSMETIC_ATTACK);

                        me->m_Events.AddLambdaEventAtOffset([this, player]()
                        {
                            if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f, true))
                                player->GetMotionMaster()->MoveKnockbackFrom(lorna->GetPositionX(), lorna->GetPositionY(), 30, 30);
                        }, 400);

                        if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f, true))
                            if (Creature* labTrigger = lorna->FindNearestCreature(NPC_GENERIC_TRIGGER_LAB, 5.0f, true))
                                labTrigger->CastSpell(player, SPELL_PULL_TO);

                        _events.ScheduleEvent(EVENT_JUMP_TO_PLAYER, 1 * IN_MILLISECONDS);
                    }
                    break;
                case EVENT_JUMP_TO_PLAYER:
                    me->GetMotionMaster()->MoveJump(josiahJumpPos, 10.0f, 14.18636f);
                    _events.ScheduleEvent(EVENT_SHOOT_JOSIAH, 1 * IN_MILLISECONDS + 200);
                    break;
                case EVENT_SHOOT_JOSIAH:
                    if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f, true))
                        lorna->CastSpell(me, SPELL_SHOOT_INSTAKILL, true);
                    break;
                default:
                    break;
            }
        }
    }

private:
    ObjectGuid _playerGuid;
    EventMap _events;
};

class spell_gilneas_pull_to : public SpellScript
{
    PrepareSpellScript(spell_gilneas_pull_to);

    void HandPullEffect(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);

        if (Unit* playerTarget = GetHitPlayer())
        {
            if (Unit* trigger = GetCaster())
            {
                float angle = playerTarget->GetAngle(trigger);
                playerTarget->SendMoveKnockBack(playerTarget->ToPlayer(), 30.0f, -7.361481f, cos(angle), sin(angle));
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_gilneas_pull_to::HandPullEffect, EFFECT_0, SPELL_EFFECT_PULL_TOWARDS);
    }
};

class npc_gilneas_children : public CreatureScript
{
    public:
        npc_gilneas_children(const char* scriptName, uint32 spellId, uint8 playerSayId) : CreatureScript(scriptName), _spellId(spellId), _playerSayId(playerSayId) { }

    private:
        uint32 _spellId;
        uint8 _playerSayId;

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new creature_script(creature, _spellId, _playerSayId);
        }

        struct creature_script : public ScriptedAI
        {
            creature_script(Creature* creature, uint32 spellId, uint8 playerSayId) : ScriptedAI(creature), _spellId(spellId), _playerSayId(playerSayId) { }

            EventMap events;
            uint64 playerGUID;
            uint32 _spellId;
            uint8 _playerSayId;
            bool activated;

            void Reset() override
            {
                events.Reset();
                playerGUID = 0;
                activated = false;
                me->SetFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

                if (me->GetEntry() == NPC_CYNTHIA)
                    events.ScheduleEvent(EVENT_CRY, 1000);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell)
            {
                if (!activated && spell->Id == _spellId)
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        activated = true;
                        playerGUID = player->GetGUID();
                        player->Say(PlayerText[_playerSayId], LANG_UNIVERSAL);
                        player->KilledMonsterCredit(me->GetEntry(), 0);
                        me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                        events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 3500);
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK_TO_PLAYER:
                        {
                            events.CancelEvent(EVENT_CRY);

                            if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                                Talk(CHILDREN_TEXT_ID, player);

                            events.ScheduleEvent(EVENT_START_RUN, 5000);
                        }
                        break;
                        case EVENT_START_RUN:
                        {
                            switch (me->GetEntry())
                            {
                                case NPC_JAMES:
                                    me->GetMotionMaster()->MoveSplinePath(JamesPath[0], JamesPathLenght, false, false, 0.f, false, false);
                                    break;
                                case NPC_CYNTHIA:
                                    me->GetMotionMaster()->MoveSplinePath(CynthiaPath[0], CynthiaPathLenght, false, false, 0.f, false, false);
                                    break;
                                case NPC_ASHLEY:
                                    me->GetMotionMaster()->MoveSplinePath(AshleyPath[0], AshleyPathLenght, false, false, 0.f, false, false);
                                    break;
                                default:
                                    return;
                            }

                            events.ScheduleEvent(EVENT_OPEN_DOOR, me->GetSplineDuration());
                        }
                        break;
                        case EVENT_OPEN_DOOR:
                        {
                            if (GameObject* door = me->FindNearestGameObject(GO_DOOR_TO_THE_BASEMENT, 10.0f))
                            {
                                if (door->GetGoState() == GO_STATE_READY)
                                {
                                    door->UseDoorOrButton();
                                    events.ScheduleEvent(EVENT_RESUME_RUN, 2000);
                                }
                                else
                                    events.ScheduleEvent(EVENT_RESUME_RUN, 0);
                            }
                        }
                        break;
                        case EVENT_RESUME_RUN:
                            me->GetMotionMaster()->MoveSplinePath(childrenBasementPath[0], childrenBasementPathLenght, false, false, 0.f, false, false);
                            me->DespawnOrUnsummon(me->GetSplineDuration());
                            break;
                        case EVENT_CRY:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
                            events.ScheduleEvent(EVENT_CRY, urand(1000, 1500));
                            break;
                    }
                }
            }
        };
};

void AddSC_gilneas()
{
    new creature_script<npc_gilneas_crow>("npc_gilneas_crow");
    new creature_script<npc_gilneas_city_guard_gate>("npc_gilneas_city_guard_gate");
    new creature_script<npc_prince_liam_greymane>("npc_prince_liam_greymane");
    new creature_script<npc_worgen_runt>("npc_worgen_runt");
    new spell_script<spell_gen_gilneas_prison_periodic_dummy>("spell_gen_gilneas_prison_periodic_dummy");
    new creature_script<npc_josiah_avery>("npc_josiah_avery");
    new creature_script<npc_josiah_avery_worgen_form>("npc_josiah_avery_worgen_form");
    new spell_script<spell_gilneas_pull_to>("spell_gilneas_pull_to");
    new npc_gilneas_children("npc_james", SPELL_SAVE_JAMES, PLAYER_SAY_JAMES);
    new npc_gilneas_children("npc_ashley", SPELL_SAVE_ASHLEY, PLAYER_SAY_ASHLEY);
    new npc_gilneas_children("npc_cynthia", SPELL_SAVE_CYNTHIA, PLAYER_SAY_CYNTHIA);
}
