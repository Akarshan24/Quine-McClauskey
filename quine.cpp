#include<bits/stdc++.h>
using namespace std;
int n;
class number
{
    public:
    string no;;
    string bin;
    int status;
    int dont_care;
};
string toBin(int no)
{   
    string s="";
    for (int i = n-1; i >= 0; i--) 
    { 
        int k = no >> i; 
        if (k & 1) 
            s+="1";
        else
            s+="0"; 
    } 
    
    return s;
}
int hemming(string num1,string num2)            //Hemming distance calculation.
{
    int c=0;
    for(int i=n-1;i>=0;i--)
    {
        if(num1[i]!=num2[i])
        c++;
    }
    return c;
}
string combine(string num1,string num2)         //Combine two numbers with hemming distance 1.
{
    string wd="";
    for(int i=n-1;i>=0;i--)
    {
        if(num1[i]!=num2[i])
            wd="_"+wd;
        else
            wd=num1[i]+wd;
    } 
    return wd;
}
int main()
{
    cout<<"Enter the number of variables"<<endl;
    cin>>n;
    int m=pow(2,n);
    number n1[m],n2[m],n3[m];
    int num,p=0,ctr=0;
    while(1)
    {
        cout<<"Enter any positive number less than "<<pow(2,n)<<". Do not enter don't care values over here.Enter -1 to stop giving inputs."<<endl;
        cin>>num;
        if(num==-1)
        break;
        ctr++;
        if(ctr>pow(2,n))
        {
            cout<<"Maximum limit reached"<<endl;
            break;
        }
        
        n1[p].no=num+"";
        n1[p].bin=toBin(num);
        n1[p].status=0;
        n1[p].dont_care=0;
        n3[p]=n1[p];                      //**dont_care=0 => not a don't care value ; dont_care=1 => is a don't care value        
        p++;
    }
    while(1)
    {
        cout<<"Enter don't care values less than "<<pow(2,n)<<". Enter -1 to stop entering values"<<endl;
        cin>>num;
        if(num==-1)
        break;
        ctr++;
        if(ctr>pow(2,n))
        {
            cout<<"Maximum limit reached"<<endl;
            break;
        }
        n1[p].no=num+"";
        n1[p].bin=toBin(num);
        n1[p].status=0;
        n1[p].dont_care=1;
        n3[p]=n1[p];                       //**dont_care=0 => not a don't care value ; dont_care=1 => is a don't care value        
        p++;
    }
    int c;
    //Grouping Algorithm:
    // * status = 0 . number not combined yet ; status = 1 . number combined*
    //1. Run 2 loops(nested) to check for pairs with hemming distance 1.
    //2. When found such a pair,combine them using function combine() and store the result in struct number n2[].
    //3. Make the status of every combined number 1.
    //4. After the iterations have been completed run another loop to see whether the status of every element is 1 or not.
    //5. If some element is there without status 1,store it to struct number n2[]
    //6. Copy the contents of n2[] to n1[]
    //7. Repeat the same process until all the status variables have value 0(They can't be combined anymore). 
    int m1=ctr;
    while(1)
    {
    c=0;
    for(int i=0;i<m1;i++)        //Combining pairs with hemming distance 1 and storing in n2[].Also making status = 1 for combined pairs.
    {
        for(int j=i+1;j<m1;j++)
        {
            if((hemming(n1[i].bin,n1[j].bin)<=1)&&(n1[i].dont_care==0||n1[j].dont_care==0))     //Checking for hemming distance=1 and also making sure 2 don't cares are not combined.
                {
                    
                    n2[c].no=n1[i].no+n1[j].no;
                    n2[c].bin=combine(n1[i].bin,n1[j].bin);
                    n2[c].status=0;
                    n2[c].dont_care=0;
                    c++;
                    n1[i].status=1;
                    n1[j].status=1;

                }
            
        }
    }
    
    
    int fl=0;
    for(int i=0;i<m1;i++)        //Checking if all the statuses are 0 or not. If all are 0 then no pairs possible so infinite loop terminated.
    {
        if(n1[i].status==1&&n1[i].dont_care==0)
        {
            fl=1;
            break;
        }
    }
    if(fl==0)
    break;
   
    for(int i=0;i<m1;i++)        //Numbers that haven't been grouped in the previous loop
    {
        if(n1[i].status==0&&n1[i].dont_care==0)
        {            
            n2[c]=n1[i];
            c++;
        }
    }
    
    for(int i=0;i<c;i++)        //Copying the elements of n2 to n1.
    {
        
        n1[i]=n2[i];
    }
    m1=c;        //Reducing number of iterations to the number of elements in the next step.
    } 
    cout<<"The final state of the terms:\t\t"<<endl;
    for(int i=0;i<m1;i++)        //Printing the final elements after grouping has been completed.
    {
        cout<<n1[i].bin<<endl;
    }
     //Printing the Gray Code
    cout<<"================================="<<endl;
    cout<<"Gray Code: "<<endl;
    string code="",l="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0;i<m1;i++)
    {
        string g="";
        int al=0;
        for(int j=0;j<n;j++)
        {
            if(n1[i].bin[j]=='1')
            cout<<l[al];
            else if(n1[i].bin[j]=='0')
            cout<<l[al]<<"'";
            al++;
        }
        if(i<m1-1)
        cout<<"+";
    }   
    return 0;

}
