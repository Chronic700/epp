/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h" 

// #include <iostream>
// using namespace std;




UnlimitedInt* avg(UnlimitedInt* i1, UnlimitedInt* i2);
void print(UnlimitedInt* n);
bool is_equal(UnlimitedInt* i1, UnlimitedInt* i2);
bool is_zero_unlimitedint(UnlimitedInt* i);
bool less_than(UnlimitedInt* num, UnlimitedInt* den);

UnlimitedInt:: UnlimitedInt(string s){
    size=s.size();
    bool zero=true;
    for(int i=0; i<size; i++){
        if(s[i]!='0'){
            zero=false;
            break;
        }
    }
    if(zero){
        sign=0;
        size=1;
        ///////////////////////////////////////////////////////
    }

    if(s[0]=='-') sign=-1;
    else sign=1;
    
    if(s[0]=='-'){
        size--;
        // capacity=2*size;
        capacity=size;
        
        int x=capacity-size;
        unlimited_int=new int[capacity];
        for(int i=0; i<x; i++){
            unlimited_int[i]=0;
        }

        for(int i=0;i<size;i++){
            unlimited_int[x+i]=(int) s[i+1]-'0';
        }
        return;
    }

    // capacity=2*size;
    capacity=size;

    unlimited_int=new int[capacity];

    int x=capacity-size;

    for(int i=0; i<x;i++){
        unlimited_int[i]=0;
    }

    for(int i=0;i<size;i++){
        unlimited_int[x+i]=(int) s[i]-'0';
    }
}

UnlimitedInt:: UnlimitedInt(int i){

    if(i==0){
        sign=0;
        size=1;
        // capacity=2*size;
        capacity=size;
        unlimited_int = new int[capacity];

        for(int j=0; j<capacity; j++){
            unlimited_int[j]=0;
        }
        ///////////////////////////////
        return;
        ///////////////////////////////

        // int num=i;

        // int x=capacity-size;
        
        // for(int j=0; j<x;j++){
        //     unlimited_int[j]=0;
        // }

        // for(int j=0;j<size;j++){
        //     unlimited_int[x+j]=0;
        // }
    }

    if(i<0){
        sign=-1;
        i=-i;
    }
    else sign=1;

    size=0;
    
    int num=i;

    while(num>0){
        size++;
        num=num/10;
    }

    // capacity=2*size;
    capacity=size;

    int x=capacity-size;

    unlimited_int = new int[capacity];

    for(int j=0; j<x;j++){
        unlimited_int[j]=0;
    }

    for(int j=0;j<size;j++){
        unlimited_int[capacity-1-j]=i%10;
        i=i/10;
    }
}

UnlimitedInt:: UnlimitedInt(){
    size=1;
    // capacity=2*size;
    capacity=size;
    unlimited_int=new int[capacity];
    for(int i=0; i<capacity;i++){
        unlimited_int[i]=0;
    }
    sign=0;
}

UnlimitedInt:: UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    unlimited_int=ulimited_int;
    capacity=cap;
    sign=sgn;
    size=sz;
}

UnlimitedInt:: ~UnlimitedInt(){
    delete[] unlimited_int;
    // delete &size;
    // delete &sign;
    // delete &capacity;
    //////////////////////////////////////////////////////////////////////////
}

