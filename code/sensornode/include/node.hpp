#pragma once

#include <thread>  
#include <iostream>
#include <vector>
#include <bitset>     
#include <mutex>
#include <unistd.h>
#include <bitset> 

#define MILLI_SECOND 1000

class Protocol;

enum states { stopped, clear, time_packing, get_data, send_data };

struct packed_data {
  std::bitset<1> sof;
  std::bitset<4> node_id;
  std::bitset<4> n_data_bytes;
  std::bitset<6> messagetype;
  std::vector<bool> data;
  void print_bool_packet(void){
    std::cout << sof;
    std::cout <<node_id;
    std::cout<<n_data_bytes;
    std::cout<<messagetype;
    print_vector_bool(this->data);
  }
  void print_vector_bool(std::vector<bool> vector){
    for (auto i : vector) {
      std::cout << i;
    }
  }
  void print_sof(void){
    std::cout<< "Start of frame: ";
    std::cout << sof << '\n';
  }
  void print_node_id(void){
    std::cout<< "Node id: ";
    std::cout<< node_id;
    std::cout << '\n';
  }
  void print_n_data_bytes(void){
    std::cout<< "Number of data bytes: ";
    std::cout<<n_data_bytes << '\n';
  }
  void print_messagetype(void){
    std::cout<< "Messagetype: ";
    std::cout<<messagetype << '\n';
    std::cout << '\n';
  }
  void print_data(void){
    std::cout<< "Data: ";
    print_vector_bool(this->data);
    std::cout << '\n';
  }
  void print(void){
    print_sof();
    print_node_id();
    print_n_data_bytes();
    print_messagetype();
    print_data();
  }
};



class Node {
private:
  long int ms;
  std::mutex ms_mutex;
  bool running;
  states state;
  Protocol* protocol;
  std::bitset<4> node_id;
  std::thread loop_out_thread;
  std::thread loop_in_thread;
  
  std::thread counter_thread;
  std::vector<packed_data> data_out;
  std::mutex data_out_mutex;
  std::vector<int> event_buffer;
  std::mutex event_buffer_mutex;

  void print_vector_bool(std::vector<bool> vector);
  packed_data get_data_from_buffer(void);
  int data_in_buffer_test(void);
  void counter(void);
  packed_data construct_time_packet(long int ms);
  std::vector<bool> bitset32_to_vector(std::bitset<32> bitset);
  int get_from_event_buffer(void);
  int evnt_in_event_buffer_test(void);
  void set_ms(long int ms_in);
  long int get_ms(void);
public:
 Node(void);
 Node(int id);
 void start(void);
 void loop_out(void);
 void loop_in(void);
 void put_data_packet(struct packed_data);
 void set_protocol(Protocol* protocol_in);
 void put_event(int);
};