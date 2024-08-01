#ifndef ERROR_H
#define ERROR_H

// Something went wrong
void Error(const char* details) 
{
    printf("Error: %s\n", details);
}

void Exception(const char* details)
{
    printf("Exception: %s\n", details);
}

// Undefined variable
void NameError(const char* name)
{
    printf("NameError: '%s' is not defined\n", name);
}

// Invalid type
void TypeError(const char* type)
{
    printf("TypeError: '%s' is not a valid type\n", type);
}

// Invalid value
void ValueError(const char* val)
{
    printf("ValueError: '%s' is not a valid value\n", val);
}

// Nonexistent index
void IndexError(const char* index)
{
    printf("IndexError: '%s' is not a valid index\n", index);
}

// Nonexistent key
void KeyError(const char* key)
{
    printf("KeyError: '%s' is not a valid key\n", key);
}

// Failed making attribute
void AttributeError(const char* attr)
{
    printf("AttributeError: '%s' is not a valid attribute\n", attr);
}

// Function not implemented
void NotImplementedError(const char* func)
{
    printf("NotImplementedError: '%s' is not implemented\n", func);
}

// Invalid syntax
void SyntaxError(const char* syntax)
{
    printf("SyntaxError: '%s' is not a valid syntax\n", syntax);
}

// Syntax is correct, but an error still happens
void RuntimeError(const char* runtime)
{
    printf("RuntimeError: '%s' is not a valid runtime\n", runtime);
}

// void InternalError(const char* internal)
// {
//     printf("InternalError: '%s' is not a valid internal\n", internal);
// }

// void UnknownError(const char* unknown)
// {
//     printf("UnknownError: '%s' is not a valid error\n", unknown);
// }

// Unexpected end of file
void EOFError(const char* location)
{
    printf("EOFError: unexpected end of file at '%s'\n", location);
}

// Ran out of memory
void MemoryError(const char* program) 
{
    printf("MemoryError: '%s' ran out of memory\n", program);
}

// Not an error, but instead a warning
void UserWarning(const char* warning)
{
    printf("UserWarning: '%s'\n", warning);
}

// If you change this to 1, it will not show warnings
int allowWarnings = 0;

// If you change this to 1, it will not show errors, which can be annoying
int allowErrors = 0;

// Checks if warnings can be shown
int checkIfWarningsCanBeShown()
{
    if (allowWarnings)
    {
        return 0;
    }
    return 1;
}

// Checks if errors can be shown
int checkIfErrorsCanBeShown()
{
    if (allowErrors)
    {
        return 0;
    }
    return 1;
}

#endif