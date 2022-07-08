#include <cstdlib>

#include <iostream>
#include <vector>
#include <regex>

namespace
{

class app
{
public:
    app(int argc, char* argv[])
    {
        print_help = false;
        exit_code = EXIT_SUCCESS;

        for(int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            if ((arg == "--help") || (arg == "-h"))
            {
                print_help = true;
            }
            else
            {
                try
                {
                    pattern_list.push_back(std::regex(arg));
                }
                catch (std::exception const & ex)
                {
                    std::cerr << "error: failed to create regular expression: " << ex.what() << std::endl;
                    print_help = true;
                    exit_code = EXIT_FAILURE;
                }
            }
        }
    }

    int run()
    {
        if (!print_help)
        {
            size_t count = 0;
            std::cout << count;

            while (std::cin.good())
            {
                std::string line;
                std::getline(std::cin, line);
                if (matches(line))
                {
                    count++;
                    std::cout << '\r' << count;
                }
            }
        
            std::cout << std::endl;
        }
        else
        {
            print_usage();
        }

        return exit_code;
    }

private:
    void print_usage() const
    {
        std::cout << R"(count, Copyright (c) 2022 Falk Werner
count matching lines from stdin

Usage:
    count <pattern> ...
)";
    }

    bool matches(std::string const & line) const
    {
        if (pattern_list.empty()) { return true; }

        for (auto const & pattern: pattern_list)
        {
            std::smatch match;
            if (std::regex_search(line, match, pattern))
            {
                return true;
            }
        }

        return  false;
    }

    std::vector<std::regex> pattern_list;
    bool print_help;
    int exit_code;
};

}


int main(int argc, char* argv[])
{
    int exit_code = EXIT_FAILURE;

    try
    {
        app count(argc, argv);
        exit_code = count.run();
    }
    catch (std::exception const & ex)
    {
        std::cerr << "error: " << ex.what() << std::endl;;
    }
    catch (...)
    {
        std::cerr << "error: unknown error" << std::endl;;
    }
    
    return exit_code;
}