int UnlimitedInt::get_size(){
    return size;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int* UnlimitedInt:: get_array(){
    return unlimited_int;
}

int UnlimitedInt:: get_capacity(){
    return capacity;
}

string UnlimitedInt :: to_string(){
    
    int i=0;
    while(i<capacity && unlimited_int[i]==0) i++;
    if(i==capacity) return "0";

    string ans="";
    
    if(sign==-1) ans+='-';
    for(;i<capacity;i++){
        ans+= ((char)('0'+ unlimited_int[i]));
    }
    return ans;


}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    // UnlimitedInt* ans=new UnlimitedInt();
    // ans->capacity=max(i1->capacity, i2->capacity);
    // // cout<<ans->capacity;
    if(i1->sign==i2->sign){
        if(i1->sign==0){
            string ans=i2->to_string();
            return new UnlimitedInt(ans);
        }
        

        int cap=max(i1->capacity, i2->capacity)+1;
        // int x=min(i1->capacity, i2->capacity);
        int* u=new int[cap];
        for(int i=0; i<cap;i++) u[i]=0;

        int carry=0;

        for(int i=0; i<cap;i++){
            int d1, d2;
            if(i<i1->capacity) d1=i1->unlimited_int[i1->capacity-1-i];
            else d1=0;

            if(i<i2->capacity) d2=i2->unlimited_int[i2->capacity-1-i];
            else d2=0;

            int sum= d1+d2+carry;
            u[cap-1-i]=sum%10;
            carry=sum/10;

            // u[cap-1-i]=(d1+d2+carry);
            // u[cap-2-i]+=(d1+d2)/10;
            
            // // cout<<d1<<' '<<d2<<' ' <<u[cap-1-i]<<' '<<u[cap-2-i]<< '\n';
        }

        // if(carry!=0){
        //     int*u1=new int[cap+5];
        //     int j=0;

        //     for(j=0; j<4;j++) u1[j]=0;
        //     u1[j]=carry;
        //     j++;
        //     for(;j<cap+5;j++){
        //         u1[j]=u[j-5];
        //     }
        //     delete[] u;
        //     u=u1;

        //     int i=0;
        //     while(u[i]==0) i++;

        //     // i-=1;
            
        //     UnlimitedInt* ans=new UnlimitedInt(u, cap+5, i1->sign, cap-i);
        //     return ans;
        // }

        // for(int i=0;i<cap-x;i++)

        
        int i=0;
        while(i<cap && u[i]==0) i++;

        if(i==cap) return new UnlimitedInt(0);

        int* arr= new int[cap-i];

        for(int j=0;j<cap-i;j++){
            arr[j]=u[i+j];
        }
        delete[] u;

        return new UnlimitedInt(arr, cap-i, i1->sign, cap-i);

    }

    else if(i1->sign==0){
        string ans=i2->to_string();
        return new UnlimitedInt(ans);
        
        // UnlimitedInt* ans=new UnlimitedInt();
        // ans->capacity=max(i1->capacity, i2->capacity);

        // ans->capacity=i2->capacity;
        // ans->size=i2->size;
        // ans->sign=i2->sign;
        // ans->unlimited_int=new int[ans->capacity];
        // for(int i=0; i<ans->capacity;i++){
        //     ans->unlimited_int[i]=i2->unlimited_int[i];
        // }
        // return i2;
    }

    else if(i2->sign==0){
        string ans=i1->to_string();
        return new UnlimitedInt(ans);

        // UnlimitedInt* ans=new UnlimitedInt();
        // ans->capacity=max(i1->capacity, i2->capacity);

        // ans->capacity=i1->capacity;
        // ans->size=i1->size;
        // ans->sign=i1->sign;
        // ans->unlimited_int=new int[ans->capacity];
        // for(int i=0; i<ans->capacity;i++){
        //     ans->unlimited_int[i]=i1->unlimited_int[i];
        // }
        // return i1;
    }
    else{

        // UnlimitedInt* ans=new UnlimitedInt();
        // ans->capacity=max(i1->capacity, i2->capacity);

        if(i1->sign==-1){
            i1->sign=1;
            UnlimitedInt* ans= sub(i2,i1);
            i1->sign=-1;
            return ans;
        }
        else{
            i2->sign=1;
            UnlimitedInt* ans= sub(i1,i2);
            i2->sign=-1;
            return ans;
        }
    }
    
}

