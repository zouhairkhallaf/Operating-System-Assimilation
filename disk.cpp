#include "disk.hpp"
using namespace std;

//Constructor
disk::disk(int d){
        D_number = d;
        D_name   = create_disk_name(d);
}

//Getters:
int disk::Get_D_number()const{
        return D_number;
}

string disk::Get_D_name()const{
        return D_name;
}


//Setters:
void disk::Set_D_number(int number){
        D_number = number;
}

void disk::Set_D_name(string name){
        D_name = name;
}

void disk::Push_to_D_queue(PCB* PCB_object){
        PCB_object->Set_PCB_printer_number( D_number );
        D_queue.push(PCB_object);
}


//Operators
ostream& operator<<(ostream& output, disk& disk_to_output){
        output<< disk_to_output.Get_D_name()<< endl;
        queue<PCB*> temp = disk_to_output.D_queue;
        int count = 0;
        while (!temp.empty()) {
            if (count == 0){
                cout <<"\t\t\t\tDISKS SNAPSHOT TABLE:"<<endl;
                cout <<"\t\t\t\tNow Disking:  PID["<< temp.front()->Get_PCB_id() <<"]";
                cout <<"\t\t File_Size["<< temp.front()->Get_PCB_file_size_to_disk() <<"]";
                cout <<"\t\t Operation["<<temp.front()->Get_PCB_disk_operation()<<"]"<< endl;
            }else{
                cout << "\t\t\t\tWAITING    :  PID["<<temp.front()->Get_PCB_id() <<"]";
                cout <<"\t\t File_Size["<<temp.front()->Get_PCB_file_size_to_disk()<<"]";
                cout <<"\t\t Operation["<<temp.front()->Get_PCB_disk_operation()<<"]"<<endl;
            }
            count+=1;
            temp.pop();
        }
        return output;
}

string  disk::create_disk_name(int disk_number){
        char int_to_char = (char)(disk_number + 48);
        string char_to_str = &int_to_char;
        string name = "Disk" + char_to_str;
        return name;
}

bool disk::terminate_job(CPU& my_CPU){
    if (D_queue.empty()) {
        return false;
    }else{
        D_queue.front()->Set_PCB_state("READY");
        D_queue.front()->Set_PCB_disk_number(0);
        D_queue.front()->Set_PCB_file_size_to_disk(0);
        D_queue.front()->Set_PCB_disk_operation("N/A");
        my_CPU.push_to_Ready_Queue(D_queue.front());
        D_queue.pop();
        return true;
    }
}
