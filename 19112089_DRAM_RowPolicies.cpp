#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
using namespace std;



vector <float> open_Row_policy(float hit_latency,float miss_latency,float conflict_latency,vector <int> row,vector <int> column,vector <float> time_of_arrival){

int num_iterations=row.size();
vector <float> served_time(num_iterations,5);
vector <float> time_of_completion(num_iterations,5);

served_time[0]=miss_latency;
time_of_completion[0]=miss_latency;

  for(int i=1;i<num_iterations;i++){
        if(time_of_arrival[i]<time_of_completion[i-1]){
              if(row[i]!=row[i-1]){
                   served_time[i]=time_of_completion[i-1]+conflict_latency;
                   time_of_completion[i]=served_time[i];
              }
              else if(row[i]==row[i-1]){
                  served_time[i]=time_of_completion[i-1]+hit_latency;
                  time_of_completion[i]=served_time[i];
              }

        }
        else if(time_of_arrival[i]>=time_of_completion[i-1]){
            if(row[i]!=row[i-1]){
                  served_time[i]=time_of_arrival[i]+conflict_latency;
                  time_of_completion[i]=served_time[i];

            }
            else if(row[i]==row[i-1]){
                  served_time[i]=time_of_arrival[i]+hit_latency;
                  time_of_completion[i]=served_time[i];
            }
        }
  }

   vector <float> openRow= served_time;
   return openRow;
}


vector <float> close_Row_policy(float hit_latency,float miss_latency,float conflict_latency,vector <int> row,vector <int> column,vector <float> time_of_arrival){
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
   vector <float> closeRow= served_time;
   return closeRow;
}






int main(int argc,char *argv[])
{

   string inputFilename = argv[1];
    ifstream infile{inputFilename};
    ofstream outfile;
    string outputFileName = "19112089_"+inputFilename;
    outfile.open(outputFileName);

    outfile<<"Row,Column  "<<setw(13)<<"TimeOfArrival"<<setw(15)<<"OpenRow"<<setw(10)<<"CloseRow"<<setw(10)<<endl;

        float hit_latency=5;
        float miss_latency=15;
        float conflict_latency=29;

        int num_rows=64;
        int num_columns=48;
        vector <int> row;
        vector <int> column;
        vector <float> time_of_arrival;
        string s;
        vector <string> line;
        if(infile.is_open())
        {
          while(!infile.eof())
          {
                getline(infile,s,'\n');
                line.push_back(s);
          }

        }
       string strhit,strmiss,strconflict,strrows,strcolumns;
       strhit=line[0].substr(line[0].size()-2,line[0].size());
       strmiss=line[1].substr(line[1].size()-2,line[1].size());
       strconflict=line[2].substr(line[2].size()-2,line[2].size());
       strrows=line[3].substr(line[3].size()-2,line[3].size());
       strcolumns=line[4].substr(line[4].size()-2,line[4].size());

       hit_latency=stof(strhit);
       miss_latency=stof(strmiss);
       conflict_latency=stof(strconflict);
       num_rows=stof(strrows);
       num_columns=stof(strcolumns);
      int num_itr=0,startidx=3;
      for(int i=0;i<line.size()-1;i++){
        string a;
        a=line[i];
        if(a[0]!='C'&&a[0]!='R'&&a[0]!='/'&&a[1]!='/'&&a.size()>0){
                num_itr++;
                if(num_itr==1){startidx=i;}
        }
      }
vector <string> r;
vector <string> c;
vector <string> toa;
      for(int i=startidx;i<line.size()-1;i++){
             string b;
             b=line[i];
             string val; int cnt=0;
             stringstream ss(b);
                  while(cnt<3){
                       getline(ss,val,',');
                       if(cnt==0){ r.push_back(val);cnt++;}
                       else if(cnt==1){c.push_back(val);cnt++;}
                       else if(cnt==2){toa.push_back(val);cnt++;}
                 }

            }
            for(auto it:r){
                    int ig;
                     stringstream ss(it);
                    ss>>ig;
                row.push_back(ig);
            }
            for(auto it:c){
                int ig;
                     stringstream ss(it);
                    ss>>ig;
                column.push_back(ig);
            }
            for(auto it:toa){
                    float ig;
            stringstream ss(it);
                ss>>ig;
                time_of_arrival.push_back(ig);
            }
       vector <float> ans_open;
       vector <float> ans_close ;
       ans_open=  open_Row_policy(hit_latency,miss_latency,conflict_latency,row,column,time_of_arrival);
       ans_close= close_Row_policy(hit_latency,miss_latency,conflict_latency,row,column,time_of_arrival);

       for(int i=0;i<row.size();i++){
       outfile<<row[i]<<","<<column[i]<<setw(13)<<time_of_arrival[i]<<setw(15)<<ans_open[i]<<setw(10)<<ans_close[i]<<setw(10)<<endl;
       }
return 0;
}