UnlimitedInt* UnlimitedInt:: sub(UnlimitedInt* i1, UnlimitedInt* i2){
    // UnlimitedInt* ans;
    // ans->capacity=max(i1->capacity, i2->capacity);
    if(i2->sign==0){
        string ans=i1->to_string();
        return new UnlimitedInt(ans);
        // ans->sign=i1->sign;
        // ans->capacity=i1->capacity;
        // ans->size=i1->size;

        // for(int i=0; i<i1->capacity; i++){
        //     ans->unlimited_int[i]=i1->unlimited_int[i];
        // }
        // return i1;
    }
    else if(i1->sign==0){
        int sign=-1*i2->sign;
        int capacity=i2->capacity;
        int size=i2->size;

        int* u= new int[capacity];
        for(int i=0; i<i2->capacity; i++){
            u[i]=i2->unlimited_int[i];
        }
        UnlimitedInt* ans=new UnlimitedInt(u, capacity, sign, size);
        return ans;
    }
    else if(i1->sign+i2->sign==0){

        // UnlimitedInt* ans;
        // ans->capacity=max(i1->capacity, i2->capacity);

        i2->sign=-1*i2->sign;
        UnlimitedInt* ans=add(i1,i2);
        i2->sign=-1*i2->sign;
        return ans;
    }
    else{
        // // cout<<"Hello\n";
        // // cout<<is_equal(i1, i2)<<'\n';
        if(is_equal(i1, i2)){
            return new UnlimitedInt(0);
        }
        // UnlimitedInt* ans;
        // ans->capacity=max(i1->capacity, i2->capacity);

        int cap;
        // int size;
        // int sign;


        // // cout<<less_than(i2,i1);
        if(less_than(i2,i1)){
            // // cout<<"GGGGGGGGGGG";
            // sign=i1->sign;
            cap=max(i1->capacity, i2->capacity);
            

            int* u=new int[cap];

            for(int i=0;i<cap;i++){
                u[i]=0;
            }

            int borr=0;

            for(int i=0;i<cap;i++){
                int d1,d2;
                // // cout<<"KKKKKKKKKKK"<<i1->capacity<<i2->capacity;
                // // cout<<i1->to_string()<<'\n'<<i2->to_string()<<'\n';
                if(i<i1->capacity) d1=i1->unlimited_int[i1->capacity-i-1];
                else d1=0;

                if(i<i2->capacity) d2=i2->unlimited_int[i2->capacity-i-1];
                else d2=0;
                // // cout<<d1<<d2;

                if(borr!=0){
                    d1-=borr;
                    borr=0;
                }

                if(d1>=d2){
                    u[cap-1-i]=d1-d2;
                    // // cout<<"+++++++++++++++\n";
                    // // cout<<'\n'<< u[cap-1-i]<<'\n';
                }
                else{
                    borr++;
                    d1+=10;
                    u[cap-1-i]=d1-d2;
                }
            }
            int i=0;
            while(i<cap && u[i]==0) i++;

            if(i==cap) return new UnlimitedInt(0);

            int* arr= new int[cap-i];

            for(int j=0;j<cap-i;j++){
                arr[j]=u[i+j];
            }
            delete[] u;

            return new UnlimitedInt(arr, cap-i, i1->sign, cap-i);

            // UnlimitedInt* ans=new UnlimitedInt(u, cap, sign, cap-i);
            // return ans;
            
        }

        else {
            UnlimitedInt* ans=sub(i2,i1);
            ans->sign*=-1;
            return ans;
        }
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->sign==0 || i2->sign==0){
        UnlimitedInt* ans=new UnlimitedInt(0);
        return ans;
    }


    // UnlimitedInt* ans;
    // ans->sign=(i1->sign)*(i2->sign);
    // ans->capacity=(i1->capacity+ i2->capacity);

    int cap=i1->capacity+i2->capacity ;
    int sign=i1->sign*i2->sign;

    int*u=new int[cap];


    for(int i=0; i<cap;i++){
        u[i]=0;
    }

    // for(int i=i1->capacity-1; i>i1->capacity-i1->size-1; i--){
    //     for(int j=i2->capacity-1; j>i2->capacity-i2->size-1;j--){
    //         int result=i1->unlimited_int[i]*i2->unlimited_int[j] + ans->unlimited_int[i+j+1];
    //         ans->unlimited_int[i+j+1]=result%10;
    //         ans->unlimited_int[i+j]=result/10;
    //     }
    // }

    for(int i=i1->capacity-1; i>=0; i--){
        for(int j=i2->capacity-1; j>=0; j--){
            int result=i1->unlimited_int[i]*i2->unlimited_int[j] + u[i+j+1];
            u[i+j+1]=result%10;
            u[i+j]+=result/10;
        }
    }

    int i=0;
    while(i<cap && u[i]==0) i++;

    if(i==cap) return new UnlimitedInt(0);

    int* arr= new int[cap-i];

    for(int j=0;j<cap-i;j++){
        arr[j]=u[i+j];
    }
    delete[] u;

    return new UnlimitedInt(arr, cap-i, sign, cap-i);
    
    // UnlimitedInt* ans=new UnlimitedInt(u, cap, sign, cap-i);
    // return ans;
}

