/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// #include <iostream>
// using namespace std;

//Write your code below this line


/////////////////
//Why NULL????
/////////////////

////////////////////////////////////////////////////////////
//Read the codes and keep count of the variables for memory location
////////////////////////////////////////////////////////////


/////////////////////////////////  Assumption: Only one return and that too at the last statement  ////////////////////////


/////////////////////////////////////////////////


void arithmetic_commands(const ExprTreeNode* const root, vector<string> &commands, SymbolTable* symtable);
void del(ExprTreeNode* &root);


EPPCompiler::EPPCompiler(){

}
/////////////////////////////////////////////////

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;

    for(int i=mem_limit-1;i>=0;i--){
        mem_loc.push_back(i);
    }

    ///////////////////////////
    // Min Heap
    ///////////////////////////
}

void EPPCompiler::compile(vector<vector<string>> code){
    // int max_size=0;
    // int curr_size=0;
    ofstream commands_file(output_file);
    commands_file<<"";
    commands_file.close();

    int s=code.size();
    for(int i=0; i<s; i++){
        if(code[i][0]=="del"){
            int memory_of_variable=targ.symtable->search(code[i][2]);
            mem_loc.push_back(memory_of_variable);
        }
        vector <string> commands_for_this_step;
        targ.parse(code[i]);

        string to_do=targ.expr_trees.back()->left->type;


        // if(targ.expr_trees.back()->left->type=="VAR") curr_size++;
        // else if(targ.expr_trees.back()->left->type=="DEL") {
        //     if(max_size>curr_size) max_size=curr_size;
        //     curr_size--;
        // }


        if(to_do=="VAR"){
            int location=targ.symtable->search(code[i][0]);
            if(location==-1) {
                int memory_for_this=mem_loc.back();
                mem_loc.pop_back();
                targ.symtable->assign_address(code[i][0], memory_for_this);
            }
            commands_for_this_step=generate_targ_commands();
        }

        else if(to_do=="DEL"){
            string variable=targ.expr_trees.back()->right->id;

            // int memory_stored=targ.symtable->search(variable);

            commands_for_this_step=generate_targ_commands();

            // mem_loc.push_back(memory_stored);
            targ.symtable->remove(variable);
            // cout<<"hi";
        }

        else if(to_do=="RET"){
            commands_for_this_step=generate_targ_commands();
        }
        commands_for_this_step.push_back("\n");

        write_to_file(commands_for_this_step);
    }

    
    // if(max_size>curr_size) max_size=curr_size;

    /////////////////////////////
    // What if memory_size set by mem_limit < max_size
    /////////////////////////////
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root=targ.expr_trees.back();
    vector<string> commands={};

    if(root->left->type=="DEL"){
        string variable=root->right->id;
        int memory_location=mem_loc.back();

        commands.push_back("DEL = mem[" + std::to_string(memory_location) + "]\n");
        return commands;
    }

    arithmetic_commands(root->right, commands, targ.symtable);

    if(root->left->type=="VAR"){
        string variable=root->left->id;
        int memory_location=targ.symtable->search(variable);

        commands.push_back("mem[" + std::to_string(memory_location) + "] = POP\n");
        return commands;
    }
    
    if(root->left->type=="RET"){
        commands.push_back("RET = POP\n");
        return commands;
    }
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream commands_file(output_file, std::ios::app);
    int s=commands.size();
    for(int i=0; i<s; i++){
        commands_file << commands[i];
    }
    commands_file.close();
}

EPPCompiler::~EPPCompiler(){
    //////////////////////////////////////
    // delete targ;
    // delete least_mem_loc
    //////////////////////////////////////

    int s=targ.expr_trees.size();
    for(int i=0; i<s; i++){
        ExprTreeNode* root=targ.expr_trees[i];
        del(root);
    }

    targ.expr_trees.clear();

    delete targ.symtable;

    output_file.clear();
    mem_loc.clear();
}



void arithmetic_commands(const ExprTreeNode* const root, vector<string> &commands, SymbolTable* symtable){
    if(root->type=="VAL"){
        commands.push_back("PUSH "+std::to_string(root->num)+"\n");
        return;
    }

    if(root->type=="VAR"){
        int memory_location=symtable->search(root->id);
        commands.push_back("PUSH mem[" + std::to_string(memory_location) + "]\n");
        return;
    }

    if(root->type=="ADD"){
        arithmetic_commands(root->right, commands, symtable);
        arithmetic_commands(root->left, commands, symtable);
        commands.push_back("ADD\n");
        return;
    }

    if(root->type=="SUB"){
        arithmetic_commands(root->right, commands, symtable);
        arithmetic_commands(root->left, commands, symtable);
        commands.push_back("SUB\n");
        return;
    }

    if(root->type=="MUL"){
        arithmetic_commands(root->right, commands, symtable);
        arithmetic_commands(root->left, commands, symtable);
        commands.push_back("MUL\n");
        return;
    }

    if(root->type=="DIV"){
        arithmetic_commands(root->right, commands, symtable);
        arithmetic_commands(root->left, commands, symtable);
        commands.push_back("DIV\n");
        return;
    }
}

void del(ExprTreeNode* &root){
    if(root){

        del(root->left);
        del(root->right);

        /////////////////////     Deleting Strings      ///////////////////////
        delete root;
        root=NULL;
    }

}

// int main(){
//     EPPCompiler* c=new EPPCompiler("file.txt", 10);
//     vector<vector<string>> statements;
//     statements={{"a", ":=", "(", "8", "*", "10", ")"}, {"b", ":=", "(", "3", "*", "4", ")"},
//                 {"c", ":=", "4"}, {"d",":=","7"},
//                 {"del",":=","d"},
//                 {"del",":=","b"},
//                 {"del",":=","a"},
//                 {"c", ":=","(", "10","+","1",")"},

//                 {"ret", ":=", "(", "c", "+", "7", ")"},
//                 };
//     c->compile(statements);
//     std::cout<<"Hello";
// }