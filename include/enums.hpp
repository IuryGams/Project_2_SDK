#pragma once

namespace ees 
{
    enum class Options 
    {
        SHOW_ALL_LINES,
        SHOW_ALL_MODELS,
        SHOW_LINE_ARES,
        SHOW_LINE_APOLO,
        SHOW_LINE_CRONOS,
        SHOW_LINE_ZEUS,
        OUT_MENU,
        UNKNOWN_OPTION
    };

    enum class Lines 
    {
        ARES,
        APOLO,
        CRONOS,
        ZEUS,
        UNKNOWN
    };
} // namespace ees