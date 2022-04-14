#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void getData(std::vector< std::vector<int> > all, std::vector< std::vector<int> > max, std::vector<int> ava, int &pro, int &res) {
    std::ifstream in;
    in.open("input.csv");

    char c;

    int i = 0;
    int j = 0;
    int k = 0;
    
    //Need to dynamically push items into rows and push new rows onto vectors (04/14/2022)
    while(!in.eof()) {
        while(in.get(c)) {
            if(c == ' ')
                k++;
            else if(c == '\n' || c == '\t' || c == '\r') {
                j++;
                i = 0;
                k = 0;
            }
            else if(c == ',') {
                i++;
                k = 0;
            }
            else if(i == 0) {
                int ch = c - '0';
                all[j][k] = ch;
            }
            else if(i == 1) {
                int ch = c - '0';
                max[j][k] = ch;
            }
            else if(i == 2) {
                int ch = c - '0';
                ava[k] = ch;
            }
        }
    }
    pro = j;
    res = ava.size();
}

int main() {
    int pro, res;

    pro = 5;
    res = 3;

    std::vector< std::vector<int> > all;
    std::vector< std::vector<int> > max;
    std::vector<int> ava;

    int fin[pro], end[pro];
    int nee[pro][res];

    int step = 0;

    for(int i = 0; i < pro; i++)
        fin[i] = 0;
    
    for(int j = 0; j < pro; j++) {
        for(int k = 0; k < res; k++)
            nee[j][k] = max[j][k] - all[j][k];
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