#ifndef PCB_hpp
#define PCB_hpp
#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <queue>


using namespace std;

class PCB {
    public:
    //Constructor
        PCB();
        PCB(int size);
    //Getters:
        int Get_PCB_id()const;
        int Get_PCB_size()const;
        int Get_PCB_memory_index()const;
        int Get_PCB_memory_start()const;
        int Get_PCB_memory_end()const;
        string Get_PCB_creation_time()const;
        string Get_PCB_state()const;
        int Get_PCB_printer_number()const;
        int Get_PCB_disk_number()const;
        int Get_PCB_file_size_to_print()const;
        int Get_PCB_file_size_to_disk()const;
        string Get_PCB_disk_operation()const;
    
    //Setters:
        void Set_PCB_id(int ID);
        void Set_PCB_size(int SIZE);
        void Set_PCB_memory_index(int new_index);
        void Set_PCB_memory_start(int new_start);
        void Set_PCB_memory_end(int new_end);
        void Set_PCB_state(string new_state);
        void Set_PCB_creation_time(string TIME);
        void Set_PCB_printer_number(int printer_number);
        void Set_PCB_disk_number(int disk_number);
        void Set_PCB_file_size_to_print(int file_size);
        void Set_PCB_file_size_to_disk(int file_size);
        void Set_PCB_disk_operation(string operation);
    
        friend ostream& operator<<(ostream& output, PCB& PCB_to_output);
    
    private :
        int PCB_id;
        int PCB_size;
        int PCB_memory_index;
        int PCB_memory_start;
        int PCB_memory_end;
        string PCB_state;
        string PCB_creation_time;
        int PCB_printer_number;
        int PCB_disk_number;
        int file_size_to_print;
        int file_size_to_disk;
        string PCB_disk_operation;
};
#endif /* PCB_hpp */
