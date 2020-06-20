#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

int findIndex(map<string,vector<string>>myMap1, string possibleTarget){
    int index = 0;
    //cout << possibleTarget << endl;
    
    for(auto iter = myMap1.cbegin() ; iter != myMap1.end(); ++iter){
        if(iter->first==possibleTarget){
            //cout << "target " << iter->first <<" "<< index << endl;
            //cout<<index;
            return index;
        }
        index++;
    }
}


int main(){
    int numInputs = 0; //the first value taken in
    cin >> numInputs;

    int numIterations = 0; //the number of power iterations
    cin >> numIterations;

    std::map<string,vector<string>> myMap; //creating a map that accepts the unique websites as input
    //also creates a vector of strings inside the map

    string websiteFrom; //the unique website with edge from
    string websiteTo; //the unique website with edge to

    for(int i = 0; i<=numInputs; i++){ //accepts the website from
        
        cin >> websiteFrom;
        cin >> websiteTo;
                
        myMap[websiteFrom].push_back(websiteTo); //at index 0 //inserts the websiteFrom, and the websiteTo (in a vector)
        myMap[websiteTo];          
    }
    
    int index = 0;
    for(auto iter = myMap.cbegin() ; iter != myMap.end(); ++iter){
        for(int i = 0; i < iter->second.size(); i++){
            findIndex(myMap, iter->second.at(i));
        }
        index++;
    }
    
    vector<vector<double>> matrix(index, vector<double>(index, 0));
    
    int count = 0;    
    for(auto iter = myMap.cbegin(); iter != myMap.end(); iter++){
        for(int i = 0; i<iter->second.size(); ++i){
            int index = findIndex(myMap, iter -> second.at(i));
            matrix[count][index] = 1;
        }
        count++;
    }
    
    for(int i =0; i<index; i++){
        int sum = 0;
        for(int j = 0; j < index; j++){
            sum += matrix[i][j];
        }
        for (int k = 0; k < index; k++){ 
            if(sum == 0){
                matrix[i][k] = 0;
            }
            else{
                 matrix[i][k]/=sum;
            }           
        }
    }
    
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            //cout << matrix[i][j] << " ";
        }
        //cout << "\n";       
    }   
    
    vector<double> powerIterator(index, 1.00/index);
    vector<double> powerTemp(index);
    
    for(int k = 0; k<numIterations-1; k++){
        for(int i = 0; i<index; i++){
            double sum = 0;
            for(int j = 0; j<index; j++){
                sum += matrix[j][i]*powerIterator[j];                                
            }
            powerTemp[i]=sum;            
            }
        powerIterator = powerTemp;
        
    }
    
    int i = 0;
    for(auto iter = myMap.cbegin(); iter != myMap.end(); iter++){
        cout << iter->first << " ";
        printf ("%.2f\n", powerIterator[i]);
        ++i;
    }        
}