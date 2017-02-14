#include "printer.hpp"


//Constructor
printer::printer(int n){
        P_number = n;
        P_name = create_P_name(n);
}

//Getters
int printer::Get_P_number()const{
        return P_number;
}

string printer::Get_P_name()const{
        return P_name;
}

//Setters
void printer::Set_P_number(int number){
        P_number = number;
}

void printer::Set_P_name(string name){
        P_name = create_P_name(P_number);
}

void printer::Push_to_P_queue(PCB* PCB_object){
        PCB_object->Set_PCB_printer_number( P_number );
        P_queue.push(PCB_object);
}

bool printer::terminate_job(CPU& my_CPU){
        if (P_queue.empty()) {
            return false;
        }else{
            P_queue.front()->Set_PCB_state("READY");
            P_queue.front()->Set_PCB_printer_number(0);
            P_queue.front()->Set_PCB_file_size_to_print(0);
            P_queue.front()->Set_PCB_disk_operation("N/A");
            my_CPU.push_to_Ready_Queue(P_queue.front());
            P_queue.pop();
            return true;
        }
}


//Operators
string printer::create_P_name(int P_number){
        char int_to_char = (char)(P_number + 48);
        string char_to_str = &int_to_char;
        string name = "Printer " + char_to_str;
        return name;
}

ostream& operator<<(ostream& output, printer& printer_to_output){
        output<< printer_to_output.Get_P_name()<< endl;
        queue<PCB*> temp = printer_to_output.P_queue;
        int count = 0;
        while (!temp.empty()) {
            if (count == 0){
                cout << "\t\t\t\tPRINTERS SNAPSHOT TABLE:" <<endl;
                cout << "\t\t\t\tNow printing: PID["<<temp.front()->Get_PCB_id() << "]";
                cout << "\t\t File_Size["<<temp.front()->Get_PCB_file_size_to_print()<<"]";
                cout << "\t\t Operation["<<temp.front()->Get_PCB_disk_operation()<<"]"<<endl;
            }else{
                cout << "\t\t\t\tWAITING     : PID["<<temp.front()->Get_PCB_id() << "]";
                cout << "\t\t File_Size["<<temp.front()->Get_PCB_file_size_to_print()<<"]";
                cout << "\t\t Operation["<<temp.front()->Get_PCB_disk_operation()<<"]"<<endl;
            }
            count+=1;
            temp.pop();
        }
        return output;
}
