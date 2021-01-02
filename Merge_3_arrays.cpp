#include <iostream>
#include <fstream>
#include <ctime>

bool generate_file(int N, const char* fname) {
    std::ofstream outFile(fname);
    if (!outFile) return false;
    while (N-- > 0)
        outFile << ' ' << rand() % 10000;
    outFile.close();
    return true;
}

bool isSortedFile(const char* fname) {
    std::ifstream inFile;
    inFile.open(fname);
    if (!inFile)
        throw "Can not open file";
    int a, b;
    bool tr = true;
    inFile >> a;
    while (inFile.peek() != EOF) {
        inFile >> b;
        if (b < a) {
            tr = false;
            break;
        }
        a = b;
    }
    inFile.close();
    return tr;
}

bool split_file(const char* fname, const char* tmp1, const char* tmp2, const char* tmp3) {
    std::ifstream inFile(fname);
    if (!inFile) throw "Can not read file";

    std::ofstream outFile[3];

    outFile[0].open(tmp1);
    if (!outFile[0]) throw "Can not write to file";

    outFile[1].open(tmp2);
    if (!outFile[1]) throw "Can not write to file";

    outFile[2].open(tmp3);
    if (!outFile[2]) throw "Can not write to file";

    bool result = false;
    int b, a;
    unsigned char num = 0;
    inFile >> a;
    outFile[num] << a;
    while (inFile.peek() != EOF) {
        inFile >> b;
        if (b< a) {
            num++;
            num %= 3;
            result = true;
        }
        outFile[num] << ' ' << b;
        a = b;
    }
    inFile.close(); outFile[0].close(); outFile[1].close();
    return result;
}

void merge_file(const char* tmp1, const char* tmp2, const char* tmp3, const char* fname) {
    std::ofstream outFile(fname);
    if (!outFile) throw "Can not write to file";

    std::ifstream inFile[3];
    inFile[0].open(tmp1);
    if (!inFile[0]) throw "Can not read file tmp1";
    inFile[1].open(tmp2);
    if (!inFile[1]) throw "Can not read file tmp2";
    inFile[2].open(tmp3);
    if (!inFile[2]) throw "Can not read file tmp3";
    unsigned char num = 0;
    int a, b[3] = { 0 };
    inFile[0] >> b[0];
    if (inFile[1].peek() != EOF) inFile[1] >> b[1];
    if (inFile[2].peek() != EOF)
    {
        inFile[2] >> b[2];
        num = 0;
        num = (b[0] < b[1] && b[0] < b[2]) ? 0 : ((b[1] < b[0] && b[1] < b[2]) ? 1 : 2);
        outFile << ' ' << b[num]; a = b[num];
        while (inFile[num].peek() != EOF)
        {
            inFile[num] >> b[num];
            bool s1 = b[0] >= a;
            bool s2 = b[1] >= a;
            bool s3 = b[2] >= a;

            if (s1 == s2 && s1 == s3)
            {
                num = (b[0] < b[1] && b[0] < b[2]) ? 0 : ((b[1] < b[0] && b[1] < b[2]) ? 1 : 2);
            }
            else
            {
                if (s1 && s2)
                {
                    num = b[0] < b[1] ? 0 : 1;
                }
                else if (s2 && s3)
                {
                    num = b[1] < b[2] ? 1 : 2;
                }
                else if (s1 && s3)
                {
                    num = b[0] < b[2] ? 0 : 2;
                }
                else
                {
                    num = s1 ? 0 : (s2 ? 1 : 2);
                }
            }
            outFile << ' ' << b[num];
            a = b[num];
        }
    }
    else num = 2;
    unsigned char k = (num + 1) % 3, l = (num + 2) % 3;
    num = (b[k] < b[l]) ? k : l;
    outFile << ' ' << b[num]; a = b[num];
    while (inFile[num].peek() != EOF)
    {
        inFile[num] >> b[num];
        bool s1 = b[num] >= a;
        unsigned char ch;
        if (num == k)
            ch = l;
        else
            ch = k;
        bool s2 = b[ch] >= a;
        if (s1 == s2) {
            num = (b[k] < b[l]) ? k : l;
        }
        else
        {
            if (!s1)
            {
                num = ch;
            }
        }
        outFile << ' ' << b[num];
        a = b[num];
    }
    if (num == l) num = k;
    else num = l;
    outFile << ' ' << b[num];
    while (inFile[num].peek() != EOF)
    {
        inFile[num] >> a;
        outFile << ' ' << a;
    }
    outFile.close(); inFile[0].close(); inFile[1].close(); inFile[2].close();
}

int MergeFileSorting_3arrays(const char* fname, const char* outfilename) {
    char tmp1[] = "_temp_file_1.txt", tmp2[] = "_temp_file_2.txt", tmp3[] = "_temp_file_3.txt";
    bool key;
    int k = 0;
    key = split_file(fname, tmp1, tmp2, tmp3);
    while (key) {
        merge_file(tmp1, tmp2, tmp3, outfilename);
        key = split_file(outfilename, tmp1, tmp2, tmp3);
        ++k;
    }
    return k;
}


int main()
{
    clock_t tictok = clock();

    char fname[] = "data.txt";
    char outfname[] = "result.txt";
    if (!generate_file(10, fname)) {
        std::cout << "Can not create file for test!" << std::endl;
        return 1;
    }

    int N = MergeFileSorting_3arrays(fname, outfname);

    std::cout << clock() - tictok << " tics" << std::endl;

    try {
        if (isSortedFile(outfname)) {
            std::cout << "File " << outfname << " is sorted." << std::endl;
            std::cout << "Total " << N << " splits." << std::endl;
        }
        else {
            std::cout << "File " << outfname << " is not sorted." << std::endl;
        }
    }
    catch (const char* error) {
        std::cout << "Error: " << error << std::endl;
    }

    return 0;
}