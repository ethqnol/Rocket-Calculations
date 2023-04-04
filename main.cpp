#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>



void printVector(std::vector<int>& vect){ 
    for(int i = 0; i<vect.size(); i++){
        std::cout << vect[i] << " ";
    }
}

std::vector<int> toIntVect(std::vector<std::string> vect){
    std::vector<int> newVect;
    for (int i=0; i< vect.size(); i++){
        int num = atoi(vect.at(i).c_str());
        newVect.push_back(num);
    }
    return newVect;
}

std::vector<std::vector<std::string> > getAltitudeReadings(){
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
    std::vector<std::vector<std::string> > final;
    final.push_back(timestamp);
    final.push_back(value);
    file.close(); 
    return final;
}


int main() {
    bool atPeak = false;
    double ffVelo;
    while (true) { 
        
        std::vector<int> timestamp = toIntVect(getAltitudeReadings()[0]);

        std::vector<int> altitudes = toIntVect(getAltitudeReadings()[1]);

        int sizeAlt = altitudes.size();
        

        printVector(timestamp);
        std::cout << " " << std::endl;
        printVector(altitudes);
        std::cout << " " << std::endl;
        if (atPeak == false && sizeAlt > 1 && altitudes[sizeAlt - 1] < altitudes[sizeAlt - 2] && altitudes[sizeAlt] < altitudes[sizeAlt - 6]) {
            atPeak = true; // apogee passed
        }


        if (atPeak) {
            // get the last 10 altitude readings
            std::vector<int> lastAltitudes(sizeAlt - 11, sizeAlt - 1);
            
            // calculate the average altitude change over the last 10 readings
            double changeInAlt = 0.0;
            for (int i = 1; i < lastAltitudes.size(); i++) {
                changeInAlt += lastAltitudes[i-1] - lastAltitudes[i];
            }
            double avAltChange = changeInAlt / 9.0;

            // calculate the free fall velocity based on the average altitude change
            ffVelo = sqrt(2.0 * 9.81 * abs(avAltChange));
            std::cout << "Apogee Detected | Free Fall Velocity: " << ffVelo << " m/s" << std::endl;
        }

        // stop calculating free fall velocity when altitude is below 5 meters
        if (altitudes[sizeAlt - 1] < 5) {
            std::cout << "Landing Detected" << std::endl;
            break;
        }

        // wait for 0.1 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  
    return 0;
    
}
