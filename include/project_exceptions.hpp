#include <exception>

namespace ees
{
    struct ThisMeterAlreadyExist : public std::exception
    {
        const char *what() const noexcept override
        {
            return "ThisMeterAlreadyExist";
        }
    };

    struct NotFound : public std::exception
    {
        const char *what() const noexcept override
        {
            return "NotFound";
        }
    };
    
} // namespace ees
