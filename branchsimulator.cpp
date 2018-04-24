#include <iostream>
#include <string>
#include <math.h>
#include <bitset>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
//#include <math>
using namespace std;

unsigned long int converthextodec(string hexdata){
    unsigned long int x;
    stringstream ss;
    ss<< hexdata;
    ss>> hex>> x;
    return x;
};
void OutputRF(int x,int y)
	{
		ofstream rfout;
		rfout.open("trace1.txt",std::ios_base::app);
		if(rfout.is_open())
		{
		rfout<<x<<" "<<y<<endl;
		}
		rfout.close();	
	};
	void Out(int x)
	{
		ofstream rfout1;
		rfout1.open("trace.txt.out",std::ios_base::app);
		if(rfout1.is_open())
		{
		rfout1<<x<<endl;
		}
		rfout1.close();	
	};
float mispredict()
{
	int counter=0;
	int miss=0;
	float missanswer;
	int original;
	int prediction;
	ifstream random;
	string linemk;
	//string 
	//int j=0;
	random.open("trace1.txt");
    if (random.is_open())
	{
		while (getline(random,linemk))
		{ 
	    stringstream sepdata(linemk);
	    sepdata >> prediction >> original;
        if(prediction!=original)
        {
            miss=miss+1;
            counter=counter+1;
        }
        else
        {
        	counter=counter+1;
        }
        }

        random.close();
    }
    //cout<<miss<<endl;
    missanswer=(miss/float(counter))*100;
    return missanswer;  
}		


int main(){
	int m;
	int k;
	vector<int> in;
    //int rows=pow(2,m);
    //cout<<rows;
    //int cols=pow(2,k);
    string ind;
    string inind;
    //bitset<32> a[5];
    bitset<2> value;
    //string hexdata;
    //a[0]=2;
    //a[1]=3;
    //a[2]=4;
    //a[3]=5;
    //a[4]=6;
    //a[5]=10;
    //bitset<2> satcount[rows][cols];
    //bitset<2> globalhist=0;
    //cout<<globalhist;
    int predict;
    int actualbr;
    int coun;
    int taken;
    int testcounter;
    string intermediateindex;
    bitset<32> ins;
    //vector<bool> a;
    //reading values of m and k
	//bitset<32> m,k; 
	ifstream param;
	string linemk;
	//string 
	//int j=0;
	param.open("config.txt");
    if (param.is_open())
	{
		while (getline(param,linemk))
		{ 
	    in.push_back(stoi(linemk));
	    //sepdata >> m >> k;
        //cout<<m<<" "<<k<<endl;
        }
        param.close();
    }  
    m=in[0];
    //cout<<m<<endl;
    k=in[1];
    //cout<<k<<endl;
    int rows=pow(2,m);
    int cols=pow(2,k);
    bitset<2> satcount[rows][cols];   
    //initializing the array
    for(int i=0;i<rows;i++)
    {
    	for(int j=0;j<cols;j++)
    	{
    		satcount[i][j]=3;
    	}
    }
	//cout<<satcount[1][1];
	//reading instructions 
	//bitset<32> ins; 
	ifstream imem;
	string line;
	vector<bool> a(k);
	if (k!=0){
	for(size_t nIndex=0;nIndex<k;nIndex++)
	{
		a[nIndex]=1;
		
	}
    }
    else{
    	coun=0;
    }
	//rotate(a.begin(),a.begin()+1,a.end())

	//string 
	//int j=0;
	imem.open("trace.txt");
    if (imem.is_open())
	{
		while (getline(imem,line))
		{ 
	    //int testcounter;
	    stringstream sepdata(line);
	    sepdata >> inind >> taken;
	    //OutputRF(taken);
	    //cout<<taken;
	    //testcounter=testcounter+1;
		ins=converthextodec(inind);
		intermediateindex=ins.to_string();
        //coun=globalhist.to_ulong(); //tells which 2 bit counter to check into or cols in our case
        coun=0;
        if(k!=0){
        for(int i=0;i<a.size();i++)
        {
        	
        	if(a[i]==1){     
        		coun=coun+pow(2,i);
        	}
        	//cout<<coun<<endl;
        	//cout<<a.size();

        }
        }
        else{coun=0;}
        int start= 32-m;
        ind=intermediateindex.substr(start,m); //generates index
        //cout<<ind<<endl;
        bitset<20> x(ind); //converts string to bitset  
        
        bitset<2> value=satcount[x.to_ulong()][coun];
        if(value.to_ulong()==3 || value.to_ulong()==2)
        {
        	predict=1;

        }
        else if(value.to_ulong()==1 || value.to_ulong()==0)
        {
        	predict=0;
        }
        //cout<<predict<<endl;
        if (predict==taken)
        {
        	if(value.to_ulong()==2)
        	{
        		value=3;
        	}
        	else if(value.to_ulong()==1)
        	{
        		value=0;
        	}
        	//else
        	//{
        		//continue;
        	//}


        }
        else
        {
        	if (taken==0 && predict==1) //comparing the prediction with the result that actually the branch was taken or not        	
        	{

            	if(value.to_ulong()==3)
        	    {
        	        value=2;
        	    }
        	    else if(value.to_ulong()==2)
        	    {
        		    value=0;
        	    }
        	    //else if(value.to_ulong()==1)
        	    //{
        		    //value=0;
        	    //}
        	    //else
        	    //{
        		    //value=0;
        	    //}
            }
            else
            {
            	if(value.to_ulong()==0)
            	{
            		value=1;
            	}
            	else if(value.to_ulong()==1)
            	{
            		value=3;
            	}
            	//else if(value.to_ulong()==2)
            	//{
            		//value=3;
            	//}
            	//else
            	//{
            		//value=3;
            	//}

            
            }
        //cout<<predict<<endl;
        }
    satcount[x.to_ulong()][coun]=value.to_ulong();
    //cout<<satcount[x.to_ulong()][coun];
    // pushing the taken or not taken in BHK
    if(k!=0)
    {	
    rotate(a.begin(),a.begin()+1,a.end());
    a[a.size()-1]=taken;
    }
    //globalhist>>=1;
    //globalhist[1]=taken;
    OutputRF(predict,taken);
    Out(predict);
	}

//OutputRF(predict,taken);	
//cout<<mispredict();
}
cout<<mispredict();
//cout<<testcounter;
};












