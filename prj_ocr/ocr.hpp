#include <Python.h>

#define DEBUG 0         //set 1 to print log on console.

class ocr_vision{
private:
    void get_append_path(char *dest);

public:
    char* detect_text(const char* filepath, const char* pythonname);
};