UnlimitedInt* UnlimitedInt:: div(UnlimitedInt* i1, UnlimitedInt* i2){

    bool i1_zero=true;

    for(int i=0; i<i1->capacity; i++){
        if(i1->unlimited_int[i]!=0){
            i1_zero=false;
            break;
        }
    }

    if(i1_zero) return new UnlimitedInt(0);


    if(less_than(i1, i2)){
        if(i1->sign==i2->sign) return new UnlimitedInt(0);
        else return new UnlimitedInt(-1);
    }

    bool i2_one=false;

    // for(int i=0; i<i2->capacity-1; i++){
    //     if(i2->unlimited_int[i]!=0){
    //         i2_one=false;
    //         break;
    //     }
    // }

    // if(i2_one){
    //     if(i2->unlimited_int[i2->capacity-1]!=1){
    //         i2_one=false;
    //     }
    // }

    string x=i2->to_string();
    if(x=="1" || x=="-1") i2_one=true;

    if(i2_one){
        int*u=new int[i1->capacity];
        for(int i=0;i<i1->capacity;i++){
            u[i]=i1->unlimited_int[i];
        }
        if(i2->sign==1){
            return new UnlimitedInt(u, i1->capacity, i1->sign, i1->size);
        }
        else return new UnlimitedInt(u, i1->capacity, -i1->sign, i1->size);
    }

    // // cout<<"hello";

    int i1_sign=i1->sign;
    int i2_sign=i2->sign;
    i1->sign=1;
    i2->sign=1;

    UnlimitedInt* start=new UnlimitedInt(0);
    UnlimitedInt* one=new UnlimitedInt(1);
    UnlimitedInt* end=sub(i1,one);
    UnlimitedInt* mid=new UnlimitedInt(1);
    // // cout<<"44444444444444444444444\n";
    // // cout<<start->to_string()<<'\n'<<one->to_string()<<'\n'<<end->to_string()<<'\n'<<mid->to_string()<<'\n';

    // // cout<<"hello";
    

    while(less_than(start,end) || start->to_string()==end->to_string()){
        // // cout<<"Hello\n";
        mid=avg(start,end);
        // // cout<<"\nMid: "<< mid->to_string() << ' '<< mid->size <<'\n';
        // // cout<<"HHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
        if(start->to_string()==end->to_string())break;


        // // cout<<mid->to_string()<<'\n';

        UnlimitedInt* prod=mul(mid, i2);
        // // cout<<prod->to_string();
        // // cout<<"\nTruth value: "<<less_than(prod, i1);
        if(prod->to_string()==i1->to_string()){
            break;
        }
        else if(less_than(prod, i1)){
            // // cout<<"ryy";
            start=add(mid,one);
            // // cout<<start->to_string()<<' '<<end->to_string()<<'\n';
            // if(start->to_string()==end->to_string()) break;
            
            // // cout<<end->to_string()<<'\n';
            delete mid;
            // // cout<<"DDDDDDDDDDDDDD";

        }
        else{
            // // cout<<"---------------";
            end=sub(mid,one);
            // // cout<<start->to_string();
            // // cout<<"\nRRRRRRRRRRR\n";
            // // cout<<"tmkc"<<std::endl;
            // // cout<<less_than(start,end)<<endl;
            // // cout<<start->to_string()<<' '<<end->to_string()<<'\n';
            // if(start->to_string()==end->to_string()) break;
            delete mid;
            // // cout<<"tmka"<<endl;
        }
    }
    // // cout<<"\nLoop Ends\n";
    //////////////////////////////////////
    if(!less_than(start, end)) mid= start;
    //////////////////////////////////////
    if(start->to_string()==end->to_string()) mid=start;

    UnlimitedInt* prod=mul(mid, i2);

    if(less_than(i1, prod)){
        // // cout<<mid->to_string()<<'\n';
        // // cout<< "I'm here\n";
        mid=sub(mid,one);
    }
    prod=mul(mid, i2);

    int sign=i1_sign*i2_sign;
    if(sign<0){
        if(sub(i1, prod)->sign>0){
            mid=add(mid, one);
        }
    }

    i1->sign=i1_sign;
    i2->sign=i2_sign;

    return new UnlimitedInt(mid->get_array(), mid->get_capacity(), sign, mid->get_size());
}



UnlimitedInt* UnlimitedInt:: mod(UnlimitedInt* i1, UnlimitedInt*i2){
    UnlimitedInt* quotient=div(i1,i2);
    UnlimitedInt* prod=mul(i2, quotient);
    return sub(i1, prod);
}




