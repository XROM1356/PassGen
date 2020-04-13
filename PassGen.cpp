#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include <vector>
#include <cstdlib> 
#include <unistd.h> 
using namespace std;

class Opts
{
private:

    static constexpr int minLen = 8;
    static constexpr int maxLen = 16;
    static constexpr int minNum = 1;
    static constexpr int maxNum = 20;
    int passLen = minLen; 
    int passNum = minNum; 
    bool useNums = false;
    bool useAlpha = false; 
    bool useSign = false; 
    void usage(const char* progName); 
public:
    Opts(int argc, char **argv); 
    int getLen() const
    {
        return passLen;   
    }
    int getNum() const
    {
        return passNum;   
    }
    bool isNums() const
    {
        return useNums;   
    }
    bool isAlpha() const
    {
        return useAlpha;   
    }
    bool isSign() const
    {
        return useSign;   
    }
};

static const string set_alpha = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
static const string set_digit = "0123456789";
static const string set_special = ".,<>?!/|\\@#$%^&*()[]";

string passgen(int len, const std::string &letters)
{
    assert(letters.length() != 0);

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<unsigned long> dist(0, letters.length() - 1);

    string passwd;
    for (int i = 0; i < len; ++i) {
        passwd += letters[dist(gen)];
    }

    return passwd;
}

vector<string> passgen(const Opts &opts)
{
    string letters;

    if (opts.isAlpha()) letters += set_alpha;
    if (opts.isNums()) letters += set_digit;
    if (opts.isSign()) letters += set_special;

    vector<string> pass_list;
    for (int i = 0; i < opts.getNum(); ++i) {
        pass_list.push_back(passgen(opts.getLen(), letters));
    }

    return pass_list;
}

int main(int argc, char **argv)
{
    Opts op(argc, argv);
    for (const std::string &pass : passgen(op)) {
        cout << pass << endl;
    }

    return 0;
}

Opts::Opts(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "l:n:0ash")) != -1) {
        switch (opt) {
        case 'l': 
            passLen = strtol(optarg,nullptr,10);
            if (passLen < minLen || passLen > maxLen) {
                cerr<<"passLen must be from 8 to 16\n";
                usage(argv[0]);
            }
            break;
        case 'n': 
            passNum = strtol(optarg,nullptr,10);
            if (passNum < minNum || passNum > maxNum) {
                cerr<<"passNum must be from 1 to 20\n";
                usage(argv[0]);
            }
            break;
        case '0': 
            useNums = true;
            break;
        case 'a': 
            useAlpha = true;
            break;
        case 's': 
            useSign = true;
            break;
        case 'h': 
        case '?': 
        case ':': 
            usage(argv[0]); 
        }
    }

    if (!useNums && !useAlpha && !useSign) {
        useAlpha = useNums = useSign = true;
    }
}

void Opts::usage(const char* progName)
{
    cout<<"Usage: "<<progName<<" [-l pass_len] [-n pass_num] [-0] [-a] [-s]\n";
    exit(1);
}
