#pragma once

#include "error.hpp"
#include "result.hpp"
#include "tree.hpp"
#include <fstream>

template<typename T>
class ResultFileHandler
{
public:
	void write(Result<T, Error> &result, std::string file_path);
    void clear(std::string file_path);
};

template<>
class ResultFileHandler<Tree *>
{
public:
	void write(Result<Tree *, Error> &result, std::string file_path);
    void clear(std::string file_path);
};


template<typename T>
inline void ResultFileHandler<T>::write(Result<T, Error> &result, std::string file_path)
{
    std::ofstream file(file_path, std::ios::app);

    if (!result.is_success())
    {
        std::vector<Error *> errs = result.get_errors();

        for (std::vector<Error *>::iterator it = errs.begin(); it != errs.end(); it++)
        {
            file << (*it)->get_message() << "\n";
        }
    }
}

inline void ResultFileHandler<Tree *>::write(Result<Tree *, Error> &result, std::string file_path)
{
    std::ofstream file(file_path, std::ios::app);

    static int tree_count = 0;
    file << "\nTree " << ++tree_count << ")\n";

    if (!result.is_success())
    {
        std::vector<Error *> errs = result.get_errors();
        for (std::vector<Error *>::iterator it = errs.begin(); it != errs.end(); it++)
        {
            file << (*it)->get_message() << "\n";
        }
    }
    else
    {
        file << result.get_value()->get_formula_to_string() << "\n";
    }
}

template<typename T>
inline void ResultFileHandler<T>::clear(std::string file_path)
{
    std::ofstream file(file_path, std::ios::trunc);
}

inline void ResultFileHandler<Tree *>::clear(std::string file_path)
{
    std::ofstream file(file_path, std::ios::trunc);
}