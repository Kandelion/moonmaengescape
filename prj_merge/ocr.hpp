#include <Python.h>

#define DEBUG 0         //set 1 to print log on console.

class ocr_vision{
private:
    void get_append_path(char *dest);

public:
    void detect_text(char * result, int result_size, const char* filepath, const char* pythonname);
};