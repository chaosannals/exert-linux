#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    void *handle = dlopen("./libdlibone.so", RTLD_LAZY);
    char* error = dlerror();
    if (!handle || error) {
        //std::cout << "load so error! " << error << std::endl;
        printf("load so error! %s \n", error);
        return 1;
    }

    void (*func)() = reinterpret_cast<void (*)()>(dlsym(handle, "dlib_say"));
    if (func == nullptr) {
        //std::cout << "load func error !" << std::endl;
        error = dlerror();
        printf("load func error !  %s \n", error);
        dlclose(handle);
        return 2;
    }

    func();
    dlclose(handle);
    return 0;
}