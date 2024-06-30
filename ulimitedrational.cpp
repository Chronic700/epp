/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

// #include <iostream>


bool is_zero(UnlimitedInt* i);
bool less_than_rational(UnlimitedInt* num, UnlimitedInt* den);
UnlimitedInt* gcd(UnlimitedInt* num, UnlimitedInt* den);


UnlimitedRational:: UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){

    if(is_zero(den)){
        p=new UnlimitedInt(0);
        q=new UnlimitedInt(0);
        return ;
        
    }

    if(is_zero(num)){
        p=new UnlimitedInt(0);
        q=new UnlimitedInt(1);
        return ;
    }

    bool numl=less_than_rational(num, den);
    // // cout<<numl<<'\n';

    if(!numl) {
        UnlimitedInt* g=gcd(num, den);
        // cout<<g->to_string()<<endl;
        p=UnlimitedInt:: div(num, g);
        q=UnlimitedInt:: div(den, g);
    }
    else{
        UnlimitedInt* g=gcd(den, num);
        p=UnlimitedInt:: div(num, g);
        q= UnlimitedInt:: div(den, g);
    }


    // p=p->div(num, g);
    // q=q->div(num, g);
}

UnlimitedRational:: ~UnlimitedRational(){
    delete p;
    delete q;
}

string UnlimitedRational:: get_p_str(){
    return p->to_string();
}

string UnlimitedRational:: get_q_str(){
    return q->to_string();
}

string UnlimitedRational:: get_frac_str(){
    return p->to_string()+'/'+q->to_string();
}

UnlimitedRational* UnlimitedRational:: add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num;
    UnlimitedInt* den;

    if(is_zero(i2->get_q()) || is_zero(i1->get_q())) {
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(0);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }
    if(is_zero(i1->get_p())){
        string p_str=i2->p->to_string();
        string q_str=i2->q->to_string();

        UnlimitedInt* newp=new UnlimitedInt(p_str);
        UnlimitedInt* newq=new UnlimitedInt(q_str);
        UnlimitedRational* ans= new UnlimitedRational(newp, newq);
        return ans;
    }
    if(is_zero(i2->get_p())){
        string p_str=i1->p->to_string();
        string q_str=i1->q->to_string();

        UnlimitedInt* newp=new UnlimitedInt(p_str);
        UnlimitedInt* newq=new UnlimitedInt(q_str);
        UnlimitedRational* ans= new UnlimitedRational(newp, newq);
        return ans;
    }


    num=UnlimitedInt::add(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    den=UnlimitedInt:: mul(i1->q, i2->q);

    // if(num->sign* den->)

    return new UnlimitedRational(num, den);
}

UnlimitedRational* UnlimitedRational:: sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num;
    UnlimitedInt* den;
    if(is_zero(i2->get_q()) || is_zero(i1->get_q())) {
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(0);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    if(is_zero(i2->get_p())){
        string p_str=i1->p->to_string();
        string q_str=i1->q->to_string();

        UnlimitedInt* newp=new UnlimitedInt(p_str);
        UnlimitedInt* newq=new UnlimitedInt(q_str);
        UnlimitedRational* ans= new UnlimitedRational(newp, newq);
        return ans;
    }
    if(is_zero(i1->get_p())){
        // UnlimitedInt* p;
        UnlimitedInt* q=i2->get_q();

        UnlimitedInt* zero=new UnlimitedInt(0);

        UnlimitedInt* p=UnlimitedInt::sub(zero, i2->get_p());
        
        // int sign=-1* ((i2->get_p())->get_sign());
        // int size=(i2->get_p())->get_size();
        // int* unl=(i2->get_p())->get_array();
        // int cap=(i2->get_p())->get_capacity();

        // UnlimitedInt* p= new UnlimitedInt(unl, cap, sign, size);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    num=UnlimitedInt::sub(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    den=UnlimitedInt::mul(i1->q, i2->q);

    return new UnlimitedRational(num, den);
}

UnlimitedRational* UnlimitedRational:: mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num;
    UnlimitedInt* den;

    if(is_zero(i2->get_q()) || is_zero(i2->get_q())){
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(0);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    if(is_zero(i1->get_p()) || is_zero(i2->get_p())){
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(1);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    num=UnlimitedInt::mul(i1->p, i2->p);
    den=UnlimitedInt::mul(i1->q, i2->q);

    return new UnlimitedRational(num, den);
}

UnlimitedRational* UnlimitedRational:: div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num;
    UnlimitedInt* den;

    if(is_zero(i2->get_p()) || is_zero(i1->get_q()) || is_zero(i2->get_q())){
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(0);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    if(is_zero(i1->get_p())){
        UnlimitedInt* p=new UnlimitedInt(0);
        UnlimitedInt* q=new UnlimitedInt(1);
        UnlimitedRational* ans=new UnlimitedRational(p, q);
        return ans;
    }

    num=num->mul(i1->p, i2->q);
    den=den->mul(i1->q, i2->p);

    return new UnlimitedRational(num, den);
}

UnlimitedInt*  UnlimitedRational :: get_p(){
    return p;
}

UnlimitedInt*  UnlimitedRational :: get_q(){
    return q;
}

bool is_zero(UnlimitedInt* i){
    string exp=i->to_string();
    if(exp=="0" || exp=="-0") return true;
    else return false;


    int* u=i->get_array();
    for(int j=0; j<i->get_capacity(); j++){
        if(u[j]!=0) return false;
    }
    return true;
}

bool less_than_rational(UnlimitedInt* num, UnlimitedInt* den){
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

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b){
    UnlimitedInt* c= c->mod(a, b);
    if(is_zero(c)) return b;
    return gcd(b, c);
}

// int main(){
//     UnlimitedInt* p1=new UnlimitedInt(9);
//     UnlimitedInt* q1=new UnlimitedInt(8);
//     UnlimitedRational* r1=new UnlimitedRational(p1,q1);
//     // cout<<r1->get_frac_str()<<'\n';

//     UnlimitedInt* p2=new UnlimitedInt(2);
//     UnlimitedInt* q2=new UnlimitedInt(1);
//     UnlimitedRational* r2=new UnlimitedRational(p2,q2);
//     // cout<<r2->get_frac_str()<<'\n';

//     // cout<<
// }