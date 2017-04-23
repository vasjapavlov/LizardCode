#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
/*
 int      ---- int
 int[]    ---- vector<int>
 String   ---- string
 String[] ---- vector<string>
 double   ---- double
 double[] ---- vector<double>
 */

ifstream fin("input.txt");
ofstream fout("output.txt");
string returnType;
int testNumber;
string expectedResult;
int cnt=0;



string to_str(int a)
{
    ostringstream os;
    os<<a;
    return os.str();
}
void trim(string &s)
{
    int i=0;
    while(s[i]==' ')
        i++;
    s=s.substr(i);
    
    i=s.size()-1;
    while(s[i]==' ')
        i--;
    
    s=s.substr(0,i+1);
}

void clear_spaces(string &s)
{
    string t="";
    int i=0;
    while(i<s.size())
    {
        while(s[i]==' ') i++;
        if(s[i]==',') {t+=","; i++;}
        else
            if(s[i]=='"')
            {
                t+=s[i];
                i++;
                while(s[i]!='"')
                {
                    t+=s[i];
                    i++;
                }
                t+=s[i];
                i++;
            }
            else {t+=s[i];i++;}
    }
    s=t;
    
}


void check_result(string params)
{
    int nn=0;
    int i,br;
    char mark=char(34);
    
    trim(expectedResult);
    clear_spaces(expectedResult);
    
    if(returnType=="vector<int>")
    {
        nn=0;
        fout<<"int ABC"<<to_str(cnt)<<"[]={";
        i=0;
        while(expectedResult[i]!='}')
        {
            nn++;
            while(expectedResult[i]<'0' || expectedResult[i]>'9') i++;
            br=0;
            while(expectedResult[i]>='0' && expectedResult[i]<='9')
            {
                br=br*10+expectedResult[i]-'0';
                i++;
            }
            if(expectedResult[i]=='}') { fout<<br; break;}
            else fout<<br<<",";
        }
        fout<<"};\n";
        cout<<"da";
        fout<<"OK=new vector<int>(&ABC"<<to_str(cnt)<<"[0],&ABC"<<to_str(cnt)<<"["<<nn<<"]);\n";
        
        fout<<"if(*OK==res"<<") cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Correct!\\n\\n"<<mark<<";"<<endl;
        fout<<"  else {"<<"cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Wrong!\\n"<<mark<<";"<<endl;
        fout<<"cout<<"<<mark<<"Expected: "<<mark<<"<<"<<mark<<expectedResult<<mark<<"<<"<<mark<<"\\n"<<mark<<";\n";
        fout<<"cout<<"<<mark<<"Recieved: {"<<mark<<";";
        fout<<"for(int k=0;k<res.size();k++) cout<<res[k]<<(k<res.size()-1?',':'}');}\n";
        fout<<"cout<<endl;\n";
        
        cnt++;
    }
    
    if(returnType=="string")
    {
        fout<<"if(res == "<<expectedResult<<") cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Correct!\\n\\n"<<mark<<";"<<endl;
        fout<<"  else {"<<"cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Wrong!\\n"<<mark<<";"<<endl;
        fout<<"cout<<"<<mark<<"Expected: "<<mark<<"<<"<<expectedResult<<"<<"<<mark<<"\\n"<<mark<<";\n";
        fout<<"cout<<"<<mark<<"Recieved: "<<mark<<"<<"<<" res <<"<<mark<<" \\n\\n"<<mark<<";}\n";
    }
    if(returnType=="int")
    {
        fout<<"if(res == "<<expectedResult<<") cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Correct!\\n\\n"<<mark<<";"<<endl;
        fout<<"  else {"<<"cout<<"<<mark<<"test #"<<mark<<"<<"<<testNumber<<"<<"<<mark<<" Wrong!\\n"<<mark<<";"<<endl;
        fout<<"cout<<"<<mark<<"Expected: "<<mark<<"<<"<<expectedResult<<"<<"<<mark<<"\\n"<<mark<<";\n";
        fout<<"cout<<"<<mark<<"Recieved: "<<mark<<"<<"<<" res <<"<<mark<<" \\n\\n"<<mark<<";}\n";
    }
    fout<<"cout<<"<<mark<<"---------------------------------------------"<<mark<<"<<"<<mark<<"\\n"<<mark<<";\n";
}


