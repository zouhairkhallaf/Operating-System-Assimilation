#ifndef CPU_hpp
#define CPU_hpp

#include "PCB.hpp"
#include "printer.hpp"
#include "RAM.hpp"
#include "disk.hpp"

class printer;
class disk;
class RAM;

class CPU{
    
    public:
        //Getters:
        queue<PCB*> Get_ready_queue()const;
        bool terminate_process_execution(RAM& My_RAM, int& process_index_in_RAM);  //return memory index of terminated process for 't' calls
        //PCB* modify_Ready_Queue();//???
        //Setters:
        bool push_to_Ready_Queue(PCB* ready_process);
        friend ostream& operator << (ostream& out, CPU& CPU_to_output);
        bool Send_process_to_printer(int printer_number, int file_size, vector<printer>& my_printers);
        bool Send_process_to_disk(int disk_number, int file_size, vector<disk>& my_disks, string operation);

    
    private:
        queue<PCB*> Ready_Queue; //CPU READY QUEUE
        bool printers_pending();//To avoid orphans
        bool disks_pending();   //To avoid orphans
        void display_PCB(PCB* some_process);
    
};

#endif /* CPU_hpp */
