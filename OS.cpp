#include <iomanip>
#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include "PCB.hpp"
#include "disk.hpp"
#include "printer.hpp"
#include "RAM.hpp"
#include "CPU.hpp"

using namespace std;

void CPU_printer_request(int printer_number, vector<printer>& my_printers,CPU& CPU);
void CPU_disk_request(int disk_number, vector<disk>& my_disks, CPU& CPU);
void sys_gen(int& num_of_printers, int& num_of_disks, int& RAM_size);
void running(int RAM_size, int num_of_printers, int num_of_disks);
bool create_process(int prog_size, RAM& RAM, CPU& CPU);
string time_stamp();

int main() {
    
    int Printers=0, Disks=0, RAM=0;
    
    cout << "\t\t\t\t\t\t . WELCOME TO OUR OPERATING SYSYEM ASSIMILATION ." <<endl;
    cout << "SUMMURY OF INPUTS POSSIBLE" <<endl;
    cout << "\t A: Creates a process"<<endl;
    cout << "\t S: Snapshots of: "<<endl;
    cout << "\t\t r: ready queue"<<endl;
    cout << "\t\t p: printers"<<endl;
    cout << "\t\t d: disks"<<endl;
    cout << "\t\t m: RAM"<<endl;
    cout << "\t pX (ex: p1): CPU Requests printer X  " <<endl;
    cout << "\t PX (ex: P1): Printer X job termination" <<endl;
    cout << "\t dY (ex: d1): CPU Requests disk Y" <<endl;
    cout << "\t DY (ex: D1): Disk Y job termination" <<endl;
    cout << "\t t:terminates process in the CPU "<<endl;
    
    sys_gen(Printers, Disks, RAM);
    
    running(RAM, Printers, Disks);
    
    return 0;
}