char next_name='A';
void generateTest(int idx,string params,string method[],int N)
{
    
    fout<<"/***************************Test "<<idx<<" ********************************/\n\n";
    fout<<"if(Test_No==0 || Test_No=="<<idx<<"){\n";
    int i,j,k;
    int v[101];
    int n;
    int br;
    string name,t;
    
    clear_spaces(params);
    //     cout<<params<<endl;
    j=0;
    for(i=2;i<N;i+=2)
    {
        ////////////
        if(method[i]=="int")
        {
            br=0;
            while(params[j]<'0' || params[j]>'9') j++;
            while(j<params.size() && params[j]!=',')
            {
                if(params[j]==' ') {j++; continue;}
                br=br*10+params[j]-'0';
                j++;
            }j++;
            fout<<method[i+1]<<" = "<<br<<";"<<endl;
            
        }
        ////////////
        if(method[i]=="vector<string>")
        {
            /*************************************************************************/
            n=0;
            while(params[j]!='{') j++;
            j++;
            fout<<"string "<<"ABC"+to_str(cnt)<<"[]={";
            
            while(params[j]!='}' && j<params.size())
            {
                while(params[j]!='"') j++;
                j++;
                t="";
                n++;
                while(j<params.size() && params[j]!='"' && params[j]!='}')
                {
                    t+=params[j];
                    j++;
                }j++;
                fout<<char(34)<<t<<char(34);
                if(params[j]=='}')  break;
                else fout<<",";
                
            }
            fout<<"};\n";
            //cout<<params[j]<<endl;
            // system("pause");
            fout<<method[i+1]<<"= new vector<string> (&"<<"ABC"+to_str(cnt)<<"[0],&"<<"ABC"+to_str(cnt)<<"["<<n<<"]);\n";
            cnt++;
            /*************************************************************************/
        }
        ////////////
        if(method[i]=="string")
        {
            string t="";
            
            while( params[j]!='"' ) //find first "
            {
                j++;
            }
            j++;
            while(params[j]!='"') //until last "
            {
                t+=params[j++];
            }j++;
            
            fout<<method[i+1]<<" = "<<char(34)<<t<<char(34)<<";"<<endl;
        }
        ////////////
        if(method[i]=="vector<int>")
        {
            n=0;
            
            fout<<"int "<<"ABC"+to_str(cnt)<<"[]={";
            while(params[j]!='{') j++;
            j++;
            
            while(params[j]!='}' && j<params.size())
            {
                while(params[j]<'0' || params[j]>'9') j++;
                br=0;
                n++;
                while(j<params.size() && params[j]!=',' && params[j]!='}')
                {
                    br=br*10+params[j]-'0';
                    j++;
                }
                fout<<br;
                if(params[j]=='}') break;
                else fout<<",";
                
            }
            fout<<"};\n";
            fout<<method[i+1]<<"= new vector<int> (&"<<"ABC"+to_str(cnt)<<"[0],&"<<"ABC"+to_str(cnt)<<"["<<n<<"]);\n";
            cnt++;
        }
        ///////////////////////
    }
    fout<<"res = "<<"tmp."<<method[1]<<"(";
    for(k=3;k<N;k+=2)
    {
        if(method[k-1]=="vector<int>") fout<<"*";
        if(method[k-1]=="vector<string>") fout<<"*";
        fout<<method[k];
        if(k+2<N) fout<<",";
        else fout<<");\n";
    }
    
    check_result(params);
    
    fout<<"\n}\n";
    fout<<"/******************************************************************/\n\n\n";
    //cout<<endl;
}



