#include <iostream>
#include <map>
#include <fstream>
#include <string>

class PatriciaNode
{
public:
    bool is_node;
    bool delete_node = false;
    std::map<std::string,PatriciaNode*> children;

    PatriciaNode()
    {
        this->is_node = false;

    }

    PatriciaNode(std::string archivo)
    {
        std::ifstream fe(archivo);
        std::string s;
        while (getline(fe,s)) {
            insert(s);
        }

    }
    void insert(std::string palabra)
    {
        PatriciaNode* curr = this;
        for (int i = 0; i < palabra.length(); i++)
        {
            std::string s;
            s.push_back(palabra[i]);
            if (curr->children[s] == nullptr)
                curr->children[s] = new PatriciaNode();

            curr = curr->children[s];
        }
        curr->is_node = true;
    }
    bool deletion(PatriciaNode*& curr, std::string key)
    {
        if (curr == nullptr)
            return false;

        if (key.length())
        {
            std::string s;
            s.push_back(key[0]);
            if (curr != nullptr &&
                curr->children[s] != nullptr &&
                deletion(curr->children[s], key.substr(1)) &&
                curr->is_node == false)
            {
                if (!haveChildren(curr))
                {
                    delete curr;
                    curr = nullptr;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        if (key.length() == 0 && curr->is_node)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;

                return true;
            }

            else
            {
                curr->is_node = false;

                return false;
            }
        }

        return false;
    }
    bool search(std::string key)
    {
        if (this == nullptr)
            return false;

        PatriciaNode* curr = this;
        for (int i = 0; i < key.length(); i++)
        {
            std::string s;
            s.push_back(key[i]);
            curr = curr->children[s];

            if (curr == nullptr)
                return false;
        }

        return curr->is_node;
    }
    bool haveChildren(PatriciaNode const* curr)
    {
        for (auto it = children.begin(); it != children.end(); it++)
            if ((*it).second)
                return true;

        return false;
    }

    void print() {
        PatriciaNode* curr = this;
        std::string palabra = "";
        std::string temp;
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            if(it->second){
                temp = palabra + it->first;
                print(temp, it->second);
                temp = palabra;
            }
        }
    }

    void print(std::string palabra, PatriciaNode* curr) {
        std::string temp;
        if(curr->is_node && curr->children.empty()) {
            std::cout << palabra << std::endl;
            return;
        }
        if(curr->is_node) {
            std::cout << palabra << std::endl;
        }
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            if(it->second){
                temp = palabra + it->first;
                print(temp, it->second);
                temp = palabra;
            }
        }
    }

    void convert_to_patricia(){
        PatriciaNode* curr = this;
        for(auto it = curr->children.begin(); it != curr->children.end(); it++) {
            convert_to_patricia((*it).first,(*it).second,curr);
        }
        kill_zone(curr);
    }

    void convert_to_patricia(std::string palabra, PatriciaNode* curr, PatriciaNode* root){
        if(curr->is_node && curr->children.empty()) {
            return;
        }
        if(curr->children.size() == 1 && !curr->is_node){
            root->children.insert({palabra + (*curr->children.begin()).first,(*curr->children.begin()).second});
            curr->delete_node = true;
            convert_to_patricia(palabra + (*curr->children.begin()).first,(*curr->children.begin()).second,root);
            return;
        } else {
            for(auto it = curr->children.begin(); it != curr->children.end(); it++) {
                convert_to_patricia((*it).first,(*it).second,curr);
            }
        }
    }
    void kill_zone(PatriciaNode* curr){
        for(auto it = curr->children.begin(); it != curr->children.end(); it++) {
            if((*it).second->delete_node)
                (*it).second = nullptr;
            else if(!(*it).second->is_node){
                kill_zone((*it).second);
            }
        }
    }
};

class TriesNode
{
public:
    bool is_node;
    std::map<std::string,TriesNode*> children;

    TriesNode()
    {
        this->is_node = false;

    }

    TriesNode(std::string archivo)
    {
        std::ifstream fe(archivo);
        std::string s;
        while (getline(fe,s)) {
            insert(s);
        }

    }
    void insert(std::string palabra)
    {
        TriesNode* curr = this;
        for (int i = 0; i < palabra.length(); i++)
        {
            std::string s;
            s.push_back(palabra[i]);
            if (curr->children[s] == nullptr)
                curr->children[s] = new TriesNode();

            curr = curr->children[s];
        }

        curr->is_node = true;
    }
    bool deletion(TriesNode*& curr, std::string key)
    {
        if (curr == nullptr)
            return false;

        if (key.length())
        {
            std::string s;
            s.push_back(key[0]);
            if (curr != nullptr &&
                curr->children[s] != nullptr &&
                deletion(curr->children[s], key.substr(1)) &&
                curr->is_node == false)
            {
                if (!haveChildren(curr))
                {
                    delete curr;
                    curr = nullptr;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        if (key.length() == 0 && curr->is_node)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;

                return true;
            }

            else
            {
                curr->is_node = false;

                return false;
            }
        }

        return false;
    }
    bool search(std::string key)
    {
        if (this == nullptr)
            return false;

        TriesNode* curr = this;
        for (int i = 0; i < key.length(); i++)
        {
            std::string s;
            s.push_back(key[i]);
            curr = curr->children[s];

            if (curr == nullptr)
                return false;
        }

        return curr->is_node;
    }
    bool haveChildren(TriesNode const* curr)
    {
        for (auto it = children.begin(); it != children.end(); it++)
            if ((*it).second)
                return true;

        return false;
    }

    void print() {
        TriesNode* curr = this;
        std::string palabra;
        std::string temp;
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            temp = palabra + it->first;
            print(temp, it->second);
            temp = palabra;
        }
    }

    void print(std::string palabra, TriesNode* curr) {
        std::string temp;
        if(curr->is_node && curr->children.empty()) {
            std::cout << palabra << std::endl;
            return;
        }
        if(curr->is_node) {
            std::cout << palabra << std::endl;
        }
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            temp = palabra + it->first;
            print(temp, it->second);
            temp = palabra;
        }
    }

    PatriciaNode convert_to_patricia(){
        PatriciaNode patricia;
        TriesNode* curr = this;
        std::string palabra;
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            palabra.push_back(it->first[0]);
            convert_to_patricia(palabra, it->second, patricia);
            palabra.clear();
        }
        patricia.convert_to_patricia();
        return patricia;
    }

    void convert_to_patricia(std::string palabra, TriesNode* curr, PatriciaNode& patricia) {
        std::string temp;
        if(curr->is_node && curr->children.empty()) {
            patricia.insert(palabra);
            return;
        }
        if(curr->is_node) {
            patricia.insert(palabra);
        }
        for(auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            temp = palabra + it->first;
            print(temp, it->second);
            temp = palabra;
        }
    }
};

int main() {
    TriesNode tries("ApellidosDeLaLibertad.txt");
    PatriciaNode patricia = tries.convert_to_patricia();
    patricia.print();
    return 0;
}
