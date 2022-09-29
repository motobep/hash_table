#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>
#include <vector>
#include <stdexcept>

#include "Hash.h"

// #define IS_DEBUG
#ifdef IS_DEBUG
#define DEBUG(s, v) { cout << s << " " << v << endl; }
#else
#define DEBUG(s, v)
#endif


using std::cout;
using std::endl;
using std::vector;

template<typename K, typename  V>
class HashTable {
    private:
        Hash hash;
        struct Node {
            K key;
            V value;
            Node* next;
        };
        vector<Node*> vec;
        size_t table_length = 0;
        size_t table_capacity = 0;
    public:
        HashTable(size_t size = 100)
        {
            table_capacity = size;
            hash.set_range(size);
            vec.resize(size);
        }

        size_t length() {
            return table_length;
        }

        size_t capacity() {
            return table_capacity;
        }

        void set(K key, V object)
        {
            ++table_length;
            if (table_length == vec.size() + 1) {
                resize_table();
            }

            Node* node = create_node(key, object);
            unsigned int idx = hash(key);
            DEBUG("index:", idx);

            if (exists(idx)) {
                Node* prev_node = vec[idx];
                
                while (prev_node->next != nullptr) {
                    prev_node = prev_node->next;
                }
                prev_node->next = node;
            } else {
                vec[idx] = node;
            }
        }

        V get(K key)
        {
            unsigned int idx = hash(key);
            Node* node = vec[idx];

            while (node != nullptr) {
                if (node->key == key) {
                    return node->value;
                }
                node = node->next;
            }
            throw std::invalid_argument("Key doesn't exist"); 
        }

        unsigned int get_index(K s)
        {
            return hash(s);
        }

        bool exists(unsigned int idx)
        {
            Node* node = vec[idx];
            return node != nullptr;
        }

        void show_vector() {
            for (auto& v : vec) {
                cout << "vec: " << v << endl;
            }
        }

    private:
        void resize_table()
        {
            // Update sizes
            table_capacity = vec.size() * 2;
            vector<Node*> new_vec(table_capacity);

            // Update hash function
            hash.set_range(table_capacity);

            // Go through every node with index
            for (unsigned int i = 0; i < vec.size(); i++) {
                Node* node_source = vec[i];

                // Go through every node within chain of nodes
                while (node_source != nullptr) {
                    K key = node_source->key;
                    unsigned int idx = hash(key);
                    Node* next_node = node_source->next;
                    DEBUG("New index:", idx);

                    if (exists_in(idx, new_vec)) {
                        Node* prev_node = new_vec[idx];

                        while (prev_node->next != nullptr) {
                            prev_node = prev_node->next;
                        }
                        prev_node->next = node_source;
                    } else {
                        // Save pointer to proceed from it on next iteration
                        next_node = node_source->next;

                        // Remove reference because it is new table with new hash function
                        node_source->next = nullptr;
                        new_vec[idx] = node_source;
                    }

                    node_source = next_node;
                }
            }

            // Update previous vector
            vec = new_vec;
        }

        bool exists_in(unsigned int idx, vector<Node*> &v)
        {
            Node* node = v[idx];
            return node != nullptr;
        }

        Node* create_node(K key, V object)
        {
            Node* node = new Node;
            node->key = key;
            node->value = object;
            node->next = nullptr;
            return node;
        }
};

#endif

