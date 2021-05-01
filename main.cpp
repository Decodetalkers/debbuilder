#include <cstdlib>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/value.h>
#include <string>
using namespace Json;
int main()
{
    Json::Value root;
    Json::Reader reader;
    const char* filename = "build.json";
    std::ifstream is;
    is.open (filename, std::ios::binary );
    if (reader.parse(is, root))
    {
        std::string name;
        std::string version;
        std::string size;
        std::string Priority;
        std::string Section;
        std::string Maintainer;
        std::string Architecture;
        std::string dependence;
        std::string dev_dependence;
        std::string source;
        std::string description;
        if (!root["name"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.
            name = root["uploadid"].asString();

    // 访问节点，Return the member named key if it exist, defaultValue otherwise.
        name = root.get("name", "null").asString();
        version = root.get("version", "null").asString();
        size = root.get("size", "null").asString();
        Priority = root.get("Priority", "null").asString();
        Section = root.get("Section", "null").asString();
        Maintainer = root.get("Maintainer", "null").asString();
        Architecture = root.get("Architecture", "null").asString();
        dependence = root.get("dependence", "null").asString();
        dev_dependence = root.get("dev-dependence", "null").asString();
        source = root.get("source", "null").asString();
        description = root.get("Description", "null").asString();
        std::cout<<name<<"  "<<version<<"  "<<size<<"  "<<dependence<<" "<<dev_dependence<<std::endl;

    // 得到"files"的数组个数
        int file_size = root["files"].size();

    // 遍历数组
        for(int i = 0; i < file_size; ++i)
        {
            Json::Value val_image = root["files"][i]["git"];
            //int image_size = val_image.size();
            //for(int j = 0; j < image_size; ++j)
            //{
            std::string url = "git clone "+val_image[0]["url"].asString();
            std::string do_it = val_image[0]["do"].asString();
            //std::cout<<url<<std::endl;
            //std::cout<<do_it<<std::endl;
            Json::Value install = val_image[0]["install"];
            std::string run = install[0]["run"].asString();
            std::string location = install[0]["location"].asString();
            std::system(url.c_str());
            std::system(do_it.c_str());
            std::cout << "test" << std::endl;
            std::string project_name = "mkdir "+name;
            std::system(project_name.c_str());
            std::cout << "test" << std::endl;
            std::string do_first="cd "+name+" && mkdir opt && mkdir opt/durapps && mkdir opt/durapps/thesnake && cd -";
            std::system(do_first.c_str());
            std::string makedeb="cp "+run+" "+name+location;
            std::cout << makedeb << std::endl;
            std::system(makedeb.c_str());
            //std::cout<<run<<std::endl;
            //std::cout<<location<<std::endl;

            //}
        }
        //before
        {
            std::cout << "before install to do" << std::endl;
            std::string before = "sudo apt install "+dev_dependence;
            system(before.c_str());
        }
        //Make the control
        {
            std::cout << "test" << std::endl;
            system("pwd");
            std::string enter = "cd "+name+"&& mkdir DEBIAN";
            //std::cout << enter << std::endl;
            system(enter.c_str());
            system("ls");
            //std::system("mkdir DEBIAN");
            std::string file = name+"/DEBIAN/control";
            std::ofstream control;
            control.open(file);
            control<<"Package:" <<name<<std::endl;
            control<<"Priority:" <<Priority<<std::endl;
            control<<"Section:" <<Section<<std::endl;
            control<<"Maintainer:" <<Maintainer<<std::endl;
            control<<"Architecture:" <<Architecture<<std::endl;
            control<<"Source:" <<source<<std::endl;
            control<<"Version:" <<version<<std::endl;
            control<<"Depends:" <<dependence<<std::endl;
            control<<"Description:" <<description<<std::endl;
            system("cd ..");
        }
        {
            std::string build = "fakeroot dpkg -b "+name;
            system(build.c_str());
        }
        //finally to do
        {

            system(("rm -rf "+name).c_str());
        }
        //std::cout<<name<<std::endl;
    }

    is.close();
    return 0;

}
