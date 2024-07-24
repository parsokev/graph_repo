#pragma once
#include <iostream>
#include <experimental/random>

// class rand_graph {
//     public:
//         rand_graph(): size(2) { create_graph(); fill_graph();}
//         rand_graph(int i): size(i) { create_graph(); fill_graph(); }
//         ~rand_graph() {release();}
//         void create_graph() {
//             srand(time(0));
//             graph = new bool *[size];
            
//             for (int i = 0; i < size; i++) {
//                 graph[i] = new bool[size];
//             }
//         }

//         void fill_graph() {
//             for (int i = 0; i < size; i++) {
//                 for (int j = 0; j < size; j++) {
//                     if (i== j) {
//                         graph[i][j] = false;
//                     } else {
//                         graph[i][j] = graph[j][i] = std::experimental::randint(0, 1);
//                     }
                    
//                 }
//             }
//         }

//         bool is_connected (bool *graph[], int size) {
//             int old_size = 0;
//             int c_size = 0;
//             bool is_connected;
//             bool *close = new bool[size];
//             bool *open = new bool[size];
//             for (int i = 0; i < size; i++) {
//                 open[i] = close[i] = false;
//             }
//             open[0] = true;
//             while (c_size < size){
//                 for (int i = 0; i < size; i++) {
//                     old_size = c_size;
//                     if(open[i] && (close[i] == false)) {
//                         close[i] = true;
//                         c_size++;
//                     }
//                     for (int j = 0; j < size; j++) {
//                         // logical OR 
//                         open[j] = open[j] || graph[i][j];
//                     } 
//                 }
//                 if (c_size == size) {
//                     is_connected = true;
//                     break;
//                 }
//                 if (old_size == c_size) {
//                     is_connected = false;
//                     break;
//                 }

//             }
//             delete[] close;
//             delete[] open; 
//             return is_connected;

//         }

//         bool **get_graph() {
//             return graph;
//         }

//         void release() {
//             for (int i = 0; i < size; i++) {
//                 delete[] graph[i];
//             }
//             delete[] graph;
//         }

//         friend std::ostream& operator<<(std::ostream& out, const rand_graph& g) {
//             for (int i = 0; i < g.size; i++) {
//                 for (int j = 0; j < g.size; j++) {
//                     out << g.graph[i][j] << '\t';
//                 }
//                 out << '\n';
//             }
//             return out;
//         }
//         int get_size() {
//             return size;
//         }

//         void set_size(int i) {
//             size = i;
//         }

//     private:
        
//         bool **graph;
//         int size;
// };

// class point {
//     public:
//         // getter functions
//         double getx() {return x;}
//         double gety() {return y;}
//         // setter functions
//         void setx(double v) { x = v;}
//         void sety(double w) { y = w;}
//         // Member function for overloading binary + operator has access to private attributes
//         friend const point operator+(const point& p1, const point&p2) {
//             const point sum = point(p1.x + p2.x, p1.y + p2.y);
//             return sum;
//         }
//         // Member function for overloading left bitshift operator for cout has access to private attributes
//         friend std::ostream& operator<<(std::ostream& out, const point& p) {
//             out << "( " << p.x << ", " << p.y << " )";
//             return out;
//         }
//         // if new point object is initialized with arguments set appropriate attribute values
//         point(double x, double y) : x(x), y(y) {}
//         // If a  
//         point(double z) : x(z), y(z) {}
//         // If new point object is passed without arguments, set all attribute values to 0
//         // point() {this->x = 0.0, this -> y =0.0;}
//         point(): x(0.0), y(0.0) {}
//     private:
//         double x, y;
// };