bool is_equal(UnlimitedInt* i1, UnlimitedInt* i2){

    if(i1->to_string()==i2->to_string()) return true;
    else return false;

    if(i1->get_size()!= i2->get_size()) return false;

    // bool equal=true;
    int i=0;
    int x1=i1->get_capacity()-i1->get_size();
    int x2=i2->get_capacity()-i2->get_size();
    int* u1=i1->get_array();
    int* u2=i2->get_array();
    for(i=0;i<i1->get_size();i++){
        if(u1[x1+i] != u2[x2+i]){
            return false;
        }
    }
    return true;

}

bool is_zero_unlimitedint(UnlimitedInt* i){
    int* u=i->get_array();
    for(int j=0; j<i->get_capacity(); j++){
        if(u[j]!=0) return false;
    }
    return true;
}

UnlimitedInt* avg(UnlimitedInt* i1, UnlimitedInt* i2){
    // // cout<<'\n';
    // // cout<<'\n';
    // // cout<<"i1: "<<i1->to_string()<<'\n';
    // // cout<<"i2: "<<i2->to_string()<<'\n';
    UnlimitedInt* sum = UnlimitedInt:: add(i1, i2);
    // // cout<<"Arr: ";
    // // // cout<<'\n';

    // for(int i=0;i<sum->get_capacity();i++){
    //     // cout<<sum->get_array()[i];
    // }
    

    // // cout<<"Sum: " <<sum->to_string()<<'\n';
    // print(sum);
    // // cout<<"\nHi\n";

    // int carry=0;

    int cap=sum->get_capacity();
    int* u=sum->get_array();

    int i=0;
    for(i=0; i<cap-1; i++){
        if(u[i]%2==1){
            u[i+1]+=10;
        }
        u[i]/=2;
    }
    u[i]/=2;

    // // cout<<'\n';

    // for(int i=0;i<cap;i++){
    //     // cout<<u[i];
    // }
    // // cout<<'\n';

    int index=0;
    while(index<cap && u[index]==0) index++;
    if(index==cap) return new UnlimitedInt(0);

    int* arr= new int[cap-index];

    for(int j=0;j<cap-index;j++){
        arr[j]=u[index+j];
    }
    delete[] u;

    return new UnlimitedInt(arr, cap-index, sum->get_sign(), cap-index);

}


bool less_than(UnlimitedInt* num, UnlimitedInt* den){

    if(num->to_string()=="0" && den->to_string()=="0") return false;
    if(num->to_string()=="0" && den->to_string()!="0") return true;
    if(num->to_string()!="0" && den->to_string()=="0") return false;


    if(num->get_size()< den->get_size()) return true;
    if(num->get_size()> den->get_size()) return false;
    bool all_same=true;
    int* u1=num->get_array();
    int* u2=den->get_array();
    int i=0;
    for(i=0;i<den->get_size();i++){
        if(u1[i] > u2[i]){
            return false;
        }
        if(u1[i]<u2[i]) return true;
        if(u1[i]!=u2[i]) all_same=false;
    }
    if(all_same) return false;
    return true;
}



void print(UnlimitedInt* n);





// int main(){
//     // UnlimitedInt* i1=new UnlimitedInt(0);
//     // UnlimitedInt* i2=new UnlimitedInt(3);
//     // // cout<<less_than(i1, i2);

//     UnlimitedInt *a =new UnlimitedInt(9);
//     // // cout<<"a::\n";
//     // print(a);
//     // // cout<<'\n';

//     UnlimitedInt* b=new UnlimitedInt(8);
//     // // cout<<"b::\n";
//     // print(b);
//     // // cout<<'\n';
//     UnlimitedInt* c=UnlimitedInt::mod(a,b);
//     // cout<<"c::\n";
//     print(c);
//     // cout<<'\n';

    
// }





void print(UnlimitedInt* n){
    // cout<<"Size: "<<n->get_size();
    // cout<<"\nSign: "<<n->get_sign();
    // cout<<"\nCap: "<<n->get_capacity();
    int* u=n->get_array();
    // cout<<"\nArr: ";
    for(int i=0;i<n->get_capacity();i++){
        // cout<<u[i];
    }
    // cout<<'\n';
    // cout<<n->to_string()<<'\n';
    // // cout<<n->to_string()<<'\n';
    // delete[] u;
}