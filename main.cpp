#include <iostream>
#include <fstream>
#include <vector>


void printVector(std::vector<std::string>& vect){ 
    for(int i = 0; i<vect.size(); i++){
        std::cout << vect[i] << " ";
    }
}



int main() {

    std::string text;

    std::vector<std::string> timestamp;
    std::vector<std::string> value;

    // Read from the text file
    std::ifstream file("data.txt");
 
    while(getline(file, text)) {
        text = text.erase(text.find_last_not_of(" \n\r\t")+1);

        int splitPoint = text.find(" ");

        //pushing individual items into their corresponding vectors
        timestamp.push_back(text.substr(0, splitPoint));
        value.push_back(text.substr(splitPoint + 1, text.length()-2));

    }
    std::cout << " " << std::endl;
    printVector(timestamp);
    std::cout << " " << std::endl;
    printVector(value);


    // Close the file
    file.close();
}