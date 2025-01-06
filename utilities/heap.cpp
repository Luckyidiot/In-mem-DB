#include <vector>
#include <iostream>

class Heap {
    private:
        std::vector<int> heap_arr;
        
        int right(int root){
            return 2*root + 1;
        }
        int left(int root){
            return 2*root;
        }
        int mother(int root){
            return root/2;
        }
        int index_mapping(int index){
            return index - 1;    
        }
    public:
        Heap(std::vector<int> arr){
            heap_arr = arr;
        }
        
        void showHeap(){
            for (int i = 0; i < heap_arr.size(); i++){
                std::cout << heap_arr[i] << " ";
            }
            std::cout << std::endl;
        }
        
        void max_heapify(int root){ // Heap is labeled starting from 1, not 0
            int l = left(root);
            int r = right(root);
            int max_index = root;
            if (l < heap_arr.size() && heap_arr[index_mapping(l)] > heap_arr[index_mapping(root)]){
                max_index = l;
            }
            if (r < heap_arr.size() && heap_arr[index_mapping(r)] > heap_arr[index_mapping(max_index)]){
                max_index = r;
            }
            
            if (max_index != root){
                int buffer = heap_arr[index_mapping(root)];
                heap_arr[index_mapping(root)] = heap_arr[index_mapping(max_index)];
                heap_arr[index_mapping(max_index)] = buffer;
                
                max_heapify(max_index);
            }
        }
        
        
    
};


int main(){
    Heap heap({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});
    heap.showHeap();
    heap.max_heapify(2);
    heap.showHeap();
    
    return 0;
}




