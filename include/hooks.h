#ifndef HOOKS
    #define HOOKS

    namespace GameHook
    {
        extern "C"
        {
            INSTRUCTIONSET SkillReqInjectCode();
        }

        bool CreateSkillReqHook();
        void CreateGameHooks();
    }
#endif