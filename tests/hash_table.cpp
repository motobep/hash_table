#include <gtest/gtest.h>
#include <string>
#include "../src/HashTable.h"

using namespace std;

TEST(Hashtable, set_get)
{
    HashTable<string, string> table = HashTable<string, string>(10);
    string str = "new";

    table.set("first", str);
    EXPECT_EQ(table.get("first"), "new");

    table.set("second", "sec");
    EXPECT_EQ(table.get("second"), "sec");

    table.set("third", "three");
    EXPECT_EQ(table.get("third"), "three");

    table.set("fourth", "four");
    EXPECT_EQ(table.get("fourth"), "four");

    table.set("fifth", "five");
    EXPECT_EQ(table.get("fifth"), "five");

    table.set("6th", "6");
    EXPECT_EQ(table.get("6th"), "6");

    table.set("7th", "7");
    EXPECT_EQ(table.get("7th"), "7");

    table.set("8th", "8");
    EXPECT_EQ(table.get("8th"), "8");

    table.set("9th", "9");
    EXPECT_EQ(table.get("9th"), "9");

    table.set("10th", "10");
    EXPECT_EQ(table.get("10th"), "10");
}

TEST(Hashtable, int_type)
{
    HashTable<string, int> table = HashTable<string, int>(10);

    table.set("first", 1);
    EXPECT_EQ(table.get("first"), 1);

    table.set("second", 5);
    EXPECT_EQ(table.get("second"), 5);
}

TEST(Hashtable, collisions)
{
    HashTable<string, string> table = HashTable<string, string>(10);
    int a = table.get_index("third");
    int b = table.get_index("fifth");
    int c = table.get_index("10th");
    EXPECT_EQ(a, b);
    EXPECT_EQ(b, c);
}

TEST(Hashtable, length_cpacity)
{
    HashTable<string, string> table = HashTable<string, string>(2);
    table.set("first", "one");
    EXPECT_EQ(table.length(), 1);
    EXPECT_EQ(table.capacity(), 2);
    table.set("second", "sec");
    EXPECT_EQ(table.length(), 2);
    EXPECT_EQ(table.capacity(), 2);
    table.set("third", "three");
    EXPECT_EQ(table.length(), 3);
    EXPECT_EQ(table.capacity(), 4);
    table.set("fourth", "4");
    table.set("5th", "5");
    EXPECT_EQ(table.length(), 5);
    EXPECT_EQ(table.capacity(), 8);
}

TEST(Hashtable, non_existing_index)
{
    HashTable<string, string> table = HashTable<string, string>();
    EXPECT_THROW({
        try
        {
            table.get("not_a_key");
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ("Key doesn't exist", e.what() );
            throw;
        }
    }, std::invalid_argument );
}

TEST(Hashtable, large_table)
{
    const size_t cap = 2000000;
    HashTable<string, string> table = HashTable<string, string>(cap);
    EXPECT_EQ(table.length(), 0);
    EXPECT_EQ(table.capacity(), cap);
}

TEST(Hashtable, default_capacity)
{
    const size_t cap = 100;
    HashTable<string, string> table = HashTable<string, string>();
    EXPECT_EQ(table.length(), 0);
    EXPECT_EQ(table.capacity(), cap);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

