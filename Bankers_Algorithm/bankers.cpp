#include <iostream> //allows output to console
#include <fstream> //allows file input
#include <vector> //allows dynamic arrays
#include <string> //allows #'s of more than 9
#include <ctype.h> //allows checking if char is numeric

//gathers data from input file to be used in allocated, max, and available vectors and calculates # of processes and # of resources
void getData(std::vector< std::vector<int> > &all, std::vector< std::vector<int> > &max, std::vector<int> &ava, int &pro, int &res) {
    std::ifstream in; //opening input file
    in.open("input.csv");

    if(!in) { //input file error checking
        std::cerr << "File failed to open..." << '\n';
        exit(1);
    }

    char c; //char for reading file by characters
    int i = 0; //iterator for different vectors
    std::string word; //string to hold value

    std::vector<int> row; //vector to hold all values in row

        while(!in.eof()) { //continues reads until end of file
            in.get(c); //reads character
            if(!isdigit(c)) { //if c is not numeric, check word 
                if(word != "") { //if word is not blank, convert word to int
                    int num = std::stoi(word); //convert word to int

                    if(i == 2) { //if iterator is 2, add to available vector
                        ava.push_back(num);
                    }
                    
                    row.push_back(num); //pushes num onto row
                }

                word = ""; //resets word
            }
            else if(isdigit(c) && c != ' ' && c != ',') { //adds c to string if c is numeric
                word.push_back(c);
            }

            if(c == '\n' || c == '\t' || c == '\r') { //checks if c is a newline char
                i = 0; //resets vector iterator
                row.clear(); //clears row values            
            }
            else if(c == ',') { //checks if c is ,
                if(i == 0) { //checks if row adds to allocate vector
                    all.push_back(row); //pushes row into allocate vector
                }
                else if(i == 1) { //checks if row adds to max vector
                    max.push_back(row); //pushes row into max vector
                }
                row.clear(); //clears row values            
                i++; //vector iterator increases
            }
        }

    pro = all.size(); //assigns # of processes to # of rows in allocate vector
    res = ava.size(); //assigns # of resources to # of items in available vector
}

int main() {
    int pro, res; //to hold # of processes and resources

    std::vector< std::vector<int> > all; //2d vector of allocated resources
    std::vector< std::vector<int> > max; //2d vector of max resources
    std::vector<int> ava; //vector of available resources
    
    getData(all, max, ava, pro, res); //inputs data from file into vectors and variables

    std::cout << "\n***Alloc resource table***\n"; //Label outputted table
    for(int i = 0; i < pro; i++) { //Output all values in alloc vector as table
        for(int j = 0; j < res; j++) {
            std::cout << all[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    std::cout << "***Max resource table***\n"; //Label outputted table
    for(int i = 0; i < pro; i++) { //Output all values in max vector as table
        for(int j = 0; j < res; j++) {
            std::cout << max[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    std::cout << "***Available resource list***\n"; //Label outputted list
    for(int i = 0; i < res; i++) {
       std::cout << ava[i] << " "; //Output all values in available vector as list
    }

    std::cout << "\n\n";

    int fin[pro]; //vectors for determining finished processes
    int end[pro]; //vector for holding safe seq order

    int nee[pro][res]; //vector for needed resources

    int step = 0; //index

    for(int i = 0; i < pro; i++) //initialize all finish values as 0
        fin[i] = 0;

    
    for(int i = 0; i < pro; i++) { //for calculating needed resources
        for(int j = 0; j < res; j++) {
            nee[i][j] = max[i][j] - all[i][j];
        }
    }

    std::cout << "***Needed resource list***\n"; //Label outputted list
    for(int i = 0; i < pro; i++) { //output all values in need vector as table
        for(int j = 0; j < res; j++) {
            std::cout << nee[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    for(int i = 0; i < pro; i++) {
        for(int j = 0; j < pro; j++) { //iterate through all processes
            if(fin[j] == 0) { //if process not finished
                int boo = 0; //safe unbool
            
                for(int k = 0; k < res; k++) { //iterate through all resources
                    if(nee[j][k] > ava[k]) { //if needed  > available resources, set unsafe bool to false
                        boo = 1;
                        break;
                    }
                }
            
                if(boo == 0) { //if unsafe bool is false
                    end[step++] = j; 

                    for(int l = 0; l < res; l++) //iterate through all resources
                        ava[l] += all[j][l]; //add allocated resource for process to available
                    
                    fin[j] = 1; //set process to finished
                }
            }
        }
    }

    int boo = 1; //set safe bool to true 

    for(int i = 0; i < pro; i++) { //iterate through all processes
        if(fin[i] == 0) { //if process is unfinished, print unsafe
            boo = 0;
            std::cout << "Sequence is unsafe\n";
            break;
        }
    }

    if(boo == 1) { //if safe bool stays true, print safe sequence order
        std::cout << "Safe sequence is: \n";
        
        for(int i = 0; i < pro - 1; i++) //iterate through processes - 1
            std::cout << " P" << end[i] << " to"; //print safe process order
        
        std::cout << " P" << end[pro-1] << '\n'; //print last process
    }
    return 0;
}