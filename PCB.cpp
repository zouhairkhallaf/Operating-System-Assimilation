#include "PCB.hpp"


//Constructor
PCB::PCB(int size){ // Default
        PCB_id = -1;
        PCB_size = size;
        PCB_memory_start = -1;
        PCB_memory_end = -1;
        PCB_creation_time = " XX:XX:XX";
        PCB_state = "EMPTY";
        file_size_to_print  = 0;
        file_size_to_disk = 0;
        PCB_printer_number = 0;
        PCB_disk_number = 0;
        PCB_memory_index = -1;
        PCB_disk_operation = "N/A";
}

PCB::PCB(){ // Default
        PCB_id = -1;
        PCB_size = 0;
        PCB_memory_start = -1;
        PCB_memory_end = -1;
        PCB_creation_time = " XX:XX:XX";
        PCB_state = "EMPTY";
        file_size_to_print  = 0;
        file_size_to_disk = 0;
        PCB_printer_number = 0;
        PCB_disk_number = 0;
        PCB_memory_index = -1;
        PCB_disk_operation = "N/A";
}

//Getters:
int PCB::Get_PCB_id()const{
        return PCB_id;
}

int PCB::Get_PCB_size()const{
        return PCB_size;
}

int PCB::Get_PCB_memory_index()const{
        return PCB_memory_index;
}

int PCB::Get_PCB_memory_start()const{
        return PCB_memory_start;
}

int PCB::Get_PCB_memory_end()const{
        return PCB_memory_end;
}

string PCB::Get_PCB_state()const{
        return PCB_state;
}

string PCB::Get_PCB_creation_time()const{
        return PCB_creation_time;
}

int PCB::Get_PCB_printer_number()const{
        return PCB_printer_number;
}

int PCB::Get_PCB_disk_number()const{
        return PCB_disk_number;
}

int PCB::Get_PCB_file_size_to_print()const{
        return file_size_to_print;
}

int PCB::Get_PCB_file_size_to_disk()const{
    return file_size_to_disk;
}

string PCB::Get_PCB_disk_operation()const{
        return PCB_disk_operation;
}


//Setters:
void PCB::Set_PCB_id(int ID){
        PCB_id = ID;
}

void PCB::Set_PCB_size(int SIZE){
        PCB_size = SIZE;
}

void PCB::Set_PCB_memory_index(int new_index){
        PCB_memory_index = new_index;
}

void PCB::Set_PCB_memory_start(int new_start){
        PCB_memory_start = new_start;
}

void PCB::Set_PCB_memory_end(int new_end){
        PCB_memory_end = new_end;
}

void PCB::Set_PCB_state(string new_state){
        PCB_state = new_state;
}

void PCB::Set_PCB_creation_time(string TIME){
        PCB_creation_time = TIME;
}

void PCB::Set_PCB_printer_number(int printer_number){
    PCB_printer_number = printer_number;
}

void PCB::Set_PCB_disk_number(int disk_number){
    PCB_disk_number = disk_number;
}

void PCB::Set_PCB_file_size_to_print(int file_size){
    file_size_to_print = file_size;
}

void PCB::Set_PCB_file_size_to_disk(int file_size){
    file_size_to_disk = file_size;
}

void PCB::Set_PCB_disk_operation(string operation){
    PCB_disk_operation = operation;
}


//Operator:
ostream& operator<<(ostream& output, PCB& PCB_to_output){
        cout <<"\t\t\t\t"<<setw(4) <<left<< PCB_to_output.Get_PCB_id();
        cout <<setw(9) <<left<< PCB_to_output.Get_PCB_state(); // 7 + gape(5) + size(11) = 23
        cout <<setw(12)<<left<< PCB_to_output.Get_PCB_size();
        cout <<setw(1) <<"["<<setw(9)<<PCB_to_output.Get_PCB_memory_start()<< setw(1)<<"-"<<setw(10)<<right<< PCB_to_output.Get_PCB_memory_end()<<setw(1)<<left<< "]";
        cout <<setw(13)<<left<< PCB_to_output.Get_PCB_creation_time();
        cout <<setw(8) <<left<< PCB_to_output.Get_PCB_printer_number();
        cout <<setw(8) <<left<< PCB_to_output.Get_PCB_file_size_to_print();
        cout <<setw(8) <<left<< PCB_to_output.Get_PCB_file_size_to_disk();
        cout <<setw(8) <<left<< PCB_to_output.Get_PCB_disk_number();
        cout <<setw(8) <<left<< PCB_to_output.Get_PCB_disk_operation();
        cout <<endl;
        return output;
}