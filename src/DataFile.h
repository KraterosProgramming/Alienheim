#pragma once
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

class DataFile
{
public:
    class String
    {
    public:
        String() { }
        String(const std::string& text)
        {
            this->text = text;
        }

        operator std::string()
        {
            return this->text;
        }

        std::string text;
    };

    bool parse(const std::string& path);

    std::ifstream file;
    std::queue<std::stringstream*> lines;
    char buffer[2048];
};

template<class Stream>
Stream& operator<<(Stream& stream, const DataFile::String& str)
{
    return stream << "\"" << str.text << "\"";
}

template<class Stream>
Stream& operator>>(Stream& stream, DataFile::String& str)
{
    char buffer[1024];
    stream.getline(buffer, 1024, '\"');
    stream.getline(buffer, 1024, '\"');
    str.text = buffer;
    return stream;
}