//Daniel Christiansen
//CS 162

#include <iostream>
#include <cstring>

const int SIZE = 100;

using namespace std;

struct Forecast {
        float high;
        float low;
        float prec; //chance of precipitation
        char info[SIZE];
        char source[SIZE];
        char rating[SIZE];
	Forecast * next;
} forecast;

lass Weather {
        public:
        ~Weather();
        Weather();
        void Display(Forecast forecast);
        void DisplayList();
        void Add(Forecast & toAdd);
        void Rate(char source[], char rating[]);
        void RateList();
        void Input();

        private:
        Forecast* head;
        int count;
	int i;
	bool whole;
};

