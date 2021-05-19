#include "rb_tree-inl.h"

void test_parse()
{
    std::vector<int> res1 = parse_input("1: 2 (1) 3 (2) ; 2: 3 (23) ; 3:");
    assert(res1[0] == 1);
    assert(res1[1] == 2);
    assert(res1[2] == 23);

    std::vector<int> res2 = parse_input("1: 2 (2142) 3 (12) ; 2: 3 (-123) ; 3:");

    assert(res2[0] == 2142);
    assert(res2[1] == 12);
    assert(res2[2] == -123);
}

void test_insert_delete()
{
    std::ofstream file_insert("data_insert.dat");
    std::ofstream file_delete("data_delete.dat");

    for (int step = 1000; step < 500000; step += 1000)
    {
        rb_tree<int> tree1;
        std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
        for (int i = 0; i < step; ++i)
        {
            tree1.insert_node(i * 5);
        }
        std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
        file_insert << step << '\t' << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << '\n';

        std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
        for (int i = 0; i < step; ++i)
        {
            node<int>* node = tree1.find_node(i * 5);
            tree1.delete_node(node);
        }
        std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
        file_delete << step << '\t' << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << '\n';
    }
}