int main()
{
    string class_name;
    string method[100];
    string params;
    int N=0;
    
    
    fout<<"/* Code generated && tested by LizardCode for CodeFu */\n";
    fout<<"#include <limits.h>\n";
    fout<<"#include <vector>\n";
    fout<<"#include <sstream>\n";
    fout<<"#include <iostream>\n";
    fout<<"#include <algorithm>\n";
    fout<<"#include <cstring>\n";
    fout<<"#include <string>\n";
    fout<<"#include <cstdlib>\n";
    fout<<"#include <cstdio>\n";
    fout<<"#include <map>\n";
    fout<<"#include <list>\n";
    fout<<"#include <queue>\n";
    fout<<"#include <set>\n\n";
    fout<<"using namespace std;\n\n";
    
    string s,t,test;
    int i,j;
    
    while(1)
    {
        getline(fin,s);
        trim(s);
        if(s=="Class Name:")
        {
            getline(fin,s);
            trim(s);
            class_name=s;
            fout<<"class "<<s<<"\n{\n  public:\n\n";
        }
        
        if(s=="Method signature:")
        {
            getline(fin,s);
            trim(s);
            //erase '(' and ')'
            s.replace(s.find("("),1," ");
            s.replace(s.find(")"),1," ");
            //erase commas
            while(s.find(",")!=-1)
            {
                s.replace(s.find(","),1," ");
            }
            //s = int func int p1 string[] p2...
            
            stringstream is(s);
            
            is>>t; //public
            while(is>>t)
            {
                if(t=="String") t="string";
                if(t=="String[]") t="string[]";
                method[N++]=t;
            }
            
            
            
            if(method[0]=="String[]") method[0]="vector<string>";
            if(method[0]=="double[]") method[0]="vector<double>";
            if(method[0]=="int[]") method[0]="vector<int>";
            
            returnType=method[0];
            fout<<"\t"<<method[0]<<" "<<method[1]<<"( ";
            i=2;
            while(i<N)
            {
                if(method[i]=="int") {fout<<"int "; method[i]="int";} else
                    if(method[i]=="int[]") {fout<<"vector<int> "; method[i]="vector<int>";} else
                        if(method[i]=="string") {fout<<"string "; method[i]="string";} else
                            if(method[i]=="string[]") {fout<<"vector<string> "; method[i]="vector<string>";} else
                                if(method[i]=="double") {fout<<"double "; method[i]="double";} else
                                    if(method[i]=="double[]") {fout<<"vector<double> "; method[i]="vector<double>";} else
                                    {fout<<method[i]<<""; if(i+1<N) fout<<", "; else fout<<" ";}
                i++;
            }
            fout<<")\n\t{\n\t \n\t \n\t}\n};";
            break;
        }//method signature END
    }
    
    fout <<"\n\nconst int Test_No=0;";
    fout<<"\n\nint main()\n{\n";
    fout<<"  "<<class_name<<" tmp;\n";
    
    fout<<"  "<<method[0]<<" res;\n";
    
    if(method[0]=="vector<int>") fout<<"  vector<int> * OK;\n";
    for(i=2;i<N;i+=2)
    {
        if(method[i]=="vector<int>") fout<<"  "<<method[i]<<" *"<<method[i+1]<<";\n";
        else
            if(method[i]=="vector<string>") fout<<"  "<<method[i]<<" *"<<method[i+1]<<";\n";
            else
                fout<<"  "<<method[i]<<" "<<method[i+1]<<";\n";
    }
    
    for(i=1;i<=10;i++)
    {
        getline(fin,s); //Test i
        getline(fin,s); //empty line
        
        getline(fin,test);//test data
        trim(test);
        expectedResult=test.substr(test.find("=")+1);
        trim(expectedResult);
        //cout<<expectedResult<<endl;
        params=test.substr(test.find("(")+1,test.find(")")-test.find("(")-1);
        
        
        testNumber=i;
        
        generateTest(i,params,method,N);
        
    }
    
    fout<<"  return 0;\n\n}\n";
    
    return 0;
}
