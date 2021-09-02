#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>

namespace ge {
    template <class ResourceObj>
    class ResourceObjArr {
    public:
        ResourceObjArr(ResourceObj *objs, unsigned int size): objs(objs), size(size) {}
        ~ResourceObjArr() {
            size = 0;
            delete[] objs;
        }
        ResourceObj& operator[](int i) { return objs[i]; }
        unsigned int getSize() { return size; }
    private:
        ResourceObj *objs;
        unsigned int size;
    };

    // Resource class
    template <class ResourceObj>
    class Resource {
    public:
        void load(std::string path) {
            std::filebuf fb;
            if (fb.open(path, std::ios::in)) {
                std:: cout << "Error: could not open path" << std::endl;
                std::exit(-1);
            }
            
            std::istream is(&fb);
            while (is) {
                std::string temp;
                std::getline(is, temp);
                if (temp.find(":") == std::string::npos) { continue; }
                
                std::string root = (path.find('/') == std::string::npos)? "" : path.substr(0, path.find_last_of('/')+1);
                std::string first = temp.substr(0, temp.find(':'));
                std::string second = temp.substr(temp.find(':')+2, temp.size()-1);
                
                load(first, root + second);
            }
            fb.close();
        }

        void load(std::string name, std::string path) {
            ResourceObj *obj = new ResourceObj();
            if (!obj->loadFromFile(path)) {
                delete obj;
                std::cout << "Error: couldn't load resource '" << name << "' from path '" << path << "'" << std::endl;
                std::exit(-1);
            }

            resources[name] = new ResourceObjArr<ResourceObj>(obj, 1);
        }

        ResourceObjArr<ResourceObj> &getResource(std::string name) { return *resources[name]; }
    private:
        std::map<std::string, ResourceObjArr<ResourceObj> *> resources;
    };
}

#endif
