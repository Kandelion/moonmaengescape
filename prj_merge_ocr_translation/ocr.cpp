#include "ocr.hpp"
#if DEBUG == 1
#include <iostream>
using namespace std;
#endif

//array dest require at least 1024 size
void ocr_vision::get_append_path(char *dest){
    char curdir[1024];
    getcwd(curdir, 1024);
    strncpy(dest, "sys.path.append('", 18);
    strcat(dest, curdir);
    strcat(dest, "')");
}

void ocr_vision::detect_text(char* result, int result_size, const char* imgpath, const char* pythonname = "ocr"){
    if(result == NULL)
        return;
    result[0] = 0;

    Py_Initialize();

    char append_path[1536];
    get_append_path(append_path);

    #if DEBUG == 1
    cout<<imgpath<<endl;
    #endif

    if(Py_IsInitialized()){
        PyRun_SimpleString("import sys");
        PyRun_SimpleString(append_path);
        PyRun_SimpleString("import ocr"); 

        PyObject *ocr = PyImport_ImportModule(pythonname);

        if(ocr){
            PyObject* detector = PyObject_GetAttrString(ocr, "detect_text");

            if(detector){
                PyObject* r = PyObject_CallFunction(detector, "s", imgpath);

                if(r){
                    #if DEBUG == 1
                    if(PyString_Check(r) != false)
                        cout<<"Not string"<<endl;
                    else
                        cout<<"String - size ("<<PyString_Size(r)<<")"<<endl;
                    #endif
                    strncpy(result, (char*)PyString_AsString(r), result_size);
                    #if DEBUG == 1
                    cout<<endl<<"==result=="<<endl;
                    cout<<result<<endl;
                    #endif
                    Py_XDECREF(r);
                }
                Py_XDECREF(detector);
            }
            Py_XDECREF(ocr);
        }

        Py_Finalize();
    }
}