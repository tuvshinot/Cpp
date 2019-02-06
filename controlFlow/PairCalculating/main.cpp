#include <iostream>
#include <vector>
#include <string>

using namespace std;

int calculate_pairs(vector<int> vec) {
    //----WRITE YOUR CODE BELOW THIS LINE----
    int result {0};
    int size = vec.size();
    
    if(size != 0 || size != 1) {
        for(int i = 0; i < size ; i ++) {
            for(int j = i + 1; j < size; j++) {
                result += vec[i]*vec[j];
            }
        }
    }
//    
//    //----WRITE YOUR CODE ABOVE THIS LINE----
//    //----DO NOT MODIFY THE CODE BELOW THIS LINE----
    return result;
}

int main() {
    vector<int> myints{1,2,3};
    
//    for(auto val : myints)
//        cout << val << endl;
//    cout << "Size of " << myints.size() << endl;

    auto result = calculate_pairs(myints);
    cout << result << endl;   
    return 0;
}


