#ifndef disk_hpp
#define disk_hpp

#include "PCB.hpp"
#include "CPU.hpp"


class CPU;
class disk {
    
     public:
     //Constructor
         disk(int d);
     //Getters:
         int Get_D_number()const;
         string Get_D_name()const;
         //queue<PCB> Get_D_queue()const;
     //Setters:
         void Set_D_number (int number);
         void Set_D_name(string name);
         void Push_to_D_queue(PCB* PCB_object);
         friend ostream& operator<<(ostream& output, disk& disk_to_output);
         bool terminate_job(CPU& my_CPU);
    
     private:
         queue<PCB*> D_queue; // DISK QUEUE
         int D_number;
         string D_name;
         string create_disk_name(int n);
         //string time_stamp();
};

#endif /* disk_hpp */
