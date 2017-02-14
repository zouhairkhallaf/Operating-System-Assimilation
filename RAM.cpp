#include "RAM.hpp"

//Constructor
RAM::RAM(int total_size){
        total_RAM = total_size;
        free_RAM = total_size;
        used_RAM = 0;
        PCB* Gost = new PCB(total_RAM);
        Gost->Set_PCB_memory_start(0);
        Gost->Set_PCB_memory_end(total_RAM-1);
        RAM_BLOCKS.push_back(Gost);
}

//Getters
void RAM::Calculate_RAM(){
        free_RAM= 0;
        used_RAM = 0;
        for (int i=0; i< RAM_BLOCKS.size(); i++) {          // This Calculates Free, and Used RAM
            if (RAM_BLOCKS[i]->Get_PCB_state() == "EMPTY")
                free_RAM += RAM_BLOCKS[i]->Get_PCB_size();
            else
                used_RAM += RAM_BLOCKS[i]->Get_PCB_size();
        }                                                   // This Makes sure our math is correct
        if( (used_RAM + free_RAM) != total_RAM){
            cout << "YOUR RAM SPACE COUNT DOES'T ADD UP CORRECTLY " <<endl;
        }
}

int RAM::Get_total_RAM()const{
        return total_RAM;
}

int RAM::Get_free_RAM()const{
        return free_RAM;
}

int RAM::Get_used_RAM()const{
        return used_RAM;
}

vector<PCB*> RAM::Get_RAM_BLOCKS()const{
        return RAM_BLOCKS;
}

void RAM::Merge_Empty_Blocks(int index_of_terminated_obj){
    int i = index_of_terminated_obj;
    int size = RAM_BLOCKS[i]->Get_PCB_size();
    int start = RAM_BLOCKS[i]->Get_PCB_memory_start();
    int end = RAM_BLOCKS[i]->Get_PCB_memory_end();
    size_t last_index = RAM_BLOCKS.size()-1;
    if (i==0 && size<total_RAM && RAM_BLOCKS[i+1]->Get_PCB_state()=="EMPTY") {
        RAM_BLOCKS[i+1]->Set_PCB_memory_start(start);
        RAM_BLOCKS[i+1]->Set_PCB_size(RAM_BLOCKS[i+1]->Get_PCB_size() + size);
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
         Calculate_RAM();
        return;
    }
    if (i==last_index && RAM_BLOCKS[i-1]->Get_PCB_state()=="EMPTY"){
        RAM_BLOCKS[i-1]->Set_PCB_memory_end(end);
        RAM_BLOCKS[i-1]->Set_PCB_size(RAM_BLOCKS[i-1]->Get_PCB_size() + size);
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
         Calculate_RAM();
        return;
    }
    if (i>0 && i<last_index && RAM_BLOCKS[i+1]->Get_PCB_state()=="EMPTY" && RAM_BLOCKS[i-1]->Get_PCB_state()=="EMPTY") {
        RAM_BLOCKS[i-1]->Set_PCB_memory_end(end);
        RAM_BLOCKS[i-1]->Set_PCB_size(RAM_BLOCKS[i-1]->Get_PCB_size() + size);
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
        RAM_BLOCKS[i-1]->Set_PCB_memory_end(RAM_BLOCKS[i]->Get_PCB_memory_end());
        RAM_BLOCKS[i-1]->Set_PCB_size(RAM_BLOCKS[i-1]->Get_PCB_size() + RAM_BLOCKS[i]->Get_PCB_size());
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
         Calculate_RAM();
        return;
    }
    if (i!=last_index && RAM_BLOCKS[i+1]->Get_PCB_state()=="EMPTY") { //Merge with top
        RAM_BLOCKS[i+1]->Set_PCB_memory_start(start);
        RAM_BLOCKS[i+1]->Set_PCB_size(RAM_BLOCKS[i+1]->Get_PCB_size() + size);
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
         Calculate_RAM();
        return;
    }
    if (i!=0 && RAM_BLOCKS[i-1]->Get_PCB_state()=="EMPTY") { // Merge with bottom
        RAM_BLOCKS[i-1]->Set_PCB_memory_end(end);
        RAM_BLOCKS[i-1]->Set_PCB_size(RAM_BLOCKS[i-1]->Get_PCB_size() + size);
        RAM_BLOCKS.erase(RAM_BLOCKS.begin()+i);
         Calculate_RAM();
        return;
    }
    Calculate_RAM();
}

int RAM::Find_process_index(int process_ID){
        for (int i=0; i<RAM_BLOCKS.size(); i++) {
            if (RAM_BLOCKS[i]->Get_PCB_id() == process_ID) {
                return i;
            }
        }
        return -1;
}

