#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm> 

using namespace std;

//design

/*
FileSystem (Directory([[Directory] | [File(String)]]))
Classes: FileSystem, Directory, File, Content
*/

class FileSystem
{
public:
    FileSystem()
    {
    }

    vector<string> ls(string path)
    {
        auto curr = getNode(path);

        if (curr->isFile)
        {
            return {split(path, '/').back()};
        }

        vector<string> result;
        for (const auto &child : curr->children)
        {
            result.emplace_back(child.first);
        }
        sort(result.begin(), result.end());
        return result;
    }

    void mkdir(string path)
    {
        auto curr = putNode(path);
        curr->isFile = false;
    }

    void addContentToFile(string filePath, string content)
    {
        auto curr = putNode(filePath);
        curr->isFile = true;
        curr->content += content;
    }

    string readContentFromFile(string filePath)
    {
        return getNode(filePath)->content;
    }

private:
    struct TrieNode
    {
        bool isFile;
        unordered_map<string, TrieNode *> children;
        string content;
    };

    TrieNode *root_;

    TrieNode *getNode(const string &path)
    {
        vector<string> parts = split(path, '/');
        auto curr = root_;
        for (const auto &str : parts)
        {
            if (curr)
                curr = curr->children[str];
        }
        return curr;
    }

    TrieNode *putNode(const string &path)
    {
        vector<string> parts = split(path, '/');
        auto curr = root_;
        for (const auto &str : parts)
        {
            if (!curr->children.count(str))
            {
                curr->children[str] = new TrieNode();
            }
            curr = curr->children[str];
        }
        return curr;
    }

    vector<string> split(const string &str, const char delimiter)
    {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter))
        {
            if (!token.empty())
            {
                tokens.emplace_back(token);
            }
        }
        return tokens;
    }
};

int main() {
    cout << "Hello world\n";
    cout << "Nishant" << endl;
   /*
    FileSystem* obj = new FileSystem();
    string path = "/a/b/c";
    obj->mkdir(path);
    */
    //for(const auto& str : output) {
    //    cout<< str << endl;
    //}

}