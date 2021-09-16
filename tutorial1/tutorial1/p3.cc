#include<iostream>
#include<string>
#include "power.cc"

using namespace std;

int main(){
	int first, second, result;
	cout << "Please enter two integers: ";
	cin >> first >> second;
	power(first, second, result);
	cout << first << " to the power " << second << " is " << result << endl;
	return 0;
}
