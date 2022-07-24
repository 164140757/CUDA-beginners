#include <math.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include <string>

// grid to stratify: (Pi*R^2)/(2R*2R)=Pi/4
int main(int argc, char const *argv[])
{
    int inside_circle_stratified=0;
    int inside_circle=0;
    int sqrt_N=10000;

    float pi_r, pi_s;
    std::ofstream outfile_r;
    std::ofstream outfile_s;

    outfile_r.open("../../../log/esti_pi_sttf_regular.txt");
    outfile_s.open("../../../log/esti_pi_sttf_stratified.txt");

    for (int i=0; i<sqrt_N; i++){
        for (int j=0;j<sqrt_N;j++){
            float x = 2*drand48()-1; //[-1, 1]
            float y = 2*drand48()-1;
            if (x*x + y*y < 1)
                inside_circle++;
            x = 2*((i+drand48())/sqrt_N)-1; // i is discrete -> stratified + rand()
            y = 2*((j+drand48())/sqrt_N)-1;
            if (x*x + y*y < 1)
                inside_circle_stratified++;  
            pi_r = 4*float(inside_circle)/(sqrt_N*sqrt_N);
            pi_s = 4*float(inside_circle_stratified)/(sqrt_N*sqrt_N);
            
            if ((i*sqrt_N+j)%100000 == 0){
                outfile_r << std::to_string(pi_r)+" ";
                outfile_s << std::to_string(pi_s)+" ";
            }
        }
    }
    outfile_r.close();
    outfile_s.close();

    std::cout << "Regular Estimate of Pi = " << pi_r << "\n";
    std::cout << "Stratified Estimate of Pi = " << pi_s << "\n";
}