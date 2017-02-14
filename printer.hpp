#ifndef printer_hpp
#define printer_hpp
#include "PCB.hpp"

#include "CPU.hpp"/// *****
class CPU;

class printer {
       public :
       //Constructor
            printer(int n);
       //Getters:
            int Get_P_number()const;
            string Get_P_name()const;
            //queue<PCB> Get_P_queue()const;
       //Setters:
            void Set_P_number(int number);
            void Set_P_name(string name);
            void Push_to_P_queue(PCB* PCB_object);
            friend ostream& operator<<(ostream& output, printer& printer_to_output);
            bool terminate_job(CPU& My_CPU);
    
      private:
            queue<PCB*> P_queue; // PRINTER QUEUE
            int P_number;
            string P_name;
            string create_P_name(int printer_number);
            string time_stamp();
};

#endif /* printer_hpp */
