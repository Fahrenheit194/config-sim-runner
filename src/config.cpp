#include "config.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

string Config::trim(string s)
{
    int a = 0;
    while (a < (int)s.size() && (s[a] == ' ' || s[a] == '\t' || s[a] == '\r' || s[a] == '\n')) a++;

    int b = (int)s.size() - 1;
    while (b >= a && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r' || s[b] == '\n')) b--;

    if (b < a) return "";
    return s.substr(a, b - a + 1);
}

int Config::findKey(string key)
{
    for (int i = 0; i < count; i++)
    {
        if (keys[i] == key) return i;
    }
    return -1;
}

void Config::set(string key, string val)
{
    int idx = findKey(key);
    if (idx != -1)
    {
        vals[idx] = val;
        return;
    }

    if (count >= MAX_KEYS)
    {
        return;
    }

    keys[count] = key;
    vals[count] = val;
    count++;
}

bool Config::load(string path)
{
    ifstream in(path);
    if (!in)
    {
        cout << "couldn't open config: " << path << "\n";
        return false;
    }

    count = 0;

    string line;
    int lineNo = 0;

    while (getline(in, line))
    {
        lineNo++;

        int hashPos = -1;
        for (int i = 0; i < (int)line.size(); i++)
        {
            if (line[i] == '#')
            {
                hashPos = i;
                break;
            }
        }
        if (hashPos != -1)
        {
            line = line.substr(0, hashPos);
        }

        line = trim(line);
        if (line == "") continue;

        int eq = -1;
        for (int i = 0; i < (int)line.size(); i++)
        {
            if (line[i] == '=')
            {
                eq = i;
                break;
            }
        }

        if (eq == -1)
        {
            cout << "config error (" << path << ":" << lineNo << "): expected key = value\n";
            cout << "line: " << line << "\n";
            return false;
        }

        string key = trim(line.substr(0, eq));
        string val = trim(line.substr(eq + 1));

        if (key == "" || val == "")
        {
            cout << "config error (" << path << ":" << lineNo << "): empty key or value\n";
            return false;
        }

        set(key, val);
    }

    return true;
}

bool Config::save(string path)
{
    ofstream out(path);
    if (!out)
    {
        cout << "couldn't write file: " << path << "\n";
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        out << keys[i] << " = " << vals[i] << "\n";
    }

    return true;
}

string Config::getString(string key, string defVal)
{
    int idx = findKey(key);
    if (idx == -1) return defVal;
    return vals[idx];
}

bool Config::getDouble(string key, double defVal, double& out)
{
    int idx = findKey(key);
    if (idx == -1)
    {
        out = defVal;
        return true;
    }

    string s = vals[idx];
    char* endPtr = nullptr;
    double v = strtod(s.c_str(), &endPtr);

    if (endPtr == s.c_str() || *endPtr != '\0')
    {
        cout << "bad number for " << key << ": " << s << "\n";
        return false;
    }

    out = v;
    return true;
}

bool Config::getInt(string key, int defVal, int& out)
{
    int idx = findKey(key);
    if (idx == -1)
    {
        out = defVal;
        return true;
    }

    string s = vals[idx];
    char* endPtr = nullptr;
    long v = strtol(s.c_str(), &endPtr, 10);

    if (endPtr == s.c_str() || *endPtr != '\0')
    {
        cout << "bad int for " << key << ": " << s << "\n";
        return false;
    }

    out = (int)v;
    return true;
}