void CPU_printer_request(int printer_number, vector<printer>& my_printers, CPU& CPU){
    int file_size_to_print;
    cout << "\t\t\t > The RUNNING process in CPU requesting \"" << my_printers[printer_number-1].Get_P_name() <<"\":"<<endl;
    
    bool non_integer_input;
    do{
        cout << "\t\t\t\t\t.Please enter the size of the file to print: ";
        cin >> file_size_to_print;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    

    if (CPU.Send_process_to_printer(printer_number, file_size_to_print, my_printers)){
        cout << "\t\t\t\t\t > PRINTER:: Pushed PCB to Printer \""<<printer_number << "\" Queue succesfully" <<endl<<endl;
    }else{
        cout << "\t\t\t\t\t > DISK:: FAILED TO PROCESS PRINTER" <<endl;
    }
}

void CPU_disk_request(int disk_number, vector<disk>& my_disks, CPU& CPU){
    bool non_integer_input;
    string operation;
    int file_size_to_disk;
    cout << "\t\t\t > The RUNNING process in CPU requesting \"" << my_disks[disk_number-1].Get_D_name() <<"\":"<<endl;
    do{
        cout << "\t\t\t\t   .Please enter the size of your file: ";
        cin >> file_size_to_disk;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    
    do{
        cout << "\t\t\t\t   .Please specify action { Reading ('r') or Writing ('w') }: ";
        cin >> operation;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    
    if (CPU.Send_process_to_disk(disk_number, file_size_to_disk, my_disks, operation)){
        cout << "\t\t\t\t\t > DISK:: Pushed PCB to Disk \""<<disk_number << "\" Queue succesfully" <<endl<<endl;
    }else{
        cout << "\t\t\t\t\t > DISK:: FAILED TO PROCESS DISK" <<endl;
    }
}

void sys_gen(int& num_of_printers, int& num_of_disks, int& RAM_size){
    bool non_integer_input;
    cout <<endl<<"SETTING UP THE SYSTEM"<<endl;

    //Printers;
    do{
        cout << "\t.How many printers you have\t: ";
        cin >> num_of_printers;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    
    //Disks
    do{
        cout <<"\t.How many disks you have\t: ";
        cin >> num_of_disks;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    
    //RAM
    do{
        cout << "\t.How much RAM you have\t\t: ";
        cin  >> RAM_size;
        non_integer_input = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while (non_integer_input == true);
    
    cout << endl;
}

void running(int RAM_size, int num_of_printers, int num_of_disks){
    //Declaring variables
    int prog_size;
    string interrupt;
    char sys_call;
    int count = 0;
    vector<printer> printers;
    vector<disk> disks;

    CPU CPU;                                //Creates CPU
    RAM RAM(RAM_size);                      //Creates RAM
    for (int i=1; i<=num_of_printers; i++){ //Creates Printers
        printer printer(i);
        printers.push_back(printer);
    }
    for (int i=1; i<=num_of_disks; i++){    //Creates Disks
        disk disk(i);
        disks.push_back(disk);
    }
    
    //Loop of the Runing System
    cout<< "SYSTEM RUNNING"<<endl;
    while (count<100) {//To control infinite loop.
        cout << "\t\t.Please enter an imput: ";
        cin  >> interrupt;
        if (interrupt == "A"){
            bool non_integer_input;
            do{
                cout << "\t\t\t.Enter the size of your new program 'A' : ";
                cin  >> prog_size;
                non_integer_input = cin.fail();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }while (non_integer_input == true);
            
            if (create_process(prog_size, RAM, CPU)){
                cout << "\t\t\t > Process Created succesfully" <<endl<<endl;
            }else{
                cout << "\t\t\t > Failed to create process" <<endl<<endl;
            }
        }else if(interrupt =="S"){
            
            do{
                cout << "\t\t\t.Please enter the second input {m,r,p,d}: ";
                cin  >> sys_call;
            }while ( sys_call!= 'm' && sys_call!= 'r' && sys_call!= 'p' && sys_call!= 'd');
            
            
            switch (sys_call) {
                case 'r':
                    cout << CPU;
                    break;
                case 'p':
                    cout << "\t\t\t\t+ Showing the PIDs of the processes in the PRINTER queues:" <<endl<<endl;
                    for (int i=0; i<printers.size(); i++) {
                        cout << "\t\t\t\t"<< printers[i] << endl;
                    }
                    break;
                case 'd':
                    cout << "\t\t\t\t+ Showing the PIDs of the processes in the DISK queues:" <<endl<<endl;
                    for (int i=0; i<disks.size(); i++) {
                        cout << "\t\t\t\t"<< disks[i] << endl;
                    }
                    break;
                case 'm':
                    cout << RAM;
                    break;
                default:
                    break;
            }
        }else if(interrupt[0]=='p'){
            int printer_number = (int)interrupt[1]-48;
            if ( printer_number > num_of_printers || printer_number <= 0) {
                cout << "\t\t\t * ERROR: Invalid printer number"<<endl<<endl;
            }else{
                CPU_printer_request(printer_number,printers, CPU);
            }
        }else if(interrupt[0]=='P'){
            int printer_number = (int)interrupt[1]-48;
            if ( printer_number > num_of_printers || printer_number <= 0) {
                cout << "\t\t\t * ERROR: Invalid printer number "<<endl<<endl;
            }else{
                if(printers[printer_number-1].terminate_job(CPU)){
                    cout << "\t\t\t > " << printers[printer_number-1].Get_P_name() << " Terminated JOB" <<endl<<endl;
                }else{
                    cout << "\t\t\t * ERROR: YOUR PRINTER QUEUE IS EMPTY, NO PROCESS TO TERMINATE IN PRINTER " << printer_number <<endl<<endl;
                }
                
            }
        }else if(interrupt[0]=='d'){  // Program in the CPU requesting DISK
            int disk_number = (int)interrupt[1]-48;
            if ( disk_number > num_of_disks || disk_number <= 0) {
                cout << "\t\t\t * ERROR: Invalid disk number "<<endl<<endl;
            }else{
                CPU_disk_request(disk_number,disks, CPU);
            }
        }else if(interrupt[0]=='D'){
            int disk_number = (int)interrupt[1]-48;
            if ( disk_number > num_of_disks || disk_number <= 0) {
                cout << "\t\t\t * ERROR: Invalid disk number "<<endl<<endl;
            }else{
                if(disks[disk_number-1].terminate_job(CPU)){
                    cout << "\t\t\t > " << disks[disk_number-1].Get_D_name() << " Terminated JOB" <<endl<<endl;
                }else{
                    cout << "\t\t\t * ERROR: YOUR DISK QUEUE IS EMPTY, NO PROCESS TO TERMINATE IN DISK " << disk_number <<endl<<endl;
                }
            }
        }else if(interrupt == "t"){
            int index_terminated;
            cout << "\t\t\t > Terminating the process currently in the CPU ..." <<endl;
            if (CPU.terminate_process_execution(RAM, index_terminated)){
                if(RAM.Delete_process(index_terminated))
                    cout << "\t\t\t > Process terminated succesfully" <<endl<<endl;
            }else{
                cout << "\t\t\t > ATTENTION: YOUR READY QUEUE IS EMPTY, NO RUNNING PROCESS TO TERMINATE" <<endl<<endl;
            }
        }else{
            cout << "\t\t\t.ERROR: Unrecognized FIRST input" <<endl<<endl; //last else
        }
        count++;
    }
}

bool create_process(int prog_size, RAM& RAM, CPU& CPU){
    if (RAM.Get_free_RAM() < prog_size) {
        cout << "\t\t\t\t > RAM:: ERROR, Attention your proram size is too big for your memory" <<endl;
        return false;
    }
    PCB* new_program = new PCB(prog_size);                  //Create object in heap
    new_program->Set_PCB_id(rand()%1000);                   //Set ID
    new_program->Set_PCB_state("READY");                    //Set state
    new_program->Set_PCB_creation_time(time_stamp());       //Set time
    return (RAM.put_in_RAM(new_program, CPU) && CPU.push_to_Ready_Queue(new_program));
}

string time_stamp(){
    time_t rawtime;
    time (&rawtime);
    string t = ctime(&rawtime);
    t = t.substr(10,9);
    return t;
}