bool RAM::Delete_process(int index_terminated){
        RAM_BLOCKS[index_terminated]->Set_PCB_state("EMPTY");
        RAM_BLOCKS[index_terminated]->Set_PCB_id(-1);
        Merge_Empty_Blocks(index_terminated);
        return true;
}

//Setters
void RAM::Set_total_RAM(int m){
        total_RAM = m;
}

void RAM::Set_free_RAM(int m_free){
        free_RAM = m_free;
}

void RAM::Set_used_RAM(int used_m){
        used_RAM = used_m;
}

bool RAM::put_in_RAM(PCB* new_process, CPU &my_CPU){
        if (best_fit_allocation(new_process , my_CPU)) {
            cout << "\t\t\t > RAM:: New process pushed to RAM" <<endl;
            return true;
        }else{
            cout << "\t\t\t > RAM:: new process FALED " << endl;
            return false;
        }
}

int RAM::find_where_to_insert_process(PCB* new_process){
    int count=0;
    int Best_fit_block_size = 0;
    int index_of_best_fit_block = -1;
    int process_size = new_process->Get_PCB_size();
    //size_t limit = RAM_BLOCKS.size();
    
    for (int i=0; i< RAM_BLOCKS.size() ; i++){
        int current_block_size = RAM_BLOCKS[i]->Get_PCB_size();
        string current_block_state = RAM_BLOCKS[i]->Get_PCB_state();
        if ( (count==0) && (current_block_state=="EMPTY") )
        {
            Best_fit_block_size = current_block_size;
            index_of_best_fit_block = i;
            count = 1;
        }
        else if ( (current_block_state == "EMPTY") && (process_size <= current_block_size) && ( current_block_size < Best_fit_block_size) )
        {
            index_of_best_fit_block = i;
            Best_fit_block_size = current_block_size;
        }
    }
    return index_of_best_fit_block;
}

bool RAM::best_fit_allocation(PCB* new_process, CPU &my_CPU){
        int insert_at = find_where_to_insert_process(new_process);
        int n_size = new_process->Get_PCB_size();
        size_t RAM_block_size = RAM_BLOCKS.size();
        vector<PCB*> inorder_container;
        bool tag=false;
        
        //Updating the new process metrics :
        new_process->Set_PCB_memory_start(RAM_BLOCKS[insert_at]->Get_PCB_memory_start()); //Start
        new_process->Set_PCB_memory_end(n_size-1 + new_process->Get_PCB_memory_start());  //End
        
        //Creating the new child and updating it's metrics
        PCB* child_gost = new PCB(RAM_BLOCKS[insert_at]->Get_PCB_size() - n_size);        //Size
        child_gost->Set_PCB_memory_start(new_process->Get_PCB_memory_end()+1);            //Start
        child_gost->Set_PCB_memory_end(RAM_BLOCKS[insert_at]->Get_PCB_memory_end());      //End
        
        //fill the container
        for (int i=0; i< RAM_block_size; i++) {
            if (i==insert_at) {
                inorder_container.push_back(new_process);
                if (n_size < RAM_BLOCKS[insert_at]->Get_PCB_size()) {
                    inorder_container.push_back(child_gost);
                }
                tag = true;
                if (RAM_block_size != 0 && insert_at != RAM_block_size) {
                }
            }
            if (i != insert_at) {
                inorder_container.push_back(RAM_BLOCKS[i]);
            }
        }
        
        //Update RAM memory blocks
        RAM_BLOCKS.clear();
        RAM_BLOCKS = inorder_container;
        Calculate_RAM();
        return tag;
}

ostream& operator << (ostream& out, RAM& RAM_to_output){
    cout << "\t\t\t > RAM:: Total RAM space: "<<RAM_to_output.Get_total_RAM() <<endl;
    cout << "\t\t\t > RAM:: Used RAM space : "<<RAM_to_output.Get_used_RAM()  <<endl;
    cout << "\t\t\t > RAM:: Free RAM space : "<<RAM_to_output.Get_free_RAM()  <<endl;
    cout << endl;
    cout << "\t\t\t\tMEMORY SNAPSHOT TABLE:"<<endl;
    cout <<"\t\t\t\t"<<setw(5)<<left<<"PID"<<setw(10)<<"STATE"<<setw(12)<<"SIZE"<<setw(20)<<"RAM MEMORY BLOCK"<<setw(9)<< "CREATED"<<setw(8)<<"PRINTER"<<setw(9)<<"P.F.SIZE" << setw(9) <<"D.F.SIZE" <<setw(6)<<"DISK"<<setw(8)<<"OPERATION"<<endl;
    for (int i=0; i<RAM_to_output.Get_RAM_BLOCKS().size(); i++) {
        out << *(RAM_to_output.Get_RAM_BLOCKS()[i]);
    }
    cout <<endl;
    return out;
}