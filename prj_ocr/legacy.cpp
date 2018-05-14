#include <iostream>
#include <Python.h>

using namespace std;

int main(int argc, char* argv[]) {
    Py_Initialize();

    char path[1024];
    getcwd(path, 1024);
    char append_path[1536] = "sys.path.append('";
    strcat(append_path, path);
    strcat(append_path, "')");

    cout<<path<<endl;

    char imgname[256];
    cout<<"input img name : ";
    cin>>imgname;

    if(Py_IsInitialized()){
        PyRun_SimpleString("print ('hi')");
        PyRun_SimpleString("import sys");
        PyRun_SimpleString(append_path);
        PyRun_SimpleString("import ocr"); 

        PyObject *ocr = PyImport_ImportModule("ocr");

        if(ocr){
            PyObject* detector = PyObject_GetAttrString(ocr, "detect_text");

            if(detector){
                PyObject* r = PyObject_CallFunction(detector, "s", imgname);

                if(r){
                    //int result = (int)PyInt_AS_LONG(r);
                    /*if(PyString_Check(r) != false)
                        cout<<"Not string"<<endl;
                    else
                        cout<<"String - size ("<<PyString_Size(r)<<")"<<endl;*/
                    char *str = (char*)PyString_AsString(r);
                    cout<<endl<<"==result=="<<endl;
                    cout<<str<<endl;
                    Py_XDECREF(r);
                }
                Py_XDECREF(detector);
            }
            Py_XDECREF(ocr);
        }












        Py_Finalize();
    }
    return 0;
}

// 컴파일 방법
// g++ c.cpp $(pkg-config --cflags --libs python2) -o py
// /usr/bin/python
// http://www.smallake.kr/wp-content/uploads/2014/09/embedded_python_using_c_api.pdf 참고