#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
using namespace std;


vector <float> close_Row_policy(float hit_latency,float miss_latency,float conflict_latency,int num_row,int num_column,vector <int> row,vector <int> column,vector <float> time_of_arrival){
float t_closing = conflict_latency-miss_latency;
int num_iterations=row.size();
vector <float> served_time(num_iterations,5);
vector <float> time_of_completion(num_iterations,5);
served_time[0]=miss_latency;
time_of_completion[0]=conflict_latency;


  for(int i=1;i<num_iterations;i++){
        if(time_of_arrival[i]<time_of_completion[i-1]){
              if(row[i]!=row[i-1]){
                   served_time[i]=time_of_completion[i-1]+miss_latency; 
                  time_of_completion[i]=served_time[i] + t_closing; 
              }
              else if(row[i]==row[i-1]){
                  served_time[i]=time_of_completion[i-1]+miss_latency;                
                 time_of_completion[i]=served_time[i] + t_closing;    
                }
              
        }
        else if(time_of_arrival[i]>=time_of_completion[i-1]){
            if(row[i]!=row[i-1]){
                  served_time[i]=time_of_arrival[i]+miss_latency; 
                  time_of_completion[i]=served_time[i] + t_closing;
                 
            }
            else if(row[i]==row[i-1]){
                  served_time[i]=time_of_arrival[i]+miss_latency; 
                  time_of_completion[i]=served_time[i] + t_closing;  
             }
        }
  }
    cout<<served_time.size()<<endl;
   vector <float> closeRow= served_time;
   return closeRow;
}




int main(int argc,char *argv[])
{
  cout<<"Row,Column  "<<setw(13)<<"TimeOfArrival"<<setw(15)<<"OpenRow"<<setw(10)<<"CloseRow"<<setw(10)<<endl;
   
        float hit_latency=20;
        float miss_latency=40;
        float conflict_latency=60;

        int num_rows=64;
        int num_columns=48;
        vector <int> row{40,41,40,40,50,50,50,50,50,40,50};
        vector <int> column{23,34,34,34,40,22,22,23,22,22,32};
        vector <float> time_of_arrival{0,10,100,200,390,450,460,490,550,650,750}; 

       vector <float> ans_open;
       vector <float> ans_close ; 
      ans_close=  close_Row_policy(hit_latency,miss_latency,conflict_latency,num_rows,num_columns,row,column,time_of_arrival); 
     for(int i=0;i<row.size();i++){
      cout<<row[i]<<","<<column[i]<<setw(13)<<time_of_arrival[i]<<setw(15)<<ans_close[i]<<setw(10)<<endl;
     }
      return 0;
}