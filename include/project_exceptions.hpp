#include <exception>

namespace exceptions
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

    struct AlreadyExists : public std::exception
    {
        const char *what() const noexcept override
        {
            return "AlreadyExists";
        }
    };

    struct NotExists : public std::exception
    {
        const char *what() const noexcept override
        {
            return "NotExists";
        }
    };

    struct UnknownError : public std::exception
    {
        const char *what() const noexcept override
        {
            return "UnknownError";
        }
    };
} // namespace exceptions
