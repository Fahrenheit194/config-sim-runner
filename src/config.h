#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

class Config
{
public:
    bool load(string path);
    bool save(string path);

    string getString(string key, string defVal);
    bool getDouble(string key, double defVal, double& out);
    bool getInt(string key, int defVal, int& out);

private:
    static const int MAX_KEYS = 256;

    string keys[MAX_KEYS];
    string vals[MAX_KEYS];
    int count;

    int findKey(string key);
    void set(string key, string val);

    string trim(string s);
};

#endif
