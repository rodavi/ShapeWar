//
// Created by rodrigo on 19/08/24.
//
#include <string>
#include <vector>
#include <fstream>
#ifndef READ_FILE_H
#define READ_FILE_H

struct Configuration {

    std::string type_config;
    std::vector<float> values;

};


class read_file {
public:
    std::string filename;
    std::vector<Configuration> m_config;
    std::string line;



    Configuration single_config(const std::string& line, const char separator = ' ') {
        unsigned int begin{0};
        unsigned int final{0};
        bool flag_separation{false};
        std::vector<std::string> elem;
        Configuration config_temp;
        bool n_elem = false;

        for(int i = 0; i < line.size(); ++i) {
            if(i+1!=line.size()) {
                if(line[i] == separator) {
                    if(flag_separation==false) {
                        if(n_elem==0) {
                            config_temp.type_config = line.substr(begin, final);
                        }
                        else {
                            config_temp.values.push_back(std::stof(line.substr(begin, final)));
                            //line.erase(begin, i);
                        }
                        flag_separation = true;
                        begin =i+1;
                        final = 0;
                        n_elem = true;
                    }else {
                        ++begin;
                    }
                }
                else {
                    flag_separation = false;
                    ++final;
                }
            }
            else {
                config_temp.values.push_back(std::stof(line.substr(begin, std::string::npos)));
                n_elem=false;
                //elem.push_back(line.substr(begin, std::string::npos));
            }
        }
        return config_temp;
    }

    read_file(const std::string& read_file): filename(read_file) {
        std::fstream fs;
        fs.open(filename, std::ios::in);
        while(!fs.eof() && fs.is_open()) {

            std::getline(fs, line);
            m_config.push_back(single_config(line));

        }
        fs.close();
    }

    std::vector<Configuration> get_config() {
        return m_config;
    }
};



#endif //READ_FILE_H
