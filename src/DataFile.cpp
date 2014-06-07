#include "DataFile.h"
#include <cstring>
#include <iostream>

bool DataFile::parse(const std::string& path)
{
    char next;

    this->file.open(path.c_str());

    if (this->file.bad())
    {
        std::cerr << "Error reading file " << path << std::endl;
    }
    else
    {
        bool done = false;
        while ((!this->file.eof()) && this->file.good() && !done)
        {
            do
            {
                next = this->file.get();
            }
            while (next == ' ' || next == '\t' || next == '\n' || next == '\r');

            if (next == '#')
            {
                this->file.getline(buffer, 2048, '\n');
                if (strcmp(buffer, "end") == 0)
                {
                    done = true;
                }
            }
            else
            {
                this->file.putback(next);
                this->file.getline(buffer, 2048, '\n');
                std::stringstream* ss = new std::stringstream(buffer);
                this->lines.push(ss);
            }
        }
    }

    this->file.close();

    return true;
}