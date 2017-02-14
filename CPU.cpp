#include "CPU.hpp"

//Setters
bool CPU::push_to_Ready_Queue(PCB* ready_process){
    if (ready_process != nullptr && ready_process->Get_PCB_state() !="EMPTY" ) {
        Ready_Queue.push(ready_process);
        Ready_Queue.front()->Set_PCB_state("RUNNING");
        cout << "\t\t\t > CPU:: New process pushed to the ready Queue..."<<endl;
        return true;
    }else{
        return false;
    }
}


//Other functions:
bool CPU::terminate_process_execution(RAM& My_RAM, int& process_index_in_RAM){
    if (Ready_Queue.empty()) {
        return false;
    }
    int index = My_RAM.Find_process_index(Ready_Queue.front()->Get_PCB_id());
    process_index_in_RAM = index;
    Ready_Queue.front()->Set_PCB_state("EMPTY");
    Ready_Queue.pop();
    if (!Ready_Queue.empty()) {
        Ready_Queue.front()->Set_PCB_state("RUNNING");
    }
    if (index == -1){
        return false;
    }else{
        My_RAM.Calculate_RAM();
        return true;
    }
    
}

bool CPU::printers_pending(){
    if(Ready_Queue.front()->Get_PCB_printer_number()== 0)
        return false;
    else
        return true;
}

bool CPU::disks_pending(){
    if(Ready_Queue.front()->Get_PCB_disk_number()== 0)
        return false;
    else
        return true;
}

ostream& operator << (ostream& out, CPU& CPU_to_output){
    if (CPU_to_output.Ready_Queue.empty()) {
        cout << "\t\t\t > CPU:: YOUR READY QUEUE IS EMPTY" <<endl<<endl;
    }else{
    queue<PCB*> temp = CPU_to_output.Ready_Queue;
    cout <<endl;
    cout <<"\t\t\t\tREADY QUEUE SNAPSHOT TABLE:" <<endl;
    cout <<"\t\t\t\t"<<setw(5)<<left<<"PID"<<setw(10)<<"STATE"<<setw(12)<<"SIZE"<<setw(20)<<"RAM MEMORY BLOCK"<<setw(9)<< "CREATED"<<setw(8)<<"PRINTER"<<setw(9)<<"P.F.SIZE" << setw(9) <<"D.F.SIZE" <<setw(6)<<"DISK"<<setw(8)<<"OPERATION"<<endl;
    while (!temp.empty()) {
        out << *(temp.front());
        temp.pop();
    }
    cout <<endl;
    }
    return out;
}

queue<PCB*> CPU::Get_ready_queue()const{
    return Ready_Queue;
}

bool CPU::Send_process_to_printer(int printer_number, int file_size, vector<printer>& my_printers){
    if (Ready_Queue.empty()) {
        cout << "\t\t\t > CPU:: ATTENTION, YOUR READY QUEUE IS EMPTY" <<endl;
        return false;
    }else{
        Ready_Queue.front()->Set_PCB_file_size_to_print(file_size); // Update PCB file_size
        Ready_Queue.front()->Set_PCB_printer_number(printer_number);// Update PCB pinter number
        Ready_Queue.front()->Set_PCB_state("PRINTING");             // Update PCB state
        Ready_Queue.front()->Set_PCB_file_size_to_disk(0);
        Ready_Queue.front()->Set_PCB_disk_number(0);
        Ready_Queue.front()->Set_PCB_disk_operation("w");           // Operation
        my_printers[printer_number-1].Push_to_P_queue(Ready_Queue.front());
        Ready_Queue.pop();                                          // kicking off the process.
        
        
        if (!Ready_Queue.empty())
            Ready_Queue.front()->Set_PCB_state("RUNNING");
        cout << "\t\t\t\t\t > CPU:: PCB Left Ready Queue succesfully" <<endl;
        return true;
    }
}

bool CPU::Send_process_to_disk(int disk_number, int file_size, vector<disk>& my_disks, string operation){
    if (Ready_Queue.empty()) {
        cout << "\t\t\t > CPU:: ATTENTION, YOUR READY QUEUE IS EMPTY" <<endl;
        return false;
    }else{
        Ready_Queue.front()->Set_PCB_file_size_to_disk(file_size);      // Update PCB file_size
        Ready_Queue.front()->Set_PCB_disk_number(disk_number);          // Update PCB disk number
        Ready_Queue.front()->Set_PCB_printer_number(0);                 // To make sure
        //Ready_Queue.front()->Set_PCB_file_size_to_printer(0);           // To make sure
        Ready_Queue.front()->Set_PCB_state("DISKING");                  // Update PCB state
        Ready_Queue.front()->Set_PCB_disk_operation(operation);         // Operation
        my_disks[disk_number-1].Push_to_D_queue(Ready_Queue.front());
        Ready_Queue.pop();                                              // kicking off the process.
        if (!Ready_Queue.empty())
            Ready_Queue.front()->Set_PCB_state("RUNNING");
        cout << "\t\t\t\t\t > CPU:: PCB Left Ready Queue succesfully" <<endl;
        return true;
    }
}
