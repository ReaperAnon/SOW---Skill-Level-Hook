#include <framework.h>

namespace GameHook
{
    // Multi Skill Equip
    const SHORT bytePattern[] = { 0x41, 0x8B, 0xE8, 0x48, 0x8B, 0xFA, 0xE8 };

    const SHORT patternLength = 7;

    const SHORT patternOffset = 0;

    // Name of the module in which to scan for byte patterns.
    const WCHAR moduleName[] = L"ShadowOfWar.exe";

    AOBScanner pScanner;

    // Injections and scanned addresses.
    extern "C"
    {
        UINT_PTR skillReqJmpAddr = 0;
        EXPORT BYTE* skillReqAddress = nullptr;
        INSTRUCTIONSET SkillReqInjectCode()
        {
            __asm__
            (
                "mov $100, %ebp\n\t"
                "mov %rdx, %rdi\n\t"
                "jmp *skillReqJmpAddr"
            );
        }
    }

    bool CreateSkillReqHook()
    {
        skillReqAddress = pScanner.PerformModuleScan(bytePattern, patternLength, patternOffset, moduleName);
        skillReqJmpAddr = (UINT_PTR)(skillReqAddress + 6);
        return skillReqAddress != nullptr;
    }

    // Hook startup.
    void CreateGameHooks()
    {
        CreateSkillReqHook();
        MH_CreateHook(skillReqAddress, (LPVOID)SkillReqInjectCode, nullptr);
        MH_EnableHook(MH_ALL_HOOKS);
    }
}