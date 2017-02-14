#ifndef RAM_hpp
#define RAM_hpp

#include "PCB.hpp"
#include "CPU.hpp"

    class CPU;

    class RAM {
        public:
        //Constructor
            RAM(int total_size);
        //Getters:
            void Calculate_RAM();
            int Get_total_RAM()const;
            int Get_free_RAM()const;
            int Get_used_RAM()const;
            vector<PCB*> Get_RAM_BLOCKS()const;
            //queue<PCB*>  Get_queue_to_execute()const;
            int Find_process_index(int process_ID);
            bool Delete_process(int index_terminated);
        //Setters:
            void Set_total_RAM(int m_space);
            void Set_free_RAM(int m_free_space);
            void Set_used_RAM(int used_m_space);
            bool put_in_RAM(PCB* new_process, CPU &my_CPU);
            //bool clean_RAM_queue();
            void Merge_Empty_Blocks(int index_of_terminated_object);
            friend ostream& operator << (ostream& out, RAM& RAM_to_output);
        
        private:
            //queue<PCB*> RAM_queue_to_execute; // RAM QUEUE
            int total_RAM;
            int free_RAM;
            int used_RAM;
            bool best_fit_allocation(PCB* new_process, CPU &my_CPU);
            vector<PCB*> RAM_BLOCKS; // To visualize "Best-Fit allocation" results
        //
            int find_where_to_insert_process(PCB* new_process);
    };


#endif /* RAM_hpp */
