#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void getData(std::vector< std::vector<int> > &all, std::vector< std::vector<int> > &max, std::vector<int> &ava, int &pro, int &res) {

    std::cerr << "In getData()..." << '\n';

    std::ifstream in;
    in.open("input.csv");

    if(!in) {
        std::cout << "File failed to open..." << '\n';
    }

    std::cerr << "File opened" << '\n';

    char c;

    int i = 0;
    
    std::vector<int> row;

    in.get(c);
    //in.get(c);
    //in.get(c);
    //Need to dynamically push items into rows and push new rows onto vectors (04/14/2022)
        while(!in.eof()) {
            in.get(c);
            std::cerr << "Looped in.get(c)..." << "\n\n";
            std::cerr << "c = " << c << '\n';
            if(c == '\n' || c == '\t' || c == '\r') {
                std::cerr << "In if(c == '\n' || c == '\t' || c == '\r')..." << '\n';

                i = 0;
                row.clear();

                std::cerr << "i = " << i << '\n';
                std::cerr << "row cleared" << '\n';                
            }
            else if(c == ',') {
                std::cerr << "In if(c == ',')..." << '\n';

                if(i == 0) {
                    std::cerr << "In if(i == 0)..." << '\n';

                    all.push_back(row);

                    std::cerr << "Called all.push_back(row)..." << '\n';
                }
                else if(i == 1) {

                    std::cerr << "In if(i == 1)..." << '\n';

                    max.push_back(row);

                    std::cerr << "Called max.push_back(row)..." << '\n';
                }

                i++;

                std::cerr << "i = " << i << '\n';

            }
            else if(i != 2 && c != ' ') {

                std::cerr << "In if(i != 2)..." << '\n';

                int ch = c - '0';

                std::cerr << "ch = " << ch << '\n';

                row.push_back(ch);

                std::cerr << "Called row.push_back(ch)..." << '\n';

                //max[j][k] = ch;
            }
            else if(i == 2 && c != ' ') {

                std::cerr << "In if(i == 2)..." << '\n';

                int ch = c - '0';

                std::cerr << "ch = " << ch << '\n';

                ava.push_back(ch);

                std::cerr << "Called ava.push_back(ch)" << '\n';
            }
        }
    pro = all.size();

    std::cerr << "pro = " << pro << '\n';

    res = ava.size();

    std::cerr << "res = " << res << '\n';
}

int main() {
    int pro, res;

    std::vector< std::vector<int> > all;
    std::vector< std::vector<int> > max;
    std::vector<int> ava;
    
    getData(all, max, ava, pro, res);

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            std::cout << all[i][j] << " ";
        }
        std::cout << '\n';
    }

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            std::cout << max[i][j] << " ";
        }
        std::cout << '\n';
    }

    for(int i = 0; i < 5; i++) {
       std::cout << ava[i] << " ";
    }
    std::cout << '\n';

    int fin[pro], end[pro];

    int nee[pro][res];

    int step = 0;

    for(int i = 0; i < pro; i++)
        fin[i] = 0;

    
    for(int i = 0; i < pro; i++) {
        for(int j = 0; j < res; j++) {
            nee[i][j] = max[i][j] - all[i][j];
        }
    }

    for(int i = 0; i < pro; i++) {
        for(int j = 0; j < pro; j++) {
            if(fin[j] == 0) {
                int boo = 0;
            
                for(int k = 0; k < res; k++) {
                    if(nee[j][k] > ava[k]) {
                        boo = 1;
                        break;
                    }
                }
            
                if(boo == 0) {
                    end[step++] = j;

                    for(int l = 0; l < res; l++)
                        ava[l] += all[j][l];
                    
                    fin[j] = 1;
                }
            }
        }
    }

    int boo = 1;

    for(int i = 0; i < pro; i++) {
        if(fin[i] == 0) {
            boo = 0;
            std::cout << "Sequence is unsafe\n";
            break;
        }
    }

    if(boo == 1) {
        std::cout << "Safe sequence is: \n";
        
        for(int i = 0; i < pro - 1; i++)
            std::cout << " P" << end[i] << " to";
        
        std::cout << " P" << end[res-1] << '\n';
    }
    return 0;
}